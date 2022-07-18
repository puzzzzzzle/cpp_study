//
// Created by khalidzhang on 2021/12/23.
//

#pragma once
#include <string>
#include "cpp_reflact.hpp"

class Base {
  public:
  virtual std::string Name() { return "Base"; }
};

class Sub : public Base {
  public:
  std::string Name() override { return "Sub"; }
};
REGISTER(Sub);