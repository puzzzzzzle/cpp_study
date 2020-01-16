//
// Created by tao on 19-1-19.
//

#ifndef UNIXSTUDY_TIMEOUT_SOCKET_OPERATOR_H
#define UNIXSTUDY_TIMEOUT_SOCKET_OPERATOR_H

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
// int test_read_timeout(int fd, long wait_sec);
//
///**
// * 检测写超时的函数（并不进行读操作）
// * if(write_timeout(fd,waitSec){
// * ERROR() //错误操作
// * }else{
// * write(...) //正确操作
// * }
// * @param fd 目标fd
// * @param wait_sec 等待时间
// * @return 正确返回0，出错返回-1
// */
// int test_write_timeout(int fd, long wait_sec);

#endif  // UNIXSTUDY_TIMEOUT_SOCKET_OPERATOR_H
