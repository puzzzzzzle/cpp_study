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
}  // namespace VirtualTest
