//
// Created by tao on 2019/6/12.
//

#include "test_func.h"

extern "C" int zero() {
  LOG_INFO("from lib")
  return 0;
}

void Hello::hello() { LOG_INFO("hello") }
