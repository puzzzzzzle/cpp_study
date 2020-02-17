//
// Created by tao zhang on 2020/2/17.
//

#pragma once

#include <utility>

template<class T>
class RingBufferInterface {
public:
    virtual int push(const T &) = 0;

    virtual void pop() = 0;

    virtual T front() = 0;

    virtual T back() = 0;

    virtual bool empty() = 0;

    virtual bool full() = 0;

    virtual size_t size() = 0;

    virtual size_t capacity() = 0;
};
