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
#include <condition_variable>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <cassert>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <sstream>

// 日志开关, 如果外部有定义 GROUP_MNG_LOG 则使用外部的
#ifndef GROUP_MNG_LOG
#define GROUP_MNG_LOG(msg)
#endif

#ifndef GROUP_MNG_LOG_INFO
#define GROUP_MNG_LOG_INFO(msg) GROUP_MNG_LOG(msg)
#endif


// 设置线程名字相关
#ifdef _POSIX_THREADS
#include <pthread.h>
#define SET_THREAD_NAME(name) pthread_setname_np(pthread_self(), name);
#else
#define SET_THREAD_NAME(name) GROUP_MNG_LOG("not support set thread name ");
#endif


namespace group_task
{
/**
 * 简单线程池
 */
class SimpleThreadPool
{
private:
    // 工作线程
    std::vector<std::thread> workers_{};
    std::queue<std::function<void()>> tasks_{};

    // 操作时需要加锁
    std::mutex queue_mutex_{};
    std::condition_variable condition_{};
    std::atomic_bool stop_{};

    /**
     * 工作线程执行的函数
     */
    void WorkerRun()
    {
        GROUP_MNG_LOG("start worker")
        SET_THREAD_NAME("worker_thread")
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                // 每2s醒来下吧, 防止停止时卡死
                condition_.wait_for(lock, std::chrono::milliseconds(2000), [this] { return stop_ || !tasks_.empty(); });
                if (stop_ && tasks_.empty())
                {
                    return;
                }
                if (tasks_.empty())
                {
                    continue;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            if (task == nullptr)
            {
                continue;
            }
            GROUP_MNG_LOG("run one task")
            task();
        }
    }

public:
    void Start(size_t threads)
    {
        for (size_t i = 0; i < threads; ++i)
        {
            workers_.emplace_back(std::bind(&SimpleThreadPool::WorkerRun, this));
        }
        GROUP_MNG_LOG("start thread pool by size " << threads)
    }
    void Stop()
    {
        GROUP_MNG_LOG("start stop thread pool")
        stop_ = true;
        condition_.notify_all();
        for (auto &worker : workers_)
        {
            worker.join();
        }
        GROUP_MNG_LOG("stop thread pool")
    }
    template<class F, class... Args>
    auto Enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);

            if (stop_)
            {
                GROUP_MNG_LOG("enqueue on stopped ThreadPool")
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return res;
    }
};
class CutDownLatch
{
private:
    std::mutex mutex_{};
    std::condition_variable cv_{};
    uint32_t count_{};

public:
    explicit CutDownLatch(uint32_t count) : count_(count) {}

    void CountDown() noexcept
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (0 == count_)
        {
            return;
        }
        --count_;
        if (count_ <= 0)
        {
            cv_.notify_all();
        }
    }

    void Wait() noexcept
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return count_ <= 0; });
    }
};
#ifndef GROUP_TASK_USE_DYN_ID_TYPE
using GroupIDType = int64_t;
using TaskIDType = int64_t;
using MergedIDType = __int128_t;
#endif
using TaskFuncType = std::function<bool()>;
inline GroupIDType GroupID(const MergedIDType &merge_id)
{
    return (GroupIDType)(merge_id >> sizeof(GroupIDType));
}
inline TaskIDType TaskID(const MergedIDType &merged_id)
{
    return TaskIDType(merged_id);
}
std::ostream &operator<<(std::ostream &oss, const MergedIDType &num)
{
    oss << "g:" << GroupID(num);
    oss << ";t:" << TaskID(num);
    return oss;
}
inline std::string ToString(const MergedIDType &num)
{
    std::ostringstream oss{};
    oss << num;
    return oss.str();
}
class SingleThreadExecutor
{
public:
    void Start() {}
    void Stop() {}

    void operator()(TaskFuncType &func, CutDownLatch &barrier, std::atomic_flag &executed)
    {
        if (func())
        {
            GROUP_MNG_LOG("one task do something")
            executed.test_and_set();
        }
        barrier.CountDown();
    }
};
class ThreadPoolExecutor
{
private:
    SimpleThreadPool thread_pool_{};

public:
    void Start()
    {
        thread_pool_.Start(std::thread::hardware_concurrency());
        GROUP_MNG_LOG("ThreadPoolExecutor Start")
    }
    void Stop()
    {
        thread_pool_.Stop();
        GROUP_MNG_LOG("ThreadPoolExecutor Stop")
    }
    void operator()(TaskFuncType &func, CutDownLatch &barrier, std::atomic_flag &executed)
    {
        thread_pool_.Enqueue(
            [&func, &barrier, &executed]()
            {
                if (func())
                {
                    GROUP_MNG_LOG("one task do something")
                    executed.test_and_set();
                }
                barrier.CountDown();
            });
    }
};
template<typename Executor = ThreadPoolExecutor>
class GroupTaskMng
{
public:
    using ExecutorT = Executor;

private:
    struct Task
    {
        // 每次执行的函数
        TaskFuncType func{};
        // 是否需要执行, 如果函数为空, 就永远执行
        TaskFuncType need_run{};

        MergedIDType id{};
    };
    // 要执行的task
    // group -> <id -> task>
    using GroupTasksType = std::map<TaskIDType, Task>;
    // 必须使用map, 保证有序
    std::map<GroupIDType, GroupTasksType> group_tasks_{};

    // 注册task需要的信息
    std::mutex wait_add_lock_{};
    std::map<GroupIDType, GroupTasksType> wait_add_tasks_{};
    std::vector<std::pair<MergedIDType, std::function<void(bool)>>> wait_stop_tasks_{};

    uint64_t id_gen_{};

    // 驱动函数
    std::thread local_driven_thread_{};
    std::atomic_bool running_{};

    // 执行器
    ExecutorT executor_{};

public:
    /**
     *
     * @param no_work_sleep_ms 没有任务干时 休息一会
     * @param auto_start
     */
    explicit GroupTaskMng(int64_t no_work_sleep_ms = 5000, bool auto_start = true)
    {
        executor_.Start();
        if (auto_start)
        {
            Start(no_work_sleep_ms);
        }
    }
    GroupTaskMng(GroupTaskMng &) = delete;
    GroupTaskMng(GroupTaskMng &&) = delete;
    void operator=(GroupTaskMng &) = delete;
    void operator=(GroupTaskMng &&) = delete;
    ~GroupTaskMng()
    {
        Stop();
    }

public:
    /**
   * 注册任务
   * @param group_id 需要大于0, 需要小于INT_MAX
   * @param func 每次执行的函数
   * @param need_run 是否需要执行
   * @return 成功: 返回groupID 失败: 返回-1
   */
    MergedIDType RegTask(GroupIDType group_id, TaskFuncType &&func, TaskFuncType &&need_run = nullptr)
    {
        std::lock_guard<std::mutex> lock(wait_add_lock_);
        MergedIDType id = group_id;
        id = id << sizeof(GroupIDType);
        id |= ++id_gen_;
        auto &group_info = wait_add_tasks_[group_id];
        auto &task_info = group_info[id];
        task_info.i_func = std::move(func);
        task_info.need_run = std::move(need_run);
        task_info.id = id;
        GROUP_MNG_LOG_INFO("reg task " << ToString(id))
        return id;
    }
    template<typename T>
    MergedIDType RegTask(T group_id, TaskFuncType &&func, TaskFuncType &&need_run = nullptr)
    {
        return RegTask((GroupIDType)group_id, std::move(func), std::move(need_run));
    }
    void StopTask(MergedIDType merged_id, std::function<void(bool)> &&callBack)
    {
        std::lock_guard<std::mutex> lock(wait_add_lock_);
        wait_stop_tasks_.emplace_back(merged_id, callBack);
    }
    bool WaitStopTask(MergedIDType merged_id)
    {
        GROUP_MNG_LOG("WaitStopTask " << ToString(merged_id))
        std::mutex mu{};
        std::condition_variable cv{};
        std::atomic_bool has_called{};
        std::atomic_bool ret_value{};
        StopTask(merged_id,
            [&](bool ret)
            {
                std::lock_guard<std::mutex> guard(mu);
                has_called = true;
                ret_value = ret;
                cv.notify_all();
            });
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, [this, &has_called]() -> bool { return has_called.load(); });
        GROUP_MNG_LOG_INFO("WaitStopTask end " << ToString(merged_id) << "\t" << (int)ret_value.load())
        return ret_value.load();
    }

public:
    /**
   * 执行指定的group, 注意: 只能有一个线程来驱动, 用来做手动驱动
   * @param group -1 : 所有group, 其他值: 指定的group
   * @return 是否有任务执行
   */
    bool RunGroup(GroupIDType group = -1)
    {
        // 手动执行时本地线程不能启动
        assert(running_.load() == false);
        bool executed{};
        // 添加新加的Task
        executed |= ApplyTask();
        // 清理要删除的数据
        executed |= ApplyStopTask();
        if (group != -1)
        {
            auto g = group_tasks_.find(group);
            if (g == group_tasks_.end())
            {
                return executed;
            }
            executed |= RunOneGroup(g->second);
        }
        else
        {
            executed |= RunAllGroup();
        }
        return executed;
    }
    /**
   * 启动驱动线程, 用来做自动驱动
     * @param sleep_ms 没有任务时的暂停时间
   */
    void Start(uint64_t sleep_ms)
    {
        GROUP_MNG_LOG("Start loop")
        if (running_)
        {
            return;
        }
        running_ = true;
        local_driven_thread_ = std::thread(
            [this, sleep_ms]()
            {
                SET_THREAD_NAME("driven_thread")
                while (running_)
                {
                    bool executed{};
                    // 合入新添加的数据
                    executed |= ApplyTask();
                    // 清理要删除的数据
                    executed |= ApplyStopTask();
                    // 执行所有group
                    executed |= RunAllGroup();
                    if (!running_.load())
                    {
                        GROUP_MNG_LOG("end loop")
                        return;
                    }
                    if (!executed)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
                    }
                }
            });
    }

    void Stop()
    {
        GROUP_MNG_LOG("Stop")
        running_ = false;
        if (local_driven_thread_.joinable())
        {
            local_driven_thread_.join();
        }
        executor_.Stop();
        GROUP_MNG_LOG("end Stop")
    }

private:
    bool RunAllGroup()
    {
        bool executed{};
        for (auto it = group_tasks_.begin(); it != group_tasks_.end();)
        {
            if (it->second.empty())
            {
                it = group_tasks_.erase(it);
            }
            else
            {
                GROUP_MNG_LOG_INFO("start one group " << it->first)
                executed |= RunOneGroup(it->second);
                ++it;
            }
        }
        return executed;
    }
    bool ApplyTask()
    {
        std::lock_guard<std::mutex> lock(wait_add_lock_);
        bool executed{};
        for (auto &group : wait_add_tasks_)
        {
            for (auto &task : group.second)
            {
                group_tasks_[group.first][task.first] = task.second;
                GROUP_MNG_LOG("apply task " << group.first << ";" << task.first)
                executed = true;
            }
        }
        wait_add_tasks_.clear();
        return executed;
    }
    bool ApplyStopTask()
    {
        std::lock_guard<std::mutex> lock(wait_add_lock_);
        bool executed{};
        for (auto &item : wait_stop_tasks_)
        {
            auto &merged_id = item.first;
            auto group_id = GroupID(merged_id);
            auto task_id = TaskID(merged_id);
            auto group = group_tasks_.find(group_id);
            bool real_removed{};
            if (group != group_tasks_.end())
            {
                real_removed = group->second.erase(task_id) != 0;
                GROUP_MNG_LOG("apply stop task " << ToString(merged_id))
                executed |= real_removed;
            }
            if (item.second != nullptr)
            {
                item.second(real_removed);
            }
        }
        wait_stop_tasks_.clear();
        return executed;
    }
    bool RunOneGroup(GroupTasksType &group)
    {
        GROUP_MNG_LOG("start one group ")
        if (group.empty())
        {
            return false;
        }
        CutDownLatch barrier(group.size());
        std::atomic_flag executed = ATOMIC_FLAG_INIT;
        for (auto &task_pair : group)
        {
            auto &task = task_pair.second;
            // 本轮不需要执行的
            if (task.need_run != nullptr && !task.need_run())
            {
                barrier.CountDown();
            }
            else
            {
                // 需要执行的分发执行
                executor_(task.i_func, barrier, executed);
                GROUP_MNG_LOG("send execute " << ToString(task.id))
            }
        }
        barrier.Wait();
        GROUP_MNG_LOG("end one group ")
        return executed.test();
    }
};
}  // namespace group_task