//
// Created by khalidzhang on 2022/12/21.
//
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <boost/format.hpp>

#include "common_includes.h"

using namespace rapidjson;
auto jsonStr = R"(
{
  "hello": "world",
  "t": true,
  "f": false,
  "n": null,
  "i": 123,
  "pi": 3.1416,
  "a": [
    1,
    2,
    3,
    4
  ]
}
)";
static std::string rapid_json_to_string(const Document& document) {
  rapidjson::StringBuffer buffer{};
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  assert(document.Accept(writer));
  return buffer.GetString();
}
TEST(rapidjson, simple_read) {
  Document document{};
  document.Parse(jsonStr);

  // 读取
  ASSERT_TRUE(document.HasMember("hello"));
  ASSERT_TRUE(document["hello"].IsString());
  LOG_DEBUG(document["hello"].GetString());
  // bool
  ASSERT_TRUE(document["t"].IsBool());
  LOG_DEBUG(boost::format("t = %s") %
            (document["t"].GetBool() ? "true" : "false"))
  // 判空
  LOG_DEBUG(boost::format("n = %s\n") % (document["n"].IsNull() ? "null" : "?"))

  // 读取数字
  // 在此情况下，IsUint()/IsInt64()/IsUint64() 也会返回 true
  ASSERT_TRUE(document["i"].IsNumber());
  ASSERT_TRUE(document["i"].IsInt());
  LOG_DEBUG("i = " << document["i"].GetInt());

  // double
  ASSERT_TRUE(document["pi"].IsNumber());
  ASSERT_TRUE(document["pi"].IsDouble());
  LOG_DEBUG("pi = " << document["pi"].GetDouble());

  LOG_DEBUG(rapid_json_to_string(document))
}

TEST(rapidjson, string) {
  Document document{};
  document.SetObject();
  Value test{};
  // rodata 中的string字面量 可以直接用, 以const string的方式全局共享
  test.SetString("test");
  // 这样add 不会拷贝, 只是拷贝指针
  document.AddMember("test", test, document.GetAllocator());

  Value test2{};
  const char* cStr = getenv("HOME");
  // 非字面量, 不允许直接设置
  // test2.SetString(cStr);
  // 但可以通过转换, 转为字面量
  test2.SetString(StringRef(cStr));
  document.AddMember("test2", test2, document.GetAllocator());

  // 临时分配的字符串, 最好不要转换为字面量格式, 不安全
  // 使用时拷贝
  std::string temp = "test3";
  // 下面key和value两种构造方式是一样的
  Value test3{};
  test3.SetString(temp.c_str(), temp.size(), document.GetAllocator());
  document.AddMember(
      Value(temp.c_str(), temp.size(), document.GetAllocator()).Move(),
      test3.Move(), document.GetAllocator());
  // 注意: member 允许键重复, 按照json标准是允许的, 但是其他许多语言可能会覆盖
  document.AddMember(
      Value(temp.c_str(), temp.size(), document.GetAllocator()).Move(), "sss",
      document.GetAllocator());
  LOG_DEBUG(rapid_json_to_string(document))

  // 删除时只删除第一个找到的
  document.RemoveMember(
      Value(temp.c_str(), temp.size(), document.GetAllocator()).Move());
  LOG_DEBUG(rapid_json_to_string(document))
}

TEST(rapidjson, pointer) {
  Document document{};
  document.Parse(jsonStr);
  // get
  Pointer p1("/hello");
  LOG_DEBUG(p1.Get(document)->GetString())

  // set
  Pointer("/i").Set(document, 1111);
  LOG_DEBUG(rapid_json_to_string(document))

  // Set() 和 Create() 自动生成父值（如果它们不存在）。
  Pointer("/s/b/0").Create(document);
  LOG_DEBUG(rapid_json_to_string(document))
  // 中间有空位的用null填充
  Pointer("/s/b/0").Set(document, 555);
  Pointer("/s/b/2").Set(document, 555);

  LOG_DEBUG(rapid_json_to_string(document))

  SetValueByPointer(document, "/project", "RapidJSON");
  SetValueByPointer(document, "/stars", 10);
  LOG_DEBUG(rapid_json_to_string(document))


}