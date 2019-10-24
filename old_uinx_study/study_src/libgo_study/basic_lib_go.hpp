#include <memory>

//
// Created by tao on 18-12-1.
//

#ifndef UNIXSTUDYCPP_BASIC_LIB_GO_HPP
#define UNIXSTUDYCPP_BASIC_LIB_GO_HPP

#include <libgo/coroutine.h>
#include <unistd.h>

#include "../log4cplus_init/log_macro.h"

void say_hello() {
    INFO("hello libgo!");
}

void long_time_func() {
    INFO("long time func start!");
    sleep(3);
    INFO("long time func end!");

}

int basic_lib_go_test() {
    INFO("libgo basic test start!");

    //调用go后并不会启动协程，这点和够语言不一样，而是等待启动命令
    go say_hello;
    go long_time_func;
    go []() { INFO("hello from lambda"); };

    //使用默认启动器启动：
    //实际上就是启动协程调度器，并负责运行，在那个线程中调用start，就有那个线程负责运行
    //当一个协程wait后他就会放弃执行权，让其他协程执行，所以协程之间没有顺序关系
    //即使当所有协程执行完，调度器也不会放弃线程使用权，而是会进入等待状态
    //start 0 强制启动cpu数量的线程
    co_sched.Start();
    INFO("test end!");
    return 0;
}

/**
 * 因为协程调度器即使执行完，也不会放弃线程使用权，使用新线程
 */
void no_wait_test() {
    go long_time_func; //调用go后并不会启动协程，这点和够语言不一样，而是等待启动命令
    go say_hello;
//    go long_time_func;
    go []() { INFO("hello from lambda"); };
    std::thread t([]() { co_sched.Start(); });
    t.detach();
    co_sleep(5000);
    INFO("thread test end!");

    //在新的调度器上调度
    //可以先启动调度器，在向其中添加任务
    co::Scheduler *m_co_sched = co::Scheduler::Create();
    std::thread t1([m_co_sched]() { m_co_sched->Start(0, std::thread::hardware_concurrency()); });
    t1.detach();

    go co_scheduler(m_co_sched) long_time_func;

    co_sleep(5000);
    TRACE("new scheduler end!");

}

void channel_test() {
    /*********************** 1. 基本使用 ************************/
    // Channel也是一个模板类,
    // 使用以下代码将创建一个无缓冲区的、用于传递整数的Channel：
    co_chan<int> ch_0;

    // channel是引用语义, 在协程间共享直接copy即可.
    go [=] {
        // 在协程中, 向ch_0写入一个整数1.
        // 由于ch_0没有缓冲区, 因此会阻塞当前协程, 直到有人从ch_0中读取数据:
        ch_0 << 1;
    };

    go [=] {
        // Channel是引用计数的, 复制Channel并不会产生新的Channel, 只会引用旧的Channel.
        // 因此, 创建协程时可以直接拷贝Channel.
        // Channel是mutable的, 因此可以直接使用const Channel读写数据,
        // 这在使用lambda表达式时是极为方便的特性.

        // 从ch_0中读取数据:
        int i;
        ch_0 >> i;
        printf("i = %d\n", i);
    };

    /*********************** 2. 带缓冲区的Channel ************************/
    // 创建缓冲区容量为1的Channel, 传递智能指针:
    co_chan<std::shared_ptr<int>> ch_1(1);

    go [=] {
        std::shared_ptr<int> p1(new int(1));

        // 向ch_1中写入一个数据, 由于ch_1有一个缓冲区空位, 因此可以直接写入而不会阻塞当前协程.
        ch_1 << p1;

        // 再次向ch_1中写入整数2, 由于ch_1缓冲区已满, 因此阻塞当前协程, 等待缓冲区出现空位.
        ch_1 << p1;
    };

    go [=] {
        std::shared_ptr<int> ptr;

        // 由于ch_1在执行前一个协程时被写入了一个元素, 因此下面这个读取数据的操作会立即完成.
        ch_1 >> ptr;

        // 由于ch_1缓冲区已空, 下面这个操作会使当前协程放弃执行权, 等待第一个协程写入数据完成.
        ch_1 >> ptr;
        printf("*ptr = %d\n", *ptr);
    };

    /*********************** 3. Try and Timeout ************************/
    // 前面两种对channel的使用方式都是无限期等待的
    // Channel还支持带超时的等待机制, 和非阻塞的模式
    co_chan<int> ch_2;

    go [=] {
        // 使用TryPop和TryPush接口, 可以立即返回无需等待.
        // 当Channel为空时, TryPop会失败; 当Channel写满时, TryPush会失败.
        // 如果操作成功, 返回true, 否则返回false.
        int val = 0;
        bool isSuccess = ch_2.TryPop(val);

        // 使用TimedPop和TimedPush接口, 可以在第二个参数设置等待的超时时间
        // 如果超时, 返回false, 否则返回true.
        // 注意：当前版本, 原生线程中使用Channel时不支持超时时间, 退化为无限期等待.
        isSuccess = ch_2.TimedPush(1, std::chrono::microseconds(100));

        (void) isSuccess;
    };

    /*********************** 4. 多读多写\线程安全 ************************/
    // Channel可以同时由多个线程读写.
    // Channel是线程安全的, 因此不必担心在多线程调度协程时会出现问题.

    /*********************** 5. 跨越多个调度器 ************************/
    // Channel可以自由地使用, 不必关心操作它的协程是属于哪个调度器的.

    /*********************** 6. 兼容原生线程 ************************/
    // Channel不仅可以用于协程中, 还可以用于原生线程.

    // 200ms后安全退出
    std::thread([] {
        co_sleep(200);
        co_sched.Stop();
    }).detach();

    co_sched.Start();
}

void channel_test_me() {
//    co::co_chan<std::shared_ptr<int>> i_sptr_ch_10(10);
    co::co_chan<int> i_ch_10(10);

    //input value
    for (int i = 0; i < 10; i++) {
        go [=] {
//            i_sptr_ch_10 << std::make_shared<int>(i);
            i_ch_10 << i;
        };
    }
    //get value;
//    for (int i = 0; i < 5; i++) {
    go [=] {
        int temp;
        INFO("get value from channel start+++++");
        for (int i = 0; i < 10; i++) {

            i_ch_10 >> temp;
            printf("%d\n", temp);
        }
        INFO("get value end!+++++");
        co_sched.Stop();
    };
//    }
    co_sched.Start(0);

}

#endif //UNIXSTUDYCPP_BASIC_LIB_GO_HPP
