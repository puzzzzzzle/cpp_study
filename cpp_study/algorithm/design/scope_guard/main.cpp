//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "common_classes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char** argv) {
    int  iRet  = 0;
    auto scope = MakeScopeGuard([]()-> void { LOG_DEBUG("run after exit scope") });
    iRet       = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}