//
// Created by tao on 18-11-25.
//

#ifndef UNIXSTUDYCPP_TIMEQUESTION_H
#define UNIXSTUDYCPP_TIMEQUESTION_H

#include <stdint.h>
#include <stdlib.h>

#include <cstdio>
#include <cstring>
#include <ctime>
void timeQuestion() {
    time_t     max = INT64_MAX, up, down;
    struct tm* tmblock;
    // 处2查找第一个符合的
    while ((tmblock = localtime(&max)) == NULL) {
        printf("%ld\twrong!\n", max);
        max /= 2;
    }
    //二分查找最大值
    down = max;
    up   = max * 2;
    while (up - down > 1) {
        max = (down + up) / 2;
        printf("max:%ld\tdown:%ld\tup:%ld\t\n", max, down, up);
        if ((tmblock = localtime(&max)) == NULL) {
            up = max;
        } else {
            down = max;
        }
    }
    printf("max:%ld\tdown:%ld\tup:%ld\t\n", max, down, up);

    if ((tmblock = localtime(&up)) != NULL) {
        max = up;
    } else {
        max     = down;
        tmblock = localtime(&down);
    }

    printf("max val is %ld,\t max year is %d\tM is %d,day is %dt\n", max, tmblock->tm_year, tmblock->tm_mon,
           tmblock->tm_mday);
}

#endif  // UNIXSTUDYCPP_TIMEQUESTION_H
