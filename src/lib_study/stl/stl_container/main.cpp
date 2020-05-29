//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "stl_common_containor.h"
TEST(test1,1){
    int size = 10;
    do{
        --size;
    }while (size>3);
    LOG_DEBUG(size);
}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}