//
// Created by khalidzhang on 2019/12/6.
//

#ifndef CPP_STUDY_ALL_TIME_GAP_HPP
#define CPP_STUDY_ALL_TIME_GAP_HPP

#include <sys/time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
#define MICRO_NANO (1000)
#define SEC_MICRO (MICRO_NANO * 1000)
#define SEC_NANO (SEC_MICRO * 1000)
#define MICRO_MILLI (1000 * 1000)

class TimeGap {
public:
    TimeGap() {
        if (gettimeofday(&start, nullptr)) {
            exit(-100);
        }
    }

    /**
     * 获取和开始时间相差的微秒数
     * @return 微秒数
     */
    inline long gap() {
        timeval end{};
        if (gettimeofday(&end, nullptr)) {
            return -1;
        }
        return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    }

    /**
     * 获取和开始时间相差的秒数
     * @return 秒数
     */
    inline long gapSec() {
        timeval end{};
        if (gettimeofday(&end, nullptr)) {
            return -1;
        }
        return (end.tv_sec - start.tv_sec);
    }

    inline int resetStart(const timeval &_start) {
        start = _start;
        return 0;
    }

    inline int resetStartNow() { return gettimeofday(&start, nullptr); }

private:
    timeval start{};
};
class TimeTools{
public:
    static void SleepMicro(long microSeconds) {
        timespec req{}, rem{};
        req.tv_sec  = microSeconds / SEC_MICRO;
        req.tv_nsec = (microSeconds % SEC_MICRO) * MICRO_NANO;
        int iRet{};
        do {
            iRet = nanosleep(&req, &rem);
            if (iRet) {
                std::cerr << strerror(errno) << std::endl;

                req = rem;
            }
        } while (iRet);
    }
    static void SleepNano(timespec req) {
        timespec rem{};
        int      iRet{};
        do {
            iRet = nanosleep(&req, &rem);
            if (iRet) {
                std::cerr << strerror(errno) << std::endl;

                req = rem;
            }
        } while (iRet);
    }
    static void SleepNano(long nanoSeconds) {
        timespec req{}, rem{};
        req.tv_sec  = nanoSeconds / SEC_NANO;
        req.tv_nsec = (nanoSeconds % SEC_NANO);
        int iRet{};
        do {
            iRet = nanosleep(&req, &rem);
            if (iRet) {
                std::cerr << strerror(errno) << std::endl;

                req = rem;
            }
        } while (iRet);
    }
    static void        SleepSec(long sec) { SleepNano(sec * SEC_NANO); }
    static inline long SubTimeMicro(timespec &end, timespec &start) {
        return (end.tv_sec - start.tv_sec) * SEC_MICRO + (end.tv_nsec - start.tv_nsec) / MICRO_NANO;
    }
    static inline long SubTimeNano(timespec &end, timespec &start) {
        return (end.tv_sec - start.tv_sec) * SEC_NANO + (end.tv_nsec - start.tv_nsec);
    }
    static inline timespec SubTime(timespec &end, timespec &start) {
        return timespec{end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec};
    };
};

#endif  // CPP_STUDY_ALL_TIME_GAP_HPP
