//
// Created by tao on 18-11-25.
//
#include <stdio.h>

#include "MyFuncLib.h"

int main(int argc, char *argv[]) {
  SayHello();
  int a = 5;
  int b = 4;
  printf("5+4=%d", add(&a, &b));
}