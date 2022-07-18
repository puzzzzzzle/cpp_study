//
// Created by khalidzhang on 2020/1/20.
//

#pragma once
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_set>
#include <vector>

#include "Traits.h"

template <typename... ARGS>
class MultiOrderedEvent {
  public:
  using funcType = typename Continuation<ARGS...>::type;

  using DelegrateWeakSave = std::weak_ptr<funcType>;
  using DelegrateDefine = std::shared_ptr<funcType>;

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

  protected:
  std::vector<DelegrateWeakSave> handleBindVec{};
  std::vector<DelegrateWeakSave> handleOnceBindVec{};

  std::mutex lock{};
  std::mutex lockOnce{};

  public:
  virtual bool Register(const DelegrateWeakSave handle) {
    std::lock_guard<std::mutex> lockGuard(lock);
    handleBindVec.emplace_back(std::move(handle));
    return true;
  }
  virtual MultiOrderedEvent* operator+=(const DelegrateWeakSave handle) {
    Register(handle);
    return this;
  }
  virtual bool Dismiss(const DelegrateWeakSave handle) {
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
  virtual MultiOrderedEvent* operator-=(const DelegrateWeakSave handle) {
    Dismiss(handle);
    return this;
  }
  virtual bool RegisterOnce(const DelegrateWeakSave handle) {
    std::lock_guard<std::mutex> lockGuard(lockOnce);
    handleOnceBindVec.emplace_back(std::move(handle));
    return true;
  }

  virtual bool DismissOnce(const DelegrateWeakSave handle) {
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
};
template <typename... ARGS>
class MultiOrderedEventImpl : public MultiOrderedEvent<ARGS...> {
  public:
  virtual bool FireEvent(ARGS... arg) {
    bool isNullHandleInList{false};
    {
      std::lock_guard<std::mutex> lockGuard(MultiOrderedEvent<ARGS...>::lock);
      for (auto it = MultiOrderedEvent<ARGS...>::handleBindVec.begin();
           it != MultiOrderedEvent<ARGS...>::handleBindVec.end();) {
        if (auto spt = it->lock()) {  // 使用之前必须复制到 shared_ptr
          (*spt)(arg...);
          ++it;
        } else {
          it = MultiOrderedEvent<ARGS...>::handleBindVec.erase(it);
          isNullHandleInList = true;
        }
      }
    }
    {
      std::lock_guard<std::mutex> lockGuard(
          MultiOrderedEvent<ARGS...>::lockOnce);
      for (auto it = MultiOrderedEvent<ARGS...>::handleOnceBindVec.begin();
           it != MultiOrderedEvent<ARGS...>::handleOnceBindVec.end();) {
        if (auto spt = it->lock()) {
          (*spt)(arg...);
        } else {
          isNullHandleInList = true;
        }
        it = MultiOrderedEvent<ARGS...>::handleOnceBindVec.erase(it);
      }
    }
    return isNullHandleInList;
  }
};
template <>
class MultiOrderedEventImpl<void> : public MultiOrderedEvent<void> {
  public:
  virtual bool FireEvent() {
    bool isNullHandleInList{false};
    {
      std::lock_guard<std::mutex> lockGuard(MultiOrderedEvent<void>::lock);
      for (auto it = MultiOrderedEvent<void>::handleBindVec.begin();
           it != MultiOrderedEvent<void>::handleBindVec.end();) {
        if (auto spt = it->lock()) {  // 使用之前必须复制到 shared_ptr
          (*spt)();
          ++it;
        } else {
          it = MultiOrderedEvent<void>::handleBindVec.erase(it);
          isNullHandleInList = true;
        }
      }
    }
    {
      std::lock_guard<std::mutex> lockGuard(lockOnce);
      for (auto it = MultiOrderedEvent<void>::handleOnceBindVec.begin();
           it != MultiOrderedEvent<void>::handleOnceBindVec.end();) {
        if (auto spt = it->lock()) {
          (*spt)();
        } else {
          isNullHandleInList = true;
        }
        it = MultiOrderedEvent<void>::handleOnceBindVec.erase(it);
      }
    }
    return isNullHandleInList;
  }
};
#define DelegateOrdered(func, para...)          \
  MultiOrderedEventImpl<para>::DelegrateDefine( \
      new MultiOrderedEventImpl<para>::DelegrateDefine::element_type(func))
