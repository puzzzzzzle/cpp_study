//
// Created by user on 5/7/24.
//
#include "common_includes.h"
namespace TemplatePtrTests {
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
  my.visitor([](TestTemplate *ptr) { ptr->t.Hello(); });
}

}  // namespace TemplatePtrTests