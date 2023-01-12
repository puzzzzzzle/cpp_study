//
// Created by tao on 19-1-17.
//
#include "group_tasks.h"
#include "common_includes.h"
TEST(test_test, 1) {
  std::atomic<std::shared_ptr<int>> destroyed_call_back{};
  destroyed_call_back = std::make_shared<int>(100);
  LOG_DEBUG(*destroyed_call_back.load());

}

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}