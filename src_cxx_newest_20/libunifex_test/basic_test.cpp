//
// Created by khalidzhang on 2022/12/21.
//

#include "common_includes.h"
#include "execution_header.h"

using namespace std::chrono;
using namespace std::chrono_literals;

TEST(Transform, Smoke) {
  timed_single_thread_context context;

  auto scheduler = context.get_scheduler();

  int count = 0;

  sync_wait(then(schedule_after(scheduler, 200ms), [&] { ++count; }));

  EXPECT_EQ(count, 1);
}

TEST(Pipeable, Transform) {
  int count = 0;

  just() | then([&] { ++count; }) | sync_wait();

  auto two_count = then([&] { ++count; }) | then([&] { ++count; });

  just() | then([&] { ++count; }) | two_count | sync_wait();

  EXPECT_EQ(count, 4);
}