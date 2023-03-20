//
// Created by tao zhang on 2020/2/11.
//

#pragma once

#include <mutex>

namespace TimerWheel {
struct TimerPoint {
  uint64_t day{}, hour{}, minute{}, second{}, frame{};

  std::string ToString() {
    std::ostringstream oss{};
    oss << "day{" << day << "},"
        << "hour{" << hour << "}, minute{" << minute << "}, second{" << second
        << "}, frame{" << frame << "};";
    return oss.str();
  }
};

using CallBack = std::function<void(TimerPoint &)>;

struct TimerTask {
  TimerPoint delayTimerPoint{};
  TimerPoint nextExecTimerPoint{};

  CallBack func{};
  bool repeatable{false};
  bool canceled{false};
  //        bool called{false};

  void Cancel() { canceled = true; }

  std::string ToString() {
    std::ostringstream oss{};
    return oss.str();
  }
};

template <uint64_t FRAME_PEER_SECOND = 60, uint64_t MAX_DAY_NUM = 365>
class TimerWheel {
  const uint64_t FRAME_PEER_ROUND =
      MAX_DAY_NUM * 24 * 60 * 60 * FRAME_PEER_SECOND;
  const uint64_t FRAME_PEER_DAY = 24 * 60 * 60 * FRAME_PEER_SECOND;
  const uint64_t FRAME_PEER_HOUR = 60 * 60 * FRAME_PEER_SECOND;
  const uint64_t FRAME_PEER_MINUTE = 60 * FRAME_PEER_SECOND;
  const uint64_t MILLISECONDS_PEER_FRAME = 1000 / FRAME_PEER_SECOND;

  using SlotContainer = std::vector<std::shared_ptr<TimerTask>>;

  std::array<SlotContainer, MAX_DAY_NUM> daySlot{};
  std::array<SlotContainer, 24> hourSlot{};
  std::array<SlotContainer, 60> minuteSlot{};
  std::array<SlotContainer, 60> secondSlot{};
  std::array<SlotContainer, FRAME_PEER_SECOND> frameSlot{};

  TimerPoint nextFrameTimerPoint{}, oneFrame{};  // 每次推进多少帧

  std::mutex lock{};

  public:
  TimerWheel() {
    oneFrame.frame = 1;  // 每次前进1帧
  }

  private:
  TimerPoint AddTimePoint(const TimerPoint &lhs, const TimerPoint &rhs) {
    TimerPoint timerPoint{};
    timerPoint.frame = lhs.frame + rhs.frame;
    timerPoint.second = lhs.second + rhs.second;
    timerPoint.minute = lhs.minute + rhs.minute;
    timerPoint.hour = lhs.hour + rhs.hour;
    timerPoint.day = lhs.day + rhs.day;

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
      timerPoint.day += timerPoint.hour / 24;
      timerPoint.hour = timerPoint.hour % 24;
    }
    if (timerPoint.day >= MAX_DAY_NUM) {
      timerPoint.day = timerPoint.day / MAX_DAY_NUM;
    }
    return timerPoint;
  }

  std::pair<int, std::weak_ptr<TimerTask>> DoAfterFrame(
      std::shared_ptr<TimerTask> task) {
    // 插入task
    do {
      // 插入
      TimerPoint &targetTimer = task->nextExecTimerPoint;
      targetTimer = AddTimePoint(nextFrameTimerPoint, task->delayTimerPoint);
      if (targetTimer.day != nextFrameTimerPoint.day) {
        daySlot[targetTimer.day].push_back(task);
        break;
      }
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

  public:
  //        std::pair<int, std::weak_ptr<TimerTask>>
  //        DoAfterMillSeconds(uint64_t millisecond, const CallBack &callBack,
  //        bool repeatable = false) {
  //            if (millisecond >= TOTAL_MILLISECONDS) {
  //                return {-1, {}};
  //            }
  //            return DoAfterFrame(millisecond / 1000 * FRAME_PEER_SECOND +
  //            (millisecond % 1000) / MILLISECONDS_PEER_FRAME,
  //                                callBack, repeatable);
  //        }

  std::pair<int, std::weak_ptr<TimerTask>> DoAfterFrame(
      uint64_t frame, const CallBack &callBack, bool repeatable = false) {
    if (frame >= FRAME_PEER_ROUND) {
      return {-1, {}};
    }
    auto task = std::make_shared<TimerTask>();
    // 分解时间到帧,并构建task
    {
      auto &point = task->delayTimerPoint;
      point.day = frame / FRAME_PEER_ROUND;
      auto frameForDay = frame % FRAME_PEER_ROUND;
      point.hour = frameForDay / FRAME_PEER_HOUR;
      point.minute = frameForDay % FRAME_PEER_HOUR / FRAME_PEER_MINUTE;
      point.second =
          frameForDay % FRAME_PEER_HOUR % FRAME_PEER_MINUTE / FRAME_PEER_SECOND;
      point.frame =
          frameForDay % FRAME_PEER_HOUR % FRAME_PEER_MINUTE % FRAME_PEER_SECOND;
      task->i_func = callBack;
      task->repeatable = repeatable;
    }
    // 锁
    std::lock_guard<std::mutex> lockGuard(lock);
    return DoAfterFrame(task);
  }

  void Tick() {
    // 锁
    std::lock_guard<std::mutex> lockGuard(lock);

    for (const auto &task : frameSlot[nextFrameTimerPoint.frame]) {
      if (task->canceled) {
        continue;
      }
      // TODO : 使用线程池去执行，不要卡主流程
      task->i_func(nextFrameTimerPoint);
      if (task->repeatable) {
        DoAfterFrame(task);
      }
    }
    frameSlot[nextFrameTimerPoint.frame].clear();
    nextFrameTimerPoint = AddTimePoint(nextFrameTimerPoint, oneFrame);

#define RESOLVE(from, to)                                        \
  {                                                              \
    auto &from##Tasks = from##Slot[nextFrameTimerPoint.from];    \
    for (const std::shared_ptr<TimerTask> &task : from##Tasks) { \
      to##Slot[task->nextExecTimerPoint.to].push_back(task);     \
    }                                                            \
    from##Tasks.clear();                                         \
  }

    // 发生进位时分解当前point
    // TODO : 重构下，太丑了
    if (nextFrameTimerPoint.frame == 0) {
      if (nextFrameTimerPoint.second == 0) {
        if (nextFrameTimerPoint.minute == 0) {
          if (nextFrameTimerPoint.hour == 0) {
            if (nextFrameTimerPoint.day == 0) {
              // 一个round过去了，所有时间复位了
              // 这里不写也行，但是为了统一还是写一下
              // 分解第0day
              RESOLVE(day, hour)
            }
            RESOLVE(day, hour)
          }
          RESOLVE(hour, minute)
        }
        RESOLVE(minute, second)
      }
      RESOLVE(second, frame)
    }
  }
};
}  // namespace TimerWheel
