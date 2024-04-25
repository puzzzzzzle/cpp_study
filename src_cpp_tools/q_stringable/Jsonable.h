#pragma once
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/pointer.h"
#include "Stringable.h"

/***
 * 快速jsonable
 * 使用 CRTP 实现静态多态 , 避免虚函数
 * 适用于大量小物体 , 保持
 * 需要实现
 * rapidjson::Value ToRapidJsonImpl(rapidjson::Document::AllocatorType &allocator) const
 * int LoadRapidJsonImpl(const rapidjson::Value &value)
 * 两个接口, 空实现也行, 但是必须有
 * @tparam T
 */
template <class T>
class Jsonable : public Stringable<T> {
public:
  // 需要实现的部分, 理论上可以用覆盖规则, 这里可以保留, 但是比较丑, 还是直接注释掉吧
  //    rapidjson::Value ToRapidJsonImpl(rapidjson::Document::AllocatorType &allocator) const
  //    {
  //        return rapidjson::Value();
  //    }
  //
  //    int LoadRapidJsonImpl(const rapidjson::Value &value)
  //    {
  //        return JSON_ERR;
  //    }
public:
  static const std::string GetNoImplJsonStr() {
    return R"({"error":"NO_IMPL_JSON"})";
  }

  static const std::string GetToJsonErrStr() {
    return R"({"error":"TO_JSON_ERR"})";
  }

  static const std::string GetRootName() {
    return "";
  }

  enum {
    JSON_OK = 0,
    JSON_ERR = 1,
    ALREADY_HAVE = 2,
  };

private:
  inline const T* GetRImpl() const {
    return static_cast<const T*>(this);
  }

  inline T* GetWImpl() {
    return static_cast<T*>(this);
  }

public:
  std::ostream& ToStringImpl(std::ostream& os) const {
    os << ToJsonString();
    return os;
  }

  std::string ToJsonString() const {
    rapidjson::Document document{};
    const std::string basePointer = GetRootName();
    int iRet = ToRapidJson(document, basePointer, true);
    if (iRet == JSON_ERR) {
      return GetNoImplJsonStr();
    }
    if (iRet != 0) {
      GetToJsonErrStr();
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    if (!document.Accept(writer)) {
      return GetToJsonErrStr();
    }
    return std::string(buffer.GetString());
  }

  int LoadJsonString(const std::string& json,
                     const std::string root = GetRootName()) {
    rapidjson::StringStream stream(json.c_str());

    rapidjson::Document document;
    document.ParseStream(stream);
    return LoadRapidJson(document, root);
  }

  int ToRapidJson(rapidjson::Document& document, const std::string& pointer,
                  bool isRoot = false) const {
    // 存在就不再添加
    if (rapidjson::Pointer(pointer.c_str()).Get(document) != nullptr) {
      // root 固定存在, 但有时候需要在root下强制插入
      if (!isRoot) {
        return ALREADY_HAVE;
      }
    }
    auto valueJson = GetRImpl()->ToRapidJsonImpl(document.GetAllocator());
    if (valueJson.IsNull()) {
      return JSON_ERR;
    }
    if (valueJson.GetType() == rapidjson::kNullType) {
      return JSON_ERR;
    }
    // 插入doc中
    rapidjson::Pointer(pointer.c_str()).Set(document, valueJson);
    return JSON_OK;
  }

  int LoadRapidJson(rapidjson::Document& document, const std::string& pointer) {
    //        BS_LOG_DEBUG("before point")
    // 存在就不再添加
    auto root = rapidjson::Pointer(pointer.c_str()).Get(document);
    if (root == nullptr) {
      return JSON_ERR;
    }

    return GetWImpl()->LoadRapidJsonImpl(*root);
  }
};