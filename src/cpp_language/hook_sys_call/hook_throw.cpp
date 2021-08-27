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

typedef _Unwind_Reason_Code (*personality_func)(int version, int actions,
                                                uint64_t ex_class,
                                                struct _Unwind_Exception *ex,
                                                struct _Unwind_Context *ctx);
static personality_func system_handle = NULL;

__attribute__((constructor)) static void init_dyn_handle();
static void init_dyn_handle() {
  printf("init hook_throw\n");
  // 获取 __gxx_personality_v0 函数的下一个声明,
  // 应为我们在后面会声明一个相同的, 所以下一个就是系统原有的
  system_handle = (personality_func)dlsym(RTLD_NEXT, "__gxx_personality_v0");
  assert(system_handle != nullptr);
}
// weak 的符号可以直接通过覆盖来替换
// 这个符号声明于 动态库中
/*
➜  bin readelf -a cpp_language_hook_sys_call |grep __gxx_personality_v0
   226: 00000000004057ae   174 FUNC    GLOBAL DEFAULT   13 __gxx_personality_v0
  1410: 00000000004057ae   174 FUNC    GLOBAL DEFAULT   13 __gxx_personality_v0

 ➜  bin readelf -a /lib64/libstdc++.so.6   |grep __gxx_personality_v0
0000002f24c8  097700000001 R_X86_64_64       000000000005e0c0 __gxx_personality_v0@@CXXABI_1.3 + 0
 2423: 000000000005e0c0  1393 FUNC    GLOBAL DEFAULT   12 __gxx_personality_v0@@CXXABI_1.3
 *
 */
extern "C" _Unwind_Reason_Code __gxx_personality_v0(
    int version, _Unwind_Action actions,
    _Unwind_Exception_Class exception_class,
    struct _Unwind_Exception *ue_header, struct _Unwind_Context *context) {
  printf("---------  call unwind  \n");
  // 调用系统原有的 system handle
  _Unwind_Reason_Code code =
      system_handle(version, actions, exception_class, ue_header, context);

  // 调用我们自己的逻辑
  if (_URC_HANDLER_FOUND == code) {
    printf("---------  cache found exception \n");
  }
  printf("%s", get_stack_trace_str(20).c_str());
  return code;
}
