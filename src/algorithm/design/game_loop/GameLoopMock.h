//
// Created by khalidzhang on 2020/1/16.
//

#pragma once
#include "GameLoop.h"
#include "GameLoopStatusHandle.h"

class GameMockApi : public GameLoopApi {
private:
    long logicNanoTime{};
    long renderNanoTime{};

public:
    StatusHandle statusHandle{};
    GameMockApi(long _logicNanoTime, long _renderNanoTime)
        : logicNanoTime(_logicNanoTime), renderNanoTime(_renderNanoTime) {}

public:
    virtual void BeforeUpdate() override {}
    virtual void FixedUpdate() override {
        if (logicNanoTime > 0) {
            TimeTools::SleepNano(logicNanoTime);
        }
        ++statusHandle.fixedUpdateTimes;
    }
    virtual void LimitedUpdate() override {
        if (renderNanoTime > 0) {
            TimeTools::SleepNano(renderNanoTime);
        }
        ++statusHandle.limitUpdateTimes;
    }
    virtual void RemainTimeUpdate(long remainNanoTime) override {
        //        LOG_DEBUG("remain time is "<< remainNanoTime)
        //        if (remainNanoTime > 0) {
        //            SleepNano(remainNanoTime);
        //        }
        ++statusHandle.remainUpdateTimes;
    }

public:
};