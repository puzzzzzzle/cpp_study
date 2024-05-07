//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) {
  std::string raw1 =
      R"(this is a text
this is a new line)";
  std::cout << raw1 << std::endl;
  raw1 =
      R"(this is a text
           this is a new line)";
  std::cout << raw1 << std::endl;
  raw1 =
      R"(this is a text"
           "this is a new line)";
  std::cout << raw1 << std::endl;
  raw1 =
      R"(this is a text"
"this is a new line)";
  std::cout << raw1 << std::endl;
  raw1 =
      R"(this is a long long long long long long long long long long long long long long long long long long)"
      R"(++ long long long long long long long long long long long long long long long long long long line)";
  std::cout << raw1 << std::endl;
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}