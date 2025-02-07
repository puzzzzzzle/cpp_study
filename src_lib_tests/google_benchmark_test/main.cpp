#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state) std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) std::string copy(x);
}
BENCHMARK(BM_StringCopy);

// with env
static void DoSetup(const benchmark::State& state) {}

static void DoTeardown(const benchmark::State& state) {}

static void BM_func(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) std::string copy(x);
}

BENCHMARK(BM_func)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

// auto range test
static void BM_memcpy(benchmark::State& state) {
  auto currRange = state.range(0);
  char* src = new char[currRange];
  char* dst = new char[currRange];
  memset(src, 'x', currRange);
  for (auto _ : state) memcpy(dst, src, currRange);
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(currRange));
  delete[] src;
  delete[] dst;
}
// BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10);
// BENCHMARK(BM_memcpy)->Range(8, 8<<10);
BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(8, 8 << 10);


// with arg and out
template <class... Args>
void BM_takes_args(benchmark::State& state, Args&&... args) {
  auto args_tuple = std::make_tuple(std::move(args)...);
  for (auto _ : state) {
    auto var0 = std::get<0>(args_tuple);
    auto var1 = std::get<1>(args_tuple);
    state.counters["var0"] = var0;
  }
}
// Registers a benchmark named "BM_takes_args/int_string_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_string_test, 42, std::string("abc"));

// Registers the same benchmark "BM_takes_args/int_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_test, 42, 43);

BENCHMARK_MAIN();