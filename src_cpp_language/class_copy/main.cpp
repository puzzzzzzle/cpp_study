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
int main(int argc, char **argv) {
  int iRet = 0;

  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}