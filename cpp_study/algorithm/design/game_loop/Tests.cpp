//
// Created by khalidzhang on 2020/1/16.
//

#include "GameLoopMock.h"
#include "common_includes.h"

TEST(game_loop, 5_5) {
    TimeGap gap;
    LOG_DEBUG("start game loop")
    GameMockApi api(5 * MICRO_MILLI, 5 * MICRO_MILLI);
    auto        obFunc = [&api](int maxTime) -> void {
        LOG_INFO("ob start");
        for (int i = 0; i <= maxTime; ++i) {
            SleepSec(1);
            auto status = api.GetStatus();
            EXPECT_LE(abs(status.physicalSpeed - 60), 1);
            LOG_INFO(status);
        }
        api.Stop();
    };
    std::thread obThread(std::bind(obFunc, 5));
    obThread.detach();
    api.GameLoop();
    LOG_DEBUG("end game loop time : " << gap.gap())
}

TEST(game_loop, 1_1) {
    TimeGap gap;
    LOG_DEBUG("start game loop")
    GameMockApi api(1 * MICRO_MILLI, 1 * MICRO_MILLI);
    auto        obFunc = [&api](int maxTime) -> void {
        LOG_INFO("ob start");
        for (int i = 0; i <= maxTime; ++i) {
            SleepSec(1);
            auto status = api.GetStatus();
            EXPECT_LE(abs(status.physicalSpeed - 60), 1);
            LOG_INFO(status);
        }
        api.Stop();
    };
    std::thread obThread(std::bind(obFunc, 5));
    obThread.detach();
    api.GameLoop();
    LOG_DEBUG("end game loop time : " << gap.gap())
}
TEST(game_loop, 0_0) {
    TimeGap gap;
    LOG_DEBUG("start game loop")
    GameMockApi api(0 * MICRO_MILLI, 0 * MICRO_MILLI);
    auto        obFunc = [&api](int maxTime) -> void {
        LOG_INFO("ob start");
        for (int i = 0; i <= maxTime; ++i) {
            SleepSec(1);
            auto status = api.GetStatus();
            EXPECT_LE(abs(status.physicalSpeed - 60), 1);
            LOG_INFO(status);
        }
        api.Stop();
    };
    std::thread obThread(std::bind(obFunc, 5));
    obThread.detach();
    api.GameLoop();
    LOG_DEBUG("end game loop time : " << gap.gap())
}