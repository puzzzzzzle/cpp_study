#include <cstdio>

#include "class2_define.h"
class Class1 {
  public:
  void fun() { printf("test::Class2\n"); }
};
void test()
{
  printf("test start \n");
  Class1 c1{};
  c1.fun();
  Class2 c2{};
  c2.fun();
}