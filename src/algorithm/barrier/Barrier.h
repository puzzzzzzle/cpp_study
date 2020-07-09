//
// Created by khalidzhang on 2020/6/20.
//

#pragma once
#include "assert.h"
#include "condition_variable"
#include "mutex"

class Barrier {
  private:
  std::size_t m_initial;
  std::size_t m_current;
  std::size_t m_cycle{0};
  std::mutex m_mtx{};
  std::condition_variable m_cond{};

  public:
  explicit Barrier(std::size_t initial)
      : m_initial{initial}, m_current{m_initial} {
    assert(initial != 0);
  }

  Barrier(Barrier const&) = delete;
  Barrier& operator=(Barrier const&) = delete;

  bool wait() {
    //    printf("a:%lu\n", m_current);
    std::unique_lock<std::mutex> lk{m_mtx};
    const std::size_t cycle = m_cycle;
    //    printf("b: %lu\n", m_current);
    if (0 == --m_current) {
      //      printf("c: %lu\n", m_current);
      ++m_cycle;
      m_current = m_initial;
      lk.unlock();  // no pessimization
      m_cond.notify_all();
      //      printf("d: %lu\n", m_current);

      return true;
    }
    //    printf("e: %lu\n", m_current);
    m_cond.wait(lk, [&] { return cycle != m_cycle; });
    //    printf("f: %lu\n", m_current);

    return false;
  }
};
