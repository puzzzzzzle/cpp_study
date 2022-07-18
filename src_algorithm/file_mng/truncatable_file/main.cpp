//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "time_gap.hpp"
#include "truncatable_file.h"
TEST(test_test, 1) {
  TruncatableFile tf{};
  ASSERT_EQ(tf.init("hello.txt"), 0);
  auto curr  = tf.read_all();
  LOG_DEBUG(curr)
//  ASSERT_EQ(tf.truncate_file(), 0);

  char buff[1024];
  TimeGap gap{};
  for (int i = 0; i < 1000; ++i) {
    snprintf(buff, sizeof(buff), "now at %d", i);
    ASSERT_EQ(tf.truncate_write(buff, strlen(buff)), 0);
  }
  LOG_DEBUG("total use " << gap.gap() << "\t" << gap.gapSec())
  auto all_data = tf.read_all();
  ASSERT_EQ(all_data, "now at 999");
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