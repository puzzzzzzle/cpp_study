/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/11/19
 * @file dyn_logger.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include "cstring"

inline const char* BaseName(const char* const name) {
  const char* p = ::strrchr(name, '/');
  return p ? p + 1 : name;
}
// 需要自定义log的地方, 需要提供一个符合一下trait的类
struct LogCtl {
  bool DLoggerFilter(const char* name, int level) { return true; }
  const char* GetLogTag(const char* name) { return BaseName(name); }
};
// 在打log的地方, 使用c++优先绑定规则, 使用最优先绑定到的 GetLogCtl 函数,
// 作为过滤器 这个是在全局没有匹配的时候, 最后使用的
inline LogCtl* GetLogCtl() {
  static LogCtl ctl{};
  return &ctl;
}
#ifdef D_LOG
#error "already defined D_LOG"
#endif
#define D_LOG(prefix, name, level, log...)                                    \
  if (GetLogCtl()->DLoggerFilter(name, level)) {                              \
    prefix("|" << GetLogCtl()->GetLogTag(name) << "|" << level << "|" << log) \
  }
