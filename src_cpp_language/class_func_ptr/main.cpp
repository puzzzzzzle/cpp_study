//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "time_gap.hpp"
class UndefinedClass;
class DefinedClass {};

TEST(test_test, 1) {
  int i = 1;
  LOG_DEBUG(sizeof(&i))

  void (DefinedClass::*d_f)();
  LOG_DEBUG(sizeof(d_f))
  void (UndefinedClass::*ud_f)();
  LOG_DEBUG(sizeof(ud_f))
}

struct TestFunc {
  // friend 默认为static的
  friend void set_v(TestFunc &c, int v) { c.v_ = v; }

  private:
  int v_{};
};

TEST(friend_func, 1)
{
  TestFunc t{};
  // t 会把 TestFunc:: 也加入搜索范围
  set_v(t,1);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}