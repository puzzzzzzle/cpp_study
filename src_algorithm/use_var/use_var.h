/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/8/13
 * @file use_var.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once

#define UNUSED(expr) \
  do {               \
    (void)(expr);    \
  } while (false)

struct UseVar {
  template <typename T>
  // 原理: UseVar 不是模板的, 但是构造函数是模板的
  // 这就可以用不同类型的T构造都是UseVar类型的结构体
  // 这些结构体可以被放在一个数组中去, 应为都是非模板的 UseVar 空对象
  // 每种类型在模板特化时会生成一个构造函数
  UseVar(T&&) {}
};
// 使用一个空对象数组消费所有不同类型的变量, 消耗可忽略
#define UNUSED_M(...)                                     \
  do {                                                    \
    UseVar unused_tmp_array_for_use_macro[]{__VA_ARGS__}; \
    (void)unused_tmp_array_for_use_macro;                 \
  } while (false)
