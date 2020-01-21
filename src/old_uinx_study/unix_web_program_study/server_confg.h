//
// Created by tao on 18-12-30.
//

#ifndef UNIXSTUDY_SERVER_CONFG_H
#define UNIXSTUDY_SERVER_CONFG_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define SVR_ADDS "127.0.0.1"
#define SVR_PORT 8981
#define SHARE_BUFF_SIZE 500

/**
 * 从一个不稳定的fd中稳定的读取数据 例如网络socket
 * @param fd
 * @param buff
 * @param max_buff_size
 * @return 读取到的数据量，出错返回-1
 */
ssize_t readn(int fd, char *buff, size_t max_buff_size) {
    printf("start read n %d\n", fd);
    //    //读取数据
    //    char *read_buff_ptr = buff;
    //    ssize_t read_buff_left_size;
    //    ssize_t read_once = 0;
    //    read_buff_left_size = max_buff_size;
    //
    //    while (read_buff_left_size > 0) {
    //        if ((read_once = read(fd, read_buff_ptr, read_buff_left_size)) < 0) {
    //            if (errno == EINTR) {
    //                //只是啥都没读取,被中断了
    //                read_once = 0;
    //            } else {
    //                //出错
    //                perror("read wrong:");
    //                return -1;
    //            }
    //            ///貌似有问题 输不进来eof ctrl d没用
    //        } else if (read_once == 0) {
    //            //结束了
    //            break;
    //        } else if (read_buff_ptr[0] == EOF) {
    //            //收到EOF
    //            break;
    //        }
    //        read_buff_left_size -= read_once;
    //        read_buff_ptr += read_once;
    //    }

    //    read(fd, read_buff_ptr, read_buff_left_size);

    ssize_t read_size;
    if ((read_size = recv(fd, buff, max_buff_size, 0)) < 0) {
        return -1;
    }
    printf("end read n %d\n", fd);
    return read_size;
}

/**
 * 向不稳定的fd中稳定的写入数据
 * @param fd
 * @param buff
 * @param len
 * @return 出错返回-1 ，不然返回0
 */
int writen(int fd, char *buff, size_t len) {
    printf("start write n %d\n", fd);

    //    //写入数据
    //    char *buff_ptr = buff;
    //    size_t write_left_size;
    //    ssize_t write_once = 0;
    //    write_left_size = len;
    //
    //    while (write_left_size > 0) {
    //        if ((write_once = write(fd, buff, write_left_size)) <= 0) {
    //            if (write_once < 0 && errno == EINTR) {
    //                //只是啥都没写入,被中断了
    //                write_once = 0;
    //            } else {
    //                //出错了！！！
    //                perror("write wrong:");
    //                return -1;
    //            }
    //        }
    //        write_left_size -= write_once;
    //        buff_ptr += write_once;
    //    }

    //    write(fd, buff, write_left_size);

    //  使用send
    ssize_t res;
    res = send(fd, buff, len, 0);

    printf("end write n %d\n", fd);
    return res == -1 ? -1 : 0;
}

#endif  // UNIXSTUDY_SERVER_CONFG_H
