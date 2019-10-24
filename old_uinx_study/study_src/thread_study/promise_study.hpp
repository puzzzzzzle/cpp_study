//
// Created by tao on 18-11-29.
//

#ifndef UNIXSTUDYCPP_PROMISE_STUDY_HPP
#define UNIXSTUDYCPP_PROMISE_STUDY_HPP

#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
// future example
#include <chrono>               // std::chrono::milliseconds
#include <unistd.h>

#include "../public_object/people.hpp"

void print_int(std::future<int> &fut) {
    int x = fut.get(); // 获取共享状态的值.
    std::cout << std::this_thread::get_id();
    std::cout << std::endl;


    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

int promise_main() {
    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.
    std::thread t1(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.
    std::thread t2(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.

    sleep(3);


    prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
    t1.join();
    t2.join();
    return 0;
}


// a non-optimized way of checking for prime numbers:
bool
is_prime(int x) {
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

int
future_main() {
    // call function asynchronously:
    std::future<bool> fut = std::async(is_prime, 444444443);

    // do something while waiting for function to set future:
    std::cout << "checking, please wait";
    std::chrono::milliseconds span(100);
    while (fut.wait_for(span) == std::future_status::timeout) {
        std::cout << '.';
        std::cout << std::flush;
    }
    bool x = fut.get();         // retrieve return value

    std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";

    return 0;
}

int thresd_task_main() {
    future_main();
    std::cout << "people\t" << sizeof(People) << std::endl;
    return 0;
}

#endif //UNIXSTUDYCPP_PROMISE_STUDY_HPP
