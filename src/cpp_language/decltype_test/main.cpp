//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "CommonClass.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
int ttt(){
  LOG_RAW_CLINE("call ttt")
}
int hhh();
OperatorLogClass get_obj()
{
  OperatorLogClass obj{};
  return obj;
}
OperatorLogClass get_obj_1()
{
  OperatorLogClass obj = get_obj();
  return obj;
}
int main(int argc, char **argv) {
  int iRet = 0;
  decltype(ttt()) i {};
  decltype(hhh()) j {};
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
//  testing::InitGoogleTest(&argc, argv);
//  iRet = RUN_ALL_TESTS();
  auto obj = get_obj_1();
  return iRet;
}