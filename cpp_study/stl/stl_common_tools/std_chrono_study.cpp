//
// Created by tao on 19-2-25.
//
#include "std_chrono_study.h"

namespace ch1 = std::chrono;

void test_chrono() {
    std::chrono::hours                             six_hours(6);
    std::chrono::duration<int64_t, std::ratio<60>> six_minutes(6);
    std::chrono::minutes                           six_minutes_1(6);
    DEBUG((six_minutes == six_minutes_1))

    // epoch
    std::chrono::system_clock::time_point tp;
    DEBUG("epoch:\t" << asString(tp))

    // now
    tp = std::chrono::system_clock::now();
    DEBUG("now:\t" << asString(tp))

    tp = std::chrono::system_clock::time_point::min();
    DEBUG("min:\t" << asString(tp))

    tp = std::chrono::system_clock::time_point::max();
    DEBUG("max:\t" << asString(tp))
}

std::string asString(std::chrono::system_clock::time_point tp) {
    std::time_t t  = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size() - 1);
    return ts;
}
