//
// Created by tao on 19-1-17.
//
#include <boost/circular_buffer.hpp>

#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(circular_buffer, 1) {
  boost::circular_buffer<int> buffer{};
  buffer.push_back(1);
  //    auto i = buffer.pop_back();
  //     i =buffer.pop_back();
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}