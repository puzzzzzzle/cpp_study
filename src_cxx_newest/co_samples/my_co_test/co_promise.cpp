//
// Created by khalidzhang on 2022/5/16.
//
#include <gtest/gtest.h>

#include <coroutine>
#include <exception>

#include "log_init.h"
namespace co_promise_test {
struct promise_test;
struct coroutine_test : std::coroutine_handle<promise_test> {
  using promise_type = promise_test;
};
struct promise_test {
  coroutine_test get_return_object() {
    return {coroutine_test::from_promise(*this)};
  }
  std::suspend_always initial_suspend() noexcept { return {}; }
  std::suspend_never final_suspend() noexcept { return {}; }
  void return_void() {}
  void unhandled_exception() {}
};
struct inner_class_co {
  int i{};
  coroutine_test f() {
    LOG_DEBUG(i)
    co_return;
  }
};

// 注意promise 空悬的问题
// 空悬后不一定出错, 但是有问题
TEST(bad, 1) {
  {
    //  inner_class_co{1} : i已经销毁, f绑定的this指针空悬了, 不能访问
    auto h = inner_class_co{1}.f();
    //    h();
  }

  {
    // lambda 中 i 被销毁了, 不能使用
    // lambda相当于一个匿名类
    auto h = [i = 1]() -> coroutine_test {
      LOG_DEBUG(i)
      co_return;
    }();
    //    h();
  }
}
TEST(good, 1) {
  //  auto lam = [](int i) -> coroutine_test {
  //    LOG_DEBUG(i)
  //    co_return;
  //  };
  auto h = [](int i) -> coroutine_test {
    LOG_DEBUG(i)
    co_return;
  }(42);
  // operator () 就是 resume
  //  h();
  h();
  LOG_DEBUG("done " << (int)h.done())
  LOG_DEBUG("done " << (int)h.done())
}
}  // namespace co_promise_test