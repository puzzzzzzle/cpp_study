//
// Created by tao on 19-2-21.
//

#ifndef UNIXSTUDY_BOOST_LOG_INIT_H
#define UNIXSTUDY_BOOST_LOG_INIT_H

#include <errno.h>

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

#define TRACE(msg) BOOST_LOG_SEV(logger1, trace) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define DEBUG(msg) BOOST_LOG_SEV(logger1, debug) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define INFO(msg) BOOST_LOG_SEV(logger1, info) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define WARNING(msg) BOOST_LOG_SEV(logger1, warning) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define ERROR(msg) BOOST_LOG_SEV(logger1, error) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
//只是一个参考，调用errno检查错误
#define PERROR(msg)                                                                                                                                                                                    \
    BOOST_LOG_SEV(logger1, error) << msg << "]   ["                                                                                                                                                    \
                                  << " reason maybe  :  " << strerror(errno) << "   " << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;
#define FATAL(msg) BOOST_LOG_SEV(logger1, fatal) << msg << "]   [" << __FILE__ << ":" << __LINE__ << "    " << __PRETTY_FUNCTION__;

/**
 * 初始化boost_log
 * @return
 */
int log_init();
#endif  // UNIXSTUDY_BOOST_LOG_INIT_H
