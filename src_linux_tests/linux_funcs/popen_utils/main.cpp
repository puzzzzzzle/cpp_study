//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

std::pair<int, std::string> CallSystem(const std::string &cmd) {
  if ("" == cmd) {
    return {1, "empty cmd"};
  }
  FILE *f = popen(cmd.c_str(), "r");
  if (f == nullptr) {
    return {1, "f == nullptr"};
  }
  char line[1024];
  std::ostringstream ss{};
  while (fgets(line, sizeof(line), f) != nullptr) {
    ss << line;
  }
  int ret = pclose(f);
  return {ret, ss.str()};
}
TEST(test_test, 1) {
#define CALL_CMD(cmd)                                             \
  {                                                               \
    auto ret = CallSystem(std::string(cmd) + " 2>&1");             \
    LOG_DEBUG("call : [ " << cmd << " ] with ret: [" << ret.first \
                          << "]  and stdout :[\n"                 \
                          << ret.second << "\n]")                 \
  }
  CALL_CMD("ls -al")
  CALL_CMD("ip  addr ")
  CALL_CMD("ifconfig")
  CALL_CMD("tar -xzvf sdfagf.gzg 2>&1")
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}