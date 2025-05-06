#include <generator>

#include "common_includes.h"
std::generator<int> num_range(int start, int end, int step = 1) {
  for (int i = start; i < end; i += step) {
    co_yield i;
  }
  co_return;
}
TEST(simple_num, 1) {
  for (auto i : num_range(10, 50, 5)) {
    LOG_DEBUG(i);
  }
  auto co = num_range(10, 50, 5);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}