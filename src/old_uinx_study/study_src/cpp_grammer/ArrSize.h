//
// Created by tao on 18-11-24.
//

#ifndef UNIXSTUDYCPP_ARRSIZE_H
#define UNIXSTUDYCPP_ARRSIZE_H

#include <stdio.h>
static int ArrSize_in = 10;
int ArrSize_out = 10;

template <typename T>
int ArrSize(const T a[]) {
  return sizeof(a) / sizeof(a[0]);
}

//边长数组 编译器不支持？？？
// template<typename T>
// T add2d(int rows, int cols, T arr[rows][cols]) {
//    T result = 0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            result += arr[i][j];
//        }
//    }
//    return result;
//}
template <typename T>
T add2d(int rows, int cols, T *arr) {
  T result = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result += *(arr + i * cols + j);
    }
  }
  return result;
}

void testArrSize() {
  int a[] = {1, 2, 3, 4, 5, 6};
  printf("right:\t%zu\n", sizeof(a) / sizeof(a[0]));
  //因为在传递时只会传递数组的首个成员的地址，所以传递后，不在保留长度信息
  printf("wrong\t%d\n", ArrSize(a));

  //变长数组

  //符合字面量
  //    (int[]) {10, 20};
  //
  int rows = 3, cols = 6;
  int b[3][6];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      b[i][j] = i * j;
    }
  }
  printf("b size:%zu\n", sizeof(b));
  int *ptr = (int *)&b[0];
  printf("ptr size:%zu\n", sizeof(ptr));

  printf("add result:%d\n", add2d(rows, cols, ptr));
}

#endif  // UNIXSTUDYCPP_ARRSIZE_H
