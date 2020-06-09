//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "sys/syscall.h"
#include <unistd.h>
#define gettidv1() syscall(__NR_gettid)
#define gettidv2() syscall(SYS_gettid)

#include <pthread.h>
#include <future>

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(thread,id){
    std::thread t([](){
        LOG_DEBUG("new thread : std::thread::id:\t"<<std::this_thread::get_id());
        LOG_DEBUG("new thread : pthread_self:\t"<<pthread_self())
        LOG_DEBUG("new thread : gettid:\t"<<gettidv1());
        LOG_DEBUG("new thread : getpid:\t"<<getpid());

        sleep(2);
    });
    sleep(1);
    LOG_DEBUG("new thread : t.get_id:"<<t.get_id());

    LOG_DEBUG("main thread : std::this_thread::get_id()"<<std::this_thread::get_id())
    LOG_DEBUG("main thread : pthread_self"<<pthread_self())
    LOG_DEBUG("main thread : gettid:\t"<<gettidv1());
    LOG_DEBUG("main thread : getpid:\t"<<getpid());

    t.join();
}

TEST(future,simple){
    std::future<int> future = std::async([]()->int{
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return 42;
    });

    LOG_DEBUG(future.get());
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