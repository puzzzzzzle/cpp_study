//
// Created by khalidzhang on 2021/8/26.
//
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <unwind.h>

#include <cassert>
#include <iostream>

#include "get_stack_str.h"

#include "test_func.h"

typedef int (*hook_func_t)();
static hook_func_t system_handle = NULL;

__attribute__((constructor)) static void init_dyn_handle();
static void init_dyn_handle() {
  printf("init hook zero\n");
  // 获取 __gxx_personality_v0 函数的下一个声明,
  // 应为我们在后面会声明一个相同的, 所以下一个就是系统原有的
//  system_handle = (hook_func_t)dlsym(RTLD_NEXT, "zero");
//  assert(system_handle != nullptr);
}
//  这个符号声明于静态库中
// 在本程序中找到了这个符号就不在静态库中找了, 所以会直接调用到本函数而非静态库中的函数
extern "C" int zero() {
  printf("-------------- call zero hook i_func \n");
  // TODO 调用静态库中的函数

  //
  return -1;
}
