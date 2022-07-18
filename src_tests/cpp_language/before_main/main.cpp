//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "header.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

namespace HGameCore{
class NullMsg{

};
}

namespace HGame{
__attribute__((unused)) void funcn()
{
  HGameCore::NullMsg msg{};
}
}
namespace HGame
{
namespace HGame{
void funcn()
{
  HGameCore::NullMsg msg{};
}
}
}

using namespace HGame;
void func()
{
  HGameCore::NullMsg msg{};
}

// static的 只会在当前 cpp 对应的 .o 文件中生效, 这样全局就可以有多个 i 定义, 每个购汇初始化
static int i = []() -> int{
  LOG_RAW_CLINE("before main in cpp")
  return 1;
}();


// 全局变量初始化
bool before_main_0() {
  printf("clike before_main_0\n");
  return true;
}
bool _before_main_ret = before_main_0();

// gcc 方言
__attribute__((constructor)) void before_main_1() { printf("clike before_main_1\n"); }

class ClassFunc
{
  // gcc 方言
  __attribute__((constructor)) static void before_main_2() { printf("ClassFunc before_main_2\n"); }

  // 全局变量初始化
  static bool before_main_3() {
    printf("ClassFunc before_main_3\n");
    return true;
  }
  static bool _before_main_ret;
};
bool ClassFunc::_before_main_ret = ClassFunc::before_main_3();

// static的 只会在当前 cpp 对应的 .o 文件中生效, 这样全局就可以有多个 i 定义, 每个购汇初始化
// 非static 时 相当于这个被拷贝到了多个cpp中, 会重定义
static int j = []() -> int{
  LOG_RAW_CLINE("before main in cpp header.h")
  return 1;
}();

int main(int argc, char **argv) {
  LOG_RAW_CLINE("main start")
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}