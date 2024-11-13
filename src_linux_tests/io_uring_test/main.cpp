#include <liburing.h>

#include <random>

#include "common_includes.h"
#include "time_gap.hpp"

static std::vector<uint8_t> gen_rand_buffer(int size) {
  // 创建一个随机数生成器
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> dis(0, 255);

  TimeGap gap{};
  LOG_DEBUG("start gen random buff")
  gap.resetStartNow();
  std::vector<uint8_t> buffer(size);
  for (int i = 0; i < buffer.size(); ++i) {
    buffer[i] = dis(gen);
  }
  gap.cacheTime();
  LOG_DEBUG("gen random buff timer use : " << gap.gapCacheUs());
  return buffer;
}
// 50M
constexpr int S50M = 1024 * 1024 * 50;

TEST(uring_write, 50) {
  auto buffer = gen_rand_buffer(S50M);
  LOG_DEBUG("write by uring")
  TimeGap gap{};
  const char *file_path = "uring_file.bin";
  int fd = open(file_path, O_RDWR|O_TRUNC);
  ASSERT_TRUE(fd>0);
  struct io_uring ioUring;
  int ret = 0;
  ret = io_uring_queue_init(1,&ioUring,0);
  ASSERT_TRUE(ret>=0);

}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}