//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

union S {
  std::int32_t n;      // 占用4字节
  std::uint16_t s[2];  // 占用4字节
  std::uint8_t c;      // 占用1字节
};                     // 整体占用4字节

TEST(build_in, 1) {
  S s = {0x12345678};  // 初始化第一个成员，当前s.n为活跃成员
  // 于此点，读取 s.s 或 s.c 是未定义行为
  std::cout << std::hex << "s.n = " << s.n << '\n';
  s.s[0] = 0x0011;  // s.s 现在是活跃成员
  // 在此点，读取 s.n 或 s.c 是未定义行为
  std::cout << "s.c is now " << +s.c << '\n'  // 11 or 00, 依赖平台实现
            << "s.n is now " << s.n << '\n';  // 12340011 or 00115678
}
/*

(C++11 前)
联合体不能含有带非平凡特殊成员函数（复制构造函数、复制赋值运算符或析构函数）的非静态数据成员。

(C++11 起)
若联合体含有带非平凡特殊成员函数（复制/移动构造函数，复制/移动赋值，或析构函数）的非静态数据成员，则联合体中的该函数默认被弃置，且需要程序员显式定义它。

若联合体含有带非平凡默认构造函数的非静态数据成员，则该联合体的默认构造函数默认被弃置，除非联合体的变体成员拥有一个默认成员初始化器。

至多一个变体成员可以拥有默认成员初始化器。
 */

namespace MyT {

class MyClass {
  public:
  std::string name{};
  std::string ToString() const {
    return "MyClass:" + name + "\t@" + std::to_string((intptr_t)this);
  }
  MyClass(){LOG_DEBUG(ToString())};
  MyClass(const std::string& _name) {
    name = _name;
    LOG_DEBUG(ToString())
  }
  MyClass(const MyClass& obj) {
    name = obj.name;
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
  };
  MyClass(MyClass&& obj) {
    LOG_DEBUG("\tobj: " << obj.ToString())
    std::swap(name, obj.name);
    LOG_DEBUG("this: " << ToString())
  };
  virtual ~MyClass(){LOG_DEBUG(ToString())};
  MyClass& operator=(const MyClass& obj) {
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
    name = obj.name;
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
    return *this;
  };

  MyClass& operator=(MyClass&& obj) {
    LOG_DEBUG("\tobj: " << obj.ToString())
    std::swap(name, obj.name);
    LOG_DEBUG("this: " << ToString())
    return *this;
  };
};
}  // namespace MyT
TEST(my_class, 1) {
  using MyT::MyClass;
  MyClass c1{};
  MyClass c2{"khalid"};
  MyClass c3(c2);
  // 没有调用 operator= 而是使用了复制构造函数, 这是为了做优化
  // 而赋值操作符要求‘=’的左右对象均已存在，它的作用就是把‘=’右边的对象的值赋给左边的对象
  MyClass c4 = c2;
  // 这种 的左右对象均已存在 才会
  MyClass c5;
  c5 = c2;
  MyClass c6(std::move(c2));
}
// error
namespace t0 {
/*
union A {
  int a;
  double b;
  std::string c;
  MyClass d;
  std::shared_ptr<MyClass> e;
};
// default constructor of 'A0' is implicitly deleted because variant field 'c'
has a non-trivial default constructor
 // c 不是平凡类型, 必须自定义构造函数
TEST(adt,1)
{
  A s;
}
*/
}
// 主动调用析构函数, 包装下免得调错
template <class T>
inline void DestoryAt(T& t) {
  t.~T();
}
namespace t1 {
union A {
  std::string c;
  MyT::MyClass d;
  std::shared_ptr<MyT::MyClass> e;
  A() {}  // 因为std::string拥有是非平凡的的数据类型，
  ~A() {}  // 则A必须自定义构造函数和析构函数，否则无法进行实例化
  // 如果想实现复制语义，还得自定义复制(构造)函数
};
TEST(adt, 1) {
  A s;
  // 激活 d
  new (&s.d) MyT::MyClass();
  // d可以使用了
  s.d.name = "in union";
  LOG_DEBUG("&s.d " << &s.d)
  // 必须手动释放 d
  // union 不会自动调用析构函数
  // 下面两种方法都行, 包装下免得调错
  DestoryAt(s.d);
  //  s.d.~MyClass();

  // 激活e
  new (&s.e) std::shared_ptr<MyT::MyClass>();
  // 初始化一个 MyClass
  s.e = std::make_shared<MyT::MyClass>();
  s.e->name = "union ptr";
  // 释放e
  DestoryAt(s.e);
}
}  // namespace t1

namespace t2 {
// 使用struct包装
struct SA {
  enum class Tag : int {
    STRING = 0,
    MY_CLASS,
    MY_CLASS_SPTR,
  };
  const Tag tag;
  union {
    std::string c;
    MyT::MyClass d;
    std::shared_ptr<MyT::MyClass> e;
  };
  SA() = delete;
  // TODO
  SA(const SA&) = delete;
  SA(const SA&&) = delete;
  SA& operator=(const SA&) = delete;
  SA& operator=(SA&&) = delete;


  SA(Tag t) : tag(t) {
    switch (tag) {
      case Tag::STRING:
        new (&c) decltype(c);
        break;
      case Tag::MY_CLASS:
        new (&d) decltype(d);
        break;
      case Tag::MY_CLASS_SPTR:
        new (&e) decltype(e);
        break;
      default:
        assert(false);
        break;
    }
  }

  virtual ~SA() {
    switch (tag) {
      case Tag::STRING:
        DestoryAt(c);
        break;
      case Tag::MY_CLASS:
        DestoryAt(d);
        break;
      case Tag::MY_CLASS_SPTR:
        DestoryAt(e);
        break;
      default:
        assert(false);
        break;
    }
  }
};
TEST(adt, struct_type) {
  {
    SA myclass(SA::Tag::MY_CLASS);
    myclass.d.name = "SA";
    LOG_DEBUG(myclass.d.ToString());
  }

  {
    SA myclassPtr(SA::Tag::MY_CLASS_SPTR);
    myclassPtr.e = std::make_shared<decltype(myclassPtr.e)::element_type>();
    myclassPtr.e->name = "SAP";
    LOG_DEBUG(myclassPtr.e->ToString());
  }

}
}  // namespace t2
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}