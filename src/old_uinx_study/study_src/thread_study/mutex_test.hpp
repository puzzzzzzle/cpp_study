//
// Created by tao on 18-11-29.
//

#ifndef UNIXSTUDYCPP_MUTEX_TEST_HPP
#define UNIXSTUDYCPP_MUTEX_TEST_HPP

#include <unistd.h>

#include <algorithm>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "../log4cplus_init/log_macro.h"

using namespace std;

// class thread_guard;

class safe_vector {
  private:
  std::mutex lock;
  std::vector<string> list;

  public:
  void insert(const string &_str) {
    std::lock_guard<std::mutex> guard(lock);
    list.push_back(_str);
  }

  string to_string() {
    std::lock_guard<std::mutex> guard(lock);
    ostringstream s;
    for_each(list.begin(), list.end(), [&s](string &_str) { s << _str; });
    return s.str();
  }
};

void fill_thread(safe_vector *sf_v) {
  for (int i = 0; i < 10; ++i) {
    ostringstream os;
    os << "str in thread :" << std::this_thread::get_id() << "\t num \t"
       << to_string(i) + "\n";
    sf_v->insert(os.str());
  }
}

class graud_thread {
  private:
  std::thread t;

  public:
  graud_thread(std::thread _t) {
    t = std::move(_t);
    if (!t.joinable()) {
      throw "empty thread!";
    }
  }

  ~graud_thread() {
    if (t.joinable()) {
      t.join();
    }
  }

  graud_thread(const graud_thread &g) = delete;

  graud_thread &operator=(graud_thread const &) = delete;
};

void mutex_test() {
  safe_vector sf_v;
  //    vector<graud_thread> gs;
  vector<std::thread> gs;
  for (int i = 0; i < 10; ++i) {
    std::thread t(fill_thread, &sf_v);

    gs.push_back(std::move(t));

    TRACE(sf_v.to_string());
    //        gs.push_back(graud_thread(t));
  }
  //    sleep(2);
  for_each(gs.begin(), gs.end(), [](std::thread &t) { t.join(); });
  //    for_each(gs.begin(), gs.end(),std::mem_fun(&std::thread::join));
  TRACE(sf_v.to_string());
}

#endif  // UNIXSTUDYCPP_MUTEX_TEST_HPP
