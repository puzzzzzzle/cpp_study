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

class ClassFunc1
{
  // gcc 方言
  __attribute__((constructor)) static void before_main_xxx() { printf("ClassFunc1 before_main_xxx %s \n",__PRETTY_FUNCTION__); }
};