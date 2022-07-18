//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "optimization_bresenham.h"

TEST(test_test, 1) {
  EXPECT_EQ(1, 1);
  useVisionLine(-5, -5, 70, 100,
                [](int y, int x) { printf(R"({"x":%d,"y":%d})", (x), (y)); });
  printf("\n");
  useVisionLine(-70, 100, 5, -5,
                [](int y, int x) { printf(R"({"x":%d,"y":%d})", (x), (y)); });
  printf("\n%f\n",pow(2,2));
  printf("\n%f\n",sqrt(5));


  printf("\natan2 :%f\n",atan2(1,-1));
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