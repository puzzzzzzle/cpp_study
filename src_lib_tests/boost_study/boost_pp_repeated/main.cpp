//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

#include <boost/preprocessor/repetition/repeat.hpp>
#define DECL(z, n, text) text##_##n=10##n;
BOOST_PP_REPEAT(255, DECL, int x)


TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}