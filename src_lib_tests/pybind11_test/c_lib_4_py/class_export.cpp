//
// Created by tao on 23-3-4.
//
#include <pybind11/pybind11.h>

int Add2(int a, int b)
{
  return a+b;
}
// 注意： CURRENT_BUILD_NAME 是在cmake中设置的, 要和二进制名字保持一致
// 不然会报dynamic module does not define module export function (PyInit
PYBIND11_MODULE(CURRENT_BUILD_NAME,m)
{
  m.doc()="pybind11 cpp lib.";
  m.def("Add2",&Add2,"add two int numbers.", py::arg("i"), py::arg("j"));
}

