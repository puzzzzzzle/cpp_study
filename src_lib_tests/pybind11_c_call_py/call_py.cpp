//
// Created by khalidzhang on 2023/3/7.
//
#include <pybind11/embed.h>
#include "common_includes.h"

namespace py = pybind11;
using namespace pybind11::literals;

int CppAdd(int i, int j) {
  return i + j;
}
PYBIND11_EMBEDDED_MODULE(cpp_module, m) {
  // `m` is a `py::module_` which is used to bind functions and classes
  m.def("add", &CppAdd);
}

TEST(simple, 1) {
  py::scoped_interpreter guard{};

  py::print("from c++");

  auto fast_calc = py::module_::import("cpp_module");
  auto result = fast_calc.attr("add")(1, 2).cast<int>();
  assert(result == 3);
  LOG_DEBUG(result)

}

TEST(load_local_module,1)
{
  py::scoped_interpreter guard{};

  auto py_module = py::module_::import("py_module.py_funcs");

  auto locals = py::dict("fmt"_a="{} + {} = {}", **py_module.attr("__dict__"));
  assert(locals["a"].cast<int>() == 1);
  assert(locals["b"].cast<int>() == 2);

  py::exec(R"(
        c = a + b
        message = fmt.format(a, b, c)
    )", py::globals(), locals);

  assert(locals["c"].cast<int>() == 3);
  assert(locals["message"].cast<std::string>() == "1 + 2 = 3");
}