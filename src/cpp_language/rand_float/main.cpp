//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
static unsigned int GetRand(unsigned int iMax) {
    static bool m_bInited = false;
    if (iMax == 0) {
        return 0;
    }

    if (!m_bInited) {
        srand((unsigned int)time(NULL));
        m_bInited = true;
    }

    return (unsigned int)rand() % iMax;
}
float RandomRangeNumber(float min, float max) {
    int   iSignificant = 1000000;
    int   gap          = (int)(max * iSignificant - min * iSignificant);
    int   radnNum      = GetRand(gap);
    float ret          = (float)radnNum / (float)iSignificant + min;
    return ret;
}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    printf("%f\n", RandomRangeNumber(-0.8, 0.9));

    return iRet;
}