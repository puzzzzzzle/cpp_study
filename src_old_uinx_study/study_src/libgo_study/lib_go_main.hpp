//
// Created by tao on 18-12-1.
//

#ifndef UNIXSTUDYCPP_LIB_GO_MAIN_HPP
#define UNIXSTUDYCPP_LIB_GO_MAIN_HPP

#include "basic_lib_go.hpp"
#include "test_cmake.h"

int lib_go_main(int argc, char **argv) {
  //    basic_lib_go_test();
  //    no_wait_test();
  channel_test_me();
  test_cmake t;
  t.sayHello();
  say_hello_from_func();
  return 0;
}

#endif  // UNIXSTUDYCPP_LIB_GO_MAIN_HPP
