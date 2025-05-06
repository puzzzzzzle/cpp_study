//
// Created by tao on 19-1-17.
//
#include <iostream>

#include "common_includes.h"


int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}