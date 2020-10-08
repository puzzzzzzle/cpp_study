//
// Created by tao on 19-1-19.
//

#ifndef UNIXSTUDY_TEST_ALARM_H
#define UNIXSTUDY_TEST_ALARM_H

#include <sys/socket.h>

void conn_alarm(int signo);

size_t recvfrom_timeo(int socket_fd, sockaddr *addr, socklen_t addr_len,
                      int sec, char *buff, size_t buff_len);

#endif  // UNIXSTUDY_TEST_ALARM_H
