//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

std::string GetInfo() { return "GlobalInfo"; }
class GetInfoBase {
  public:
  virtual std::string GetInfo() const { return "GetInfoBase"; }
  std::string Hello() { return "GetInfoBase::Hello:\t" + GetInfo(); }
};

class GetInfoImpl : public virtual GetInfoBase {
  public:
  virtual std::string GetInfo() const { return "GetInfoImpl"; }
  std::string Hello() { return "GetInfoImpl::Hello:\t" + GetInfo(); }
  std::string Greet() { return "GetInfoImpl::Greet:\t" + GetInfo(); }
};
TEST(test_test, 1) {
#define LOG_WITH_CODE(msg) LOG_DEBUG(#msg << "\t" << msg)
  LOG_WITH_CODE(GetInfo())
  LOG_WITH_CODE(GetInfoBase().Hello())
  LOG_WITH_CODE(GetInfoImpl().Greet())
  LOG_DEBUG(__FILE__)
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