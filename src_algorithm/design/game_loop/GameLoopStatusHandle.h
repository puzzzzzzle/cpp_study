//
// Created by tao zhang on 2020/2/16.
//

#pragma once

class StatusHandle {
  public:
  typedef struct Status {
    long fixedUpdateSpeed{};
    long limitUpdateSpeed{};
    long remainUpdateSpeed{};
    friend std::ostream &operator<<(std::ostream &os, const Status &status) {
      os << "fixedUpdateSpeed:" << status.fixedUpdateSpeed
         << ",limitUpdateSpeed:" << status.limitUpdateSpeed
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
    Status status{};
    clock_gettime(CLOCK_MONOTONIC, &nowTime);
    auto gap = TimeTools::SubTime(nowTime, lastStatusTime);
    long sec = gap.tv_sec + gap.tv_nsec / SEC_NANO;
    status.fixedUpdateSpeed = fixedUpdateTimes / sec;
    status.limitUpdateSpeed = limitUpdateTimes / sec;
    status.remainUpdateSpeed = remainUpdateTimes / sec;

    // 清理数据
    clock_gettime(CLOCK_MONOTONIC, &lastStatusTime);
    fixedUpdateTimes = 0;
    limitUpdateTimes = 0;
    remainUpdateTimes = 0;
    return std::move(status);
  }
};
