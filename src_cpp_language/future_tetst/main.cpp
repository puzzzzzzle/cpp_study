/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2020/10/12
 * @file main.cpp
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

/*
我的理解中
 async -> packaged_task -> promise -> future
 future 必须依赖promise, 否则没有意义
 */
#include <future>

#include "common_includes.h"
#include "time_gap.hpp"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(promise, 1) {
  double dVal = 3.14;
  std::promise<double> pro{};
  // 注意 future 只能获取一次
  auto fu = pro.get_future();
  //  fu = pro.get_future(); // error
  auto producer = [&pro, dVal]() {
    TimeTools::SleepSec(2);
    pro.set_value(dVal);
  };
  std::thread pt(producer);
  LOG_DEBUG("start wait for result")
  auto ret = fu.get();
  LOG_DEBUG("get result " << ret << " with time ")
  //  fu.wait(); // get 后 不可以调用wait
  pt.join();
}
TEST(promise, 2) {
  double ret = 3.14;
  std::promise<double> pro{};
  // 注意 future 只能获取一次
  auto fu = pro.get_future();
  //  fu = pro.get_future(); // error
  auto producer = [&pro, ret]() {
    TimeTools::SleepSec(2);
    pro.set_value(ret);
  };
  std::thread pt(producer);
  LOG_DEBUG("start wait for result")
//  auto ret = fu.get();
//  LOG_DEBUG("get result " << ret << " with time ")
  fu.wait();  // wait / get 只能调用一次
  pt.join();
}

/**
 * 同步调用 task
 */
TEST(packaged_task, sync) {
  std::packaged_task<double(double)> task([](double seq) {
    TimeTools::SleepSec(2);
    return -1.0 / 12 * seq;
  });
  auto fu = task.get_future();
  LOG_DEBUG("before wait for result")
  task(3.14);
  LOG_DEBUG("start wait for result")
  auto ret = fu.get();
  LOG_DEBUG("get result " << ret << " with time ")
}
/**
 * 异步调用 task
 */
TEST(packaged_task, async) {
  std::packaged_task<double(double)> task([](double seq) {
    TimeTools::SleepSec(2);
    return -1.0 / 12 * seq;
  });
  auto fu = task.get_future();
  LOG_DEBUG("before wait for result")
  std::thread pt(std::move(task),3.14);
  LOG_DEBUG("start wait for result")
  auto ret = fu.get();
  LOG_DEBUG("get result " << ret << " with time ")
  pt.join();
}


TEST(async,async)
{
  auto fu = std::async(std::launch::async,[](){
    LOG_DEBUG("start get result "<< std::this_thread::get_id())
    TimeTools::SleepSec(2);
    return -1.0 / 12;
  });// 这里已经新起了线程执行
  LOG_DEBUG("start wait for result "<< std::this_thread::get_id())
  auto ret = fu.get();
  LOG_DEBUG("get result " << ret << " with time ")
}
TEST(async,defer_1)
{
  auto fu = std::async(std::launch::deferred,[](){
    LOG_DEBUG("start get result "<< std::this_thread::get_id())
    return -1.0 / 12;
  });// 这里还没有执行
  LOG_DEBUG("start wait for result "<< std::this_thread::get_id())
  TimeTools::SleepSec(2);
  auto ret = fu.get(); // 这里再同一个线程上执行
  LOG_DEBUG("get result " << ret << " with time ")
  std::cout<<std::endl;
}
TEST(async,defer_2)
{
  auto fu = std::async(std::launch::deferred,[](){
    LOG_DEBUG("start get result "<< std::this_thread::get_id())
    return -1.0 / 12;
  });// 这里还没有执行
  LOG_DEBUG("start wait for result "<< std::this_thread::get_id())
  auto ret = fu.get();// 这里再同一个线程上执行
  TimeTools::SleepSec(2);
  LOG_DEBUG("get result " << ret << " with time ")
  std::cout<<std::endl;
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}