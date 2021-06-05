/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/6/5
 * @file another.cpp
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#include "common_includes.h"

#include "header.h"
// static的 只会在当前 cpp 对应的 .o 文件中生效, 这样全局就可以有多个 i 定义, 每个都会初始化
static int i = []() -> int{
  LOG_RAW_CLINE("before main in cpp another.cpp")
  return 1;
}();