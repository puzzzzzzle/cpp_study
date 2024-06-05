//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <iostream>
#include <sstream>
#include <vector>

#define LOG_DEBUG(msg) std::cout << msg << std::endl;
class MyStream {
  protected:
  std::stringstream _buffer;

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
std::ostream& operator<<(std::ostream& os, const Base& a) {
  os << a.ToString() << &a;
  return os;
}
}  // namespace GGG

namespace A {
class ClassA : public GGG::Base {
  public:
  virtual std::string ToString() const override { return "ClassA"; }
};
}  // namespace A



namespace B {
using A::ClassA;

void main() {
  ClassA a{};
  LOG_DEBUG(a)
  std::ostringstream oss{};
  oss << a;
  LOG_DEBUG(oss.str())
  std::vector<ClassA> va{};
  std::vector<std::vector<ClassA>> vas{};

  for (int i = 0; i < 10; ++i) {
    va.emplace_back();
    vas.push_back(va);
  }
  LOG_DEBUG(va)
  LOG_DEBUG(vas)

  MyStream ms{};
  ms << a << std::endl;
  ms << va << std::endl;
}
}  // namespace B
namespace C {
using A::ClassA;
void main() {}
}  // namespace C

int main(int argc, char** argv) {
  B::main();
  C::main();
  //  testing::InitGoogleTest(&argc, argv);
  //  iRet = RUN_ALL_TESTS();
  //  return iRet;
}