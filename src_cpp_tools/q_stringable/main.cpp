#include "common_includes.h"
#include "Stringable.h"
#include "Jsonable.h"
#ifndef JSONABLE_LOG
#define JSONABLE_LOG(log)
#endif

// 构造存储在rappidjson中的string
#define MAKE_STRING_VALUE(str, alloc) rapidjson::Value(str.c_str(), str.length(), alloc).Move()

// object getter
#define RAPID_OBJ_SET_MEMBER(obj, var, name) obj.AddMember(name, var, allocator);
// 使用变量的名字作为json名字存储
#define RAPID_OBJ_SET_MEMBER_SAME(obj, var) RAPID_OBJ_SET_MEMBER(obj, var, #var)

// object setter
// 参数 jsonObj, alloc, 保存用的变量, json名字, 类型
#define RAPID_OBJ_GET_MEMBER_BASE(obj, alloc_var, var, name, type, default_value) \
alloc_var var = default_value; \
auto var##It = obj.FindMember(name); \
if (var##It == obj.MemberEnd()) \
{ \
JSONABLE_LOG("not found member:" << #var) \
} \
else if (!var##It->value.Is##type()) \
{ \
JSONABLE_LOG("type not match, type is:" << var##It->value.GetType()) \
} \
else \
{ \
var = var##It->value.Get##type(); \
}

// 指定名字, 赋值给已存在的变量，找不到字段或者类型不匹配时使用默认值
#define RAPID_OBJ_GET_MEMBER_EXIST(obj, var, name, type, default_value) \
RAPID_OBJ_GET_MEMBER_BASE(obj, , var, name, type, default_value)
// 指定名字, 同时生成一个同名变量存储，找不到字段或者类型不匹配时使用默认值
#define RAPID_OBJ_GET_MEMBER(obj, var, name, type, default_value) \
RAPID_OBJ_GET_MEMBER_BASE(obj, auto, var, name, type, default_value)
// 变量和json使用同一个名字, 赋值给已存在的变量，找不到字段或者类型不匹配时使用默认值
#define RAPID_OBJ_GET_MEMBER_EXIST_SAME(obj, var, type, default_value) \
RAPID_OBJ_GET_MEMBER_EXIST(obj, var, #var, type, default_value)
// 变量和json使用同一个名字, 同时生成一个同名变量存储，找不到字段或者类型不匹配时使用默认值
#define RAPID_OBJ_GET_MEMBER_SAME(obj, var, type, default_value) \
RAPID_OBJ_GET_MEMBER(obj, var, #var, type, default_value)

class StringTest : public Stringable<StringTest> {
public:
  int i_ = 1;
  float f_ = 4.2;
  std::string str_ = "ssss1";

  std::ostream& ToStringImpl(std::ostream& os) const {
    os << " i_:" << i_;
    os << " f_:" << f_;
    os << " str_:" << str_;
    return os;
  }
};

TEST(test_test, string_test) {
  const StringTest t1{};
  LOG_DEBUG(t1);
  ASSERT_EQ(t1.ToString(), " i_:1 f_:4.2 str_:ssss1");
  std::vector<StringTest> ts{};
  ts.resize(5);
  LOG_DEBUG(ts);
  ASSERT_EQ(vec_like_to_string(ts),
            "[ i_:1 f_:4.2 str_:ssss1, i_:1 f_:4.2 str_:ssss1, i_:1 f_:4.2 str_:ssss1, i_:1 f_:4.2 str_:ssss1, i_:1 f_:4.2 str_:ssss1]");
}

class JsonTest : public Jsonable<JsonTest> {
public:
  int i_ = 1;
  // float 输出有精度问题, 忽略
  // float f_ = 4.2;
  std::string str_ = "ssss1";

  rapidjson::Value ToRapidJsonImpl(
      rapidjson::Document::AllocatorType& allocator) const {
    rapidjson::Value obj{};
    obj.SetObject();
    RAPID_OBJ_SET_MEMBER_SAME(obj, i_);
    // RAPID_OBJ_SET_MEMBER_SAME(obj, f_);
    RAPID_OBJ_SET_MEMBER(obj, MAKE_STRING_VALUE(str_,allocator), "str_");
    return obj;
  }

  int LoadRapidJsonImpl(const rapidjson::Value& value) {
    RAPID_OBJ_GET_MEMBER_EXIST_SAME(value, i_, Int, 0);
    // RAPID_OBJ_GET_MEMBER_EXIST_SAME(value, f_, Float, 0.0);
    RAPID_OBJ_GET_MEMBER_EXIST_SAME(value, str_, String, "");
    return JSON_OK;
  }
};

TEST(test_test, json_test) {
  const JsonTest t1{};
  LOG_DEBUG(t1);
  auto result = R"({"i_":1,"str_":"ssss1"})";
  ASSERT_EQ(t1.ToString(), result);
  std::vector<JsonTest> ts{};
  ts.resize(5);
  LOG_DEBUG(ts);
  ASSERT_EQ(vec_like_to_string(ts),
            R"([{"i_":1,"str_":"ssss1"},{"i_":1,"str_":"ssss1"},{"i_":1,"str_":"ssss1"},{"i_":1,"str_":"ssss1"},{"i_":1,"str_":"ssss1"}])");
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}