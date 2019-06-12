//
// Created by tao on 19-1-21.
//

#ifndef UNIXSTUDY_COMMON_FUNCS_H
#define UNIXSTUDY_COMMON_FUNCS_H


#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

//>其他文件中的方法
#include "log_init.h"
//<

/**
 * memncpy 类似strncpy
 * @param dest 目标
 * @param dest_len 目标最大长度
 * @param src 源
 * @param src_len 源最大长度
 * @return 实际拷贝的长度
 */
size_t memncpy(void *__restrict dest, size_t dest_len, const void *__restrict src, size_t src_len);

/**
 * memncpy,不返回任何信息
 */
#define MEMNCPY(dest, dest_len, src, src_len) memcpy(dest, src, (src_len < dest_len) ? src_len : dest_len)

/**
 * 检测读超时的函数（并不进行读操作）
 * 也可以用于accept函数
 * eg：
 * if(read_timeout(fd,waitSec){
 * ERROR() //错误操作
 * }else{
 * read(...) //正确操作
 * }
 * @param fd 目标fd
 * @param wait_sec 等待时间
 * @return 正确返回0，出错返回-1
 */
int test_read_timeout(int fd, long wait_sec);

/**
 * 检测写超时的函数（并不进行读操作）
 * if(write_timeout(fd,waitSec){
 * ERROR() //错误操作
 * }else{
 * write(...) //正确操作
 * }
 * @param fd 目标fd
 * @param wait_sec 等待时间
 * @return 正确返回0，出错返回-1
 */
int test_write_timeout(int fd, long wait_sec);

char randChar();

#endif //UNIXSTUDY_COMMON_FUNCS_H
