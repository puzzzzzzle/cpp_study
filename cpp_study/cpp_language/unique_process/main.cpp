//
// Created by tao on 19-1-17.
//
#include "SysUnique.hpp"
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    //    int iRet = 0;
    //    iRet = beforeRun();
    //    if (iRet)
    //    {
    //        std::cerr << "init fail with " << iRet << std::endl;
    //    }
    //    testing::InitGoogleTest(&argc, argv);
    //    iRet = RUN_ALL_TESTS();
    if (argc != 3) {
        printf("need id\n");
        return -1;
    }
    SysUnique stUnique(argv[2]);
    if (strcmp("start", argv[1]) == 0) {
        if (!stUnique.Init()) {
            printf("already run \n");
            return -1;
        }
        while (true) {
            printf("run\n");
            sleep(5);
        }
    }
    if (strcmp("isrun", argv[1]) == 0) {
        if (stUnique.IsRun()) {
            printf("already run \n");
        } else {
            printf("no run \n");
        }
    }
    return -1;
}