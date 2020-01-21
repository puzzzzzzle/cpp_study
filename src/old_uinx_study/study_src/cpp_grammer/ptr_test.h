//
// Created by tao on 18-11-25.
//

#ifndef UNIXSTUDYCPP_PTR_TEST_H
#define UNIXSTUDYCPP_PTR_TEST_H

#include <cstdio>

void ptr_func1(int, char *);

void ptr_test() {
    void (*func1)(int, char *) = ptr_func1;
    func1(0, const_cast<char *>("sss"));
}

void ptr_func1(int argc, char *argv) { printf("ptrfunc1\n"); }

#endif  // UNIXSTUDYCPP_PTR_TEST_H
