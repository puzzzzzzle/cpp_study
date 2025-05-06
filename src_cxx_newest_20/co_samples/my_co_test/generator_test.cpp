//
// Created by khalidzhang on 2023/4/13.
//
#include "generator.h"

#include "common_includes.h"
using namespace coro;

// send test
generator_send<int> consumer() {
  while (true) {
    // co_yield void 目前的协程机制不支持
    auto n = co_yield 0;
    LOG_DEBUG(" -- consume : " << n)
  }
  co_return;
}
generator_void producer(generator_send<int>& c) {
  c.start();
  for (int i = 0; i < 5; ++i) {
    auto data = i + 1000;
    LOG_DEBUG(" -- produce: " << data)
    c.send(data);
  }
  co_return;
}
void consumer_producer_test() {
  auto c = consumer();
  auto p = producer(c);
  p.start();
}
TEST(generator, 1) { consumer_producer_test(); }
//
// yield  test
generator_yield<int> yield_value_test(int n) {
  for (int i = 0; i < n; ++i) {
    co_yield i;
  }
}

TEST(generator, yield) {
  auto c = yield_value_test(5);
  c.start();
  while (!c.done()) {
    LOG_DEBUG("yield " << c.get_yield())
    c.send();
  }
}

// all test
// yield , return, send
generator<std::string, int, double> all_test(int count) {
  int sum = 0;
  double send;
  for (int i = 0; i <= count; ++i) {
    send = co_yield std::to_string(send) + "_from_coro";
    sum += (int)send;
  }
  co_return sum;
}

TEST(generator, send) {
  auto c = all_test(5);
  c.start();
  int i = 0;
  while (!c.done()) {
    c.send(i+1000.001);
    ++i;
    LOG_DEBUG("yield " << c.get_yield())
  }
  LOG_DEBUG("return " << c.get_ret())
}
