/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/4/13
 * @file generator.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
//
// Created by khalidzhang on 2023/4/13.
//
#include <coroutine>
#include <iostream>
#include <stdexcept>

namespace coro {
template <typename T>
struct promise_type_base {
  promise_type_base() = default;
  ~promise_type_base() = default;
  auto initial_suspend() { return std::suspend_always{}; }
  auto final_suspend() noexcept { return std::suspend_always{}; }
  void unhandled_exception() { std::exit(1); }
};
template <typename T>
struct generator_base {
  T& underlying() { return static_cast<T&>(*this); }
  T const& underlying() const { return static_cast<T const&>(*this); }
  auto& coro_handle() { return static_cast<T&>(*this).coro_handle_; }
  //
  bool started_{false};

  public:
  ~generator_base() {
    //! 自行销毁
    if (coro_handle()) {
      coro_handle().destroy();
    }
  }
  generator_base() {}
  generator_base(const generator_base&) = delete;
  generator_base(generator_base&& s) {
    coro_handle() = s.coro_handle();
    s.coro_handle() = nullptr;
  }
  generator_base& operator=(const generator_base&) = delete;
  generator_base& operator=(generator_base&& s) {
    coro_handle() = s.coro_handle();
    s.coro_handle() = nullptr;
    return *this;
  }
  bool done() { return coro_handle().done(); }
  bool start() {
    if (started_) {
      return coro_handle().done();
    }
    if (coro_handle().done()) {
      return true;
    }
    started_ = true;
    coro_handle().resume();
    return coro_handle().done();
  }
  //! 恢复协程，返回是否结束
  bool send_base() {
    if (!started_) {
      start();
    }
    if (coro_handle().done()) {
      return true;
    }
    coro_handle().resume();
    return coro_handle().done();
  }
};

template <typename T>
struct suspend_always_send_value : std::suspend_always {
  constexpr auto await_resume() const { return m_p->send_data_; }

  constexpr suspend_always_send_value(T* p) : m_p(p) {}
  T* m_p;
};
// 可以 send 值 给协程, 协程也可以yield/return值给调用放
template <typename YIELD_TYPE, typename RET_TYPE, typename SEND_TYPE>
struct generator
    : public generator_base<generator<YIELD_TYPE, RET_TYPE, SEND_TYPE>> {
  class promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  using generator_base<generator>::generator_base;

  generator(handle_type h) : coro_handle_(h) {}

  //! 协程句柄
  handle_type coro_handle_;

  bool send(const SEND_TYPE& send) {
    coro_handle_.promise().send_data_ = send;
    return generator_base<generator>::send_base();
  }

  RET_TYPE get_ret() { return coro_handle_.promise().return_data_; }
  YIELD_TYPE get_yield() { return coro_handle_.promise().yield_data_; }

  struct promise_type : public promise_type_base<promise_type> {
    template <class T>
    friend class suspend_always_send_value;
    void return_value(RET_TYPE v) { return_data_ = v; }
    auto yield_value(YIELD_TYPE v) {
      yield_data_ = v;
      return suspend_always_send_value(this);
    }
    auto get_return_object() {
      auto t = handle_type::from_promise(*this);
      return generator{t};
    }
    YIELD_TYPE yield_data_;
    RET_TYPE return_data_;
    SEND_TYPE send_data_;
  };
};
// 协程可以yield/return值给调用方, 调用方不可以传值给协程
template <typename YIELD_TYPE, typename RET_TYPE>
struct generator_yield_ret
    : public generator_base<generator_yield_ret<YIELD_TYPE, RET_TYPE>> {
  class promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  using generator_base<generator_yield_ret>::generator_base;

  generator_yield_ret(handle_type h) : coro_handle_(h) {}

  //! 协程句柄
  handle_type coro_handle_;

  bool send() { return generator_base<generator_yield_ret>::send_base(); }

  RET_TYPE get_ret() { return coro_handle_.promise().return_data_; }
  YIELD_TYPE get_yield() { return coro_handle_.promise().yield_data_; }

  struct promise_type : public promise_type_base<promise_type> {
    template <class T>
    void return_value(RET_TYPE v) { return_data_ = v; }
    auto yield_value() {
      yield_data_ = v;
      return std::suspend_always();
    }
    auto get_return_object() {
      auto t = handle_type::from_promise(*this);
      return generator_yield_ret{t};
    }
    YIELD_TYPE yield_data_;
    RET_TYPE return_data_;
  };
};
// 只是通知执行, 不进行值交换
struct generator_void : public generator_base<generator_void> {
  class promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  using generator_base<generator_void>::generator_base;

  generator_void(handle_type h) : coro_handle_(h) {}

  //! 协程句柄
  handle_type coro_handle_;

  bool send() { return generator_base<generator_void>::send_base(); }

  struct promise_type : public promise_type_base<promise_type> {
    template <class T>
    friend class suspend_always_send_value;
    void return_void() {}
    auto yield_value() { return std::suspend_always{}; }
    auto get_return_object() {
      auto t = handle_type::from_promise(*this);
      return generator_void{t};
    }
  };
};
// 协程可以yield/return值给调用方, 调用方不可以传值给协程
template <typename YIELD_TYPE>
struct generator_yield : public generator_base<generator_yield<YIELD_TYPE>> {
  class promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  using generator_base<generator_yield>::generator_base;

  generator_yield(handle_type h) : coro_handle_(h) {}

  //! 协程句柄
  handle_type coro_handle_;

  bool send() { return generator_base<generator_yield>::send_base(); }

  YIELD_TYPE get_yield() { return coro_handle_.promise().yield_data_; }

  struct promise_type : public promise_type_base<promise_type> {
    template <class T>
    friend class suspend_always_send_value;
    void return_void() {}
    auto yield_value(YIELD_TYPE v) {
      yield_data_ = v;
      return suspend_always_send_value(this);
    }
    auto get_return_object() {
      auto t = handle_type::from_promise(*this);
      return generator_yield{t};
    }
    YIELD_TYPE yield_data_;
  };
};
// 协程可以yield/return值给调用方, 调用方不可以传值给协程
template <typename RET_TYPE>
struct generator_ret : public generator_base<generator_ret<RET_TYPE>> {
  class promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  using generator_base<generator_ret>::generator_base;

  generator_ret(handle_type h) : coro_handle_(h) {}

  //! 协程句柄
  handle_type coro_handle_;

  bool send() { return generator_base<generator_ret>::send_base(); }

  RET_TYPE get_ret() { return coro_handle_.promise().return_data_; }

  struct promise_type : public promise_type_base<promise_type> {
    template <class T>
    friend class suspend_always_send_value;
    void return_value(RET_TYPE v) { return_data_ = v; }
    auto yield_value() { return suspend_always_send_value(this); }
    auto get_return_object() {
      auto t = handle_type::from_promise(*this);
      return generator_ret{t};
    }
    RET_TYPE return_data_;
  };
};
}  // namespace coro