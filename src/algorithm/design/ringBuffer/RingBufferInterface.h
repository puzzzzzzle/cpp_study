//
// Created by tao zhang on 2020/2/17.
//

#pragma once

#include <utility>

template<class T>
class RingBufferInterface {
public:
    virtual int Push(const T &) = 0;

    virtual void Pop() = 0;

    virtual T Front() = 0;

    virtual bool Empty() = 0;

    virtual bool Full() = 0;

    virtual size_t Size() = 0;

    virtual size_t Capacity() = 0;
};
