#include <memory>

#include "common_includes.h"
#include "proxy/proxy.h"
struct Formattable : pro::facade_builder ::support_format ::build {};

TEST(format, 1) {
  std::string str = "Hello World";
  pro::proxy<Formattable> p1 = &str;
  FLOG_DEBUG("p1 = {}", *p1);  // Prints "p1 = Hello World"

  pro::proxy<Formattable> p2 = std::make_unique<int>(123);
  FLOG_DEBUG("p2 = {}", *p2);  // Prints "p2 = 123"

  pro::proxy<Formattable> p3 = pro::make_proxy<Formattable>(3.14159);
  FLOG_DEBUG("p3 = {:.2f}", *p3);  // Prints "p3 = 3.14"
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}