//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, success) {
  std::map<int,std::shared_ptr<int>> m{};
  m[1] = std::make_shared<int>(42);

  auto it = m.find(1);
  ASSERT_TRUE(it!=m.end());
  LOG_DEBUG(it->second.use_count()) // 1

  auto second = it->second;
  LOG_DEBUG(second.use_count()) // 2

  m.erase(it);
  LOG_DEBUG("value \t"<<*second)  // 42
}
TEST(test_test, fail) {
  std::map<int,std::shared_ptr<int>> m{};
  m[1] = std::make_shared<int>(42);

  auto it = m.find(1);
  ASSERT_TRUE(it!=m.end());
  LOG_DEBUG(it->second.use_count()) // 1

  m.erase(it);

  LOG_DEBUG(it->second.use_count()) // 0
  //segment fault
//  LOG_DEBUG("value\t"<<*(it->second))
  auto second = it->second;
  //segment fault
//  LOG_DEBUG(*second)
  LOG_DEBUG(second.use_count()) // 1
}
TEST(test_test, ptr)
{
  std::shared_ptr<int> ptr1= nullptr;
  LOG_DEBUG(ptr1.use_count());
  auto ptr2 = ptr1;
  LOG_DEBUG(ptr1.use_count());
  LOG_DEBUG(ptr2.use_count());

}
TEST(test_test, ptr2)
{
  std::shared_ptr<int> ptr1= std::make_shared<int>(42);
  LOG_DEBUG(ptr1.use_count());
  ptr1 = nullptr;
  LOG_DEBUG(ptr1.use_count());
  auto ptr2 = ptr1;
  LOG_DEBUG(ptr1.use_count());
  LOG_DEBUG(ptr2.use_count());

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