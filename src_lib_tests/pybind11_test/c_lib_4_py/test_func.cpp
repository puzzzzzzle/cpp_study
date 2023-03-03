//
// Created by khalidzhang on 2023/3/2.
//
#include <pybind11/pybind11.h>

int Add(int a, int b)
{
  return a+b;
}
// 注意： CURRENT_BUILD_NAME 是在cmake中设置的, 要和二进制名字保持一致
// 不然会报dynamic module does not define module export function (PyInit
PYBIND11_MODULE(CURRENT_BUILD_NAME,m)
{
  m.doc()="pybind11 cpp lib.";
  m.def("Add",&Add,"add two int numbers.");
}

