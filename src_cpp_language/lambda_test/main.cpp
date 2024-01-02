#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

class Base {
  public:
//  virtual ~Base() {}
      Base() = default;
      Base(const Base* other)
          {

          LOG_DEBUG("")
      };
      Base(const int* other)
          {

              LOG_DEBUG("")
          };
  virtual const std::string& Name() { return "Base"; }
};
class Derived : public Base {
  virtual const std::string& Name() { return "Derived"; }
};
void CallBack(std::function<void(int result, const Base& rsp)> func)
{
        func(0, Derived());
}
TEST(test_test, 2) {
  // lambda 不会自动转换, 这里不能用 Derived
//  CallBack([&](int result, const Derived& rsp) {
//    EXPECT_EQ(result, 0);
//
//  });
  CallBack([&](int result, const Base& rsp) {
    EXPECT_EQ(result, 0);

  });
// shared_ptr<Class>(nullptr) 并不是真的创建了一个空指针, 而是创建一个对象, 然后用nullptr去初始化它
std::shared_ptr<std::function<void(int result, const Base& rsp)>> null0;
  auto ptr = std::make_shared<std::function<void(int result, const Base& rsp)>>(nullptr);
  LOG_DEBUG(" " << (ptr == nullptr))
  LOG_DEBUG(" " << (*ptr == nullptr))
  LOG_DEBUG(" " << (ptr == null0))

  auto ptr1 = std::make_shared<Base>((int*)nullptr);
  LOG_DEBUG(" " << (ptr == nullptr))
  LOG_DEBUG(" " << (*ptr == nullptr))

  LOG_DEBUG("")
}
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}