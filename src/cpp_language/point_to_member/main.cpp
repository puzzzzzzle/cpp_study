//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

struct S {
  S(int n) : mi(n) {}
  mutable int mi;
  int f(int n) { return mi + n; }
};

struct D : public S {
  D(int n) : S(n) {}
};
TEST(test_test, 1) {
  int S::*pmi = &S::mi;
  int (S::*pf)(int) = &S::f;

  const S s(7);
  //  s.*pmi = 10; // error: cannot modify through mutable
  LOG_DEBUG(s.*pmi)
  ASSERT_EQ(s.*pmi, 7);

  D d(7);  // base pointers work with derived object
  D* pd = &d;
  LOG_DEBUG((d.*pf)(7))
  LOG_DEBUG((pd->*pf)(8))

  ASSERT_EQ((d.*pf)(7), 14);
  ASSERT_EQ((pd->*pf)(8), 15);
  sleep(1);
}

int main(int argc, char** argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}