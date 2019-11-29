//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "QuadTree.h"
QuadTree <int> * qtree;
int main(int argc, char **argv) {
    int iRet = 0;
    iRet = beforeRun();
    if(iRet){
        std::cerr<<"init fail with "<<iRet<<std::endl;
        return iRet;
    }

    vertex origin (0, 0);
    vertex axis (128.0, 128.0);
    qtree = new QuadTree <int> (origin, axis, 1);


    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}