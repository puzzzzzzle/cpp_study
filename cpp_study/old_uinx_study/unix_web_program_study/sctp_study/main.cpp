//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>

#include <thread>

#include "log_init.hpp"
#include "log_macro.h"

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    int result;
    log_init();
    INFO("log4cplus start!");
    testing::InitGoogleTest(&argc, argv);

    result = RUN_ALL_TESTS();
    return result;
}