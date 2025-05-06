//
// Created by user on 10/16/24.
//
#include <arpa/inet.h>

#include <iostream>
#include <unifex/just.hpp>
#include <unifex/static_thread_pool.hpp>
#include <unifex/sync_wait.hpp>
#include <unifex/task.hpp>
#include <unifex/then.hpp>

#include "common_includes.h"

using namespace unifex;

task<int> async_add(int a, int b) { co_return a + b; }

task<void> example() {
  int result = co_await async_add(3, 4);
  LOG_DEBUG("Result: " << result)
}

//TEST(test_simple_co, 2) {
//  // 创建一个包含4个线程的线程池
//  unifex::static_thread_pool threadPool{4};
//
//  // 获取线程池的调度器
//  auto scheduler = threadPool.get_scheduler();
//
//  // 创建一个简单的任务
//  auto task = unifex::then(
//      unifex::just(),
//      []() {
//        std::cout << "Task is running on a thread from the thread pool." << std::endl;
//      }
//  );
//
//  // 提交任务到线程池并等待其完成
//  unifex::sync_wait(unifex::schedule(scheduler) | std::move(task));
//}
