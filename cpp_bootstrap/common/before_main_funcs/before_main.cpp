/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/1/30
 * @file before_main.cpp
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#include <cstdlib>
#include <ctime>

#include "log_init.h"

static int before_run() {
  srand(time(NULL));
  int iRet = LogInit::log_init();
  LOG_RAW_CLINE("before main init " <<iRet);
  return 0;
}

__attribute__((unused)) static int before_main_ret = before_run();