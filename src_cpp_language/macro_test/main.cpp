//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "def.h"
#include "inc1.h"
#include "inc2.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

#define TEST_MACRO_FUNC(msg) LOG_DEBUG(msg)

#define IF_TRUE_ACTION(cond,action,args...) if(cond){ \
    LOG_DEBUG(args);                                                  \
    action;                                           \
  }
int main(int argc, char **argv) {
  DefTest defTest{};
  Inc1Test inc1Test{};
  Inc2Test inc2Test{};
  defTest.test();
  inc1Test.test();
  inc2Test.test();
  IF_TRUE_ACTION(true,return 0,"")

#ifdef TEST_MACRO_FUNC
  TEST_MACRO_FUNC("has TEST_MACRO_FUNC")
#endif
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}