//
// Created by khalidzhang on 2020/1/16.
//

#include "GameLoopMock.h"
#include "common_includes.h"

TEST(game_loop, 5_5) {
  TimeGap gap;
  LOG_DEBUG("start game loop")
  GameMockApi api(5 * MICRO_MILLI, 5 * MICRO_MILLI);
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_LE(abs(status.fixedUpdateSpeed - 60), 1);
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
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_LE(abs(status.fixedUpdateSpeed - 60), 1);
      LOG_INFO(status);
    }
    api.Stop();
  };
  std::thread obThread(std::bind(obFunc, 5));
  obThread.detach();
  api.GameLoop();
  LOG_DEBUG("end game loop time : " << gap.gap())
}

TEST(game_loop, 20_1) {
  TimeGap gap;
  LOG_DEBUG("start game loop")
  GameMockApi api(20 * MICRO_MILLI, 1 * MICRO_MILLI);
  auto timeOutCallBack = DELEGRATE_FIXED_TIMEOUT([](long time) {
    LOG_WARNING("fixed update time out happened : " << time)
  });
  api.GetFixedTimeOutEventPrt()->Register(timeOutCallBack);
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_GE(abs(status.fixedUpdateSpeed - 60), 1);
      LOG_INFO(status);
    }
    api.Stop();
  };
  std::thread obThread(std::bind(obFunc, 5));
  obThread.detach();
  api.GameLoop();
  LOG_DEBUG("end game loop time : " << gap.gap())
}

TEST(fixed_update, fixed_update_120) {
  TimeGap gap;
  LOG_DEBUG("start game loop")
  GameMockApi api(0 * MICRO_MILLI, 0 * MICRO_MILLI);
  api.SetFixedUpdateFrequency(120);
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_LE(abs(status.fixedUpdateSpeed - 120), 1);
      LOG_INFO(status);
    }
    api.Stop();
  };
  std::thread obThread(std::bind(obFunc, 5));
  obThread.detach();
  api.GameLoop();
  LOG_DEBUG("end game loop time : " << gap.gap())
}

TEST(fixed_update, fixed_update_0) {
  TimeGap gap;
  LOG_DEBUG("start game loop")
  GameMockApi api(0 * MICRO_MILLI, 0 * MICRO_MILLI);
  api.SetFixedUpdateFrequency(0);
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_LE(abs(status.fixedUpdateSpeed - 0), 1);
      LOG_INFO(status);
    }
    api.Stop();
  };
  std::thread obThread(std::bind(obFunc, 5));
  obThread.detach();
  api.GameLoop();
  LOG_DEBUG("end game loop time : " << gap.gap())
}

TEST(fixed_update, fixed_update_120_limit_30) {
  TimeGap gap;
  LOG_DEBUG("start game loop")
  GameMockApi api(0 * MICRO_MILLI, 0 * MICRO_MILLI);
  api.SetFixedUpdateFrequency(120);
  api.SetLimitUpdateFrequencyMax(30);
  auto obFunc = [&api](int maxTime) -> void {
    LOG_INFO("ob start");
    for (int i = 0; i <= maxTime; ++i) {
      TimeTools::SleepSec(1);
      auto status = api.statusHandle.GetStatus();
      EXPECT_LE(abs(status.fixedUpdateSpeed - 120), 1);
      LOG_INFO(status);
    }
    api.Stop();
  };
  std::thread obThread(std::bind(obFunc, 5));
  obThread.detach();
  api.GameLoop();
  LOG_DEBUG("end game loop time : " << gap.gap())
}