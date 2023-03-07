//
// Created by tao on 23-3-4.
//
#include <pybind11/pybind11.h>

#include "classes.h"
#include "funcs.h"

// 注意： CURRENT_BUILD_NAME 是在cmake中设置的, 要和二进制名字保持一致
// 不然会报dynamic module does not define module export function (PyInit
using namespace pybind11::literals;
using namespace pybind11;
PYBIND11_MODULE(CURRENT_BUILD_NAME, m) {
  m.doc() = "pybind11 cpp lib.";
  //  m.def("Add", &Add, "add two int numbers.",
  //        pybind11::arg("a"),pybind11::arg("b"));
  m.def("Add", &Add, "add two int numbers.", "a"_a = 1, "b"_a = 2);

  class_<Person>(m, "Person", dynamic_attr())
      .def(init<const std::string &>(),"name"_a = "unknown")
      .def_property("name", &Person::GetName, &Person::SetName)
      .def("Hello", &Person::Hello, "target"_a)
      .def_readwrite("age", &Person::age_)
      .def("Play",overload_cast<int>(&Person::Play))
      .def("Play",overload_cast<double>(&Person::Play))
      .def("__repr__", [](const Person &a) {
        return "<example.Pet named '" + a.GetName() + "'>";
      });
}
