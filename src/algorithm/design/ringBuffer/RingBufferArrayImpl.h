//
// Created by tao zhang on 2020/2/17.
//

#pragma once

#include "RingBufferInterface.h"
#include <array>

template<class T>
class RingBufferArrayImpl : public RingBufferInterface<T> {
private:
    int capacity{};     //  为了方便起见冗余一份容量大小，反正也不会变
    std::unique_ptr<T[]> buffer{};
    volatile int head, tail;
public:
    RingBufferArrayImpl(int _capacity) : capacity(_capacity), head(0), tail(0) {
        buffer = std::unique_ptr<T[]>(new T[_capacity]);
    }

public:
    virtual int push(const T &) = 0;

    virtual void pop() = 0;

    virtual T front() {
        T tmp = m_data[m_front];
        m_front = (m_front + 1)%m_size;
    }

    virtual T back() = 0;

    virtual bool empty() {
        return tail == head;
    }

    virtual bool full(){
        return head==(tail+1)%capacity;
    }

    virtual size_t size() = 0;

    virtual size_t capacity() {
        return capacity;
    }
};