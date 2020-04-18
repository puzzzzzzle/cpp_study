//
// Created by tao on 19-1-17.
//
#include <condition_variable>
#include <mutex>

#include "common_classes.h"
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
class TestLock {
public:
    std::mutex              lock{};
    std::condition_variable cond{};
    int                     Test() {
        auto                             gard = MakeScopeGuard([]() { LOG_DEBUG("exit Test") });
        bool                             isSet{false};
        std::vector<AutoJoinThreadGuard> ts{};

        ts.emplace_back(([&]() {
            LOG_DEBUG("+M Before Get Lock\t" << time(0))
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            LOG_DEBUG("\t+M before lock")
            std::unique_lock<std::mutex> uniqueLock(lock);
            LOG_DEBUG("\t+M after lock")

            isSet = true;
            cond.notify_all();
            LOG_DEBUG("+M After Get Lock\t" << time(0))
        }));
        sleep(1);
        for (int i = 0; i < 10; ++i) {
            ts.emplace_back([&]() {
                int index = i;
                LOG_DEBUG("" << index << "\tBefore Get Lock\t" << time(0))
                std::unique_lock<std::mutex> uniqueLock(lock);
                uniqueLock.unlock();
                while (!isSet) {
                    LOG_DEBUG("\tbefore wait" << index)
                    cond.wait(uniqueLock);
                    LOG_DEBUG("\tafter wait" << index)
                }
                LOG_DEBUG("" << index << "\tAfter Get Lock\t" << time(0))
            });
        }
        LOG_DEBUG("all thread inited")
        return 0;
    }
};

class UniqueLockTest {
public:
    std::mutex lock{};
    int        Test() {
        auto                             gard = MakeScopeGuard([]() { LOG_DEBUG("exit Test") });
        std::vector<AutoJoinThreadGuard> ts{};
        ts.emplace_back([&]() {
            LOG_DEBUG("before lock")
            std::unique_lock<std::mutex> uniqueLock(lock);
            LOG_DEBUG("after lock")
            sleep(3);
            LOG_DEBUG("free lock")
        });
        sleep(1);
        ts.emplace_back([&]() {
            LOG_DEBUG("before wait lock")
            std::unique_lock<std::mutex> uniqueLock(lock);
            LOG_DEBUG("after wait lock")
            LOG_DEBUG("free wait lock")
        });
    };
};
int main(int argc, char **argv) {
    TestLock testLock{};
    testLock.Test();
    UniqueLockTest uniqueLockTest{};
    uniqueLockTest.Test();
    int iRet = 0;
    //    iRet     = beforeRun();
    //    if (iRet) {
    //        std::cerr << "init fail with " << iRet << std::endl;
    //    }
    //    testing::InitGoogleTest(&argc, argv);
    //    iRet = RUN_ALL_TESTS();
    return iRet;
}