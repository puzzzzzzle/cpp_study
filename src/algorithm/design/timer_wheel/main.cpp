//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "TimerWheel.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(timer,1){

}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
//    testing::InitGoogleTest(&argc, argv);
//    iRet = RUN_ALL_TESTS();
    TimerWheel::TimerWheel<60> wheel{};
    wheel.DoAfterFrame(10,[](){LOG_DEBUG("called after 10 frame")});
    wheel.DoAfterFrame(1,[](){LOG_DEBUG("+++called every 1 frame")}, true);
    int i;
    for(i=0;i<100;++i){
        LOG_DEBUG("tick:"<<i)
        wheel.Tick();
    }
    LOG_DEBUG(i)
    sleep(5);
    return iRet;
}