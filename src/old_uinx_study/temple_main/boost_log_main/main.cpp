//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>

#include <thread>

#include "boost_log_init.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    int result = 0;
    log_init();
    testing::InitGoogleTest(&argc, argv);
    result = RUN_ALL_TESTS();
    return result;
}