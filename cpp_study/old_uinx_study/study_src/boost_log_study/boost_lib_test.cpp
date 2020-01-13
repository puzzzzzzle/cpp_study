//
// Created by tao on 18-12-25.
//

#include "boost_lib_main.h"
#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/keywords/severity.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>


#include <boost/log/sources/logger.hpp>


#include <boost/log/support/date_time.hpp>


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

void boost_lib_test_init() {

    logging::add_console_log(std::cout, keywords::format = "[%TimeStamp%][]: %Message%");


    logging::add_file_log
            (
                    keywords::file_name = "log/boost_log_%N.log",
                    keywords::rotation_size = 10 * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
                    keywords::format = "[%TimeStamp%]: %Message%"
            );

    logging::add_common_attributes();


//    logging::core::get()->set_filter
//            (
//                    logging::trivial::severity >= logging::trivial::info
//            );



//    src::logger my_logger;
//    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
//
//    src::logger_mt& lg = my_logger::get();
//
//    logging::record rec = lg.open_record();
//    if (rec)
//    {
//        logging::record_ostream strm(rec);
//        strm << "Hello, World!";
//        strm.flush();
//        lg.push_record(boost::move(rec));
//    }


}


int boost_lib_test_main() {

    boost_lib_test_init();

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}