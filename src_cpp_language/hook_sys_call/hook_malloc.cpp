//
// Created by khalidzhang on 2021/8/26.
//
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
typedef void *(*malloc_type)(size_t __size);

static malloc_type system_handle = nullptr;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void init_dyn_handle() {
  system_handle = (malloc_type)dlsym(RTLD_NEXT, "malloc");
  assert(system_handle != nullptr);
}

extern "C" void *malloc(size_t __size) {
  pthread_once(&init_once, init_dyn_handle);

  // 使用一个简单的标志来防止递归调用
  static thread_local bool in_malloc = false;
  if (in_malloc) {
    return system_handle(__size);
  }

  in_malloc = true;
  void *ret = system_handle(__size);
  in_malloc = false;

  // 使用 write 代替 printf 以避免递归调用
  char buffer[256];
  int len = snprintf(buffer, sizeof(buffer), "malloc %zu @ %p\n", __size, ret);
  write(1, buffer, len);

  return ret;
}