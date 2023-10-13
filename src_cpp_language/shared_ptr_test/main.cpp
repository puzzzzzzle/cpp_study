#include "common_includes.h"
#include "cstdio"
class TestClass {
  public:
  int i{};
  char data[100];
  double *d{};
  TestClass() {
    d = new double;
    *d = 3.14;
    LOG_DEBUG("construct " << this)
  }
  ~TestClass() {
    delete d;
    d = nullptr;
    LOG_DEBUG("destruct " << this)
  }
};
void UseTestClass(const TestClass * const data)
{
  LOG_DEBUG(""<<data->i)
}
template<class T>
void UseTestClass(const T * const data)
{
  LOG_DEBUG(""<<data->i)
}
template<class T>
void UseTestClass(const std::shared_ptr<T>& data)
{
  LOG_DEBUG(""<<data->i)
}
void UseTestClass(const TestClass& data)
{
  LOG_DEBUG(""<<data.i)
}
void ttttt()
{
  auto d = std::make_shared<TestClass>()->d;
  printf("%f",*d);
}
TEST(test_test, 1) {
  ttttt();
}
TEST(test_test, 2) {
  auto test = std::make_shared<TestClass>();
  test->i=42;
  UseTestClass(*test);
  UseTestClass(test.get());
  UseTestClass(test);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}