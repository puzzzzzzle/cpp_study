//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "udp.h"
TEST(test_test, 1) {
  LOG_DEBUG(sizeof (sockaddr))
  LOG_DEBUG(sizeof (sockaddr_in))
  LOG_DEBUG(sizeof (sockaddr_in6))

  EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  int iRet = 0;
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}