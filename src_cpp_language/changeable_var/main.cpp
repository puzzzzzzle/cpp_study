//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>
#include <stdarg.h>

#include <thread>
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
/**
 * 测试可变参数
 * @param argc 可变参数数量
 * @param ... 可变参数表
 * @return 接收到的可变参数数量
 */
int test_changeable_var(int argc, ...) {
  int count{};
  const char *line{};

  va_list args{};

  va_start(args, argc);

  while (argc > 0) {
    line = va_arg(args, const char *);
    ++count;
    --argc;
    LOG_INFO("get args:\t" << line)
  }
  va_end(args);
  return count;
}
TEST(changeable_args, 0) {
  int count = test_changeable_var(0);
  EXPECT_EQ(count, 0);
}
TEST(changeable_args, 1) {
  int count = test_changeable_var(1, "hello");
  EXPECT_EQ(count, 1);
}
TEST(changeable_args, 3) {
  int count = test_changeable_var(3, "hello", "i'm tao!", "bye bye!");
  EXPECT_EQ(count, 3);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}