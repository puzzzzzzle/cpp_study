//
// Created by khalidzhang on 2023/4/13.
//
#include "generator.h"

#include "common_includes.h"
using namespace coro;

// send test
generator<int,int, int> consumer() {
  while (true) {
    // co_yield void 就行 没意义 暂未适配void
    auto n = co_yield -1;
    LOG_DEBUG(" -- consume : " << n)
  }
  // co_return void 就行 没意义 暂未适配void
  co_return -1;
}
generator<int,int, int> producer(generator<int,int, int>& c) {
  c.start();
  for (int i = 0; i < 5; ++i) {
    auto data = i + 1000;
    LOG_DEBUG(" -- produce: " << data)
    c.send(data);
  }
  // co_return void 就行 没意义 暂未适配void
  co_return -1;
}
void consumer_producer_test() {
  auto c = consumer();
  auto p = producer(c);
  p.start();
}
TEST(generator, 1) { consumer_producer_test(); }
//
//// yield / return test
//generator<int, void> yield_value(int n) {
//  for (int i = 0; i < n; ++i) {
//    co_yield i;
//  }
//  co_return 1000;
//}
//TEST(generator, yield) {
//  auto c = yield_value(5);
//  c.start();
//  while (!c.done()) {
//     c.send();
//    LOG_DEBUG("yield " << c.get())
//  }
//}
