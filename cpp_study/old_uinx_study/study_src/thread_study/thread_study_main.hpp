//
// Created by tao on 18-11-28.
//

#ifndef UNIXSTUDYCPP_THREAD_STUDY_MAIN_H
#define UNIXSTUDYCPP_THREAD_STUDY_MAIN_H

#include <unistd.h>

#include <iostream>
#include <thread>

#include "../log4cplus_init/log_macro.h"
#include "mutex_test.hpp"

using namespace std;

/// base test
void thread_test_1() {
    std::thread t1([]() {
        sleep(2);
        TRACE("hello from another thread!");
    });
    TRACE("hello from main!");
    t1.join();
}

/// test data transform
void work_func(const string &str) {
    cout << str << endl;
}

void thread_test_wrong_data() {
    char buff[100];
    snprintf(buff, sizeof(buff), "hello world!");
    std::thread t1(work_func, buff);
    t1.detach();
}

void thread_test_right_data() {
    char buff[100];
    snprintf(buff, sizeof(buff), "hello world!");
    // thread 接受拷贝的值，传入char *时拷贝地址，但是main提前结束，地址释放！
    std::thread t1(work_func, string(buff));
    t1.detach();
}

/// test thread guard
class thread_guard {
private:
    std::thread &t;

public:
    thread_guard(std::thread &_t) : t(_t) {}

    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(std::thread const &) = delete;

    thread_guard &operator=(thread_guard &) = delete;
};

void test_thread_guard() {
    std::thread  t([]() {
        sleep(2);
        TRACE("msg from thread :\t" << std::this_thread::get_id());
    });
    thread_guard g(t);
    TRACE("msg from main :\t" << std::this_thread::get_id());
}

/// main
void thread_study_main() {
    //    thread_test_wrong_data();
    //    test_thread_guard();
    mutex_test();
}

#endif  // UNIXSTUDYCPP_THREAD_STUDY_MAIN_H
