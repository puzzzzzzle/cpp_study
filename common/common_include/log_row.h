//
// Created by khalidzhang on 2019-08-11.
//

#ifndef CPP_STUDY_TEMPLATE_LOG_ROW_H
#define CPP_STUDY_TEMPLATE_LOG_ROW_H
//
// Created by tao on 19-2-21.
//

#ifndef UNIXSTUDY_BOOST_LOG_INIT_H
#define UNIXSTUDY_BOOST_LOG_INIT_H

#include <errno.h>
#include <stdio.h>

#define LOG_TRACE(msg)                                                                                                 \
    std::cout << "[" << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]"          \
              << std::endl;
#define LOG_DEBUG(msg)                                                                                                 \
    std::cout << "[" << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]"          \
              << std::endl;
#define LOG_INFO(msg)                                                                                                  \
    std::cout << "[" << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]"          \
              << std::endl;
#define LOG_WARNING(msg)                                                                                               \
    std::cerr << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]" << std::endl;
#define LOG_ERROR(msg)                                                                                                 \
    std::cerr << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]" << std::endl;
//只是一个参考，调用errno检查错误
#define LOG_PERROR(msg)                                                                                                \
    std::cerr << msg << "]   ["                                                                                        \
              << " reason maybe  :  " << strerror(errno) << "   " << __FILE__ << ":" << __LINE__ << "    "             \
              << __PRETTY_FUNCTION__ << "]" << std::endl;
#define LOG_FATAL(msg)                                                                                                 \
    std::cerr << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__ << "]" << std::endl;
///// 原始输出
#define LOG_RAW_COUT(msg) std::cout << msg;
#define LOG_RAW_CLINE(msg) std::cout << msg << std::endl;
#define LOG_RAW_PRINTF(fmt, args...) printf(fmt, ##args);
#define LOG_RAW_PLINE(fmt, args...)                                                                                    \
    printf(fmt, ##args);                                                                                               \
    printf("\n");

#endif  // UNIXSTUDY_BOOST_LOG_INIT_H

#endif  // CPP_STUDY_TEMPLATE_LOG_ROW_H
