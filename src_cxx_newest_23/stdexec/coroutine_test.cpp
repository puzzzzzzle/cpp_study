#include "common_includes.h"

#include <stdexec/execution.hpp>
#include <exec/static_thread_pool.hpp>
#include <exec/task.hpp>

#if !STDEXEC_NO_STDCPP_COROUTINES()

// 1. 基础协程：co_await 一个 sender
auto async_square(int x) -> exec::task<int> {
    auto result = co_await (stdexec::just(x) | stdexec::then([](int v) { return v * v; }));
    co_return result;
}

TEST(stdexec_coroutine, basic_task) {
    auto [result] = stdexec::sync_wait(async_square(7)).value();
    EXPECT_EQ(result, 49);
}

// 2. 协程链式调用：一个协程 co_await 另一个协程
auto async_add(int a, int b) -> exec::task<int> {
    co_return a + b;
}

auto async_compute() -> exec::task<int> {
    int sum = co_await async_add(10, 20);
    int squared = co_await async_square(sum);
    co_return squared;
}

TEST(stdexec_coroutine, chained_tasks) {
    auto [result] = stdexec::sync_wait(async_compute()).value();
    EXPECT_EQ(result, 900); // (10+20)^2
}

// 3. 协程内 when_all 并发
auto async_parallel_sum() -> exec::task<int> {
    auto [a, b, c] = co_await stdexec::when_all(
        async_square(3),
        async_square(4),
        async_square(5)
    );
    co_return a + b + c;
}

TEST(stdexec_coroutine, when_all_in_coroutine) {
    auto [result] = stdexec::sync_wait(async_parallel_sum()).value();
    EXPECT_EQ(result, 50); // 9 + 16 + 25
}

// 4. 在线程池上运行协程
auto async_work_on_pool(exec::static_thread_pool::scheduler sched) -> exec::task<std::thread::id> {
    co_await stdexec::schedule(sched);
    co_return std::this_thread::get_id();
}

TEST(stdexec_coroutine, task_on_thread_pool) {
    exec::static_thread_pool pool(2);
    auto sched = pool.get_scheduler();

    auto work = stdexec::starts_on(sched, async_work_on_pool(sched));
    auto [tid] = stdexec::sync_wait(std::move(work)).value();

    EXPECT_NE(tid, std::this_thread::get_id());
}

// 5. let_value 与协程混用
TEST(stdexec_coroutine, sender_pipe_with_coroutine) {
    auto work = stdexec::just(6)
        | stdexec::let_value([](int x) {
            return async_square(x);
        })
        | stdexec::then([](int squared) {
            return squared + 1;
        });

    auto [result] = stdexec::sync_wait(std::move(work)).value();
    EXPECT_EQ(result, 37); // 6^2 + 1
}

// 6. 多个协程并发跑在同一个线程池上 (starts_on + when_all)
auto pool_task(exec::static_thread_pool::scheduler sched, int value) -> exec::task<std::pair<int, std::thread::id>> {
    co_await stdexec::schedule(sched);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    co_return std::pair{value * value, std::this_thread::get_id()};
}

TEST(stdexec_coroutine, multiple_tasks_on_pool) {
    exec::static_thread_pool pool(4);
    auto sched = pool.get_scheduler();

    auto work = stdexec::when_all(
        stdexec::starts_on(sched, pool_task(sched, 2)),
        stdexec::starts_on(sched, pool_task(sched, 3)),
        stdexec::starts_on(sched, pool_task(sched, 4)),
        stdexec::starts_on(sched, pool_task(sched, 5))
    );

    auto [r1, r2, r3, r4] = stdexec::sync_wait(std::move(work)).value();

    EXPECT_EQ(r1.first, 4);
    EXPECT_EQ(r2.first, 9);
    EXPECT_EQ(r3.first, 16);
    EXPECT_EQ(r4.first, 25);

    // 至少用到了 2 个不同线程（4 个任务在 4 线程池上并发）
    std::set<std::thread::id> tids{r1.second, r2.second, r3.second, r4.second};
    EXPECT_GE(tids.size(), 2u);

    std::cout << "tasks ran on " << tids.size() << " different threads\n";
}

// 7. 用 bulk 在线程池上做数据并行
TEST(stdexec_coroutine, bulk_on_pool) {
    exec::static_thread_pool pool(4);
    auto sched = pool.get_scheduler();

    constexpr int N = 100;
    std::vector<int> data(N, 0);

    auto work = stdexec::starts_on(sched,
        stdexec::just()
        | stdexec::bulk(N, [&data](int i) {
            data[i] = i * i;
        })
    );

    stdexec::sync_wait(std::move(work));

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(data[i], i * i);
    }
}

// 8. 协程内动态 fan-out: 启动 N 个子任务并汇总
auto fan_out_sum(exec::static_thread_pool::scheduler sched, int n) -> exec::task<long long> {
    // 先在池上启动，后续 co_await 因为 scheduler affinity 会自动回到池上
    co_await stdexec::schedule(sched);

    long long total = 0;
    // 每次 2 个一组并发
    for (int i = 0; i < n; i += 2) {
        int j = std::min(i + 1, n - 1);
        auto [a, b] = co_await stdexec::when_all(
            stdexec::starts_on(sched, async_square(i)),
            stdexec::starts_on(sched, async_square(j))
        );
        total += a;
        if (i != j) total += b;
    }
    co_return total;
}

TEST(stdexec_coroutine, fan_out_in_coroutine) {
    exec::static_thread_pool pool(4);
    auto sched = pool.get_scheduler();

    auto work = stdexec::starts_on(sched, fan_out_sum(sched, 10));
    auto [result] = stdexec::sync_wait(std::move(work)).value();

    // 0^2 + 1^2 + 2^2 + ... + 9^2 = 285
    EXPECT_EQ(result, 285);
}

#else

#pragma message("STDEXEC_NO_STDCPP_COROUTINES() is defined")

#endif // !STDEXEC_NO_STDCPP_COROUTINES()
