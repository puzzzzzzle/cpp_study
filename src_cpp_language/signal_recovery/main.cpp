#include "common_includes.h"
#include <csignal>
#include <csetjmp>
// linux 没有 类似Windows上结构化异常处理(SEH) 的能力, 这个需要内核支持, 只能用信号模拟
std::jmp_buf jumpBuffer;

namespace LongJump
{
void signalHandler(int signal) {
  std::cerr << "Caught signal: " << signal << std::endl;
  longjmp(jumpBuffer, 1);  // 跳转回 setjmp
}

TEST(LongJump, 1) {
  signal(SIGSEGV, signalHandler);  // 注册信号处理程序
  SIGUSR1;
  if (setjmp(jumpBuffer) == 0) {
    LOG_DEBUG("About to cause a segmentation fault.")
    int * a = nullptr;
    *a = 42;
  } else {
    LOG_DEBUG("Returned to main after handling signal.");
  }
}
}
namespace SigLongJump
{
void signalHandler(int signal) {
  std::cerr << "Caught signal: " << signal << std::endl;
  siglongjmp(jumpBuffer, 1);  // 跳转回 setjmp
}

TEST(SigLongJump, 1) {
  signal(SIGSEGV, signalHandler);  // 注册信号处理程序

  if (sigsetjmp(jumpBuffer,1) == 0) {
    LOG_DEBUG("About to cause a segmentation fault.")
    int * a = nullptr;
    *a = 42;
  } else {
    LOG_DEBUG("Returned to main after handling signal.");
  }
}
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}