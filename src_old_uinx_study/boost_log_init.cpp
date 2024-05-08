#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <fstream>
#include <string>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

using namespace std;
using namespace logging::trivial;
src::severity_channel_logger<severity_level, std::string> logger1(
    keywords::channel = "MySink1");
src::severity_channel_logger<severity_level, std::string> logger2(
    keywords::channel = "MySink2");

int log_init() {
  logging::add_common_attributes();
  logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());

  logging::register_simple_formatter_factory<severity_level, char>("Severity");
  logging::register_simple_filter_factory<severity_level, char>("Severity");

  std::ifstream file("boost_log_settings.ini");
  if (!file.is_open()) {
    std::cerr << "open settings fail" << std::endl;
    return -1;
  }
  logging::init_from_stream(file);
  file.close();
  return 0;
}

//#include <iostream>
//
//
//#include <boost/log/common.hpp>
//#include <boost/log/expressions.hpp>
//
//
//#include <boost/log/utility/setup/file.hpp>
//#include <boost/log/utility/setup/console.hpp>
//#include <boost/log/utility/setup/common_attributes.hpp>
//
//
//#include <boost/log/attributes/timer.hpp>
//#include <boost/log/attributes/named_scope.hpp>
//
//
//#include <boost/log/sources/logger.hpp>
//
//
//#include <boost/log/support/date_time.hpp>
//
//
// namespace logging = boost::log;
// namespace sinks = boost::log::sinks;
// namespace attrs = boost::log::attributes;
// namespace src = boost::log::sources;
// namespace expr = boost::log::expressions;
// namespace keywords = boost::log::keywords;
//
//
// using boost::shared_ptr;
//
//
//// Here we define our application severity levels.
// enum severity_level {
//    trace,
//    debug,
//    info,
//    warning,
//    error,
//    fatal,
//};
//
//
//// The formatting logic for the severity level
// template<typename CharT, typename TraitsT>
// inline std::basic_ostream<CharT, TraitsT> &operator<<(
//        std::basic_ostream<CharT, TraitsT> &strm, severity_level lvl) {
//    static const char *const str[] =
//            {
//                    "trace",
//                    "debug",
//                    "info",
//                    "warning",
//                    "error",
//                    "fatal",
//            };
//    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
//        strm << str[lvl];
//    else
//        strm << static_cast< int >(lvl);
//    return strm;
//}
//
//
// int log_init() {
//    // This is a simple tutorial/example of Boost.Log usage
//
//
//    // The first thing we have to do to get using the library is
//    // to set up the logging sinks - i.e. where the logs will be written to.
//    logging::add_console_log(
//            std::cout,
//            keywords::format = expr::stream
//                    <<
//                    expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
//                    "%Y-%m-%d, %H:%M:%S.%f")
//                    << " [" <<
//                    expr::format_date_time<attrs::timer::value_type>("Uptime",
//                    "%O:%M:%S")
//                    << "] [" << expr::format_named_scope("Scope",
//                    keywords::format = "%n (%f:%l)")
//                    << "] [" << expr::attr<severity_level>("Severity")
//                    << "]  " << expr::message
//    );
//
//
//    // One can also use lambda expressions to setup filters and formatters
//    logging::add_file_log
//            (
//                    "sample.log", keywords::auto_flush = true,
//                    keywords::filter = expr::attr<severity_level>("Severity")
//                    >= trace, keywords::format = expr::stream
//                            <<
//                            expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
//                            "%Y-%m-%d, %H:%M:%S.%f")
//                            << " [" <<
//                            expr::format_date_time<attrs::timer::value_type>("Uptime",
//                            "%O:%M:%S")
//                            << "] [" << expr::format_named_scope("Scope",
//                            keywords::format = "%n (%f:%l)")
//                            << "] <" << expr::attr<severity_level>("Severity")
//                            << "> " << expr::message
//                    /*
//                            keywords::format = expr::format("%1% [%2%] [%3%]
//                            <%4%> %5%")
//                                % expr::format_date_time<
//                                boost::posix_time::ptime >("TimeStamp",
//                                "%Y-%m-%d, %H:%M:%S.%f") %
//                                expr::format_date_time<
//                                attrs::timer::value_type >("Uptime",
//                                "%O:%M:%S") %
//                                expr::format_named_scope("Scope",
//                                keywords::format = "%n (%f:%l)") % expr::attr<
//                                severity_level >("Severity") % expr::message
//                    */
//            );
//    logging::add_common_attributes();
//    src::severity_logger<severity_level> slg;
//
//
//    // Let's pretend we also want to profile our code, so add a special timer
//    attribute. slg.add_attribute("Uptime", attrs::timer());
//
//
//    BOOST_LOG_SEV(slg, trace) <<__FILE__
//    <<":"<<__LINE__<<":"<<__PRETTY_FUNCTION__<< "A normal severity message,
//    will not pass to the file"; BOOST_LOG_SEV(slg, info) << "A warning
//    severity message, will pass to the file"; BOOST_LOG_SEV(slg, fatal) << "An
//    f severit!!!!!!!y message, will pass to the file";
//
//
//    return 0;
//}