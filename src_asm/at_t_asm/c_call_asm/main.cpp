//
// Created by khalidzhang on 2021/6/18.
//
#include "cstdio"
extern "C"
{
void cpu_id();
void test_func();
}
int main(int argc, char* argv[])
{
  printf("start \n");
  cpu_id();
  test_func();
  printf("end \n");
  return 0;
}