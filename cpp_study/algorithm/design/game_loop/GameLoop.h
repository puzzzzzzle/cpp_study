//
// Created by khalidzhang on 2020/1/16.
//

#pragma once

#include "common_includes.h"
#include "time.h"
#include "time_gap.hpp"
#include "unistd.h"

class GameApi {
protected:
    unsigned long nanoSecPeerUpdate{}; // 物理帧间隔
    unsigned long nanoSecPeerRender{}; // 渲染帧间隔
    bool isRun{true};
    timespec startTime{};

public:
    GameApi(unsigned long _nanoSecPeerUpdate)
            : nanoSecPeerUpdate(_nanoSecPeerUpdate) {}

public:
    virtual void Stop() { isRun = false; }
    virtual void DoInput() = 0;
    virtual void DoUpdate() = 0;
    virtual void DoRender() = 0;

public:
    int GameLoop() {
        timespec previous{}, current{};
        int iRet{};
        unsigned long lag{}; // 落后的时间
        if ((iRet = clock_gettime(CLOCK_MONOTONIC, &previous))) {
            return iRet;
        }
        startTime = previous;
        while (isRun) {
            clock_gettime(CLOCK_MONOTONIC, &current);
            lag += SubTimeNano(current, previous);

            // 处理输入
            DoInput();

            // 追赶落后的时间
            while (lag >= nanoSecPeerUpdate) {
                DoUpdate();
                lag -= nanoSecPeerUpdate;
            }
            DoRender();

            previous = current;
        }
        return 0;
    }
};
