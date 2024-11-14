#include <liburing.h>
#include <filesystem>
#include <random>
#include <fstream>

#include "common_includes.h"
#include "time_gap.hpp"

namespace fs = std::filesystem;

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
  FLOG_DEBUG("gen random buff timer use : {} us", gap.gapCacheUs());
  return buffer;
}

#define ASSERT_TRUE_WITH_PERROR(cond) \
if (!(cond)) {                      \
perror(#cond);                    \
}                                   \
ASSERT_TRUE((cond));                \
do {                                \
} while (0);

constexpr size_t TOTAL_MEM = 1024 * 1024 * 100;
constexpr size_t EACH_TRUNK_SIZE = 1024*64;
constexpr size_t URINT_ENTRIES_SIZE = TOTAL_MEM/EACH_TRUNK_SIZE + 10;

TEST(uring_write, 1) {
  auto buffer = gen_rand_buffer(TOTAL_MEM);
  LOG_DEBUG("write by uring")
  fs::path p = "./uring_file.bin";
  p = fs::absolute(p);
  LOG_DEBUG("will open " << p)
  int fd = open(p.c_str(), O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
  ASSERT_TRUE_WITH_PERROR(fd > 0);

  // init
  TimeGap gap{};
  struct io_uring ioUring;
  int ret = io_uring_queue_init(URINT_ENTRIES_SIZE, &ioUring, 0);
  ASSERT_TRUE_WITH_PERROR(ret == 0);
  gap.cacheTime();
  FLOG_DEBUG("init time use : {} us", gap.gapCacheUs());  // init time use : 59 us

  gap.resetStartNow();

  auto totalTrunk = size_t(std::ceil((double)TOTAL_MEM / EACH_TRUNK_SIZE));
  for (size_t i = 0; i < totalTrunk; ++i) {
    // get sqe
    io_uring_sqe *sqe = io_uring_get_sqe(&ioUring);
    ASSERT_TRUE_WITH_PERROR(sqe != nullptr);
    // prepare
    size_t startPos = i * EACH_TRUNK_SIZE;
    size_t writeSize = EACH_TRUNK_SIZE;
    writeSize = std::min(EACH_TRUNK_SIZE, TOTAL_MEM - startPos);

    io_uring_prep_write(sqe, fd, &buffer[startPos], writeSize, startPos);

  }

  // submit
  ret = io_uring_submit(&ioUring);
  ASSERT_TRUE_WITH_PERROR(ret == totalTrunk);

  // wait finish
  for (size_t i = 0; i < totalTrunk; ++i) {
    io_uring_cqe *cqe;
    ret = io_uring_wait_cqe(&ioUring, &cqe);
    ASSERT_TRUE_WITH_PERROR(ret == 0);
    ASSERT_TRUE_WITH_PERROR(cqe->res >= 0);
    // mark finish
    io_uring_cqe_seen(&ioUring, cqe);
  }

  gap.cacheTime();
  FLOG_DEBUG("write time use : {} us", gap.gapCacheUs()); //write time use : 105,886 us

  // exit
  close(fd);
  io_uring_queue_exit(&ioUring);
}
TEST(fstream_write, 1) {
  auto buffer = gen_rand_buffer(TOTAL_MEM);
  LOG_DEBUG("write by uring")
  fs::path p = "./fstream.bin";
  p = fs::absolute(p);
  std::ofstream ofs(p,std::ios::out|std::ios::trunc|std::ios::binary);
  ASSERT_TRUE(ofs.is_open());
  TimeGap gap{};
  ofs.write(reinterpret_cast<const char *>(buffer.data()),buffer.size());
  gap.cacheTime();
  FLOG_DEBUG("write time use : {} us", gap.gapCacheUs()); // write time use : 94,957 us
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}