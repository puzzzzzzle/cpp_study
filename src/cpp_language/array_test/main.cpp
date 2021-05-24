//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
TEST(arrayTest, 1) {
  // (,) 表达式的结果是后一个的值,
  int i = (1, 2);
  LOG_DEBUG(i);
  //  int array[3][3] = [[1, 2, 3], [ 4, 5, 6 ], [ 7, 8, 9 ]];
  int **array{};
  int row = 3;
  int col = 3;
  array = new int *[row];
  for (int r = 0; r < row; ++r) {
    array[r] = new int[col];
    for (int c = 0; c < col; ++c) {
      array[r][c] = r * col + c +1;
    }
  }
  LOG_DEBUG((array[1, 2]))
  LOG_DEBUG(array[2])

  LOG_DEBUG((*array[1, 2]))
}
TEST(arrayTest, 2) {
  int i = (1, 2);
  LOG_DEBUG(i);
    int array[3][3] = {{1, 2, 3}, { 4, 5, 6 }, { 7, 8, 9 }};
  LOG_DEBUG(&(array[1, 2]))
  LOG_DEBUG(&array[2])
  LOG_DEBUG((*array[1, 2]))
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