//
// Created by tao on 19-1-17.
//
#include <cstring>

#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

std::string getString() {
  char temp[64];
  snprintf(temp, sizeof(temp), "%s", "aha test!");
  return temp;
}
int main(int argc, char **argv) {
  int iRet = 0;
  LOG_DEBUG(getString())

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
#define TestGet(para)                      \
  LOG_DEBUG("find:\t" << (para) << "\t:\t" \
                      << FindParaEx(argc, argv, (para), "<not found>"))
  TestGet("--hp");
  TestGet("--bs");
  TestGet("ggg");
  TestGet("1545");
  return iRet;
}