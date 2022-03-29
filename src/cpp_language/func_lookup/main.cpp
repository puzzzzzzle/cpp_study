//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

class MyStream {
  protected:
  std::ostringstream _buffer;

  public:
  MyStream() {}
  ~MyStream(){LOG_DEBUG(_buffer.str())} MyStream(const MyStream&) = delete;
  MyStream& operator=(const MyStream&) = delete;

  /**
   * 重载<<
   * @tparam P
   * @param t
   * @return
   */
  template <typename P>
  MyStream& operator<<(const P& t) {
    _buffer << t;
    return *this;
  }

  /**
   * endl,flush等函数
   */
  typedef std::ostream& (*F)(std::ostream& os);
  MyStream& operator<<(F f) {
    (f)(_buffer);
    return *this;
  }

  /**
   * hex等系列函数
   */
  typedef std::ios_base& (*I)(std::ios_base& os);
  MyStream& operator<<(I f) {
    (f)(_buffer);
    return *this;
  }

  /**
   * 字段转换成ostream类型.
   * @return
   */
  operator std::ostream&() { return _buffer; }
};
namespace GGG {
class Base {
  public:
  virtual std::string ToString() const { return "Base"; }
};
}  // namespace GGG

// 按照 ADL规则, operator<< 最好和类的生命处于相同的命名空间中
namespace GGG {
std::ostream& operator<<(std::ostream& os, Base& a) {
  os << a.ToString() << &a;
  return os;
}
std::ostringstream& operator<<(std::ostringstream& os, Base& a) {
  os << a.ToString() << &a;
  return os;
}
MyStream& operator<<(MyStream& os, Base& a) {
  os << a.ToString() << &a;
  return os;
}
}  // namespace GGG

namespace A {
class ClassA : public GGG::Base {
  virtual std::string ToString() const override { return "ClassA"; }
};
}  // namespace A

namespace B {
void main() {
  A::ClassA a{};
  std::cout << a << std::endl;
  std::ostringstream oss{};
  oss << a;
  std::cout << oss.str();

  MyStream ms{};
  ms << a << std::endl;
}
}  // namespace B
namespace C {
using A::ClassA;
void main() {}
}  // namespace C

int main(int argc, char** argv) {
  B::main();
  C::main();

  //  int iRet = 0;
  //  iRet = beforeRun();
  //  if (iRet) {
  //    std::cerr << "init fail with " << iRet << std::endl;
  //  }
  //  testing::InitGoogleTest(&argc, argv);
  //  iRet = RUN_ALL_TESTS();
  //  return iRet;
}