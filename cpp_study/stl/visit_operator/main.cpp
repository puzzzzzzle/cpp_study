//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <array>
#include <map>

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
TEST(map, at_operator) {
  std::map<int, int> testMap{};
  // begin cbegin 是同一个值,只是房屋权限不同
  EXPECT_EQ(testMap.cbegin(), testMap.begin());
  auto it = testMap.find(1);
  // 还没插入,找不到
  EXPECT_EQ(it, testMap.cend());
  EXPECT_EQ(it, testMap.end());

  // 虽然没有,但是访问过后就被初始化了
  LOG_DEBUG("after visit will be set to  " << testMap[1])

  // 这次能找到
  it = testMap.find(1);
  // 存在了,尽管没有插入
  EXPECT_NE(it, testMap.cend());
  EXPECT_NE(it, testMap.end());
}

TEST(array, at_operator) {
  // 不调用初始化
  // 有几率没有初始化
  {
    bool isBreak = false;
    std::array<int, 1000> testArray;
    for (const auto &i : testArray) {
      if (i != 0) {
        isBreak = true;
        break;
      }
    }
    EXPECT_TRUE(isBreak);
  }
  {
    bool isBreak = false;
    int arrRow[1000];
    isBreak = false;
    for (const auto &i : arrRow) {
      if (i != 0) {
        isBreak = true;
        break;
      }
    }
    EXPECT_TRUE(isBreak);
  }
  // 初始化列表初始化
  {
    bool isBreak = false;
    std::array<int, 1000> testArray{};
    for (const auto &i : testArray) {
      if (i != 0) {
        isBreak = true;
        break;
      }
    }
    EXPECT_FALSE(isBreak);
  }
  {
    bool isBreak = false;
    int arrRow[1000]{};
    isBreak = false;
    for (const auto &i : arrRow) {
      if (i != 0) {
        isBreak = true;
        break;
      }
    }
    EXPECT_FALSE(isBreak);
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
  return iRet;
}