//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "stl_common_containor.h"
#include "common_funcs.h"

TEST(split, simple_1) {
  auto str = "hello_world_by_c++";
  auto vec = Split(str, "_");
  LOG_DEBUG("origin: " << str)
  LOG_DEBUG("split: " << vec)
}
TEST(test1, 1) {
  int size = 10;
  do {
    --size;
  } while (size > 3);
  LOG_DEBUG(size);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}