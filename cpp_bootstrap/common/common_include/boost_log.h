/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/1/21
 * @file boost_log.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace trivial = logging::trivial;
using LogChannal =
    src::severity_channel_logger<trivial::severity_level, std::string>;

namespace LogInit {
inline LogChannal& GetLogger() {
  static LogChannal logger{};
  return logger;
}
/**
 * 初始化boost_log 只能由main函数调用一次
 * @return
 */
inline int log_init() {
  boost::log::add_common_attributes();
  std::ifstream file("./data/boost_log_settings.ini");
  if (!file.is_open()) {
    std::cerr << "open settings fail" << std::endl;
    return -1;
  }
  logging::init_from_stream(file);
  file.close();
  return 0;
}
}  // namespace LogInit
template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& p, const T& v) {
  std::ostringstream oss{};
  oss << v;
  p << oss.str();
  return p;
}
#define LOG_BASE(msg)                                            \
  << "[" << msg << "]| " << __FILE__ << ":" << __LINE__ << " | " \
  << __PRETTY_FUNCTION__ << " |" << std::this_thread::get_id();
#define LOG_TRACE(msg)                                                \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::trace) \
  LOG_BASE(msg)
#define LOG_DEBUG(msg)                                                \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::debug) \
  LOG_BASE(msg)

#define LOG_INFO(msg)                                                \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::info) \
  LOG_BASE(msg)

#define LOG_WARNING(msg)                                                \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::warning) \
  LOG_BASE(msg)

#define LOG_ERROR(msg)                                                \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::error) \
  LOG_BASE(msg)

// 只是一个参考，调用errno检查错误
#define LOG_PERROR(msg)                                               \
  BOOST_LOG_SEV(LogInit::GetLogger(), trivial::severity_level::error) \
  LOG_BASE(msg) << "|reason maybe:" << strerror(errno)
#define LOG_FATAL(msg)                       \
  BOOST_LOG_SEV(LogInit::GetLogger(), fatal) \
  LOG_BASE(msg)
