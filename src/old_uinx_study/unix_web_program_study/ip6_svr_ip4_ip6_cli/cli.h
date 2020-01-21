//
// Created by tao on 19-1-18.
//

#ifndef UNIXSTUDY_CLI_H
#define UNIXSTUDY_CLI_H

#include <cstdio>

ssize_t do_request(const char *msg, ssize_t len, char *receive_buff, size_t buff_len, const char *addr,
                   const char *port);

ssize_t do_requestv4(const char *msg, ssize_t len, char *receive_buff, size_t buff_len, const char *addr, int port);

ssize_t do_requestv6(const char *msg, ssize_t len, char *receive_buff, size_t buff_len, const char *addr, int port);

#endif  // UNIXSTUDY_CLI_H
