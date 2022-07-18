/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * 检查是否存在全局函数
 * 注意: 由于c/c++的函数查找规则, 只是代表在 HAS_GLOBAL_FUNC(xxx) 使用时是否存在
 * 使用后固定, 即使后面再声明了, 也不会判定找到
 * @time 2022/4/26
 * @file has_global_func.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <type_traits>

#define HAS_GLOBAL_FUNC(func_name)                                        \
  namespace anonymous_##func_name {                                       \
    struct anonymous {};                                                  \
    template <typename... Args>                                           \
    constexpr anonymous func_name(Args...);                               \
  }                                                                       \
  namespace has_##func_name {                                             \
    using namespace anonymous_##func_name;                                \
    struct check {                                                        \
      enum { value = !std::is_same_v<decltype(func_name()), anonymous> }; \
    };                                                                    \
  }
