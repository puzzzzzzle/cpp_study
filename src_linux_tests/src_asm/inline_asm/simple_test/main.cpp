//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

void inline_asm_test() {
  int64_t a{10}, b{};
  __asm__ __volatile__(R"(movq %1,%%rax;
movq %%rax,%0;
)"
                       : "=r"(b)
                       : "r"(a)
                       : "%rax");
  LOG_DEBUG("a:" << a << "\tb:" << b)
}

TEST(simple, asm_1) { inline_asm_test(); }

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