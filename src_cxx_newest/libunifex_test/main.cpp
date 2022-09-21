//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <unifex/scheduler_concepts.hpp>
#include <unifex/sync_wait.hpp>
#include <unifex/timed_single_thread_context.hpp>
#include <unifex/just.hpp>
#include <unifex/then.hpp>
#include <unifex/let_done.hpp>
#include <unifex/sequence.hpp>
#include <unifex/stop_when.hpp>

#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

using namespace unifex;
using namespace std::chrono;
using namespace std::chrono_literals;

TEST(Transform, Smoke) {
  timed_single_thread_context context;

  auto scheduler = context.get_scheduler();

  int count = 0;

  sync_wait(
      then(
          schedule_after(scheduler, 200ms),
          [&]{ ++count; }));

  EXPECT_EQ(count, 1);
}

TEST(Pipeable, Transform) {
  int count = 0;

  just()
      | then([&]{ ++count; })
      | sync_wait();

  auto two_count = then([&]{ ++count; }) | then([&]{ ++count; });

  just()
      | then([&]{ ++count; })
      | two_count | sync_wait();

  EXPECT_EQ(count, 4);
}

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}