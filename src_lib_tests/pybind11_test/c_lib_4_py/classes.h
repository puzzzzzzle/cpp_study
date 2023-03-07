/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 23-3-4
 * @file classes.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once

#include <sstream>
#include <string>

class Person {
  private:
  std::string name_{};

  public:
  int age_{};

  public:
  Person() = default;
  Person(const std::string &name) : name_(name) {}
  void SetName(const std::string &name) { name_ = name; }
  const std::string &GetName() const { return name_; }

  std::string Hello(const std::string &target) {
    std::ostringstream oss{};
    oss << "hello to " << target;
    oss << " from " << name_;
    return oss.str();
  }
  std::string Play(int a) { return name_ + " play int " + std::to_string(a); }
  std::string Play(double a) {
    return name_ + " double int " + std::to_string(a);
  }
};