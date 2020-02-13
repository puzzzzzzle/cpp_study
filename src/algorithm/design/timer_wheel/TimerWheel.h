//
// Created by tao zhang on 2020/2/11.
//

#pragma once

#include <mutex>

namespace TimerWheel {
    using CallBack = std::function<void()>;

    struct TimerPoint {
        uint32_t hour{}, minute{}, second{}, frame{};

        std::string ToString() {
            std::ostringstream oss{};
            oss << "hour{" << hour << "}, minute{" << minute << "}, second{" << second << "}, frame{" << frame << "};";
            return oss.str();
        }
    };

    TimerPoint SubTimer(const TimerPoint &lhs, const TimerPoint &rhs, uint32_t FRAME_PEER_SECOND) {
        TimerPoint timerPoint{};
        timerPoint.frame = lhs.frame + rhs.frame;
        timerPoint.second = lhs.second + rhs.second;
        timerPoint.minute = lhs.minute + rhs.minute;
        timerPoint.hour = lhs.hour + rhs.hour;
        if (timerPoint.frame >= FRAME_PEER_SECOND) {
            timerPoint.second += timerPoint.frame / FRAME_PEER_SECOND;
            timerPoint.frame = timerPoint.frame % FRAME_PEER_SECOND;
        }
        if (timerPoint.second >= 60) {
            timerPoint.minute += timerPoint.second / 60;
            timerPoint.second = timerPoint.second % 60;
        }
        if (timerPoint.minute >= 60) {
            timerPoint.hour += timerPoint.minute / 60;
            timerPoint.minute = timerPoint.minute % 60;
        }
        if (timerPoint.hour >= 24) {
            timerPoint.hour = timerPoint.hour % 24;
        }
        return timerPoint;
    }

    struct TimerTask {
        TimerPoint timerPoint{};
        CallBack func{};
        bool repeatable{false};
        bool canceled{false};
//        bool called{false};

        void Cancel() {
            canceled = true;
        }

        std::string ToString() {
            std::ostringstream oss{};
//            oss << "hour{" << hour << "},minute{" << minute << "},second{" << second << "},peerSecond{" << peerSecond
//                << "}";
//            oss << "millisecond{" << millisecond << "}";
            return oss.str();
        }

    };

    template<uint32_t FRAME_PEER_SECOND = 60>
    class TimerWheel {
        const uint64_t TOTAL_MILLISECONDS = 24 * 60 * 60 * 1000;
        const uint64_t FRAME_PEER_DAY = 24 * 60 * 60 * FRAME_PEER_SECOND;
        const uint64_t FRAME_PEER_HOUR = 60 * 60 * FRAME_PEER_SECOND;
        const uint64_t FRAME_PEER_MINUTE = 60 * FRAME_PEER_SECOND;
        const uint64_t MILLISECONDS_PEER_FRAME = 1000 / FRAME_PEER_SECOND;

        using SlotContainer = std::vector<std::shared_ptr<TimerTask>>;

        std::array<SlotContainer, 24> hourSlot{};
        std::array<SlotContainer, 60> minuteSlot{};
        std::array<SlotContainer, 60> secondSlot{};
        std::array<SlotContainer, FRAME_PEER_SECOND> frameSlot{};

        TimerPoint nextFrameTimerPoint{}, oneFrame{}; // 下一个要执行的帧

        std::mutex lock{};
    public:
        TimerWheel() {
            nextFrameTimerPoint.frame = 1;  // 初始化后应该执行下一帧的数据，让第一次调用前的注册到第一帧上，第0帧用来初始化
            oneFrame.frame = 1;   // 每次前进1帧
        }

    public:
        std::pair<int, std::weak_ptr<TimerTask>>
        DAfterMillSeconds(uint64_t millisecond, const CallBack &callBack, bool repeatable = false) {
            if (millisecond >= TOTAL_MILLISECONDS) {
                return {-1, {}};
            }
            return DoAfterFrame(millisecond / 1000 * FRAME_PEER_SECOND + (millisecond % 1000) / MILLISECONDS_PEER_FRAME,
                                callBack, repeatable);
        }

        std::pair<int, std::weak_ptr<TimerTask>>
        DoAfterFrame(std::shared_ptr<TimerTask> task) {
            // 插入task
            do {
                // 插入
                TimerPoint targetTimer = SubTimer(nextFrameTimerPoint, task->timerPoint, FRAME_PEER_SECOND);
                if (targetTimer.hour != nextFrameTimerPoint.hour) {
                    hourSlot[targetTimer.hour].push_back(task);
                    break;
                }
                if (targetTimer.minute != nextFrameTimerPoint.minute) {
                    minuteSlot[targetTimer.minute].push_back(task);
                    break;
                }
                if (targetTimer.second != nextFrameTimerPoint.second) {
                    secondSlot[targetTimer.second].push_back(task);
                    break;
                }
                if (targetTimer.frame != nextFrameTimerPoint.frame) {
                    frameSlot[targetTimer.frame].push_back(task);
                    break;
                }
                // 插入的就是当前帧的下一帧
                frameSlot[targetTimer.frame].push_back(task);
            } while (false);
            return {0, std::weak_ptr<TimerTask>(task)};
        }

        std::pair<int, std::weak_ptr<TimerTask>>
        DoAfterFrame(uint64_t frame, const CallBack &callBack, bool repeatable = false) {
            if (frame >= FRAME_PEER_DAY) {
                return {-1, {}};
            }
            auto task = std::make_shared<TimerTask>();
            // 分解时间到帧,并构建task
            {
                auto &point = task->timerPoint;
                point.hour = frame / FRAME_PEER_HOUR;
                point.minute = frame % FRAME_PEER_HOUR / FRAME_PEER_MINUTE;
                point.second = frame % FRAME_PEER_HOUR % FRAME_PEER_MINUTE / FRAME_PEER_SECOND;
                point.frame = frame % FRAME_PEER_HOUR % FRAME_PEER_MINUTE % FRAME_PEER_SECOND;
                task->func = callBack;
                task->repeatable = repeatable;
            }
            std::lock_guard<std::mutex> lockGuard(lock);
            return DoAfterFrame(task);
        }

        void Tick() {
            LOG_DEBUG(nextFrameTimerPoint.ToString())
            for (auto task : frameSlot[nextFrameTimerPoint.frame]) {
                if (task->canceled) {
                    continue;
                }
                task->func();
                if (task->repeatable) {
                    DoAfterFrame(task);
                }
            }
            frameSlot[nextFrameTimerPoint.frame].clear();
            nextFrameTimerPoint = SubTimer(nextFrameTimerPoint, oneFrame, FRAME_PEER_SECOND);
            if (nextFrameTimerPoint.frame == 0) {
                if (nextFrameTimerPoint.second == 0) {
                    if (nextFrameTimerPoint.minute == 0) {
                        if (nextFrameTimerPoint.hour == 0) {

                        }
                    }
                }
            }
        }
    };
}
