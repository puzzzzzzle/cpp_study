//
// Created by tao on 19-1-17.
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <thread>

#include "co_routine.h"
#include "co_routine_inner.h"
#include "common_includes.h"

int loop(void *) {
    return 0;
}
static void *routine_func(void *) {
    stCoEpoll_t *ev = co_get_epoll_ct();  // ct = current thread
    co_eventloop(ev, loop, 0);
    return 0;
}

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    std::thread t([]() { routine_func(nullptr); });
    t.detach();
    return iRet;
}