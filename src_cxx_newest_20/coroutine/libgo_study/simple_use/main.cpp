//
// Created by tao on 19-1-17.
//
#include <libgo.h>
#include <stdio.h>

#include <iostream>
#include <thread>

#include "common_includes.h"

// 有参函数
void global_func(int a) {  //全局函数
  std::cout << "call global_func:" << a << std::endl;
}

auto labmda = [](int a) { std::cout << "lambda:" << a << std::endl; };

class ClassA {
  public:
  ClassA() { std::cout << "constructor for ClassA" << std::endl; }
  void member_func(int a) {  //类成员函数
    std::cout << "call ClassA::member_func:" << a << std::endl;
  }

  static void static_member_func(int a) {  //类静态函数
    std::cout << "call ClassA::static_member_func:" << a << std::endl;
  }
};

class Functor {  //仿函数
  public:
  void operator()(int a) { std::cout << "call Functor()" << a << std::endl; }
};

//无参函数
void foo() { std::cout << "function pointer\n" << std::endl; }

struct StructA {
  void fA() { std::cout << "std::bind\n" << std::endl; }
  void fB() { std::cout << "std::function\n" << std::endl; }
};

int lib_go_main() {
  //   创建拥有10MB大栈的协程只是设置下opt，在被调度时才会正真的创建
  // go co_stack(10 * 1024 * 1024)[]
  // {
  //     std::cout << "++++large stack 10M\n"<< std::endl;
  // };
  // 匿名lambda
  go[] {
    std::cout << "+++++++++++++start co tasks+++++++++++++++++\n" << std::endl;
  };
  // 无参函数
  go foo;

  // 成员函数 , 会比前面的先调用，协程只有再调用运行函数后才被调度
  ClassA a;
  a.member_func(1);
  //类成员函数
  // 无参
  go std::bind(&StructA::fA, StructA());

  std::function<void()> fn(std::bind(&StructA::fB, StructA()));
  go fn;

  // 有参
  go std::bind(&ClassA::member_func, ClassA(), 1);
  go std::bind(&ClassA::member_func, a, 2);

  // 有参函数
  go std::bind(global_func, 3);
  go std::bind(labmda, 4);

  //仿函数
  Functor f;
  f(7);
  go std::bind(f, 8);

  go[]() {
    co_sleep(3000);
    std::cout << "after sleep\n" << std::endl;
    co_sched
        .Stop();  //协程在运行完毕后，调度器并不会关闭，而是等待新的协程，需要手动关闭
  };

  //调度
  co_sched.Start();  // 仅使用主线程调度协程.

  // co_sched.Start(0);//使用等同于cpu核心数的线程调度协程.(包括主线程)
  // co_sched.Start(0,
  // 1024);//允许调度器自由扩展线程数，上限为1024.可用线程数总是等于Start的第一个参数(0表示cpu核心数).

  // 如果不想让调度器卡住主线程, 可以使用以下方式:
  // std::thread t([] { co_sched.Start(); });
  // t.detach();
  // co_sleep(100);
  // go[]
  // {
  //     std::cout << "+++++++++++++start co tasks+++++++++++++++++\n"<<
  //     std::endl; co_sched.Stop();
  //     //协程在运行完毕后，调度器并不会关闭，而是等待新的协程，需要手动关闭
  // };

  //----------------------------------
  // 除了上述的使用默认的调度器外, 还可以自行创建额外的调度器,
  // 协程只会在所属的调度器中被调度, 创建额外的调度器可以实现业务间的隔离.

  // 创建一个调度器
  // co::Scheduler *sched = co::Scheduler::Create();

  // // 启动4个线程执行新创建的调度器
  // std::thread t2([sched] { sched->Start(4); });
  // t2.detach();

  // // 在新创建的调度器上创建一个协程
  // go co_scheduler(sched)[]
  // {
  //     std::cout << "run in my scheduler.\n"<< std::endl;
  // };

  // co_sleep(100);
  return 0;
}
TEST(test_test, 1) { EXPECT_EQ(lib_go_main(), 0); }

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}