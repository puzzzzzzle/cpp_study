//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "mem_gap.h"
TEST(get_pid, 1) {
  LOG_DEBUG("pid:" << getpid() << "\ttid:" << gettid() << "\tgid:" << getgid())
  auto r = std::thread([]() {
    LOG_DEBUG("pid:" << getpid() << "\ttid:" << gettid()
                     << "\tgid:" << getgid())
  });
  r.join();
}
TEST(mem, Run) {
  std::vector<char *> tmp{};
  for (int i = 0; i < 10000; ++i) {
    char *t = new char[1024];
    t[sizeof(t) - 1] = 1;
    tmp.push_back(t);
  }
  LOG_DEBUG("statm rss " << GetStatm().m_resident)
  LOG_DEBUG("getrusage rss " << GetUsage().ru_maxrss)
  LOG_DEBUG("malloc_info " << GetMallocInfo())
  malloc_stats();
  for (auto item : tmp) {
    delete[] item;
  }
}

TEST(mem, Currect) {
  MemGap gap{};
  LOG_DEBUG("mem gap " << gap.GapRssAndReset() << "\tnow\t" << gap.NowRss())
  std::atomic_int p{};
  int buffSize = 102400;
  char **buff = new char *[buffSize];
  LOG_DEBUG("mem gap " << gap.GapRssAndReset() << "\tnow\t" << gap.NowRss())
  auto allocSize = [&](size_t size, int count,
                       char initValue) -> std::vector<int> {
    std::vector<int> result{};
    for (int i = 0; i < count; ++i) {
      auto currP = p++;
      assert(currP < buffSize);
      char *tmp = new char[size];
      buff[currP] = tmp;
      if (initValue != 0) {
        memset(tmp, initValue, size);
      }
      result.push_back(currP);
    }
    return result;
  };
  auto deletePointer = [&](std::vector<int> &ps) {
    for (auto point : ps) {
      assert(point < buffSize);
      delete[] buff[point];
      buff[point] = nullptr;
    }
  };
  // 10k * 10240
  auto allocPointer = allocSize(10 * 1024, 10240, 1);
  LOG_DEBUG("create : mem gap " << gap.GapRssAndReset() << "\tnow\t"
                                << gap.CurrRecord())

  // delete
  // not free now
  deletePointer(allocPointer);
  LOG_DEBUG("delete but not malloc_trim :mem gap " << gap.GapRssAndReset() << "\tnow\t"
                                            << gap.CurrRecord())
  malloc_trim(0);
  LOG_DEBUG("malloc_trim : mem gap " << gap.GapRssAndReset() << "\tnow\t"
                                  << gap.CurrRecord())

  auto r = GetUsage();
  {
    auto currP = p.load();
    ASSERT_TRUE(currP < buffSize);
    for (int i = 0; i < currP; ++i) {
      delete[] buff[i];
    }
    delete[] buff;
  }
  LOG_DEBUG("exit : mem gap " << gap.GapRssAndReset() << "\tnow\t"
                              << gap.NowRss())
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}