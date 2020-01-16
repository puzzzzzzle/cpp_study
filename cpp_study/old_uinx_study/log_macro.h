//
// Created by tao on 18-11-26.
// 对日志的宏封装
//

#ifndef UNIXSTUDYCPP_LOG_MIC_H
#define UNIXSTUDYCPP_LOG_MIC_H

#include <iostream>

///////< log4cplus init
//#include <log4cplus/logger.h>
//#include <log4cplus/loggingmacros.h>
//
//#include <stdio.h>
//#include <string.h>
//#include <errno.h>
//
// extern log4cplus::Logger file, console;

//同时输出到控制台和文件
//#define TRACE(msg) LOG4CPLUS_TRACE(file, msg);
//#define DEBUG(msg) LOG4CPLUS_DEBUG(file, msg);
//#define INFO(msg) LOG4CPLUS_INFO(file, msg);
//#define WARN(msg) LOG4CPLUS_WARN(file, msg);
//#define ERROR(msg) LOG4CPLUS_ERROR(file, msg);
//#define PERROR(msg) LOG4CPLUS_ERROR(file, msg);LOG4CPLUS_ERROR(file, "err reason maybe : \t"<<strerror(errno));
//#define FATAL(msg) LOG4CPLUS_FATAL(file, msg);
//输出到控制台
//#define TRACE_CON(msg) LOG4CPLUS_TRACE(console, msg);
//#define DEBUG_CON(msg) LOG4CPLUS_DEBUG(console, msg);
//#define INFO_CON(msg) LOG4CPLUS_INFO(console, msg);
//#define WARN_CON(msg) LOG4CPLUS_WARN(console, msg);
//#define ERROR_CON(msg) LOG4CPLUS_ERROR(console, msg);
//#define PERROR_CON(msg) LOG4CPLUS_ERROR(console, msg);LOG4CPLUS_ERROR(console, "err reason maybe :
//\t"<<strerror(errno)); #define FATAL_CON(msg) LOG4CPLUS_FATAL(console, msg);

//////< console log init
#define TRACE(msg) std::cout << "log4cplus::TRACE\t" << msg << std::endl;
#define DEBUG(msg) std::cout << "log4cplus::DEBUG\t" << msg << std::endl;
#define INFO(msg) std::cout << "log4cplus::INFO\t" << msg << std::endl;
#define WARN(msg) std::cout << "log4cplus::WARN\t" << msg << std::endl;
#define ERROR(msg) std::cerr << "log4cplus::ERROR\t" << msg << std::endl;
//#define PERROR(msg) printf("%s\n",msg);
#define FATAL(msg) std::cerr << "log4cplus::FATAL\t" << msg << std::endl;

#endif  // UNIXSTUDYCPP_LOG_MIC_H
