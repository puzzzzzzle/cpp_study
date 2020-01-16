//
// Created by khalidzhang on 2020/1/16.
//

#pragma once
#include "GameLoop.h"


class GameMockApi : public GameApi {

    //// status
public:
    typedef struct Status {
        long fps{};
        long physicalSpeed{};
        friend std::ostream &operator<<(std::ostream &os, const Status &status) {
            os << "fps:" << status.fps << ",physicalSpeed:" << status.physicalSpeed;
            return os;
        }
    } Status;

private:
    // int 一写多读造成的原子性延迟在统计fps之类时可以忽略,为提高速度就不用atomic了
    unsigned int updateTimes{};
    unsigned int renderTimes{};
    timespec lastStatusTime{};
    bool gettingStatus{false};
    //// status end

private:
    long logicNanoTime{};
    long renderNanoTime{};

public:
    GameMockApi(long _logicNanoTime, long _renderNanoTime,
                long _nanoSecPeerUpdate)
            : GameApi(_nanoSecPeerUpdate), logicNanoTime(_logicNanoTime),
              renderNanoTime(_renderNanoTime) {
        clock_gettime(CLOCK_MONOTONIC, &lastStatusTime);
    }

public:
    virtual void DoInput() override {}
    virtual void DoUpdate() override {
        if (logicNanoTime > 0) {
            SleepNano(logicNanoTime);
        }
        ++updateTimes;
    }
    virtual void DoRender() override {
        if (renderNanoTime > 0) {
            SleepNano(renderNanoTime);
        }
        ++renderTimes;
    }

public:
    virtual Status GetStatus() {
        timespec nowTime{};
        Status status{};
        clock_gettime(CLOCK_MONOTONIC, &nowTime);
        auto gap = SubTime(nowTime, lastStatusTime);
        long sec = gap.tv_sec + gap.tv_nsec / SEC_NANO;
        status.fps = renderTimes / sec;
        status.physicalSpeed = updateTimes / sec;
        clock_gettime(CLOCK_MONOTONIC, &lastStatusTime);
        updateTimes = 0;
        renderTimes = 0;
        return std::move(status);
    }
};