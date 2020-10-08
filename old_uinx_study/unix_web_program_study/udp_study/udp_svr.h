//
// Created by tao on 19-1-17.
//

#ifndef UNIXSTUDY_UDP_SVR_H
#define UNIXSTUDY_UDP_SVR_H

#include <netinet/in.h>

#define MAX_LINE_LEN 1024
#define ADDR "127.0.0.1"
#define PORT 8960

int start_svr();

void do_response(int fd, sockaddr_in *client_addr, socklen_t len,
                 char *read_buff, ssize_t read_len, char *write_buff,
                 ssize_t write_len);

#endif  // UNIXSTUDY_UDP_SVR_H
