//
// Created by tao on 19-1-17.
//
#include "CommonClass.h"
#include "common_includes.h"

void to_leaf(long value){LOG_DEBUG(value)}

OperatorLogClass get_big_obj(long value) {
  to_leaf(value);
  OperatorLogClass obj{};
  return obj;
}
OperatorLogClass get_big_obj_1(long value) {
  return get_big_obj(value);
}
TEST(oper, 2) {
  auto obj = get_big_obj_1(42);
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