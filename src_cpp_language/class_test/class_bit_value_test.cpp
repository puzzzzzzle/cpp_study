//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

namespace ClassBitValueTests {
struct MyType {
  int index = 1;
  int index2 : 8;  // 占用8个bit(1 char)，无法使用sizeof操作符
  int index3{3};
};

class MyClass {
  public:
  int index = 1;
  int index2 : 8;  // 占用8个bit，无法使用sizeof操作符
  int index3{3};
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
TEST(ClassBitValueTests, struct) {
  MyType type;
  LOG_INFO("default " << type.index2)

  EXPECT_EQ(type.index, 1);
  //    EXPECT_EQ( type.index2, 0);
  EXPECT_EQ(type.index3, 3);

  type.index2 = 127;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, 127);

  type.index2 = 128;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, -128);
  EXPECT_NE(type.index2, 128);

  type.index2 = 255;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, -1);
  EXPECT_NE(type.index2, 255);

  type.index2 = 256;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, 0);
  EXPECT_NE(type.index2, 256);

  EXPECT_EQ(type.index, 1);
  EXPECT_EQ(type.index3, 3);
}
TEST(ClassBitValueTests, class) {
  MyClass type;
  LOG_INFO("default " << type.index2)

  EXPECT_EQ(type.index, 1);
  //    EXPECT_EQ( type.index2, 0);
  EXPECT_EQ(type.index3, 3);

  type.index2 = 127;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, 127);

  type.index2 = 128;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, -128);
  EXPECT_NE(type.index2, 128);

  type.index2 = 255;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, -1);
  EXPECT_NE(type.index2, 255);

  type.index2 = 256;
  LOG_INFO(type.index2)
  EXPECT_EQ(type.index2, 0);
  EXPECT_NE(type.index2, 256);

  EXPECT_EQ(type.index, 1);
  EXPECT_EQ(type.index3, 3);
}
#pragma GCC diagnostic pop
}  // namespace StructTest
