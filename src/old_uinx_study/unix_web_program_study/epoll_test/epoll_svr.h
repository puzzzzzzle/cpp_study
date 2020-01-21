//
// Created by 23591 on 2019/1/24.
//

#ifndef UNIXSTUDY_EPOLL_SVR_H
#define UNIXSTUDY_EPOLL_SVR_H

#include <netinet/in.h>

#define MAX_LINE_LEN 1024
#define MAX_TCP_QUEUE 64

int start_epoll_svr(const char *host, int port);

int do_epoll_svr_lt(int svr_fd);

size_t do_response(char *read_buff, ssize_t read_len, char *write_buff, ssize_t write_len);

ssize_t do_requestv4(const char *msg, ssize_t len, char *receive_buff, size_t buff_len, const char *addr, int port);

#endif  // UNIXSTUDY_EPOLL_SVR_H
