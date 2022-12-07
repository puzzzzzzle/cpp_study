
#pragma once

#include <execinfo.h>

#include <cstdlib>
#include <sstream>
// 获取栈字符串
inline std::string get_stack_trace_str(int size = 16) {
  void** array = new void*[size];
  int stack_num = backtrace(array, size);
  char** stacktrace = backtrace_symbols(array, stack_num);
  std::stringstream ss;
  ss << "stack trace:\n";
  for (int i = 0; i < stack_num; ++i) {
    ss << "[" << i << "]:" << stacktrace[i] << "\n";
  }
  free(stacktrace);
  delete[] array;
  return ss.str();
}