#include "common_includes.h"
int test_mem(size_t size) {
  LOG_DEBUG("will malloc size " << size)
  char *mem = static_cast<char *>(malloc(size));
  LOG_DEBUG("will set mem " << size)
    memset(mem,1,size);
//  mem[size - 1] = 0;
  free(mem);
}
TEST(test_test, 1) { test_mem(1024L * 1024 * 1024 * 10); }

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}