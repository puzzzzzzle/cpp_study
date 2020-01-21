//
// Created by tao on 18-11-24.
//

#ifndef UNIXSTUDYCPP_PERRTEST_H
#define UNIXSTUDYCPP_PERRTEST_H

#include <cstdio>
#include <cstdlib>

void perrTest() {
    FILE *p;
    if ((p = fopen("/notExits", "r+")) == nullptr) {
        perror("ERROR:\t");
        // perror 不会结束函数，手动退出为好
        exit(EXIT_FAILURE);
    }
    printf("open OK!");
}
#endif  // UNIXSTUDYCPP_PERRTEST_H
