//
// Created by tao on 19-1-17.
//
#include <iostream>
#include <type_traits>
#include <typeinfo>

#include "common_includes.h"

template <class A>
void foo(const A &) {
  typedef typename std::remove_all_extents<A>::type Type;
  std::cout << "underlying type: " << typeid(Type).name() << '\n';
}

void test() {
  float a1[1][2][3];
  int a2[3][2];
  float a3[1][1][1][1][2];
  double a4[2][3];

  foo(a1);
  foo(a2);
  foo(a3);
  foo(a4);
}

TEST(test_test, 1) { test(); }

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}