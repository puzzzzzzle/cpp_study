//
// Created by tao on 19-1-17.
//
#include <future>

#include "common_includes.h"

template <class RetType, class Cond>
std::pair<bool, std::vector<RetType>> WhenAllIf(
    std::vector<std::future<RetType>> &tasks, Cond cond) {
  bool allSuccess{true};
  std::vector<RetType> results{};
  for (auto &futureTask : tasks) {
    futureTask.wait();
    auto result = futureTask.get();
    results.push_back(result);
    if (!cond(result)) {
      LOG_ERROR("one task fail ")
      allSuccess = false;
    }
  }
  return {allSuccess, std::move(results)};
}

TEST(when_all, 1) {
  int workersNum = 10;
  std::vector<std::future<int>> startFus{};
  for (int i = 0; i < workersNum; ++i) {
    //    startFus.push_back(worker->InitAndStart());
    startFus.push_back(std::async(std::launch::async, [i]() -> int {
      LOG_WARNING("call " << i << "\t" << std::this_thread::get_id())
      return i % 5;
    }));
  }
  auto func = [](int initRet) -> bool { return initRet != 0; };
  auto ret1 = WhenAllIf(startFus, func);

  LOG_WARNING("called " << workersNum << "\tret: " << "\t" << ret1)
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}