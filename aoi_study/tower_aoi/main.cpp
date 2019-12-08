//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet = beforeRun();
//    srand(0);       // 保证每次随机到的一样，方便测试
    srand(time(nullptr));       // 随机测试，扩大样本

    if(iRet){
        std::cerr<<"init fail with "<<iRet<<std::endl;
    }
    testing::InitGoogleTest(&argc,argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}