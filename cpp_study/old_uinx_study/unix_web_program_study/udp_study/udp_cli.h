//
// Created by tao on 19-1-17.
//

#ifndef UNIXSTUDY_UDP_CLI_H
#define UNIXSTUDY_UDP_CLI_H

int do_request(const char *msg, ssize_t len,
               char *receive_buff, size_t buff_len
);

#endif //UNIXSTUDY_UDP_CLI_H
