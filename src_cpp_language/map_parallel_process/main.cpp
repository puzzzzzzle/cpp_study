//
// Created by tao on 19-1-17.
//
#include <unordered_map>

#include "common_includes.h"
#include "time_gap.hpp"
TEST(test_test, 1) {
  std::map<int, int> typeMapRef;
  size_t threadGap = 100;
  for (int i = 0; i < 1024; ++i) {
    typeMapRef[i] = i;
  }
  using IteratorType = decltype(typeMapRef)::iterator;

  auto size = typeMapRef.size();
  auto beginIt = typeMapRef.begin();
  auto endIt = beginIt;
  auto process = [&typeMapRef](IteratorType beginIt, IteratorType endIt) {
    LOG_DEBUG("start at " << beginIt->first
                          << "\t end at] :" << (--endIt)->first)
  };
  while (size > 0) {
    auto diff = std::min(size, threadGap);
    size -= diff;
    std::advance(endIt, diff);
    process(beginIt, endIt);
    beginIt = endIt;
  }
}
TEST(test_test, 2) {
  TimeGap gap{};
  int diffGap = 100000;
  int max = 100 * diffGap;
  {
    gap.resetStartNow();
    std::map<int, int> map_data;
    for (int i = 0; i < max; ++i) {
      map_data[i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
  {
    gap.resetStartNow();
    std::map<int, std::map<int, int>> map_data;
    for (int i = 0; i < max; ++i) {
      map_data[(int)(i % diffGap)][i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
}
struct EnumClassHash {
  template <typename T>
  size_t operator()(T t) const {
    return static_cast<size_t>(t);
  }
};
TEST(test_test, 3) {
  TimeGap gap{};
  int diffGap = 100000;
  int max = 100 * diffGap;
  {
    gap.resetStartNow();
    std::unordered_map<int, int> map_data;
    for (int i = 0; i < max; ++i) {
      map_data[i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
  {
    gap.resetStartNow();
    std::unordered_map<int, std::unordered_map<int, int>> map_data;
    for (int i = 0; i < max; ++i) {
      map_data[(int)(i % diffGap)][i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
}

TEST(test_test, 4) {
  TimeGap gap{};
  int diffGap = 10000;
  int max = 1000 * diffGap;
  std::vector<int> data_vec{};
  {
    for (int i = 0; i < max; ++i) {
      data_vec.push_back(rand());
    }
  }
  {
    gap.resetStartNow();
    std::unordered_map<int, int> map_data;
    for (auto i : data_vec) {
      map_data[i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
  {
    gap.resetStartNow();
    std::unordered_map<int, std::unordered_map<int, int>> map_data;
    for (auto i : data_vec) {
      map_data[(int)(i % diffGap)][i] = i;
    }
    LOG_DEBUG("one " << gap.gap() << "\tsec" << gap.gapSec())
  }
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