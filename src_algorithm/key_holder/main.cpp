//
// Created by tao on 19-1-17.
//
#include <cassert>

#include "KeyHolder.h"
#include "common_includes.h"
#include "time_gap.hpp"
int main(int argc, char **argv) {
  auto holder = std::make_shared<KeyHolder<uint64_t>>(100000000);
  uint64_t key{}, operate{};
  int ret{};
  TimeGap gap{};
  for (int i = 0; i < 10000000; ++i) {
    if (i % 1000000 == 0) {
      LOG_DEBUG("now at " << i)
    }
    operate = RAND(0, 100);
    if (operate < 80) {
      //            LOG_DEBUG("add\t" << i);
      ret = holder->Add(i);
      if (ret == 0) {
      } else if (ret == -2) {
        LOG_DEBUG("full\t" << i);
      } else {
        LOG_DEBUG("fail add m_searchRet \t" << ret);
      }
    } else {
      ret = holder->Rand(&key);
      if (ret == 0) {
        //                LOG_DEBUG("rem\t" << key);
        assert(holder->Remove(key) == 0);
      } else if (ret == 1) {
        LOG_DEBUG("empty\t" << key);
      } else {
        LOG_DEBUG("fail rem m_searchRet\t" << key);
      }
    }
  }
  LOG_DEBUG("time\t" << gap.gap())

  //    int iRet = 0;
  //    testing::InitGoogleTest(&argc, argv);
  //    iRet = RUN_ALL_TESTS();
  //    return iRet;
}