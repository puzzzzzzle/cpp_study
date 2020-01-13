//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <new>
char buff[4096]{0};

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
    int *arr = new(buff) int[50];
    ASSERT_TRUE(buff == (char*)arr);
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