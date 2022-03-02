//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "time_gap.hpp"
class UndefinedClass;
class DefinedClass{};


TEST(test_test, 1) {
  int i=1;
  LOG_DEBUG(sizeof (&i))

  void (DefinedClass::*d_f)();
  LOG_DEBUG(sizeof (d_f))
  void (UndefinedClass::*ud_f)();
  LOG_DEBUG(sizeof (ud_f))

  TimeGap gap{};
  TimeTools::SleepMicro(1234567);
  LOG_DEBUG(gap.gap())
  LOG_DEBUG(gap.gapUs())
  LOG_DEBUG(gap.gapMs())
  LOG_DEBUG(gap.gapSec())

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