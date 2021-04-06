//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

#include <boost/preprocessor/repetition/repeat.hpp>
#define DECL(z, n, text) text##220##n=10##n;
BOOST_PP_REPEAT(255, DECL, int x)


TEST(test_test, 1) { EXPECT_EQ(1, 1); }

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