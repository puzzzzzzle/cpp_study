//
// Created by tao on 19-2-21.
//

#ifndef UNIXSTUDY_BOOST_LOG_INIT_H
#define UNIXSTUDY_BOOST_LOG_INIT_H

#include <errno.h>
#include <stdio.h>

#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>

namespace logging  = boost::log;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs    = boost::log::attributes;
namespace sinks    = boost::log::sinks;

using namespace logging::trivial;

extern src::severity_channel_logger<severity_level, std::string> logger1;
extern src::severity_channel_logger<severity_level, std::string> logger2;

#define LOG_TRACE(msg)                                                                                                 \
    BOOST_LOG_SEV(logger1, trace) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define LOG_DEBUG(msg)                                                                                                 \
    BOOST_LOG_SEV(logger1, debug) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define LOG_INFO(msg)                                                                                                  \
    BOOST_LOG_SEV(logger1, info) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define LOG_WARNING(msg)                                                                                               \
    BOOST_LOG_SEV(logger1, warning) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define LOG_ERROR(msg)                                                                                                 \
    BOOST_LOG_SEV(logger1, error) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
//只是一个参考，调用errno检查错误
#define LOG_PERROR(msg)                                                                                                \
    BOOST_LOG_SEV(logger1, error) << msg << "]   ["                                                                    \
                                  << " reason maybe  :  " << strerror(errno) << "   " << __FILE__ << ":" << __LINE__   \
                                  << "    " << __PRETTY_FUNCTION__;
#define LOG_FATAL(msg)                                                                                                 \
    BOOST_LOG_SEV(logger1, fatal) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
///// 原始输出
#define LOG_RAW_COUT(msg) std::cout << msg;
#define LOG_RAW_CLINE(msg) std::cout << msg << std::endl;
#define LOG_RAW_PRINTF(fmt, args...) printf(fmt, ##args);
#define LOG_RAW_PLINE(fmt, args...)                                                                                    \
    printf(fmt, ##args);                                                                                               \
    printf("\n");

#define TRACE(msg) LOG_TRACE(msg);
#define DEBUG(msg) LOG_DEBUG(msg);
#define INFO(msg) LOG_INFO(msg);
#define WARNING(msg) LOG_WARNING(msg);
#define ERROR(msg) LOG_ERROR(msg);
#define PERROR(msg) LOG_PERROR(msg);
#define FATAL(msg) LOG_FATAL(msg);
#define RAW_COUT(msg) LOG_RAW_COUT(msg);
#define RAW_CLINE(msg) LOG_RAW_CLINE(msg);
#define RAW_PRINTF(fmt, args...) printf(fmt, ##args);
#define RAW_PLINE(fmt, args...)                                                                                        \
    printf(fmt, ##args);                                                                                               \
    printf("\n");

/**
 * 初始化boost_log 只能由main函数调用一次
 * @return
 */
int log_init();

#endif  // UNIXSTUDY_BOOST_LOG_INIT_H
