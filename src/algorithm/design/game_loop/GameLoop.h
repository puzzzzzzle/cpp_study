//
// Created by khalidzhang on 2020/1/16.
//

#pragma once

#include <common_classes.h>

#include "common_includes.h"
#include "time.h"
#include "time_gap.hpp"
#include "unistd.h"
class StatusHandle {
public:
    typedef struct Status {
        long                 fixedUpdateSpeed{};
        long                 limitUpdateSpeed{};
        long                 remainUpdateSpeed{};
        friend std::ostream &operator<<(std::ostream &os, const Status &status) {
            os << "fixedUpdateSpeed:" << status.fixedUpdateSpeed << ",limitUpdateSpeed:" << status.limitUpdateSpeed
               << ",remainUpdateSpeed:" << status.remainUpdateSpeed;
            return os;
        }
    } Status;

private:
    timespec lastStatusTime{};

public:
    StatusHandle() { clock_gettime(CLOCK_MONOTONIC, &lastStatusTime); }
    long fixedUpdateTimes{}, limitUpdateTimes{}, remainUpdateTimes{};

    Status GetStatus() {
        timespec nowTime{};
        Status   status{};
        clock_gettime(CLOCK_MONOTONIC, &nowTime);
        auto gap                 = TimeTools::SubTime(nowTime, lastStatusTime);
        long sec                 = gap.tv_sec + gap.tv_nsec / SEC_NANO;
        status.fixedUpdateSpeed  = fixedUpdateTimes / sec;
        status.limitUpdateSpeed  = limitUpdateTimes / sec;
        status.remainUpdateSpeed = remainUpdateTimes / sec;

        // 清理数据
        clock_gettime(CLOCK_MONOTONIC, &lastStatusTime);
        fixedUpdateTimes  = 0;
        limitUpdateTimes  = 0;
        remainUpdateTimes = 0;
        return std::move(status);
    }
};

class GameLoopApi {
public:
    using FixedUpdateTimeOutCallBackFunc = void (*)(long timeOutTime);

protected:
    long                           nanoSecPeerFixedUpdate{};  // FixedUpdate 帧间隔
    long                           nanoSecPeerLimitUpdate{};  // LimitedUpdate 帧间隔
    bool                           isRun{true};
    timespec                       startTime{};
    FixedUpdateTimeOutCallBackFunc fixedUpdateTimeOutCallBackFunc{nullptr};  // fixed 调用超时 回调函数

public:
    GameLoopApi(long _nanoSecPeerFixedUpdate = 16666666) : nanoSecPeerFixedUpdate(_nanoSecPeerFixedUpdate) {}

public:
    /**
     * FixedUpdate调用超时回调
     * @param func
     */
    void SetFixedUpdateTimeOutCallBackFunc(FixedUpdateTimeOutCallBackFunc func) {
        fixedUpdateTimeOutCallBackFunc = func;
    }

    /**
     * FixedUpdate 频率, frequency <= 0 暂停
     * @param frequency
     */
    void SetFixedUpdateFrequency(int frequency) {
        if (frequency <= 0) {
            nanoSecPeerFixedUpdate = INT64_MAX;
        } else {
            nanoSecPeerFixedUpdate = 1000000000 / frequency;
        }
    }
    /**
     * LimitUpdate 频率, <=0 暂停,保证不超过这个上限
     * @param frequency
     */
    void SetLimitUpdateFrequencyMax(int frequency) {
        if (frequency <= 0) {
            nanoSecPeerLimitUpdate = INT64_MAX;
        } else {
            nanoSecPeerLimitUpdate = 1000000000 / frequency;
        }
    }

public:
    virtual void Stop() { isRun = false; }

public:
    /**
     * 每次循环开始前调用一次,不要放太多的逻辑
     */
    virtual void BeforeUpdate() = 0;
    /**
     * 优先级最高的调用,尽可能的保证按照固定的频率调用,时间不够时会优先调用它,一个loop中可能会调用多次进行追赶
     * 耗时不能频繁超过nanoSecPeerFixedUpdate,不然会导致永远也追赶不上进度
     */
    virtual void FixedUpdate() = 0;
    /**
     * 低速限制帧率的调用,保证不超过最大限制,用来进行一些旁路逻辑,如客户端进行渲染,服务端进行makeCache等
     */
    virtual void LimitedUpdate() = 0;
    /**
     * 每一个loop完成后剩余多少时间,可能为负,表示这一个loop超时了
     * @param remainTime 剩余时间 纳秒
     */
    virtual void RemainTimeUpdate(long remainNanoTime) = 0;

public:
    int GameLoop() {
        timespec previousLoopStart{}, currLoopStart{}, previousLimitedStart{}, currentLimitedStart{},
            currentRemainStart{};
        int  iRet{};
        long lag{};  // 落后的时间

        // 超时检测使用
        timespec fixedCheckTimeStart{}, fixedCheckTimeEnd;

        // 初始化时间
        if ((iRet = clock_gettime(CLOCK_MONOTONIC, &previousLoopStart))) {
            return iRet;
        }
        startTime            = previousLoopStart;
        previousLimitedStart = previousLoopStart;
        // 开始循环
        while (isRun) {
            clock_gettime(CLOCK_MONOTONIC, &currLoopStart);
            lag += TimeTools::SubTimeNano(currLoopStart, previousLoopStart);

            // 调用前
            BeforeUpdate();

            // FixedUpdate 固定间隔调用
            // 追赶落后的时间方式保证频率
            while (lag >= nanoSecPeerFixedUpdate) {
                // 超时检测
                clock_gettime(CLOCK_MONOTONIC, &fixedCheckTimeStart);
                // 超时回调
                auto scopeGuard = MakeScopeGuard([&fixedCheckTimeStart, &fixedCheckTimeEnd, this]() {
                    clock_gettime(CLOCK_MONOTONIC, &fixedCheckTimeEnd);
                    long timeOutTime = TimeTools::SubTimeNano(fixedCheckTimeEnd, fixedCheckTimeStart);
                    if (timeOutTime > nanoSecPeerFixedUpdate) {
                        if (fixedUpdateTimeOutCallBackFunc != nullptr) {
                            fixedUpdateTimeOutCallBackFunc(timeOutTime);
                        }
                    }
                });

                FixedUpdate();
                lag -= nanoSecPeerFixedUpdate;
            }

            // LimitedUpdate 主逻辑已经追赶上了可以进行一些旁路逻辑
            clock_gettime(CLOCK_MONOTONIC, &currentLimitedStart);
            if (TimeTools::SubTimeNano(currentLimitedStart, previousLimitedStart) >= nanoSecPeerLimitUpdate &&
                TimeTools::SubTimeNano(currentLimitedStart, currLoopStart) < nanoSecPeerFixedUpdate) {
                LimitedUpdate();
                previousLimitedStart = currentLimitedStart;
            }

            // 剩余时间调用
            clock_gettime(CLOCK_MONOTONIC, &currentRemainStart);
            RemainTimeUpdate(nanoSecPeerFixedUpdate - TimeTools::SubTimeNano(currentRemainStart, currLoopStart));
            previousLoopStart = currLoopStart;
        }
        return 0;
    }
};
