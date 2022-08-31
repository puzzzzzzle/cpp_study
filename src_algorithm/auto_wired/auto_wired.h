//
// Created by khalidzhang on 2021/10/15.
//

#pragma once
#include <map>
#include <vector>
#include <string>
//#define AUTO_WIRED_BASE(name, var, index) \
//  name##Export* var {}
//#define AUTO_WIRED(name, var) AUTO_WIRED_BASE(name, var, 0)
template <class T>
class AutoWiredValueBase {
  public:
  T* value_{};
  T* Value() { return value_; }
  void SetValue(T* rhs) { value_ = rhs; }
  T* operator*() { return this->value_; }
  AutoWiredValueBase(T* value) : value_(value) {}
  AutoWiredValueBase() = default;
  //  AutoWiredValueBase(AutoWiredValueBase&) = delete;
  //  AutoWiredValueBase(AutoWiredValueBase&& rhs) {
  //    this->value_ = rhs.value_;
  //    rhs.value_ = nullptr;
  //  };
  //  void operator=(AutoWiredValueBase&) = delete;
  //  void operator=(AutoWiredValueBase&& rhs) {
  //    this->value_ = rhs.value_;
  //    rhs.value_ = nullptr;
  //  }
};
template <class T>
using AutoWiredValue = AutoWiredValueBase<T>;
// template <class T>
// class AutoWiredValue : public AutoWiredValueBase<T> {
//   public:
//
//   ~AutoWiredValue() { delete this->value_; }
// };
//  template <>
//  class AutoWiredValue<void> : public AutoWiredValueBase<void> {
//
//  };

// 创建工厂

// 存储
class AutoWiredData {
  public:
  using ValueType = AutoWiredValue<void>;
  using InjectionHolder =
      std::map<std::string,
               std::vector<std::pair<AutoWiredValue<void*>, bool>>>;

  private:
  InjectionHolder injectionInfos_{};

  public:
  template <class T>
  void RegValue(const std::string& name, T** value) {
    injectionInfos_[name].push_back(
        std::make_pair(AutoWiredValue<void*>((void**)value), false));
  }
  InjectionHolder& GetHolder() { return injectionInfos_; }
  //  int DoAutoWired()
};
class SimpleAutoWiredFactory {
  private:
  std::map<const std::string, AutoWiredData::ValueType> values_;

  public:
  template <class T>
  int RegValue(const std::string& name, T* value) {
    auto it = values_.find(name);
    if (it != values_.end()) {
      return 1;
    }
    values_[name] = AutoWiredData::ValueType((void*)value);
    return 0;
  }
  AutoWiredData::ValueType Get(const std::string& name) {
    auto it = values_.find(name);
    if (it != values_.end()) {
      return it->second;
    }
    return AutoWiredData::ValueType(nullptr);
  }
};

template <class Factory = SimpleAutoWiredFactory>
class AutoWiredImpl {
  public:
  using ValueHolder = std::map<std::string, AutoWiredData::ValueType>;

  private:
  Factory* factory_{};
  AutoWiredData injectionInfo_{};
  ValueHolder values_{};

  public:
  AutoWiredImpl() { factory_ = new Factory(); }
  AutoWiredImpl(Factory* f) : factory_(f) {}
  ~AutoWiredImpl() { delete factory_; }
  Factory* GetFactory() { return factory_; }
  AutoWiredData* GetInjMng() { return &injectionInfo_; }

  public:
  int DoAutoWired() {
    auto& holder = GetInjMng()->GetHolder();
    for (auto& injectionItem : holder) {
      auto it = values_.find(injectionItem.first);
      AutoWiredData::ValueType value{};
      if (it == values_.end()) {
        auto temp = factory_->Get(injectionItem.first);
        if (temp.Value() == nullptr) {
          return -1000;
        }
        values_[injectionItem.first] = temp;
        value = temp;
      } else {
        value = it->second;
      }
      for (auto& inj : injectionItem.second) {
        if (inj.second) {
          continue;
        }
        *(inj.first.value_) = value.Value();
      }
    }
    return 0;
  }
};

#define PRINT_WIRED_INFO(ret, value) \
  printf("reg value %s %s -> %d\n", __PRETTY_FUNCTION__, #value, ret);
#define AUTO_WIRED(ctx, value)                                                \
  __attribute__((constructor)) static void reg_autowired_value() {            \
    int ret = ctx.GetInjMng()->RegValue(std::string(__PRETTY_FUNCTION__) + "_" + #value, \
                                        &value);                            \
    PRINT_WIRED_INFO(ret, value)                                              \
  }
