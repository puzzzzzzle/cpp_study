/************************************************
 * @author puzzzzzzle
 * @email khalidzhangtao@gmail.com
 * @desc
 * @time 2023/1/9
 * @file group_tasks.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
class GroupTaskMng {
  private:
  struct Task {
    std::function<void()> func{};

    std::function<bool()> need_run{};
    bool repeated{};
    std::atomic_bool destroyed{};
    std::atomic<std::shared_ptr<int>> destroyed_call_back{};
  };
  // 要执行的task
  std::map<int, std::map<int64_t , Task>> group_tasks_{};
  // 注册task需要的信息
  std::mutex m_wait_add_lock{};
  std::map<int, std::map<int64_t, Task>> wait_add_tasks_{};

  public:
      int64_t RegTask(    std::function<void()> func,
                      std::function<bool()> need_run,
                      bool repeated)
      {

      }
};