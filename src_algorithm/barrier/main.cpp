//
// Created by tao on 19-1-17.
//
#include <atomic>
#include <time_gap.hpp>

#include "Barrier.h"
#include "atomic"
#include "common_classes.h"
#include "common_includes.h"

void TestBarrer() {
  int waitNum = 11, checkNum = 10000;

  Barrier barrier(waitNum);

  for (int loop = 0; loop < checkNum; ++loop) {
    std::atomic_int flag(0);
    std::vector<std::thread> ts{};


    for (int i = 0; i < waitNum -1; ++i) {
      ts.emplace_back([&barrier, &flag]() {
        flag += 1;
        barrier.wait();
      });
    }
    barrier.wait();
    assert(flag == 10);

    for (int i = 0; i < waitNum -1; ++i) {
      ts.emplace_back([&barrier, &flag]() {
        flag += 1;
        barrier.wait();
      });
    }
    barrier.wait();
    assert(flag == 20);

    for (int i = 0; i < waitNum -1; ++i) {
      ts.emplace_back([&barrier, &flag]() {
        flag += 1;
        barrier.wait();
      });
    }
    barrier.wait();
    assert(flag == 30);


    for (auto &t : ts) {
      if (t.joinable()) {
        t.join();
      }
    }
    if (loop % 1000 == 0) {
      LOG_RAW_CLINE("loop finish!" << loop)
    }
  }

  LOG_RAW_CLINE("leave")
}
TEST(test_test, 1) {}

int main(int argc, char **argv) {
  int iRet = 0;
  TestBarrer();

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}