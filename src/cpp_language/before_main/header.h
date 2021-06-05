/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/6/5
 * @file header.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once

#include "common_includes.h"

// static的 只会在当前 cpp 对应的 .o 文件中生效, 这样全局就可以有多个 i 定义, 每个购汇初始化
// 非static 时 相当于这个被拷贝到了多个cpp中, 会重定义
static int j = []() -> int{
  LOG_RAW_CLINE("before main in cpp header.h")
  return 1;
}();