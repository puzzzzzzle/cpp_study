//
// Created by khalidzhang on 2019/12/6.
//

#ifndef CPP_STUDY_ALL_TIME_GAP_HPP
#define CPP_STUDY_ALL_TIME_GAP_HPP

#include <sys/time.h>

class TimeGap
{
public:
    TimeGap()
    {
        if (gettimeofday(&start, nullptr))
        {
            exit(-100);
        }
    }

    /**
     * 获取和开始时间相差的微秒数
     * @return 微秒数
     */
    inline long gap()
    {
        timeval end{};
        if (gettimeofday(&end, nullptr))
        {
            return -1;
        }
        return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    }

    /**
     * 获取和开始时间相差的秒数
     * @return 秒数
     */
    inline long gapSec()
    {
        timeval end{};
        if (gettimeofday(&end, nullptr))
        {
            return -1;
        }
        return (end.tv_sec - start.tv_sec);
    }

    inline int resetStart(const timeval &_start)
    {
        start = _start;
        return 0;
    }

    inline int resetStartNow()
    {
        return gettimeofday(&start, nullptr);
    }

private:
    timeval start{};
};

#endif //CPP_STUDY_ALL_TIME_GAP_HPP
