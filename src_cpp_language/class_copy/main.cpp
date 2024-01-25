//
// Created by tao on 19-1-17.
//
#include "CommonClass.h"
#include "common_includes.h"

void to_leaf(long value){LOG_DEBUG(value)}

OperatorLogClass get_big_obj(long value) {
  to_leaf(value);
  OperatorLogClass obj{};
  return obj;
}
OperatorLogClass get_big_obj_1(long value) {
  return get_big_obj(value);
}
TEST(oper, 2) {
  auto obj = get_big_obj_1(42);
}

class Base{};
std::ostream& operator<<(std::ostream& os, const Base & obj)
{
  os << "cref \n";
  return os;
}
//std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Base> & obj)
//{
//  os << "sptr \n";
//  return os;
//}
//std::ostream& operator<<(std::ostream& os, const std::shared_ptr<const Base> & obj)
//{
//  os << "csptr \n";
//  return os;
//}
//std::ostream& operator<<(std::ostream& os, const Base * obj)
//{
//  os << "ptr \n";
//  return os;
//}
std::ostream& operator<<(std::ostream& os, const Base * const obj)
{
  os << "cptr \n";
  return os;
}
class Sub : public Base{};

TEST(oper, 3) {
  auto obj = std::make_shared<Sub>();
  std::cout << *obj;
  std::cout << obj;
  std::cout << obj.get();
  const std::shared_ptr<const Base> cobj = obj;
  std::cout << *cobj;
  std::cout << cobj;
  std::cout << cobj.get();

}
class OperatorLogClassSub :public OperatorLogClass
{
  using OperatorLogClass::OperatorLogClass;
};
TEST(cp,1)
{
  OperatorLogClassSub sub1,sub2;
  sub2=sub1;
  sub2=std::move(sub1);
  OperatorLogClassSub sub3(sub1);
  OperatorLogClassSub sub4(std::move(sub1));
}

namespace DestructTest
{
class OnDeleteLog {
  public:
      std::string name_{};
  ~OnDeleteLog() { LOG_DEBUG("OnDeleteLog called " << this <<"\t" << name_) }
};
class Base {
  public:
//  virtual ~Base() {}  // 声明为虚函数
};

class Derived : public Base {
  public:
  OnDeleteLog p;
  Derived(const std::string&name){
    p.name_=name;
  }
};
}
namespace DestructTestVirtual
{
class OnDeleteLog {
  public:
  std::string name_{};
  ~OnDeleteLog() { LOG_DEBUG("OnDeleteLog called " << this <<"\t" << name_) }
};
class Base {
  public:
    virtual ~Base() {}  // 声明为虚函数
};

class Derived : public Base {
  public:
  OnDeleteLog p;
  Derived(const std::string&name){
    p.name_=name;
  }
};
}
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
int main(int argc, char **argv) {
  int iRet = 0;


  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}