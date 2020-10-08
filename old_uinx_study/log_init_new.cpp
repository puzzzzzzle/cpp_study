//
// Created by tao on 19-1-21.
//!!!!!!!!!!!!!!!!已删除，由于log4cplus的兼容性问题，以不在使用log4cplus，以前的宏全部改为cout，以后会换为boost.log
//

#include "log_init_new.h"

//#include <log4cplus/logger.h>
//#include <log4cplus/configurator.h>
//#include <log4cplus/loggingmacros.h>
//
// log4cplus::Logger file, console;

/**
 * 初始化logger，在此之前不要使用logger,要使用log4cplus则必须在main中引用，并调用init
 * @return
 */
int log_init() {
  //    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log4cplus_root.properties"));
  //    console = log4cplus::Logger::getRoot();
  //    file = log4cplus::Logger::getInstance("file");

  return 0;
}
