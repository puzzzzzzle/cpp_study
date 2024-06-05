//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "funcs.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

void func1() { throw std::exception(); }
void func2() { func1(); }
void func3() { func2(); }
void func4() { func3(); }
void func5() { func4(); }

int main(int argc, char **argv) {
  int iRet = 0;
  malloc(10);
  try {
    func5();
  } catch (...) {
    LOG_INFO("----------- hook exceptions \n");
  }
  LOG_INFO("value from static lib " << zero());
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}