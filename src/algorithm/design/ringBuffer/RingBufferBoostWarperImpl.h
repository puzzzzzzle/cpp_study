//
// Created by tao zhang on 2020/2/17.
// 简单的ring buffer，按照对象存储，不支持动态大小
//

#include "RingBufferInterface.h"
#include <boost/circular_buffer.hpp>

#pragma once

template<class T>
class RingBufferBoostWarper : public RingBufferInterface<T> {
private:
    boost::circular_buffer<T> circularBuffer;
public:
    RingBufferBoostWarper(int capacity) : circularBuffer(capacity) {

    }

public:
    virtual int push(const T & item) {
        if(circularBuffer.full()){
            return -1;
        }
        circularBuffer.push_back(item);
        return 0;
    }

    virtual void pop() {
        circularBuffer.pop_front();
    }

    virtual T front() {
        return circularBuffer.front();
    }

    virtual T back() {
        return circularBuffer.back();
    }

    virtual bool empty() {
        return circularBuffer.empty();
    }

    virtual bool full() {
        return circularBuffer.full();
    }

    virtual size_t size() {
        return circularBuffer.size();
    }

    virtual size_t capacity() {
        return circularBuffer.capacity();
    }
};

