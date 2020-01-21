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
class UnOrderedEvent {
public:
    using funcType = typename Continuation<ARGS...>::type;

    using DelegrateWeakSave = std::weak_ptr<funcType>;
    using DelegrateDefine   = std::shared_ptr<funcType>;

    struct HandleBindHash {
        std::size_t operator()(DelegrateWeakSave const& ptr) const {
            if (auto spt = ptr.lock()) {  // 使用之前必须复制到 shared_ptr
                return reinterpret_cast<size_t>(&(*spt));
            } else {
                return 0;
            }
        }
        std::size_t operator()(DelegrateDefine const& ptr) const { return reinterpret_cast<size_t>(&(*ptr)); }
    };
    struct HandleBindEqual {
        bool operator()(const DelegrateWeakSave& lhs, const DelegrateWeakSave& rhs) const {
            return HandleBindHash()(lhs) == HandleBindHash()(rhs);
        }
    };

protected:
    std::unordered_set<DelegrateWeakSave, HandleBindHash, HandleBindEqual> handleBindSet{};
    std::unordered_set<DelegrateWeakSave, HandleBindHash, HandleBindEqual> handleOnceBindSet{};

    std::mutex lock{};
    std::mutex lockOnce{};

public:
    virtual bool Register(const DelegrateWeakSave handle) {
        std::lock_guard<std::mutex> lockGuard(lock);
        return handleBindSet.emplace(std::move(handle)).second;
    }

    virtual UnOrderedEvent* operator+=(const DelegrateWeakSave handle) {
        Register(handle);
        return this;
    }
    virtual bool Dismiss(const DelegrateWeakSave handle) {
        std::lock_guard<std::mutex> lockGuard(lock);
        return handleBindSet.erase(std::move(handle)) == 0;
    }

    virtual UnOrderedEvent* operator-=(const DelegrateWeakSave handle) {
        Dismiss(handle);
        return this;
    }

    virtual bool RegisterOnce(const DelegrateWeakSave handle) {
        std::lock_guard<std::mutex> lockGuard(lockOnce);
        return handleOnceBindSet.emplace(std::move(handle)).second;
    }

    virtual bool DismissOnce(const DelegrateWeakSave handle) {
        std::lock_guard<std::mutex> lockGuard(lockOnce);
        return handleOnceBindSet.erase(std::move(handle)) == 0;
    }
};
template <typename... ARGS>
class UnOrderedEventImpl : public UnOrderedEvent<ARGS...> {
public:
    virtual bool FireEvent(ARGS... arg) {
        bool isNullHandleInList{false};
        {
            std::lock_guard<std::mutex> lockGuard(UnOrderedEvent<ARGS...>::lock);
            for (auto it = UnOrderedEvent<ARGS...>::handleBindSet.begin();
                 it != UnOrderedEvent<ARGS...>::handleBindSet.end();) {
                if (auto spt = it->lock()) {  // 使用之前必须复制到 shared_ptr
                    (*spt)(arg...);
                    ++it;
                } else {
                    it                 = UnOrderedEvent<ARGS...>::handleBindSet.erase(it);
                    isNullHandleInList = true;
                }
            }
        }
        {
            std::lock_guard<std::mutex> lockGuard(UnOrderedEvent<ARGS...>::lockOnce);
            for (auto it = UnOrderedEvent<ARGS...>::handleOnceBindSet.begin();
                 it != UnOrderedEvent<ARGS...>::handleOnceBindSet.end();) {
                if (auto spt = it->lock()) {
                    (*spt)(arg...);
                } else {
                    isNullHandleInList = true;
                }
                it = UnOrderedEvent<ARGS...>::handleOnceBindSet.erase(it);
            }
        }
        return isNullHandleInList;
    }
};
template <>
class UnOrderedEventImpl<void> : public UnOrderedEvent<void> {
public:
    virtual bool FireEvent() {
        bool isNullHandleInList{false};
        {
            std::lock_guard<std::mutex> lockGuard(UnOrderedEvent<void>::lock);
            for (auto it = UnOrderedEvent<void>::handleBindSet.begin();
                 it != UnOrderedEvent<void>::handleBindSet.end();) {
                if (auto spt = it->lock()) {  // 使用之前必须复制到 shared_ptr
                    (*spt)();
                    ++it;
                } else {
                    it                 = UnOrderedEvent<void>::handleBindSet.erase(it);
                    isNullHandleInList = true;
                }
            }
        }
        {
            std::lock_guard<std::mutex> lockGuard(lockOnce);
            for (auto it = UnOrderedEvent<void>::handleOnceBindSet.begin();
                 it != UnOrderedEvent<void>::handleOnceBindSet.end();) {
                if (auto spt = it->lock()) {
                    (*spt)();
                } else {
                    isNullHandleInList = true;
                }
                it = UnOrderedEvent<void>::handleOnceBindSet.erase(it);
            }
        }
        return isNullHandleInList;
    }
};
#define DelegateUnOrdered( func,para...)                                                                                   \
    UnOrderedEventImpl<para>::DelegrateDefine(new UnOrderedEventImpl<para>::DelegrateDefine::element_type(func))