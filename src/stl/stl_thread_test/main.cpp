//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <thread>
#include "common_classes.h"
#include "sys/syscall.h"
#include <unistd.h>
#define gettidv1() syscall(__NR_gettid)
#define gettidv2() syscall(SYS_gettid)

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(threadtest, throwTest) {
    std::thread thrower([]() {
        LOG_INFO("start")
        sleep(2);
        LOG_INFO("before")
        throw std::runtime_error("throw something");
        LOG_INFO("after")
        sleep(2);
        LOG_INFO("stop")

    });
    auto gard = MakeScopeGuard([&thrower]() {
        if (thrower.joinable()) {
            LOG_INFO("joinable")
            thrower.join();
        } else {
            LOG_INFO("cannot join")
        }
    });
    LOG_INFO("main thread before end")

}

// err 会导致跳出循环，结束线程，和预期一致
// 注意：如果在join前线程已经结束了，那就收不到事件了, 只有terminal
TEST(threadtest, whileThrowTest) {
    std::thread thrower([]() {
        LOG_INFO("start")
        for (int i = 0; i < 10; ++i) {
            LOG_INFO(i)
            if (i == 3) {
                LOG_INFO("before")
                throw std::runtime_error("throw something");
                LOG_INFO("after")
            }
        }
        LOG_INFO("stop")

    });
    sleep(3);
    auto gard = MakeScopeGuard([&thrower]() {
        if (thrower.joinable()) {
            LOG_INFO("joinable")
            thrower.join();
        } else {
            LOG_INFO("cannot join")
        }
    });
    LOG_INFO("main thread before end")

}

TEST(deatchTest, 1) {
    std::thread t([]() {
        for (int i = 0; i < 3; ++i) {
            LOG_INFO("now at " << i)
//            std::cout << "now at " << i<<std::endl;
            sleep(1);
        }
        LOG_INFO("end")
    });
    t.detach();
    ASSERT_EQ(t.joinable(), false);
}


int main(int argc, char **argv) {
    int iRet = 0;
    iRet = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    pthread_exit(nullptr);
}