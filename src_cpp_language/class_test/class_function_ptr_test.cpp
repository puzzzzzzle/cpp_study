//
// Created by user on 5/7/24.
//
#include "common_includes.h"
namespace ClassFunctionPtrTests {
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
TEST(ClassFunctionPtrTests, 1) {
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
}  // namespace ClassFunctionPtrTests
