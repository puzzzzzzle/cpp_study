//
// Created by tao zhang on 2020/2/14.
//
#include <time_gap.hpp>
#include "common_includes.h"
#include "TimerWheel.h"

const uint64_t ONE_DAY_FRAME = 60 * 60 * 60 * 24;

TEST(tick_frame, short_time) {
    TimerWheel::TimerWheel<> timerWheel{};

    struct TestResourceHandle {
        int varAddOnce{0};
        int varAddOnceOneDayDelay{0};

        int varAddEveryFrame{0};
        int varAddEverySecond{0};
        int varAddEveryMinute{0};
        int varAddEveryHour{0};
    };
    TestResourceHandle handle{};
    timerWheel.DoAfterFrame(100, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
//        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddOnce++;
    });
    timerWheel.DoAfterFrame(36 *60 * 60 * 60, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddOnceOneDayDelay++;
    });
    timerWheel.DoAfterFrame(1, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
//        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddEveryFrame++;
    }, true);
    timerWheel.DoAfterFrame(60, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
//        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddEverySecond++;
    }, true);
    timerWheel.DoAfterFrame(60 * 60, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
//        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddEveryMinute++;
    }, true);
    timerWheel.DoAfterFrame(60 * 60 * 60, [&handle](TimerWheel::TimerPoint &execTimerPoint) {
//        LOG_DEBUG(execTimerPoint.ToString())
        handle.varAddEveryHour++;
    }, true);
    TimeGap gap{};
    for (uint64_t i = 0; i <= 3*ONE_DAY_FRAME ; ++i) {
        timerWheel.Tick();
    }
    LOG_DEBUG("total tick used time(microsecond) :"<< gap.gap())
    ASSERT_EQ(handle.varAddOnce, 1);
    ASSERT_EQ(handle.varAddOnceOneDayDelay, 1);

    ASSERT_EQ(handle.varAddEveryHour, 3*ONE_DAY_FRAME / 60 / 60 / 60);
    ASSERT_EQ(handle.varAddEveryMinute, 3*ONE_DAY_FRAME / 60 / 60);
    ASSERT_EQ(handle.varAddEverySecond, 3*ONE_DAY_FRAME / 60);
    ASSERT_EQ(handle.varAddEveryFrame, 3*ONE_DAY_FRAME);
}
