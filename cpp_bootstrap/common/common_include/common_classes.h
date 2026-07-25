/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/5/24
 * @file common_classes.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#pragma once
#include <cstdlib>
#include <functional>
#include <mutex>

#include "thread"

template <class Function>
class ScopeGuard {
  private:
  Function m_func;
  bool m_dismiss{false};

  public:
  explicit ScopeGuard(Function func) : m_func(func), m_dismiss(false) {}
  ~ScopeGuard() {
    if (!m_dismiss) m_func();
  }
  ScopeGuard() = delete;
  ScopeGuard(const ScopeGuard&) = delete;
  ScopeGuard& operator=(const ScopeGuard&) = delete;

  void dismiss() { m_dismiss = true; }

  ScopeGuard(ScopeGuard&& rhs)
      : m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss) {
    rhs.dismiss();
  }
};
template <class Fun>
ScopeGuard<Fun> MakeScopeGuard(Fun f) {
  return ScopeGuard<Fun>(std::move(f));
}

class AutoJoinThreadGuard {
  private:
  std::thread t;

  public:
  AutoJoinThreadGuard(std::function<void()> func) : t(func) {}
  AutoJoinThreadGuard(AutoJoinThreadGuard&) = delete;
  AutoJoinThreadGuard(AutoJoinThreadGuard&& guard) : t(std::move(guard.t)) {}
  ~AutoJoinThreadGuard() {
    if (t.joinable()) {
      printf("join");
      t.join();
    }
  }
};