//
// Created by khalidzhang on 2022/12/21.
//
#include <thread>

#include "common_includes.h"
#include "execution_header.h"
TEST(hello_world, 1) {
  static_thread_pool tpContext;
  auto sch = tpContext.get_scheduler();

  // 创建schedule
  auto begin = schedule(sch);

  // 连接 begin 和 hi_again, begin返回void, 但是它的信号会让 hi_again 触发, hi_again 也没有参数
  auto hi_again = then(begin, []() {
    LOG_DEBUG("hello world")
    return 13;
  });
  // 连接 hi_again 和 add_42, hi_again 返回int, 当做 add_42的输入
  auto add_42 = then(hi_again, [](int arg) { return arg + 42; });

  auto i = sync_wait(add_42).value();
  LOG_DEBUG(i)
}