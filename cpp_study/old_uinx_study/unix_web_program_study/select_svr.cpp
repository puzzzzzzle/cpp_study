//
// Created by tao on 19-1-16.
//

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <boost/concept_check.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_LINE_LENGTH 1024
#define SVR_BUFF 1024
#define SVR_DEQUE 256
const char *SVR_ADDRESS = "127.0.0.1";
const int   PORT        = 8951;

// record all resources that needs to be released when the sys exited;
typedef struct resource_handle {
    int svr_fd;
} r_handle;
static r_handle handle{-1};

void when_exit() {
    printf("start exit: clear the log \n");
    if (handle.svr_fd > 0) {
        if (close(handle.svr_fd)) {
            perror("close the svr file err ");
        }
    }
}

void progress_one_request(int fd, const char *__restrict read_buff, size_t read_len, char *write_buff, size_t write_buff_len) {
    int append_len = 5;
    strncpy(write_buff, "echo:", write_buff_len);
    int write_buff_len_rest = write_buff_len - append_len;
    memcpy(write_buff + append_len, read_buff, read_len < write_buff_len_rest ? read_len : write_buff_len_rest);
    send(fd, write_buff, (read_len + append_len) < write_buff_len ? (read_len + append_len) : write_buff_len, 0);
}

int main(int argc, char **argv) {
    printf("select svr start to start!\n");

    atexit(when_exit);

    // define init variables
    fd_set      r_set;
    fd_set      all_set;
    char        svr_buff[SVR_BUFF];
    int         svr_fd, max_fd;
    int         client_fds[FD_SETSIZE];
    sockaddr_in svr_address{};

    // init listen

    // init address
    svr_address.sin_family = AF_INET;
    if (inet_pton(AF_INET, SVR_ADDRESS, &svr_address.sin_addr.s_addr) != 1) {
        perror("init address wrong");
        exit(0);
    }
    svr_address.sin_port = htons(PORT);
    printf("svr will start at : %s:%d\n", inet_ntop(AF_INET, &svr_address.sin_addr.s_addr, svr_buff, sizeof(svr_buff)), ntohs(svr_address.sin_port));

    // to bind and listen
    if ((svr_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
        perror("init svr socket err");
        exit(0);
    }
    // recode fd to handle
    handle.svr_fd = svr_fd;

    if (bind(svr_fd, (sockaddr *)&svr_address, sizeof(svr_address))) {
        perror("bind err");
        exit(0);
    }
    if (listen(svr_fd, SVR_DEQUE)) {
        perror("listen err");
        exit(0);
    }

    // init select
    max_fd = svr_fd;
    for (int &client_fd : client_fds) {
        client_fd = -1;
    }
    FD_ZERO(&r_set);
    FD_ZERO(&all_set);
    FD_SET(svr_fd, &all_set);

    ////////////////////////////loop/////////////////
    // before select loop, init variables that the loop needs
    char        read_buff[MAX_LINE_LENGTH], write_buff[MAX_LINE_LENGTH];
    int         ready_number = -1, client_fd = -1, i = 0, max_i = 0, read_len = 0;
    sockaddr_in client_address{};
    socklen_t   client_address_len;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        /***********
        注意：
         先复制set的状态，然后调用select
         这样在下一次select通过时
         r_set代表有事件发生的
         all_set代表为所有已连接的
         每一次select之后，没有事件发生的位将会被清空，不复制会导致一次select后清空没有事件发生的位
        ******************/
        r_set        = all_set;
        ready_number = select(max_fd + 1, &r_set, nullptr, nullptr, nullptr);

        // to progress new conn
        if (FD_ISSET(svr_fd, &r_set)) {
            client_fd = accept(svr_fd, (sockaddr *)&client_address, &client_address_len);
            // find a place to save client fd
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client_fds[i] < 0) {
                    client_fds[i] = client_fd;
                    i++;
                    break;
                }
            }
            if (i >= FD_SETSIZE) {
                fprintf(stderr, "too many clients");
            }
            FD_SET(client_fd, &all_set);
            if (client_fd > max_fd) {
                max_fd = client_fd;
            }
            if (i > max_i) {
                max_i = i;
            }
            printf("conn from %s:%d\n", inet_ntop(AF_INET, &client_address, svr_buff, sizeof(svr_buff)), ntohs(client_address.sin_port));
            // unnecessary to avoid unused loop
            if (--ready_number <= 0) {
                continue;
            }
        }
        // to progress client request
        for (i = 0; i < max_i; i++) {
            if ((client_fd = client_fds[i]) < 0) {
                continue;
            }
            if (FD_ISSET(client_fd, &r_set)) {
                // conn finished
                if ((read_len = recv(client_fd, read_buff, sizeof(read_buff), 0)) <= 0) {
                    if (close(client_fd)) {
                        fprintf(stderr, "close fd[%d] err,the reason maybe :{%s}", client_fd, strerror(errno));
                    }
                    FD_CLR(client_fd, &all_set);
                    client_fds[i] = -1;
                } else {
                    progress_one_request(client_fd, read_buff, read_len, write_buff, sizeof(write_buff));
                }
                if (--ready_number <= 0) {
                    break;
                }
            }
        }
    }
#pragma clang diagnostic pop
    return 0;
}