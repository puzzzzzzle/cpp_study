//
// Created by tao on 19-1-19.
//

#include "test_alarm.h"

#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <csignal>

#include "log_macro.h"

// todo 打断失败！
size_t recvfrom_timeo(int socket_fd, sockaddr *addr, socklen_t addr_len, int sec, char *buff, size_t buff_len) {
    int            res, read_n;
    __sighandler_t pre_handle;
    pre_handle = signal(SIGALRM, conn_alarm);

    if (alarm(sec)) {
        FATAL("alarm signal err")
        exit(-1);
    }
    //    do {
    if ((res = recvfrom(socket_fd, buff, buff_len, 0, addr, &addr_len)) < 0) {
        INFO("start progress " << res)
        if (errno == EINTR) {
            ERROR("timeout!")
            //                continue;
        }
        close(socket_fd);
        read_n = 0;
        //            break;
    } else {
        read_n       = res;
        buff[read_n] = '\0';
        //            break;
    }
    //    } while (true);
    alarm(0);
    signal(SIGALRM, pre_handle);
    return read_n;
}

void conn_alarm(int signo) {
    FATAL("alarm was sended :" << signo)
    return;
}
