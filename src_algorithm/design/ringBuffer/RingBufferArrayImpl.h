//
// Created by tao zhang on 2020/2/17.
//

#pragma once

#include <array>
#include <memory>
#include "RingBufferInterface.h"
template <class T>
class RingBufferArrayImpl : public RingBufferInterface<T> {
  private:
  int capacity{};
  std::unique_ptr<T[]> buffer{};
  volatile int front, back;

  public:
  RingBufferArrayImpl(int _capacity)
      : capacity(_capacity + 1), front(0), back(0) {
    buffer = std::unique_ptr<T[]>(new T[capacity]);
  }

  public:
  virtual int Push(const T &item) {
    if (Full()) {
      return -1;
    }
    buffer[back] = item;
    back = (back + 1) % capacity;
    return 0;
  }

  virtual void Pop() { front = (front + 1) % capacity; }

  virtual T Front() { return buffer[front]; }

  virtual bool Empty() { return front == back; }

  virtual bool Full() { return front == (back + 1) % capacity; }

  virtual size_t Size() { return ((back + capacity) - front) % capacity; }

  virtual size_t Capacity() { return capacity - 1; }
};