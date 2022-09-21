//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "mem_gap.h"

TEST(mem, 1) {
  char *t = new char[1024 * 1024];
  t[sizeof(t) - 5] = 1;
  MemGap gap{};
  malloc_stats();
  LOG_DEBUG("pid:" << getpid() << "\ttid:" << gettid() << "\tgid:" << getgid())
  auto r = std::thread([]() {
    LOG_DEBUG("pid:" << getpid() << "\ttid:" << gettid()
                     << "\tgid:" << getgid())
  });
  r.join();
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