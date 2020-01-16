#ifndef UNIXSTUDYCPP_LOG4CPLUS_INIT_HPP
#define UNIXSTUDYCPP_LOG4CPLUS_INIT_HPP

//#include <log4cplus/logger.h>
//#include <log4cplus/configurator.h>
//#include <log4cplus/loggingmacros.h>
//
#include <iostream>
using namespace std;
//
// Logger file, console;

/**
 * 初始化logger，在此之前不要使用logger,要使用log4cplus则必须在main中引用，并调用init
 * @return
 */
int log_init() {
    //    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log4cplus_root.properties"));
    //    console = Logger::getRoot();
    //    file = log4cplus::Logger::getInstance("file");

    return 0;
}

#endif