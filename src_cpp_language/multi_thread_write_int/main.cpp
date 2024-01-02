#include <iostream>
#include <string>
#include <thread>
#include <vector>
// 正常, 每个线程有自己的变量
//thread_local int level = 0;

// 多线程异常
//int level = 0;

// 多线程异常, i++ 是三个指令 : load add save, 无法保证原子性
//volatile int level = 0;

// 正常
std::atomic_int level = 0;

class Test {
  std::string m_prefix;
  std::string str_;

  public:
  Test(std::string str)
      : m_prefix(std::string(level * 2, '+')), str_(std::move(str)) {
    level++;
  }
  ~Test() { level--; }
  void DoSomething(int recursiveLevel = 0) {
    if (rand() % 100 < 50 && recursiveLevel < 5) {
      DoSomething(++recursiveLevel);
    }

    if ("test" != str_) {
      std::cerr << "wrong ....." << std::endl;
    }
  }
};
void TestFunc() {
  Test test("test");
  test.DoSomething();
}
void Run(int n) {
  for (int i = 0; i < n; i++) {
    if (i % 1000000 == 0) {
      std::cout << std::this_thread::get_id() << " run at " << i << "/" << n
                << std::endl;
    }
    try {
      TestFunc();
    } catch (const std::exception &e) {
      std::cerr << "catch std exception: " << e.what() <<" level "<< level << std::endl;
    } catch (...) {
      std::cerr << "catch unknown exception: " << std::endl;
    }
  }
}
int main(int argc, char **argv) {
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++) {
    threads.emplace_back(Run, 10000000);
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}