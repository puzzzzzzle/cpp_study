//
// Created by tao on 19-1-19.
//

//#include <string.h>
// #include <unistd.h>
//#include <cerrno>
//#include <cstring>
//#include "timeout_socket_operator.h"
//
///**
// * 检测读超时的函数（并不进行读操作）
// * 也可以用于accept函数
// * eg：
// * if(read_timeout(fd,waitSec){
// * ERROR() //错误操作
// * }else{
// * read(...) //正确操作
// * }
// * @param fd 目标fd
// * @param wait_sec 等待时间
// * @return 正确返回0，出错返回-1
// */
// int test_read_timeout(int fd, long wait_sec) {
//    int ready_number;
//    fd_set r_set{};
//    timeval wait_time{};
//
//    FD_ZERO(&r_set);
//    FD_SET(fd, &r_set);
//
//    wait_time.tv_sec = wait_sec;
//    wait_time.tv_usec = 0;
//
//    do {
//        ready_number = select(fd + 1, &r_set, nullptr, nullptr, &wait_time);
//    } while (ready_number < 0 && errno == EINTR); //等待被(信号)打断的情况
//
//    return (ready_number == 1) ? 0 : 1;
//}
//
///**
// * 检测写超时的函数（并不进行读操作）
// * if(write_timeout(fd,waitSec){
// * ERROR() //错误操作
// * }else{
// * read(...) //正确操作
// * }
// * @param fd 目标fd
// * @param wait_sec 等待时间
// * @return 正确返回0，出错返回-1
// */
// int test_write_timeout(int fd, long wait_sec) {
//    int ready_number;
//    fd_set w_set{};
//    struct timeval wait_time{};
//
//    FD_ZERO(&w_set);
//    FD_SET(fd, &w_set);
//
//    wait_time.tv_sec = wait_sec;
//    wait_time.tv_usec = 0;
//
//    do {
//        ready_number = select(fd + 1, nullptr, &w_set, nullptr, &wait_time);
//    } while (ready_number < 0 && errno == EINTR); //等待被(信号)打断的情况
//
//    return (ready_number == 1) ? 0 : -1;
//}
