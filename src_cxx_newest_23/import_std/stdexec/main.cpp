#include "common_includes.h"

#include <stdexec/execution.hpp>
#include <exec/static_thread_pool.hpp>

TEST(stdexec_test, basic_just_then) {
    auto work = stdexec::just(42) | stdexec::then([](int i) { return i * 2; });
    auto [result] = stdexec::sync_wait(std::move(work)).value();
    EXPECT_EQ(result, 84);
}

TEST(stdexec_test, when_all_on_thread_pool) {
    exec::static_thread_pool pool(3);
    auto sched = pool.get_scheduler();

    auto square = [](int i) { return i * i; };
    auto work = stdexec::when_all(
        stdexec::starts_on(sched, stdexec::just(0) | stdexec::then(square)),
        stdexec::starts_on(sched, stdexec::just(3) | stdexec::then(square)),
        stdexec::starts_on(sched, stdexec::just(5) | stdexec::then(square))
    );

    auto [a, b, c] = stdexec::sync_wait(std::move(work)).value();
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 9);
    EXPECT_EQ(c, 25);
}

TEST(stdexec_test, let_value_chain) {
    auto work = stdexec::just(10)
        | stdexec::let_value([](int x) {
            return stdexec::just(x + 5)
                | stdexec::then([](int y) { return y * 3; });
        });

    auto [result] = stdexec::sync_wait(std::move(work)).value();
    EXPECT_EQ(result, 45);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
