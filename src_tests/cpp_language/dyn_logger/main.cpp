//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "dyn_logger.h"
#define F_LOG_TRACE(level, log...) D_LOG(LOG_TRACE, __FILE__, level, log)
#define F_LOG_DEBUG(level, log...) D_LOG(LOG_DEBUG, __FILE__, level, log)
#define F_LOG_INFO(level, log...) D_LOG(LOG_INFO, __FILE__, level, log)
#define F_LOG_WARN(level, log...) D_LOG(LOG_WARN, __FILE__, level, log)
#define F_LOG_ERROR(level, log...) D_LOG(LOG_ERROR, __FILE__, level, log)

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

struct Temp {
  struct LogCtl {
    bool DLoggerFilter(const char* name, int level) { return true; }
    const char* GetLogTag(const char* name) { return "class -> Temp"; }
  };
  LogCtl* GetLogCtl() {
    static LogCtl ctl{};
    return &ctl;
  }
  void Hello() { F_LOG_DEBUG(1, "hhhh") }
};

namespace Inner {
struct LogCtl {
  bool DLoggerFilter(const char* name, int level) { return true; }
  const char* GetLogTag(const char* name) { return "Inner -> Temp"; }
};
LogCtl* GetLogCtl() {
  static LogCtl ctl{};
  return &ctl;
}
void Hello() { F_LOG_DEBUG(1, "hhhh") }
}  // namespace Inner
struct CmpStr {
  bool operator()(char const* a, char const* b) const {
    return std::strcmp(a, b) < 0;
  }
};
TEST(test_test, 2) {
  std::map<const char*, int, CmpStr> data{};
  auto c1 = "/hhh/lll";
  data[c1] = 1;
  auto c2 = "/hhh/";
  data[c2] = 1;
  auto c3 = "/hhh/lll/ppp";
  data[c3] = 1;
  auto c4 = "/kkk/p";
  data[c4] = 1;
  for (auto& item : data) {
    LOG_DEBUG(item.first)
  }
}
int main(int argc, char** argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  F_LOG_DEBUG(1, "hello")

  Temp t{};
  t.Hello();
  Inner::Hello();
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}