//
// Created by tao on 19-1-17.
//
#include <inttypes.h>
#include <stdio.h>

#include "common_includes.h"

extern "C" int64_t maxofthree(int64_t, int64_t, int64_t);

TEST(test_test, 1) {
  EXPECT_EQ(maxofthree(1, -4, -7), 1);
  EXPECT_EQ(maxofthree(2, -6, 1), 2);
  EXPECT_EQ(maxofthree(2, 3, 1), 3);
  EXPECT_EQ(maxofthree(-2, 4, 3), 4);
  EXPECT_EQ(maxofthree(2, -6, 5), 5);
  EXPECT_EQ(maxofthree(2, 4, 6), 6);
  EXPECT_EQ(1, 1);
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