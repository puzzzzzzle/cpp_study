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
  int waitNum = 5, checkNum = 1000000;
  std::atomic_int flag(0);
  //  std::vector<AutoJoinThreadGuard> ts{};

  Barrier barrier(waitNum);

  for (int loop = 0; loop < checkNum; ++loop) {
    std::vector<std::thread> ts{};
    //    LOG_RAW_CLINE("one loop start!")
    for (int i = 0; i < waitNum - 1; ++i) {
      ts.emplace_back([&barrier, &flag]() {
        //        sleep(1);
        //        LOG_RAW_CLINE("before wait!")
        flag += 1;
        barrier.wait();
        //        LOG_RAW_CLINE("after wait!")
      });
    }
    //    LOG_RAW_CLINE("main wait one loop finish!")
    barrier.wait();
    assert(flag == 4);
    flag = 0;
    for (auto &t : ts) {
      if (t.joinable()) {
        t.join();
      }
    }
    if (loop % 10000 == 0) {
      LOG_RAW_CLINE("loop finish!" << loop)
    }
    //    LOG_RAW_CLINE("one loop finish!" << loop)
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