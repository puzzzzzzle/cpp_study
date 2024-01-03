#include <iostream>
#include <string>
#include <thread>
#include <vector>

int unused = 42;
constexpr int MAX_LEVEL = 5;
// 正常, 每个线程有自己的变量
thread_local int level = 0;

// 多线程异常
// int level = 0;

// 多线程异常, i++ 是#~5个指令 : mem -> cache, cache -> reg, add reg, reg ->
// cache, cache -> mem, 无法保证原子性
// volatile int level = 0;

// 正常
// std::atomic_int level = 0;

class Test {
  public:
  Test() {
    if (level < 0) {
      throw std::runtime_error("level < 0: (" + std::to_string(level) + ")");
    }
    if (level > MAX_LEVEL) {
      throw std::runtime_error("level > MAX_LEVEL: (" + std::to_string(level) +
                               ")");
    }
    level++;
  }
  ~Test() { level--; }
  void UpdateLevel() { unused = level; }
};
void DoSomething(int recursiveLevel = 0) {
  Test test{};
  test.UpdateLevel();
  if (recursiveLevel < 5) {
    DoSomething(++recursiveLevel);
  }
}
void TestFunc() { DoSomething(0); }
void Run(int n) {
  auto t = std::time(nullptr);
  for (int i = 0; i < n; i++) {
    if (i % 5000000 == 0) {
      auto curr = std::time(nullptr);
      std::cout << std::this_thread::get_id() << " run at " << i << "/" << n
                << "\ttime use: " << (curr - t) << std::endl;
      t = curr;
    }
    try {
      TestFunc();
    } catch (const std::exception &e) {
      std::cerr << "catch std exception: " << e.what() << " level " << level
                << std::endl;
    } catch (...) {
      std::cerr << "catch unknown exception: " << std::endl;
    }
  }
  std::cout << unused << "\t" << level << std::endl;
}
int main(int argc, char **argv) {
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++) {
    threads.emplace_back(Run, 11000000);
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}