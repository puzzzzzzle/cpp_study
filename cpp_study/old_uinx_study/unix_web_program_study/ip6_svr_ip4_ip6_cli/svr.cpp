//
// Created by tao on 19-1-18.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>

#include "log_macro.h"
#include "svr.h"

#define TCP_QUEUE 64
#define MAX_POLL_SIZE 4096
//#define USE_SELECT
#define USE_POLL

const char *echo = "echo:";

bool is_run = true;

int start_svr_v6(const char *host, int port) {
    //init bind
    sockaddr_in6 svraddr{};
    int svr_fd;

    //socket
    if ((svr_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
        FATAL("init socket err" << strerror(errno))
        exit(-2);
    }

    //address
    svraddr.sin6_family = AF_INET6;
    if (inet_pton(AF_INET6, host, &svraddr.sin6_addr.__in6_u) != 1) {
        FATAL("translate host err" << strerror(errno))
        exit(-2);
    }
    svraddr.sin6_port = htons(port);

    //bind
    if (bind(svr_fd, (sockaddr *) &svraddr, sizeof(svraddr))) {
        FATAL("bind err" << strerror(errno))
        exit(-2);
    }

    //listen
    if (listen(svr_fd, TCP_QUEUE)) {
        FATAL("listen err" << strerror(errno))
        exit(-2);
    }

    //service
#ifdef USE_SELECT
    //use select
    if (select_svr(svr_fd)) {
        FATAL("select_svr start err" << strerror(errno))
        exit(-2);
    }
#else
    //use poll
    if (poll_svr(svr_fd)) {
        FATAL("poll_svr start err" << strerror(errno))
        exit(-2);
    }
#endif


    return 0;
}

int select_svr(int svr_fd) {
    //variables
    sockaddr_in6 client_addr{};
    socklen_t client_addr_len = sizeof(client_addr);

    fd_set curr_set{}, all_set{};
    int client_fd = 0, ready_number = 0;
    ssize_t read_len = -1, write_len = -1, real_write_len = -1;
    int i = 0, max_client_i = -1, max_fd = -1;
    int client_fds[FD_SETSIZE];
    //buff
    char read_buff[MAX_LINE_LEN], write_buff[MAX_LINE_LEN], svr_buff[MAX_LINE_LEN], svr_buff1[MAX_LINE_LEN];

    //init varables
    FD_ZERO(&curr_set);
    FD_ZERO(&all_set);
    FD_SET(svr_fd, &all_set);
    for (int &fd:client_fds) {
        fd = -1;
    }
    max_fd = svr_fd;
    while (is_run) {

//        LOG4CPLUS_DEBUG(file, "000");
        DEBUG("start a new run :" << is_run);
        curr_set = all_set;
        ready_number = select(max_fd + 1, &curr_set, nullptr, nullptr, nullptr);

        //new conn comes
        do {
            if (FD_ISSET(svr_fd, &curr_set)) {
                client_fd = accept(svr_fd, (sockaddr *) &client_addr, &client_addr_len);
                if (client_fd < 0) {
                    ERROR("something wrong happeneds when accept" << strerror(errno))
                    break;
                }
                for (i = 0; i < FD_SETSIZE; i++) {
                    if (client_fds[i] < 0) {
                        client_fds[i] = client_fd;
                        i++;
                        break;
                    }
                }
                snprintf(svr_buff, sizeof(svr_buff), "%s:%d",
                         inet_ntop(AF_INET6, &client_addr.sin6_addr.__in6_u, svr_buff1,
                                   sizeof(svr_buff1)), ntohs(client_addr.sin6_port));

                if (i >= FD_SETSIZE) {
                    ERROR("too many conns, throw this :" << svr_buff)
                    break;
                }

                INFO("conn from " << svr_buff)

                FD_SET(client_fd, &all_set);

                if (i > max_client_i) {
                    max_client_i = i;
                }
                if (client_fd > max_fd) {
                    max_fd = client_fd;
                }


            }
        } while (false);

        if (FD_ISSET(svr_fd, &curr_set) && (--ready_number <= 0)) {
            continue;
        }
        //old conn happens something
        for (i = 0; i < max_client_i; i++) {
            DEBUG("progress old :" << is_run);
            if ((client_fd = client_fds[i]) <= 0) {
                continue;
            }
            if (FD_ISSET(client_fd, &curr_set)) {
                if ((read_len = recv(client_fd, read_buff, sizeof(read_buff), 0)) < 0) {
                    if (errno == EINTR) {
                        //interrupt by sys break
                        DEBUG("EINTR happends")
                    } else {
                        ERROR("something wrong happends when read : " << ":\t" << strerror(errno))
                        if (close(client_fd)) {
                            ERROR("something wrong happends when close : " << ":\t" << strerror(errno))
                        }
                        client_fds[i] = -1;
                        FD_CLR(client_fd, &all_set);
                    }
                } else if (read_len == 0) {
                    if (close(client_fd)) {
                        ERROR("something wrong happends when close : " << ":\t" << strerror(errno))
                    }
                    client_fds[i] = -1;
                    FD_CLR(client_fd, &all_set);
                } else {
                    write_len = do_response(read_buff, read_len, write_buff, sizeof(write_buff));
                    if ((real_write_len = (send(client_fd, write_buff, write_len, 0))) != write_len) {
                        ERROR("need to send " << write_len << " real send " << real_write_len)
                    }
                }
                if (--ready_number <= 0) {
                    continue;
                }
            }
        }
    }
    return 0;
}

int poll_svr(int svr_fd) {
    //variables
    int client_fd;
    sockaddr_in6 client_addr{};
    socklen_t client_addr_len = sizeof(client_addr);
    pollfd all_conns[MAX_POLL_SIZE];
    int i = 0, max_i = 0, ready_n, read_len, write_len, real_write_len;
    //buff
    char read_buff[MAX_LINE_LEN], write_buff[MAX_LINE_LEN], svr_buff[MAX_LINE_LEN], svr_buff1[MAX_LINE_LEN];

    for (pollfd &fd:all_conns) {
        fd.fd = -1;
    }
    all_conns[0].fd = svr_fd;
    all_conns[0].events = POLLRDNORM;
    max_i = 0;


    while (is_run) {
        DEBUG("start a new run :" << is_run);
        ready_n = poll(all_conns, max_i + 1, -1);
        //new conn comes
        do {
            if (all_conns[0].revents & POLLRDNORM) {
                client_fd = accept(svr_fd, (sockaddr *) &client_addr, &client_addr_len);
                if (client_fd <= 0) {
                    ERROR("something wrong happeneds when accept" << strerror(errno))
                    break;
                }
                for (i = 0; i < FD_SETSIZE; i++) {
                    if (all_conns[i].fd < 0) {
                        all_conns[i].fd = client_fd;
                        all_conns[i].events = POLLRDNORM;
                        i++;
                        break;
                    }
                }
                snprintf(svr_buff, sizeof(svr_buff), "%s:%d",
                         inet_ntop(AF_INET6, &client_addr.sin6_addr.__in6_u, svr_buff1,
                                   sizeof(svr_buff1)), ntohs(client_addr.sin6_port));

                if (i >= FD_SETSIZE) {
                    ERROR("too many conns, throw this :" << svr_buff)
                    break;
                }
                INFO("conn from " << svr_buff)

                if (i > max_i) {
                    max_i = i;
                }
            }
        } while (false);

        if ((all_conns[0].revents & POLLRDNORM) && (--ready_n <= 0)) {
            continue;
        }


        //produce result
        for (i = 0; i < max_i; i++) {
            DEBUG("progress old :" << is_run);

            if (all_conns[i].fd <= 0) {
                continue;
            }
            if (all_conns[i].revents & (POLLRDNORM | POLLERR)) {
                if ((read_len = recv(all_conns[i].fd, read_buff, sizeof(read_buff), 0)) < 0) {
                    if (errno == EINTR) {
                        //sys interrupt
                        //do nothing
                    } else {
                        close(all_conns[i].fd);
                        all_conns[i].fd = -1;
                        ERROR("read err")
                    }
                } else if (read_len == 0) {
                    close(all_conns[i].fd);
                    all_conns[i].fd = -1;
                } else {
                    write_len = do_response(read_buff, read_len, write_buff, sizeof(write_buff));
                    if ((real_write_len = (send(client_fd, write_buff, write_len, 0))) != write_len) {
                        ERROR("need to send " << write_len << " real send " << real_write_len)
                    }

                }
                if (--ready_n <= 0) {
                    continue;
                }
            }

        }

    }
    return 0;
}

size_t do_response(char *read_buff, ssize_t read_len,
                   char *write_buff, ssize_t write_len) {
    strncpy(write_buff, echo, strlen(echo));
    strncpy(write_buff + strlen(echo), read_buff, write_len - strlen(echo));
    return strlen(echo) + read_len;
}