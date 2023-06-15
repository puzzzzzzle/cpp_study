//
// Created by khalidzhang on 2020/6/20.
//

#pragma once
#include "assert.h"
#include "condition_variable"
#include "mutex"

class CyclicBarrier
{
  public:
  CyclicBarrier(size_t count) : m_count(count), m_waiting(0), m_generation(0) {}

  void wait()
  {
    std::unique_lock<std::mutex> lock(m_mutex);

    size_t gen = m_generation;

    ++m_waiting;
    if (m_waiting == m_count)
    {
      ++m_generation;
      m_waiting = 0;
      lock.unlock();
      m_cv.notify_all();
    }
    else
    {
      m_cv.wait(lock, [this, gen] { return gen != m_generation; });
    }
  }

  private:
  const size_t m_count;
  size_t m_waiting;
  size_t m_generation;
  std::mutex m_mutex;
  std::condition_variable m_cv;
};
using Barrier = CyclicBarrier;