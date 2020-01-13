//
// Created by tao on 19-1-18.
//

#ifndef UNIXSTUDY_SVR_H
#define UNIXSTUDY_SVR_H

#include <netinet/in.h>

#define MAX_LINE_LEN 1024

int start_svr_v6(const char *host, int port);

int select_svr(int svr_fd);

int poll_svr(int svr_fd);

size_t do_response(
        char *read_buff, ssize_t read_len,
        char *write_buff, ssize_t write_len
);

#endif //UNIXSTUDY_SVR_H
