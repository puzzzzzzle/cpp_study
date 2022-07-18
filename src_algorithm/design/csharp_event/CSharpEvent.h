//
// Created by khalidzhang on 2020/1/20.
//

#pragma once
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_set>
#include <vector>

namespace CSharpEvent {

using DelegrateWeakSave = std::weak_ptr<std::function<void()>>;
using DelegrateDefine = std::shared_ptr<std::function<void()>>;

struct HandleBindHash {
  std::size_t operator()(DelegrateWeakSave const& ptr) const {
    if (auto spt = ptr.lock()) {  // 使用之前必须复制到 shared_ptr
      return reinterpret_cast<size_t>(&(*spt));
    } else {
      return 0;
    }
  }
  std::size_t operator()(DelegrateDefine const& ptr) const {
    return reinterpret_cast<size_t>(&(*ptr));
  }
};
struct HandleBindEqual {
  bool operator()(const DelegrateWeakSave& lhs,
                  const DelegrateWeakSave& rhs) const {
    return HandleBindHash()(lhs) == HandleBindHash()(rhs);
  }
};
/**
 * 事件接口定义
 * 事件订阅者需要自己保持订阅函数共享指针,如果订阅者自己丢失指针的话,这边也会删除事件
 * 因为很有可能是订阅者已经析构了
 */
class Event {
  public:
  /**
   * 添加长期事件
   * @param handle
   * @return
   */
  virtual bool Register(const DelegrateWeakSave handle) = 0;
  virtual Event* operator+=(const DelegrateWeakSave handle) = 0;

  /**
   * 删除长期事件
   * @param handle
   * @return
   */
  virtual bool Dismiss(const DelegrateWeakSave handle) = 0;
  virtual Event* operator-=(const DelegrateWeakSave handle) = 0;

  /**
   * 添加一次性事件
   * @param handle
   * @return
   */
  virtual bool RegisterOnce(const DelegrateWeakSave handle) = 0;
  /**
   * 删除一次性事件
   * @param handle
   * @return
   */
  virtual bool DismissOnce(const DelegrateWeakSave handle) = 0;

  /**
   * 触发一次事件
   * @return
   */
  virtual bool FireEvent() = 0;
};

/**
 *  不重复事件类型
 *  重复插入一个事件会返回false
 */
class UnOrderedEvent : Event {
  public:
  private:
  std::unordered_set<DelegrateWeakSave, HandleBindHash, HandleBindEqual>
      handleBindSet{};
  std::unordered_set<DelegrateWeakSave, HandleBindHash, HandleBindEqual>
      handleOnceBindSet{};

  std::mutex lock{};
  std::mutex lockOnce{};

  public:
  virtual bool Register(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lock);
    return handleBindSet.emplace(std::move(handle)).second;
  }

  virtual Event* operator+=(const DelegrateWeakSave handle) override {
    Register(handle);
    return this;
  }
  virtual bool Dismiss(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lock);
    return handleBindSet.erase(std::move(handle)) == 0;
  }

  virtual Event* operator-=(const DelegrateWeakSave handle) override {
    Dismiss(handle);
    return this;
  }

  virtual bool RegisterOnce(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lockOnce);
    return handleOnceBindSet.emplace(std::move(handle)).second;
  }

  virtual bool DismissOnce(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lockOnce);
    return handleOnceBindSet.erase(std::move(handle)) == 0;
  }
  virtual bool FireEvent() override {
    bool isNullHandleInList{false};
    {
      std::lock_guard<std::mutex> lockGuard(lock);
      for (auto it = handleBindSet.begin(); it != handleBindSet.end();) {
        if (auto spt = it->lock()) {
          (*spt)();
          ++it;
        } else {
          it = handleBindSet.erase(it);
          isNullHandleInList = true;
        }
      }
    }
    {
      std::lock_guard<std::mutex> lockGuard(lockOnce);
      for (auto it = handleOnceBindSet.begin();
           it != handleOnceBindSet.end();) {
        if (auto spt = it->lock()) {
          (*spt)();
        } else {
          isNullHandleInList = true;
        }
        it = handleOnceBindSet.erase(it);
      }
    }
    return isNullHandleInList;
  }
};

/**
 * 重复事件,插入的事件可以重复,按照插入顺序调用
 */
class MultiOrderedEvent : Event {
  public:
  private:
  std::vector<DelegrateWeakSave> handleBindVec{};
  std::vector<DelegrateWeakSave> handleOnceBindVec{};

  std::mutex lock{};
  std::mutex lockOnce{};

  public:
  virtual bool Register(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lock);
    handleBindVec.emplace_back(std::move(handle));
    return true;
  }
  virtual Event* operator+=(const DelegrateWeakSave handle) override {
    Register(handle);
    return this;
  }
  virtual bool Dismiss(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lock);
    bool isDelete{false};
    for (auto it = handleBindVec.begin(); it != handleBindVec.end();) {
      if (HandleBindHash()(*it) == HandleBindHash()(handle)) {
        it = handleBindVec.erase(it);
        isDelete = true;
      } else {
        ++it;
      }
    }
    return isDelete;
  }
  virtual Event* operator-=(const DelegrateWeakSave handle) override {
    Dismiss(handle);
    return this;
  }
  virtual bool RegisterOnce(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lockOnce);
    handleOnceBindVec.emplace_back(std::move(handle));
    return true;
  }

  virtual bool DismissOnce(const DelegrateWeakSave handle) override {
    std::lock_guard<std::mutex> lockGuard(lockOnce);
    bool isDelete{false};
    for (auto it = handleOnceBindVec.begin(); it != handleOnceBindVec.end();) {
      if (HandleBindHash()(*it) == HandleBindHash()(handle)) {
        it = handleOnceBindVec.erase(it);
        isDelete = true;
      } else {
        ++it;
      }
    }
    return isDelete;
  }
  virtual bool FireEvent() override {
    bool isNullHandleInList{false};
    {
      std::lock_guard<std::mutex> lockGuard(lock);
      for (auto it = handleBindVec.begin(); it != handleBindVec.end();) {
        if (auto spt = it->lock()) {  // 使用之前必须复制到 shared_ptr
          (*spt)();
          ++it;
        } else {
          it = handleBindVec.erase(it);
          isNullHandleInList = true;
        }
      }
    }
    {
      std::lock_guard<std::mutex> lockGuard(lockOnce);
      for (auto it = handleOnceBindVec.begin();
           it != handleOnceBindVec.end();) {
        if (auto spt = it->lock()) {
          (*spt)();
        } else {
          isNullHandleInList = true;
        }
        it = handleOnceBindVec.erase(it);
      }
    }
    return isNullHandleInList;
  }
};

#define Delegate(func) DelegrateDefine(new DelegrateDefine::element_type(func))
#define MakeDelegate(paraName, func) auto paraName = Delegate(func)

}  // namespace CSharpEvent