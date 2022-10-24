//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "delay_array.h"

TEST(delay_array,1)
{
  delay_array::delay_array<int,10> a1{};
  std::vector<int>::iterator it{};
  for (auto i : a1)
  {
    LOG_DEBUG(i)
  }
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