//
// Created by tao on 19-1-17.
//
#include <coroutine>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <thread>

#if true
#include "common_includes.h"
#else
#define LOG_DEBUG(msg)
#endif

struct awaitable_t {
  awaitable_t() { LOG_DEBUG("- call : " << __PRETTY_FUNCTION__) }
  ~awaitable_t() { LOG_DEBUG("- call : " << __PRETTY_FUNCTION__) }
  bool await_ready() {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
    return false;
  }
  void await_suspend(std::coroutine_handle<> h) {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
  }
  void await_resume() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
};
struct promise_t;
using handle_t = std::coroutine_handle<promise_t>;
struct task_t {
  using promise_type = promise_t;
  task_t(const handle_t& h) : h_(h) {
    LOG_DEBUG("- call : " << __PRETTY_FUNCTION__)
  }
  ~task_t() {
    // final_suspend suspend_always 时需要手动销毁, suspend_never时会自动销毁
    h_.destroy();
    LOG_DEBUG("- call : " << __PRETTY_FUNCTION__)
  }
  handle_t h_{};
};

struct promise_t {
  promise_t() { LOG_DEBUG("- call : " << __PRETTY_FUNCTION__) }
  ~promise_t(){LOG_DEBUG("- call : " << __PRETTY_FUNCTION__)}

  task_t get_return_object() {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
    return handle_t::from_promise(*this);
  }
  std::suspend_always initial_suspend() {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
    return {};
  }
  std::suspend_always final_suspend() noexcept {
    LOG_DEBUG("call : " << __PRETTY_FUNCTION__)
    return {};
  }
  void destroy() const noexcept { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }

  void return_void() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
  void unhandled_exception() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
};

auto resume_latter() -> task_t {
  LOG_DEBUG("start resume_latter")
  // 生成 等待体, 但是不执行
  auto awaitable_t_var = awaitable_t{};
  LOG_DEBUG("awaitable_t_var")
  // 执行 完 await_ready await_suspend 后 这个函数直接返回一个 task_t
  // 对象到调用者上
  co_await awaitable_t_var;
  LOG_DEBUG("co_await")

  // 这个并不会被立即执行 需要等 协程 resume 后才会
  LOG_DEBUG("end resume_latter")
  co_return;
}
void run_coroutine() {
  LOG_DEBUG("start call coroutine")
  auto t = resume_latter();
  LOG_DEBUG("is done " << (int)t.h_.done())
  while (!t.h_.done()) {
    LOG_DEBUG("start resume coroutine")
    t.h_.resume();
    LOG_DEBUG("end resume coroutine")
    LOG_DEBUG("is done " << (int)t.h_.done())
  }
  LOG_DEBUG("end run_coroutine")
  // 不用destroy
  //  t.h_.destroy();
}
int main(int argc, char** argv) {
  run_coroutine();
  return 0;
}
/*
[DEBUG]    [2022-05-19 07:53:00]    [start call coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:80    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : promise_t::promise_t()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:44    promise_t::promise_t()]
[DEBUG]    [2022-05-19 07:53:00]    [call : task_t promise_t::get_return_object()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:48    task_t promise_t::get_return_object()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : task_t::task_t(const handle_t&)]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:33    task_t::task_t(const handle_t&)]
[DEBUG]    [2022-05-19 07:53:00]    [call : std::__n4861::suspend_always promise_t::initial_suspend()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:52    std::__n4861::suspend_always promise_t::initial_suspend()]
[DEBUG]    [2022-05-19 07:53:00]    [is done 0]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:82    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [start resume coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:84    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [start resume_latter]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:66    task_t resume_latter()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : awaitable_t::awaitable_t()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:17    awaitable_t::awaitable_t()]
[DEBUG]    [2022-05-19 07:53:00]    [awaitable_t_var]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:69    task_t resume_latter()]
[DEBUG]    [2022-05-19 07:53:00]    [call : bool awaitable_t::await_ready()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:20    bool awaitable_t::await_ready()]
[DEBUG]    [2022-05-19 07:53:00]    [call : void awaitable_t::await_suspend(std::__n4861::coroutine_handle<void>)]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:24    void awaitable_t::await_suspend(std::__n4861::coroutine_handle<void>)]
[DEBUG]    [2022-05-19 07:53:00]    [end resume coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:86    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [is done 0]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:87    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [start resume coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:84    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [call : void awaitable_t::await_resume()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:26    void awaitable_t::await_resume()]
[DEBUG]    [2022-05-19 07:53:00]    [co_await]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:73    task_t resume_latter()]
[DEBUG]    [2022-05-19 07:53:00]    [end resume_latter]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:76    task_t resume_latter()]
[DEBUG]    [2022-05-19 07:53:00]    [call : void promise_t::return_void()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:61    void promise_t::return_void()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : awaitable_t::~awaitable_t()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:18    awaitable_t::~awaitable_t()]
[DEBUG]    [2022-05-19 07:53:00]    [call : std::__n4861::suspend_always promise_t::final_suspend()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:56    std::__n4861::suspend_always promise_t::final_suspend()]
[DEBUG]    [2022-05-19 07:53:00]    [end resume coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:86    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [is done 1]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:87    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [end run_coroutine]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:89    void run_coroutine()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : promise_t::~promise_t()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:45    promise_t::~promise_t()]
[DEBUG]    [2022-05-19 07:53:00]    [- call : task_t::~task_t()]   [/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:38    task_t::~task_t()]

Process finished with exit code 0


Process finished with exit code 0

 */