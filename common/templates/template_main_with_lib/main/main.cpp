//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "test_func.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(test_test, 0) { EXPECT_EQ(0, zero()); }

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  INFO("logger inited")
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
    return iRet;
  }
  Hello h;
  h.hello();
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}