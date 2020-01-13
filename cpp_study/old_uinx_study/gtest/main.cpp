//
// Created by tao on 19-1-17.
//

#include <string.h>
#include <unistd.h>
#include "log_init.hpp"
#include "log_macro.h"
#include <gtest/gtest.h>

#include "simple_test.h"

TEST(testCase, test0) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(testCase, wrong) {
//    malloc(100);
    EXPECT_EQ(add(2, 3), 6);
}

TEST(testSTR, test0) {
    EXPECT_STREQ("hhh", "hhh");
}

int call_test(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

int main(int argc, char **argv) {
    log_init();
    TRACE("trace")
    INFO("info!")
    DEBUG("debug")
    WARN("warn")
    ERROR("err")
    FATAL("fatal")
    return call_test(argc, argv);


}
