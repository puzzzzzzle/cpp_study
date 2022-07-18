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

typedef void *(*malloc_type)(size_t __size);

static malloc_type system_handle = NULL;

__attribute__((constructor)) static void init_dyn_handle();
static void init_dyn_handle() {
  printf("init hook_malloc\n");
  // 获取 __gxx_personality_v0 函数的下一个声明,
  // 应为我们在后面会声明一个相同的, 所以下一个就是系统原有的
  system_handle = (malloc_type)dlsym(RTLD_NEXT, "malloc");
  assert(system_handle != nullptr);
}

// 动态链接的库也可以直接覆盖, 这样在本二进制中找到了, 就不会去动态库中找了
extern "C" void *malloc(size_t __size) {
  void *ret = system_handle(__size);
  printf("malloc %d @ %p \n", __size, ret);
  return ret;
}
