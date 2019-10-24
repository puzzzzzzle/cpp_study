//
// Created by 23591 on 2019/1/24.
//

#include <arpa/inet.h>
#include <cstdlib>
#include <sys/epoll.h>
#include <fcntl.h>
#include "boost_log_init.h"
#include "epoll_svr.h"


#define EVENT_BUFF_SIZE 256
bool is_run = true;

const char *echo = "echo:";

int setnonblocking(int sock)//将套接字设置为非阻塞
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
        ERROR("fcntl(sock,GETFL):" << strerror(errno));
        return -1;
    }
    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
        ERROR("fcntl(sock,SETFL,opts):" << strerror(errno));
        return -1;
    }
    return 0;
}

int start_epoll_svr(const char *host, int port) {
    int svr_fd;
    sockaddr_in svr_addr{};

    //socket
    if ((svr_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        FATAL("err when get socket")
        exit(-2);
    }

    //init
    svr_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, host, &svr_addr.sin_addr.s_addr) != 1) {
        FATAL("err when inet_pton")
        exit(-2);
    }
    svr_addr.sin_port = htons(port);

    //bind
    if (bind(svr_fd, (sockaddr *) &svr_addr, sizeof(svr_addr))) {
        FATAL("err when bind")
        exit(-2);
    }

    //listen
    if (listen(svr_fd, MAX_TCP_QUEUE)) {
        FATAL("err when listen")
        exit(-2);
    }

    do_epoll_svr_lt(svr_fd);

    return 0;
}

int do_epoll_svr_lt(int svr_fd) {
    size_t read_len, wait_number;
    int epoll_fd;
    epoll_event svr_event{}, buff_event[EVENT_BUFF_SIZE]{};

    epoll_fd = epoll_create(1024);

    svr_event.events = EPOLLIN;
    svr_event.data.fd = svr_fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, svr_fd, &svr_event);

    while (is_run) {
        wait_number = epoll_wait(epoll_fd, buff_event, EVENT_BUFF_SIZE, -1);
    }
}

ssize_t do_requestv4(const char *msg, ssize_t len,
                     char *receive_buff, size_t buff_len,
                     const char *addr, int port) {
    //init addr
    int client_fd;
    sockaddr_in svr_addr{};
    ssize_t send_len;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
        FATAL("svr socket get err fd : " << client_fd)
        exit(-1);
    }

    svr_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, addr, &svr_addr.sin_addr.s_addr) != 1) {
        FATAL("translate ip address err!")
        exit(-2);
    }
    svr_addr.sin_port = htons(port);

    if (connect(client_fd, (sockaddr *) &svr_addr, sizeof(svr_addr))) {
        FATAL("connect err! : " << strerror(errno))
        exit(-2);
    }
    if ((send_len = send(client_fd, msg, len, 0)) != len) {
        ERROR("need to send : " << len << " real send : " << send_len)
    }

    shutdown(client_fd, SHUT_WR);
    return recv(client_fd, receive_buff, buff_len, 0);
}

size_t do_response(char *read_buff, ssize_t read_len,
                   char *write_buff, ssize_t write_len) {
    strncpy(write_buff, echo, strlen(echo));
    strncpy(write_buff + strlen(echo), read_buff, write_len - strlen(echo));
    return strlen(echo) + read_len;
}