//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#pragma region R_1


#pragma endregion


#define VALUE 100

int get_value_1() { return VALUE; }

#pragma push_macro("VALUE")
#undef VALUE
#define VALUE 42
int get_value_2() { return VALUE; }
#pragma pop_macro("VALUE")

int get_value_3() { return VALUE; }

TEST(macro, 1) {
  LOG_DEBUG(get_value_1())
  LOG_DEBUG(get_value_2())
  LOG_DEBUG(get_value_3())


  ASSERT_EQ(100, get_value_1());
  ASSERT_EQ(42, get_value_2());
  ASSERT_EQ(100, get_value_3());
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