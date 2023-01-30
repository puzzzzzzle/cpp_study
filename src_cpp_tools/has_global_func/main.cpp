//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "has_global_func.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

// 这一刻, 是不是存在 foo 函数, 之后再申明不管
HAS_GLOBAL_FUNC(foo)
// foo 没有声明
static_assert(!has_foo::check::value);
// 申明foo
void foo();
// 在 HAS_GLOBAL_FUNC(foo) 已经绑定了, foo还是不存在
static_assert(!has_foo::check::value);

// 声明一个func
void func();
HAS_GLOBAL_FUNC(func)
static_assert(has_func::check::value);

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}