//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <stdio.h>
#include <inttypes.h>

extern "C" int64_t maxofthree(int64_t, int64_t, int64_t);

TEST(test_test, 1) {
    printf("%ld\n", maxofthree(1, -4, -7));
    printf("%ld\n", maxofthree(2, -6, 1));
    printf("%ld\n", maxofthree(2, 3, 1));
    printf("%ld\n", maxofthree(-2, 4, 3));
    printf("%ld\n", maxofthree(2, -6, 5));
    printf("%ld\n", maxofthree(2, 4, 6));
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet = beforeRun();
    if(iRet){
        std::cerr<<"init fail with "<<iRet<<std::endl;
    }
    testing::InitGoogleTest(&argc,argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}