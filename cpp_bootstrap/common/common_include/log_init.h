/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/5/24
 * @file log_init.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#include <cerrno>
#include <cstdio>
#include <iostream>

// func name
#ifdef WIN32
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

// log defind
#ifdef LOG_BOOST
#include "boost_log.h"
#else
#include "std_log.h"
#endif

///// 原始输出
#define LOG_RAW_COUT(msg) std::cout << msg;
#define LOG_RAW_CLINE(msg) std::cout << msg << std::endl;
#define LOG_RAW_PRINTF (fmt, args...) printf(fmt, ##args);
#define LOG_RAW_PLINE                 \
  (fmt, args...) printf(fmt, ##args); \
  printf("\n");

#define RAW_COUT(msg) LOG_RAW_COUT(msg);
#define RAW_CLINE(msg) LOG_RAW_CLINE(msg);
#define RAW_PRINTF(fmt, args...) printf(fmt, ##args);
#define RAW_PLINE(fmt, args...) \
  printf(fmt, ##args);          \
  printf("\n");
