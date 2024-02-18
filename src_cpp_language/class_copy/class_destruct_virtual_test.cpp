//
// Created by tao on 19-1-17.
//
#include "CommonClass.h"
#include "common_includes.h"
class OnDeleteLog {
  public:
  std::string name_{};
  ~OnDeleteLog() { LOG_DEBUG(name_ << " : OnDeleteLog called " << this) }
};
/// 析构函数非虚函数
namespace DestructTest {
class Base {};
class Derived : public Base {
  public:
  OnDeleteLog p;
  Derived(const std::string& name) { p.name_ = name; }
};
}  // namespace DestructTest

/// 析构函数为虚函数
namespace DestructTestVirtual {
class Base {
  public:
  virtual ~Base() {}  // 声明为虚函数
};
class Derived : public Base {
  public:
  OnDeleteLog p;
  Derived(const std::string& name) { p.name_ = name; }
};
}  // namespace DestructTestVirtual

TEST(class_copy_Destruct, 1) {
  {
    // 父类有申明为虚函数，子类的析构会被调用。
    DestructTestVirtual::Base* rowPtrVirtual = new DestructTestVirtual::Derived("DestructTestVirtual row ptr");
    delete rowPtrVirtual;
    LOG_DEBUG("row ptr deleted deleted");

    // 析构函数也会被调用
    std::shared_ptr<DestructTestVirtual::Base> basePtr =
        std::make_shared<DestructTestVirtual::Derived>("DestructTestVirtual shared ptr");
    basePtr = nullptr;
    LOG_DEBUG("shared_ptr deleted");
  }

  {
    // 父类没有virtual析构，子类的析构不会被调用。
    DestructTest::Base* rowPtr = new DestructTest::Derived("DestructTest row ptr");
    delete rowPtr;
    LOG_DEBUG("row ptr deleted");

    // shared ptr 特殊, 构造的时候额外保存了析构块, 类似类型擦除, 可以在析构时调用子类的析构函数
    std::shared_ptr<DestructTest::Base> basePtr =
        std::make_shared<DestructTest::Derived>("DestructTest shared ptr");
    basePtr = nullptr;
    LOG_DEBUG("shared_ptr deleted");
  }
}