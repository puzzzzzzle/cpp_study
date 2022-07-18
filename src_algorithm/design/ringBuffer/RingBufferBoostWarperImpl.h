//
// Created by tao zhang on 2020/2/17.
// 简单的ring buffer，按照对象存储，不支持动态大小
//

#include <boost/circular_buffer.hpp>

#include "RingBufferInterface.h"

#pragma once

template <class T>
class RingBufferBoostWarper : public RingBufferInterface<T> {
  private:
  boost::circular_buffer<T> circularBuffer;

  public:
  RingBufferBoostWarper(int Capacity) : circularBuffer(Capacity) {}

  public:
  virtual int Push(const T& item) {
    if (circularBuffer.full()) {
      return -1;
    }
    circularBuffer.push_back(item);
    return 0;
  }

  virtual void Pop() { circularBuffer.pop_front(); }

  virtual T Front() { return circularBuffer.front(); }

  virtual bool Empty() { return circularBuffer.empty(); }

  virtual bool Full() { return circularBuffer.full(); }

  virtual size_t Size() { return circularBuffer.size(); }

  virtual size_t Capacity() { return circularBuffer.capacity(); }
};
