//
// Created by tao on 19-1-17.
//
#include <fstream>

#include "common_includes.h"
#include "snow_flake_change.h"
#include "time_gap.hpp"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(chrono, 1) {
    SnowFlakeChange snowFlakeChange{};
    snowFlakeChange.SetID(10);
    // unix time : +8 2020-04-18 14:50:44
    snowFlakeChange.SetEpoch(1587192644152);
    //    snowFlakeChange.SetEpoch(getNowMs());

    // gen
    std::set<long> uidSet{};
    {
        //        LOG_DEBUG("start correct test")
        for (int i = 0; i < 100000000; ++i) {
            auto uid = snowFlakeChange.Generate();
            if (!uidSet.insert(uid).second) {
                LOG_ERROR("uid fail ")
                LOG_DEBUG("\n" << snowFlakeChange.DumpInfo())
            }
        }
    }
}
int main(int argc, char **argv) {
    int iRet = 0;
    //    iRet     = beforeRun();
    //    if (iRet) {
    //        std::cerr << "init fail with " << iRet << std::endl;
    //    }
    //    testing::InitGoogleTest(&argc, argv);
    //    iRet = RUN_ALL_TESTS();
    SnowFlakeChange snowFlakeChange{};
    snowFlakeChange.SetID(10);
    // unix time : +8 2020-04-18 14:50:44
    //    snowFlakeChange.SetEpoch(1587192644152);
    snowFlakeChange.SetEpoch(getNowMs());

    // gen
    TimeGap        gap{};
    std::set<long> uidSet{};
    {
        //        LOG_DEBUG("start correct test")
        for (int i = 0; i < 100000000; ++i) {
            auto uid = snowFlakeChange.Generate();
            if (!uidSet.insert(uid).second) {
                LOG_ERROR("uid fail ")
                LOG_ERROR("\n" << snowFlakeChange.DumpInfo())
                iRet = -1;
            }
        }
    }
    LOG_DEBUG("time use(us) : " << gap.gap())
    return iRet;
}