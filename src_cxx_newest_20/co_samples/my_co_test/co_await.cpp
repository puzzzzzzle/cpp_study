//
// Created by khalidzhang on 2022/5/17.
//
//#define CPP_INSIGHTS
#ifndef CPP_INSIGHTS
#include <gtest/gtest.h>

#include "log_init.h"
#else
#include <iostream>
#define LOG_DEBUG(msg) std::cout << msg;
#endif

#include <chrono>
#include <coroutine>
#include <exception>
#include <thread>

namespace co_await_test {
struct awaitable {
  int64_t ms_{};
  std::thread t_{};
  bool await_ready() {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)

    return false;
  }
  void await_suspend(std::coroutine_handle<> h) {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
  }
  void await_resume() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
};
auto awaitable_test() { return awaitable{}; }
struct task {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    task get_return_object() {
      LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
      return handle_type::from_promise(*this);
    }
    std::suspend_never initial_suspend() {
      LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
      return {};
    }
    std::suspend_never final_suspend() noexcept {
      LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
      return {};
    }
    void destroy() const noexcept {
      LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
    }

    void return_void() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
    void unhandled_exception() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
  };
  task(const handle_type& h) : h_(h) {}
  handle_type h_{};
};
auto resume_by_thread_timer() -> task {
  LOG_DEBUG("start")
  // 生成 等待体, 但是不执行
  auto awaitable = awaitable_test();
  // 执行 完 await_ready await_suspend 后 这个函数直接返回一个 task
  // 对象到调用者上
  co_await awaitable;

  // 这个并不会被立即执行 需要等 协程 resume 后才会
  LOG_DEBUG("end")
}
void RunTests() {
  LOG_DEBUG("start call coroutine")
  auto t = resume_by_thread_timer();
  LOG_DEBUG("start resume coroutine")
  t.h_.resume();
  LOG_DEBUG("end resume coroutine")
  // 不用destroy
  //  t.h_.destroy();
}
#ifndef CPP_INSIGHTS
TEST(co_await_test, 1) { RunTests(); }
#else
int main(int argc, char* argv[]) {
  RunTests();
  return 0;
}
#endif
}  // namespace co_await_test