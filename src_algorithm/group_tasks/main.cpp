//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

//#define GROUP_MNG_LOG(msg) LOG_DEBUG(" -- group mng :" << msg)
#define GROUP_MNG_LOG_INFO(msg) LOG_DEBUG(" -- group mng :" << msg)

#include "group_tasks.h"
using group_task::GroupTaskMng;
class CondCheck
{
private:
    std::mutex checkLock{};
};
TEST(test_test, 1)
{
    GroupTaskMng group(600, true);
    // 组 1 上注册一个生产者, 进行生产
    // product 虽然是无锁且被多线程访问, 但是一定不会有问题, 因为 组1 和组2 是分开执行的
    int product{};
    time_t last_produce_time;
    time(&last_produce_time);

    auto task1 = group.RegTask(1,
        [&product, &last_produce_time]()
        {
            // 进行生产
            time_t curr_time;
            if (time(&curr_time) - last_produce_time > 0)
            {
                ++product;
                last_produce_time = curr_time;
                LOG_DEBUG("produce: run task 1 in group 1");
                return true;
            }
            else
            {
                LOG_DEBUG("not need produce task 1 in group 1");
                return false;
            }
        });
    // 一定和task1 一起执行
    for (int i = 0; i < 3; ++i)
    {
        group.RegTask(1,
            []()
            {
                LOG_DEBUG("run in group 1");
                // 陪同执行, 就不用认为有任务执行了
                return false;
            });
    }
    sleep(2);

    // 组2 上注册一个消费者, 只有当product不为空时, 才会拉起消费
    group.RegTask(
        2,
        [&product]()
        {
            // 进行消费
            if (product > 0)
            {
                --product;
                LOG_DEBUG("consume :run task 3 in group 2");
                return true;
            }
            else
            {
                LOG_DEBUG("not need consume task 3 in group 2");
                return false;
            }
        },
        [&product]() { return product > 0; });
    for (int i = 0; i < 3; ++i)
    {
        group.RegTask(2,
            []()
            {
                LOG_DEBUG("run in group 2");
                // 陪同执行, 就不用认为有任务执行了
                return false;
            });
    }
    sleep(2);
    // 停止生产 task1
    group.WaitStopTask(task1);

    // task 3 在消费完后, 也就停止执行了
    sleep(4);
    ASSERT_TRUE(product == 0);
}

int main(int argc, char **argv)
{
    int iRet = 0;

    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    sleep(1);
    return iRet;
}