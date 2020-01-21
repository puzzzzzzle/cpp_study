//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>

#include <thread>

#include "boost_log_init.h"
#include "epoll_simple_test.hpp"
#include "epoll_svr.h"

#define HOST "127.0.0.1"
#define PORT 9015

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    int result = 0;
    log_init();
    //
    //    if(start_epoll_svr(HOST, PORT)){
    //        FATAL("start svr err")
    //        exit(-1);
    //    }
    //    sleep(1);
    //
    //    testing::InitGoogleTest(&argc, argv);
    //    result = RUN_ALL_TESTS();

    epoll_simple_test();
    return result;
}