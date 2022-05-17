//
// Created by khalidzhang on 2022/5/17.
//
#include <gtest/gtest.h>

#include <chrono>
#include <coroutine>
#include <exception>
#include <thread>

#include "log_init.h"

namespace co_await_test {
struct task {
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};
auto thread_wait_timer(int64_t ms) {
  struct thread_awaitable {
    int64_t ms_{};
    std::thread t_{};
    bool await_ready() {
      LOG_DEBUG("call")
      return false;
    }
    void await_suspend(std::coroutine_handle<> h) {
      LOG_DEBUG("start")
      int64_t sleepMs = ms_;
      t_ = std::thread([h, sleepMs]() {
        LOG_DEBUG("wait")
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        LOG_DEBUG("resume")
        h.resume();
      });
      LOG_DEBUG("end")
    }
    void await_resume() { LOG_DEBUG("call") }
  };
  return thread_awaitable{ms};
}
task resume_by_thread_timer() {
  LOG_DEBUG("start")
  auto awaitable = thread_wait_timer(1000);
  co_await awaitable;

  // TODO co_await 后 就直接保存状态返回调用方了, 到不了这里
  LOG_DEBUG("end")
  awaitable.t_.join();
}
TEST(co_await_test, 1) { resume_by_thread_timer(); }
}  // namespace co_await_test