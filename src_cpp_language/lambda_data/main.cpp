//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

// lambda 拷贝捕获的数据是const的
// auto get_lambda() {
//   int id = 0;
//
//   return [id]() {
//     LOG_DEBUG(id);
//     ++id;
//     return id;
//   };
// }
auto get_lambda_1() {
  struct Data {
    int id{};
  };
  auto ptr = std::make_shared<Data>();
  return [ptr]() {
    LOG_DEBUG(ptr->id);
    ++ptr->id;
    return ptr->id;
  };
}
auto get_lambda_2() {
  auto ptr = std::make_shared<int>(0);
  return [ptr]() {
    LOG_DEBUG(*ptr);
    ++(*ptr);
    return (*ptr);
  };
}
TEST(test_test, 1) {
  auto f = get_lambda_1();
  auto f2 = get_lambda_2();
  for (int i = 0; i < 10; ++i) {
    f();
    f2();
  }
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}