/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2022/9/21
 * @file mem_gap.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#include <fcntl.h>
#include <malloc.h>
#include <sys/resource.h>

#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

// 获取 top 中展示的内存格式数据
struct Statm {
  // 单位: kB
  // VIRT, RES,SHR
  unsigned long m_size, m_resident, m_share, m_text, m_lib, m_data, m_dt;
};
/**
 *  获取 top 中展示的内存格式数据
 *  单位 pageSize
 * @return
 */
inline Statm GetStatm() {
  //  auto pagesize = getpagesize();
  Statm result{};
  const char* statm_path = "/proc/self/statm";

  FILE* f = fopen(statm_path, "r");
  if (!f) {
    perror(statm_path);
    fclose(f);
    return {};
  }
  if (7 != fscanf(f, "%ld %ld %ld %ld %ld %ld %ld", &result.m_size,
                  &result.m_resident, &result.m_share, &result.m_text,
                  &result.m_lib, &result.m_data, &result.m_dt)) {
    perror(statm_path);
    fclose(f);
    return {};
  }
  // convert to byte
  //  decltype(result.m_size)* tmp = &result.m_size;
  //  for (int i = 0; i < sizeof(result) / sizeof(result.m_size); ++i) {
  //    tmp[i] *= (pagesize / 1024);
  //  }
  fclose(f);
  return result;
}

/**
 * 获取malloc info 中统计的内存信息
 * 精确到byte, 但是需要自己手动接xml, 还没处理
 * 单位: byte
 * @return xml 格式
 */
inline std::string GetMallocInfo() {
  // crete buff
  std::string result{};
  char* buffer = NULL;
  size_t bufferSize = 0;
  auto ss = open_memstream(&buffer, &bufferSize);

  // get status
  int ret = malloc_info(0, ss);
  fflush(ss);
  if (ret) {
    fprintf(stderr, "call malloc_info fail %d", ret);
    result = "error";
  } else {
    result = std::string(buffer);
  }

  // close
  fclose(ss);
  free(buffer);
  return result;
}
/**
 * 获取 getrusage 信息, 应该是VIRT
 * 单位: kB
 * @return
 */
inline rusage GetUsage() {
  rusage u{};
  getrusage(RUSAGE_SELF, &u);
  return u;
}
inline void GetUsage(rusage& u) { getrusage(RUSAGE_SELF, &u); }
/**
 * 内存统计GAP
 * 单位 kB
 */
class MemGap {
  private:
  long m_rss{};

  public:
  void ResetNow() { m_rss = NowRss(); }
  long CurrRecord() { return m_rss; }
  static long NowRss() {
    return (long)GetStatm().m_resident * getpagesize() / 1024;
  }

  public:
  MemGap() { ResetNow(); }
  /**
   * 当前内存和上次存档的变化
   * @return
   */
  long GapRss() { return NowRss() - m_rss; }
  /**
   * 当前内存和上次存档的变化, 并重置记录为当前内存大小
   * @return
   */
  long GapRssAndReset() {
    auto curr = NowRss();
    auto ret = curr - m_rss;
    m_rss = curr;
    return ret;
  }
};