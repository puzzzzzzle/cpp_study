//
// Created by khalidzhang on 2022/5/18.
//
#include <coroutine>
#include <iostream>
#include <stdexcept>

#include "common_includes.h"
namespace co_test_funcs {

//! coro_ret 协程函数的返回值，内部定义promise_type，承诺对象
template <typename RET_TYPE, typename SEND_TYPE>
struct coroutine_ret {
  struct promise_type;
  struct suspend_always_yield_value : std::suspend_always {
    friend promise_type;
    constexpr SEND_TYPE await_resume() const { return m_p->send_data_; }

private:
    constexpr suspend_always_yield_value(promise_type* p) : m_p(p) {}
    promise_type* m_p;
  };
  using handle_type = std::coroutine_handle<promise_type>;
  //! 协程句柄
  handle_type coro_handle_;
  //
  bool started_{false};
  coroutine_ret(handle_type h) : coro_handle_(h) {}
  coroutine_ret(const coroutine_ret&) = delete;
  coroutine_ret(coroutine_ret&& s) : coro_handle_(s.coro_) {
    s.coro_handle_ = nullptr;
  }
  ~coroutine_ret() {
    //! 自行销毁
    if (coro_handle_) {
      LOG_DEBUG("destroy coroutine")
      coro_handle_.destroy();
    }
  }
  coroutine_ret& operator=(const coroutine_ret&) = delete;
  coroutine_ret& operator=(coroutine_ret&& s) {
    coro_handle_ = s.coro_handle_;
    s.coro_handle_ = nullptr;
    return *this;
  }

  //! 恢复协程，返回是否结束
  bool send(const SEND_TYPE& send) {
    if (!started_) {
      start();
    }
    LOG_DEBUG("send ")
    coro_handle_.promise().send_data_ = send;
    coro_handle_.resume();
    return coro_handle_.done();
  }
  bool start() {
    if (started_) {
      return coro_handle_.done();
    }
    LOG_DEBUG("start ")
    started_ = true;
    coro_handle_.resume();
    return coro_handle_.done();
  }
  //! 通过promise获取数据，返回值
  RET_TYPE get() { return coro_handle_.promise().return_data_; }
  //! promise_type就是承诺对象，承诺对象用于协程内外交流
  struct promise_type {
    promise_type() = default;
    ~promise_type() = default;

    //! 生成协程返回值
    auto get_return_object() {
      return coroutine_ret<RET_TYPE, SEND_TYPE>{
          handle_type::from_promise(*this)};
    }

    //! 注意这个函数,返回的就是awaiter
    //! 如果返回std::suspend_never{}，就不挂起，
    //! 返回std::suspend_always{} 挂起
    //! 当然你也可以返回其他awaiter
    auto initial_suspend() {
      // return std::suspend_never{};
      return std::suspend_always{};
    }
    //! co_return 后这个函数会被调用
    void return_value(RET_TYPE v) {
      return_data_ = v;
      return;
    }
    //!
    auto yield_value(RET_TYPE v) {
      LOG_DEBUG("yield_value invoked.")
      return_data_ = v;
      return suspend_always_yield_value(this);
    }
    //! 在协程最后退出后调用的接口。
    //! 若 final_suspend 返回 std::suspend_always 则需要用户自行调用
    //! handle.destroy() 进行销毁，但注意final_suspend被调用时协程已经结束
    //! 返回std::suspend_always并不会挂起协程（实测 VSC++ 2022）
    auto final_suspend() noexcept {
      LOG_DEBUG("final_suspend invoked.")
      return std::suspend_always{};
    }
    //
    void unhandled_exception() { std::exit(1); }
    // 返回值
    RET_TYPE return_data_;
    // send 值
    SEND_TYPE send_data_;
  };
};

// 这就是一个协程函数
coroutine_ret<int, int> coroutine_int_vec(int value) {
  // 进入协程看initial_suspend，返回std::suspend_always{};会有一次挂起
  LOG_DEBUG("Coroutine start !!!")
  int yield_get = 0;
  for (int i = 0; i < value; ++i) {
    yield_get = co_yield i + yield_get * 1000;
    LOG_DEBUG("yield value: " << i << "; send data: " << yield_get)
  }
  co_return 0;
}
int test() {
  bool done = false;
  LOG_DEBUG("Start test")
  // 调用协程,得到返回值c_r，后面使用这个返回值来管理协程。
  auto c_r = coroutine_int_vec(10);
  // 第一次停止因为initial_suspend 返回的是suspend_always
  // 此时没有进入Stage 1
  LOG_DEBUG("Coroutine ret =" << c_r.get())
  c_r.start();
  auto send = 1;
  while (true) {
    done = c_r.send(send);
    LOG_DEBUG("Coroutine " << (done ? "is done " : "isn't done ")
                           << "ret =" << c_r.get())
    if (done) {
      break;
    }
    ++send;
  }
  return 0;
}
// 暂未写 ret send data 为void的适配, 用不到的值用-1代替
TEST(co_test_funcs, 1) { test(); }
coroutine_ret<int, int> consumer() {
  while (true) {
    // co_yield void 就行 没意义 暂未适配void
    auto n = co_yield -1;
    LOG_DEBUG(" -- consume : " << n)
  }
  // co_return void 就行 没意义 暂未适配void
  co_return -1;
}
coroutine_ret<int, int> producer(coroutine_ret<int, int>& c) {
  c.start();
  for (int i = 0; i < 5; ++i) {
    auto data = i + 1000;
    LOG_DEBUG(" -- produce: " << data)
    c.send(data);
  }
  // co_return void 就行 没意义 暂未适配void
  co_return -1;
}
void consumer_producer_test() {
  auto c = consumer();
  auto p = producer(c);
  p.start();
}
TEST(consumer_producer_test, 1) { consumer_producer_test(); }
}  // namespace co_test_funcs