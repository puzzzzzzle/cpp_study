//
// Created by tao on 19-1-17.
//
#define PAHT_DEBUG_INFO
#include "common_includes.h"
#include "jps.h"
#include "jps.hh"
#include "path_find_common.h"

using PathFindType = PathSearch::JPS<DataType, Point>;
#include "path_find_test.h"


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