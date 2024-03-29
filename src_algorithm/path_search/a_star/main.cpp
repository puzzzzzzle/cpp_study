//
// Created by tao on 19-1-17.
//
#define PAHT_DEBUG_INFO
#include "common_includes.h"
#include "a_star.h"
#include "path_find_common.h"

using PathFindType = PathSearch::AStar<DataType, Point>;
#include "path_find_test.h"


int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}