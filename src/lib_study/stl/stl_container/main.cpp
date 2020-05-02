//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "stl_common_containor.h"

int run_gtest(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int main(int argc, char **argv) {
    log_init();

    return run_gtest(argc, argv);
}