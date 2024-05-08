//
// Created by khalidzhang on 2020/7/14.
//
#include <ucontext.h>

#include "common_includes.h"

void co_print_test(int val) {
  int posInt{};
  LOG_INFO("log from co " << val << "stack pos is " << &posInt)
}

/**
 * 切换到协程, 无法再切换回来了
 */
TEST(ucontext_test_, link_null) {
  int posInt{};
  LOG_INFO("log from co "
           << "stack pos is " << &posInt)

  char co_stack[4096];
  ucontext uc{};
  getcontext(&uc);
  uc.uc_link = nullptr;
  uc.uc_stack.ss_size = sizeof(co_stack);
  uc.uc_stack.ss_sp = co_stack;
  makecontext(&uc, (void (*)(void)) & co_print_test, 1, 42);

  setcontext(&uc);

  // 没有机会输出了
  LOG_INFO("log from end of test will never have change to output")
}

/**
 * 切换到协程, 再切换回来
 */
TEST(ucontext_test_, continue_main) {
  int posInt{};
  LOG_INFO("log from co "
           << "stack pos is " << &posInt)
  ucontext main_uc{};

  char co_stack[4096];
  ucontext uc{};
  getcontext(&uc);
  uc.uc_link = &main_uc;
  uc.uc_stack.ss_size = sizeof(co_stack);
  uc.uc_stack.ss_sp = co_stack;
  makecontext(&uc, (void (*)(void)) & co_print_test, 1, 42);

  swapcontext(&main_uc, &uc);

  // 可以再切换回来
  LOG_INFO("log from main ctx")
}

/**
 * 切换到协程, 再切换回来
 */
TEST(ucontext_test_, continue_main_1) {
  int posInt{};
  LOG_INFO("log from co "
               << "stack pos is " << &posInt)
  ucontext main_uc{};

  char co_stack[4096];
  ucontext uc{};
  getcontext(&uc);
  uc.uc_link = nullptr;
  uc.uc_stack.ss_size = sizeof(co_stack);
  uc.uc_stack.ss_sp = co_stack;
  makecontext(&uc, (void (*)(void)) & co_print_test, 1, 42);

  swapcontext(&main_uc, &uc);

  // 可以再切换回来
  LOG_INFO("log from main ctx")
}
/**
 * 无限循环, 递增成功
 */
TEST(ucontext_test_, _loop_1) {
  ucontext uc{};
  int index{};
  getcontext(&uc);
  LOG_DEBUG("curr index is "<< index)
  ++index;
  setcontext(&uc);
}


/**
 * 无限循环, 递增失败
 */
TEST(ucontext_test_, _loop_2) {
  ucontext uc{};
  getcontext(&uc);
  int index{};
  LOG_DEBUG("curr index is "<< index)
  ++index;
  setcontext(&uc);
}