//
// Created by user on 5/1/24.
//
#include "common_includes.h"
/*
 * 多态只能通过指针类型（指针和引用）实现。当你使用值类型时，会发生对象切割（slicing）
 * 即子类对象被切割成父类对象，只保留父类部分的成员变量和方法。这样，多态就无法实现。
 */
namespace VirtualFunctionTest {
class Parent {
  public:
  int i1 = 1;
  std::string s1 = "parent";
  virtual void hello() { LOG_DEBUG("hello from parent " << i1 << "\t" << s1) }
  virtual ~Parent() {}
};
class Sub : public Parent {
  public:
  int i2 = 2;
  std::string s1 = "sub";
  virtual void hello() {
    LOG_DEBUG("hello from sub " << i1 << "\t" << i2 << "\t" << s1)
  }
  ~Sub() {}
};

TEST(VirtualFunctionTest, 1) {
  {
    Parent p;
    p.hello();
    // hello from parent 1	parent
  }
  {
    Sub s;
    s.hello();
    // hello from sub 1	2	sub
  }
  {
    Parent s = Sub();
    s.hello();
    // hello from parent 1	parent
  }
  {
    Sub s;
    Parent p = s;
    p.hello();
    // hello from parent 1	parent
  }
  {
    Sub s;
    Parent& p = s;
    p.hello();
    // hello from sub 1	2	sub
  }
  {
    Sub s;
    Parent&& p = std::move(s);
    p.hello();
    // hello from sub 1	2	sub
  }
  {
    Sub s;
    Parent* p = &s;
    p->hello();
    // hello from sub 1	2	sub
  }
}
}  // namespace VirtualFunctionTest

namespace VirtualClassTest {

class Parent {
  public:
  virtual void func(const std::vector<double>& vec) {
    for (const auto d : vec) {
      func(d);
    }
  }
  virtual void func(double d) { LOG_DEBUG("parent" << d) }
  virtual void hello() {
    std::vector<double> vec{};
    vec.push_back(1);
    func(vec);
    LOG_DEBUG("parend hello")
  }
};
class Child : public Parent {
  public:
  void func(double d) { LOG_DEBUG("Child" << d) }
  virtual void hello() override {
    std::vector<double> vec{};
    vec.push_back(1);
    // error : c++ 重载不能跨域, 即使继承也不行
    //    func(vec);
    LOG_DEBUG("Child hello")
  }
};
class Child2 : public Child {
  void func(double d) { LOG_DEBUG("Child" << d) }
  virtual void hello() override {
    std::vector<double> vec{};
    vec.push_back(1);
    // error : c++ 重载不能跨域, 即使继承也不行
    //    func(vec);
    LOG_DEBUG("Child hello")
  }
};
void class_test_foo() {
  Parent* ch = new Child{};
  ch->hello();
  ch->func(3.14);
  return;
}
TEST(calss_test, 1) {
  class_test_foo();
  LOG_DEBUG("------------")
  auto ch = std::make_shared<Child>();
  ch->hello();
  LOG_DEBUG("------------")
  Parent& p = *ch;
  p.hello();
}
}  // namespace VirtualClassTest

namespace VirtualOverrideTests {
class Base1 {};
class Base2 {};
class Sub1 : public Base1 {};
class Sub2 : private Base1 {};
class Sub3 : public Base1, Base2 {
  void fun() { Base2* tt = this; }
};
TEST(VirtualFunctionTest, 2) {
  Base1* b1 = new Sub1;
  //  Base1 *b2 = new Sub2;  // private 不能视为是继承

  //  Base2 * b3 = new Sub3;  // 每个继承父类, 必须被主动声明没public
}
}  // namespace VirtualOverrideTests