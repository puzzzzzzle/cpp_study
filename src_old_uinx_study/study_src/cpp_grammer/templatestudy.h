//
// Created by tao on 18-11-24.
//

#ifndef UNIXSTUDY_TEMPLETESTUDY_H
#define UNIXSTUDY_TEMPLETESTUDY_H

#include <stdio.h>

#include <iostream>

#include "ArrSize.h"

using namespace std;
// extern 用于使用在其他文件中申明的具有程序作用域的变量而不用include它们
extern int ArrSize_in;
extern int ArrSize_out;
template <typename T>
void MySwap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}
void templatetest() {
  int a = 10, b = 20;
  double c = 1.0, d = 2.0;
  printf("a:%d,b:%d\n", a, b);
  MySwap(a, b);
  printf("a:%d,b:%d\n", a, b);

  printf("c:%.2f,d:%.2f\n", c, d);
  MySwap(c, d);
  printf("c:%.2f,d:%.2f\n", c, d);
  testArrSize();
  printf("%d,%d\n", ArrSize_in, ArrSize_out);
}
#endif  // UNIXSTUDY_TEMPLETESTUDY_H
