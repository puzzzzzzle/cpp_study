//
// Created by tao on 19-1-17.
//
#include "common_classes.h"
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char** argv) {
  int iRet = 0;
  auto scope =
      MakeScopeGuard([]() -> void { LOG_DEBUG("run after exit scope") });

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}