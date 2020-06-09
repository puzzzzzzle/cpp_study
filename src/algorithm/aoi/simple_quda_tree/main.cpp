//
// Created by tao on 19-1-17.
//
#include "QuadTree.h"
#include "common_includes.h"

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
    return iRet;
  }

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}