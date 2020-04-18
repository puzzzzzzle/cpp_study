//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "def.h"
#include "inc1.h"
#include "inc2.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    DefTest defTest{};
    Inc1Test inc1Test{};
    Inc2Test inc2Test{};
    defTest.test();
    inc1Test.test();
    inc2Test.test();


    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}