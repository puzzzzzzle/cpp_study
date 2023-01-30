//
// Created by tao on 19-1-17.
//
#include <exception>

#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

void always_throw() {
  bool is_run = true;
  int value = 0;
  while (is_run) {
    ++value;
    if(value>2){
      break;
    }
    try {
      throw std::exception();
    } catch (std::exception e) {
      LOG_DEBUG(e.what() << "\tvalue\t" << value)
    } catch (...) {
      LOG_DEBUG("unknown"
                << "\tvalue\t" << value)
    }
    sleep(1);
  }
  LOG_DEBUG("\tend\t" << value)
  assert(false);
  abort();
  throw std::exception();
}
int main(int argc, char **argv) {
  std::string temp{};
  std::cin >> temp;
  always_throw();
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}