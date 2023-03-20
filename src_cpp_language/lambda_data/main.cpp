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

void use_lambda_void(const std::function<void()>& f) { f(); }
void use_lambda_int(const std::function<int()>& f) { LOG_DEBUG(f()); }
TEST(function_ret, 1) {
  auto b = []() {
    LOG_DEBUG("call b");
    return 43;
  };
  auto v = []() { LOG_DEBUG("call v"); };
  use_lambda_void(b);
  use_lambda_void(v);

  use_lambda_int(b);
  //   use_lambda_int(v);  //error :nvalid initialization of reference of type
  //   'const std::function<int()>&' from expression of type
  //   'arg_1_Test::TestBody()::<lambda()>'
}
int i_func() {
  LOG_DEBUG("call i_func")
  return 42;
}
void v_func() { LOG_DEBUG("call v_func") }

// 没有数组需求的话 (*) 可有可无, 都是函数指针, 不过按照习惯加上好些
using int_func_t = int (*)();
using void_func_t = void (*)();

void c_use_func_void(void_func_t f) { f(); }
void c_use_func_int(int_func_t f) { LOG_DEBUG(f()); }
TEST(c_function, 1) {
  c_use_func_void(&v_func);
//  c_use_func_void(&i_func); //error invalid conversion from 'int (*)()' to 'void_func_t' {aka 'void (*)()'} [-fpermissive]

//  c_use_func_int(&v_func); //error invalid conversion from 'void (*)()' to 'int_func_t' {aka 'int (*)()'} [-fpermissive]
  c_use_func_int(&i_func);
}
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}