//
// Created by tao on 19-1-17.
//
#include "boost/format.hpp"
#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

// 类对象初始化测试
class TestFieldNameClass {
  public:
  TestFieldNameClass() { LOG_DEBUG("init test class " << (size_t)this); }
  int value;
  int i_value{};
  void print() const {
    LOG_DEBUG(boost::format("value %d  i_value  %d\n") % value % i_value);
  }
};
TestFieldNameClass g_val;  // 全局默认初始化, 在main函数前初始化,
                           // 即使没有声明要初始化的变量value也会被置为默认值
TestFieldNameClass g_i_val{};  // 全局默认初始化
// static 全局变量只能在本文件中访问 , 初始化上没区别 , 只是为了格式统一
static TestFieldNameClass g_s_val;      // 全局默认初始化
static TestFieldNameClass g_s_i_val{};  // 全局默认初始化

void testFunc() {
  printf("==== start func \n");

  int a;                     // 局部基础变量不会初始化
  int i_a{};                 // 局部变量调用默认初始化函数初始化
  TestFieldNameClass l_val;  // 类变量总是初始化, i_value 会被初始化, 但是 value
                             // 不会, 应为不再构造函数初始化表中
  TestFieldNameClass l_i_val{};  // 类变量初始化
  static TestFieldNameClass
      l_s_val;  // 局部静态变量在第一次调用函数时初始化 i_value 和 value
                // 都会初始化,和全局变量的初始化规则类似, 只是时机晚一些
  static TestFieldNameClass
      l_s_i_val{};  // 局部静态变量在第一次调用函数时初始化

#define PRINT_C(name)                                                    \
  LOG_DEBUG(((boost::format("now check [%s]  [%p] ") % #name % &name))); \
  name.print();

  LOG_DEBUG(((boost::format("test int [a : %d]  [i_a : %d]\n") % a % i_a)));

  PRINT_C(g_val)
  PRINT_C(g_i_val)
  PRINT_C(g_s_val)
  PRINT_C(g_s_i_val)
  PRINT_C(l_val)
  PRINT_C(l_i_val)
  PRINT_C(l_s_val)
  PRINT_C(l_s_i_val)
#undef PRINT_C
}

// 模板类 指针测试
template <class T>
class TestTemplateT {
  public:
  T t{};
  void visitor(std::function<void(TestTemplateT *)> func) { func(this); }
};
class TClass {
  public:
  void Hello() { LOG_DEBUG("hello") }
};
using TestTemplate = TestTemplateT<TClass>;
TEST(class_type, 2) {
  TestTemplate my{};
  // 直接使用特化后的指针
  my.visitor([](TestTemplate *t) { t->t.Hello(); });
}

// 类函数指针测试

class FuncClass;
class FuncSubClass;

// 下面两种声明方法都行
typedef void (FuncClass::*FuncClassFuncPtrAnother)();
using FuncClassFuncPtr = void (FuncClass::*)();
using FuncClassFuncPtrInt = void (FuncClass::*)(int);
using SubFuncClassFuncPtr = void (FuncSubClass::*)();
using SubFuncClassFuncPtrInt = void (FuncSubClass::*)(int);
// FuncClass impl 之前调用它中的函数
void TestCallBeforeClassImpl(FuncClass *c, FuncClassFuncPtr func) {
  (c->*func)();
}
void TestCallSubClassBeforeClassImpl(FuncClass *c, FuncClassFuncPtrInt func,
                                     int value) {
  (c->*func)(value);
}
void SubTestCallBeforeClassImpl(FuncSubClass *c, SubFuncClassFuncPtr func) {
  (c->*func)();
}
void SubTestCallSubClassBeforeClassImpl(FuncSubClass *c,
                                        SubFuncClassFuncPtrInt func,
                                        int value) {
  (c->*func)(value);
}
class FuncClass {
  public:
  // 重载函数
  virtual void Hello() { LOG_DEBUG("Hello") }
  // 覆盖函数
  void HelloOv() { LOG_DEBUG("HelloOv") }
};
class FuncSubClass : public FuncClass {
  public:
  virtual void Hello() override { LOG_DEBUG("Hello by sub") }
  // 覆盖父类中的 但不重载
  void HelloOv() { LOG_DEBUG("HelloOv by sub") }
  virtual void Call(int i) { LOG_DEBUG("Call  by sub" << i) }
};
TEST(func_ptr, 1) {
  {
    FuncClass c{};
    TestCallBeforeClassImpl(&c, &FuncClass::Hello);
    TestCallBeforeClassImpl(&c, &FuncClass::HelloOv);
    //  TestCallSubClassBeforeClassImpl(&c, &FuncSubClass::Call,42);
  }

  {
    FuncSubClass sub{};
    SubTestCallBeforeClassImpl(&sub, &FuncSubClass::Hello);
    // override 函数正常覆盖
    SubTestCallBeforeClassImpl(&sub, &FuncSubClass::HelloOv);
    // 可以正常访问子类覆盖父类的函数
    SubTestCallSubClassBeforeClassImpl(&sub, &FuncSubClass::Call, 42);
    // override 函数正常覆盖
    SubTestCallBeforeClassImpl(&sub, &FuncClass::Hello);
    // 可以正常访问被覆盖的服类函数
    SubTestCallBeforeClassImpl(&sub, &FuncClass::HelloOv);
  }
}
class Parent {
  public:
  virtual void func(const std::vector<double> &vec) {
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
    //error : c++ 重载不能跨域, 即使继承也不行
//    func(vec);
    LOG_DEBUG("Child hello")
  }
};
class Child2 : public Child {
  void func(double d) { LOG_DEBUG("Child" << d) }
  virtual void hello() override {
    std::vector<double> vec{};
    vec.push_back(1);
    //error : c++ 重载不能跨域, 即使继承也不行
//    func(vec);
    LOG_DEBUG("Child hello")
  }
};
TEST(calss_test, 1) {
  LOG_DEBUG("------------")
  auto ch = std::make_shared<Child>();
  ch->hello();
  LOG_DEBUG("------------")
  Parent &p = *ch;
  p.hello();
}
int main(int argc, char **argv) {
  testFunc();
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}