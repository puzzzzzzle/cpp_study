//
// Created by tao on 19-1-17.
//
#include "auto_wired.h"
#include "common_includes.h"
AutoWiredImpl<> g_autoWired{};
TEST(basic_test, 1) {
  AutoWiredImpl<> autoWired{};

  int injValue = 42;
  // reg value
  ASSERT_EQ(autoWired.GetFactory()->RegValue("int1", &injValue), 0);

  // req value
  int *beenIbj = nullptr;
  autoWired.GetInjMng()->RegValue("int1", &beenIbj);

  // only allow reg once for one value
  ASSERT_NE(autoWired.GetFactory()->RegValue("int1", &injValue), 0);

  // can reg multi for req
  int *beenIbj1 = nullptr;
  autoWired.GetInjMng()->RegValue("int1", &beenIbj1);

  // do auto wired
  ASSERT_EQ(autoWired.DoAutoWired(), 0);

  ASSERT_EQ(beenIbj, &injValue);
  ASSERT_EQ(*beenIbj, injValue);
  ASSERT_EQ(beenIbj1, &injValue);
  ASSERT_EQ(*beenIbj1, injValue);
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