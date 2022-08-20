/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/5/12
 * @file ObjectPool.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include <atomic>
#include <cassert>
#include <memory>
#include <mutex>
#include <queue>
namespace ObjectPoolImpl {
/**
 * 每个对象被get 时 调用的构造方法
 * @tparam Object
 */
template <typename Object>
struct DefaultObjectConstructor {
  using ObjectT = Object;
  void operator()(ObjectT object) const {}
};
/**
 * 每个对象被 release, 重新放回 pool 时 调用的析构方法
 * @tparam Object
 */
template <typename Object>
struct DefaultObjectDestructor {
  using ObjectT = Object;
  void operator()(ObjectT object) const {}
};
/**
 * 非线程安全的队列池
 * @tparam Object
 */
template <typename Object>
struct QueuePoolType {
  using ObjectT = Object;
  using PoolTypeT = std::queue<ObjectT>;
  /**
   * 放回一个物体, 必须成功, 否则会内存泄漏
   * @param ptr
   */
  void Put(ObjectT ptr) { m_pool.push(ptr); }
  /**
   * 取出一个物体
   * 用于在pool析构时释放所有对象
   * @return
   */
  ObjectT Take() {
    if (m_pool.empty()) {
      return nullptr;
    }
    auto ptr = m_pool.front();
    m_pool.pop();
    return ptr;
  }
  size_t Size() { return m_pool.size(); }

  private:
  PoolTypeT m_pool{};
};
/**
 * 线程安全的队列池
 * 锁实现的性能较差
 * 有需要的话可以使用 moodycamel 实现的无锁安全队列
 * https://github.com/cameron314/concurrentqueue
 * @tparam Object
 */
template <typename Object>
struct ThreadSafeQueuePoolType {
  using ObjectT = Object;
  using PoolTypeT = QueuePoolType<ObjectT>;
  using LockT = std::unique_lock<std::mutex>;
  void Put(ObjectT ptr) {
    LockT lock(m_lock);
    m_pool.Put(ptr);
  }
  ObjectT Take() {
    LockT lock(m_lock);
    return m_pool.Take();
  }
  size_t Size() {
    LockT lock(m_lock);
    return m_pool.Size();
  }

  private:
  PoolTypeT m_pool{};
  std::mutex m_lock;
};
/**
 * 自动回收的对象池实现
 * 线程安全性取决于 PoolType 是否是线程安全的
 * 只回收裸指针, shared_ptr不会回收
 * @tparam Object 要存储的数据类型
 * @tparam PoolType 用于存储池子中的对象, 默认是一个有锁的队列, 多线程安全性取决于它
 * @tparam KEEP_SIZE_NUM 决定池子保存的对象的最大大小和每次分配量
 * @tparam Constructor 从池子中获取一个对象前总会调用的策略
 * @tparam Destructor 一个对象共享指针计数为0 时总会调用, 无论是否放回池子
 */
template <typename Object,
          typename ReusePoolType = ThreadSafeQueuePoolType<Object *>,
          size_t KEEP_SIZE_NUM = 10000,
          typename Constructor = DefaultObjectConstructor<Object *>,
          typename Destructor = DefaultObjectDestructor<Object *>>
class ObjectPool {
  public:
  using ObjectT = Object;
  using ConstructorT = Constructor;
  using DestructorT = Destructor;
  const size_t KEEP_SIZE = KEEP_SIZE_NUM;
  using ObjectPtrT = std::shared_ptr<ObjectT>;
  using ReusePoolTypeT = ReusePoolType;

  private:
  ReusePoolTypeT m_reusePool{};
  ConstructorT m_constructor{};
  DestructorT m_destructor{};
  std::atomic_bool m_isStopping;

  private:
  void ReleaseObject(ObjectT *ptr) {
    bool needReuse = true;
    // 析构池子时, 不再回收,
    if (m_isStopping) {
      needReuse = false;
    }
    if (m_reusePool.Size() > KEEP_SIZE) {
      needReuse = false;
    }

    m_destructor(ptr);
    if (needReuse) {
      // 回收一个对象

      // 这里不会有问题, 前一个shared_ptr 调用了 deleter 后, 就不再管这个指针了,
      // 只要我们没有真的delete, 相当与这个指针泄漏了
      // 但是这里把这个指针保存起来了, 下次再用, 就没有泄漏
      m_reusePool.Put(ptr);
    } else {
      // 直接释放, 不再回收
      delete ptr;
    }
  }
  ObjectT *AllocWithTrunk() {
    for (int i = 0; i < KEEP_SIZE / 10; ++i) {
      m_reusePool.Put(new ObjectT());
    }
    return new ObjectT();
  }

  public:
  ~ObjectPool() {
    // 标记不再回收
    m_isStopping = true;
    // 释放所有对象
    while (m_reusePool.Size() > 0) {
      auto *rowPtr = m_reusePool.Take();
      delete rowPtr;
    }
  }
  ObjectPool() : m_isStopping(false){};
  ObjectPtrT Alloc() {
    // 有可重用的, 就直接使用
    ObjectT *rowPtr = m_reusePool.Take();
    if (rowPtr == nullptr) {
      // 没有就申请
      rowPtr = AllocWithTrunk();
    }
    assert(rowPtr != nullptr);
    m_constructor(rowPtr);
    return std::shared_ptr<ObjectT>(
        rowPtr, [this](ObjectT *ptr) { ReleaseObject(ptr); });
  }
};
/**
 * 手动回收的对象池实现
 * 线程安全性取决于 PoolType 是否是线程安全的
 * 连 shared_ptr 也一同回收
 * 但是需要手动调用回收函数
 * 如果回收时, 引用计数不为1, 就会放弃回收
 * 回收后, 原来的指针会被置为null
 *
 * 如果一个对象没有被 ReleaseObject 那就不会调用 Destructor, 而是直接使用默认的析构函数
 * 需要保证析构函数和 Destructor 都可以做到资源释放, 且二次释放没有问题
 *
 * 没有特殊需求不使用这个, 仅用于 对象量极大, 连shared_ptr的构造和析构都是瓶颈的地方
 * @tparam Object
 * @tparam PoolType
 * @tparam KEEP_SIZE_NUM
 * @tparam Constructor
 * @tparam Destructor
 */
template <typename Object,
          typename ReusePoolType =
              ThreadSafeQueuePoolType<std::shared_ptr<Object>>,
          size_t KEEP_SIZE_NUM = 10000,
          typename Constructor = DefaultObjectConstructor<Object *>,
          typename Destructor = DefaultObjectDestructor<Object *>>
class ObjectManualPool {
  public:
  using ObjectT = Object;
  using ConstructorT = Constructor;
  using DestructorT = Destructor;
  const size_t KEEP_SIZE = KEEP_SIZE_NUM;
  using ObjectPtrT = std::shared_ptr<ObjectT>;
  using ReusePoolTypeT = ReusePoolType;

  private:
  ReusePoolTypeT m_reusePool{};
  ConstructorT m_constructor{};
  DestructorT m_destructor{};
  std::atomic_bool m_isStopping;

  private:
  void ReleaseObject(ObjectPtrT &ptr) {
    bool needReuse = true;
    // 析构池子时, 不再回收,
    if (m_isStopping) {
      needReuse = false;
    }
    if (m_reusePool.Size() > KEEP_SIZE) {
      needReuse = false;
    }

    m_destructor(ptr.get());
    if (needReuse) {
      // 回收一个对象

      // 这里不会有问题, 前一个shared_ptr 调用了 deleter 后, 就不再管这个指针了,
      // 只要我们没有真的delete, 相当与这个指针泄漏了
      // 但是这里把这个指针保存起来了, 下次再用, 就没有泄漏
      m_reusePool.Put(ptr);
    } else {
      // 直接释放, 不再回收
    }
  }
  ObjectPtrT AllocWithTrunk() {
    for (int i = 0; i < KEEP_SIZE / 10; ++i) {
      m_reusePool.Put(std::make_shared<ObjectT>());
    }
    return std::make_shared<ObjectT>();
  }

  public:
  ~ObjectManualPool() {
    // 标记不再回收
    m_isStopping = true;
    // 释放所有对象
    while (m_reusePool.Size() > 0) {
      auto ptr = m_reusePool.Take();
      ptr = nullptr;
    }
  }
  ObjectManualPool() : m_isStopping(false){};
  ObjectPtrT Alloc() {
    // 有可重用的, 就直接使用
    ObjectPtrT ptr = m_reusePool.Take();
    if (ptr == nullptr) {
      // 没有就申请
      ptr = AllocWithTrunk();
    }
    assert(ptr != nullptr);
    m_constructor(ptr.get());
    return ptr;
  }
  bool TryPushBack(ObjectPtrT &ptr) {
    if (ptr.use_count() == 1) {
      ReleaseObject(ptr);
      ptr = nullptr;
      return true;
    }
    return false;
  }
};
}  // namespace ObjectPoolImpl