#include <time_gap.hpp>

#include "common_includes.h"
#include "Stringable.h"
#include "Jsonable.h"
#define JSONABLE_LOG(log) LOG_DEBUG(log)
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

class Point : public Stringable<Point> {
public:
  int x_{};
  int y_{};
  Point() = default;

  Point(int x, int y): x_(x), y_(y) {
  }

  std::ostream& ToStringImpl(std::ostream& os) const {
    os << "y:" << x_;
    os << "y:" << y_;
    return os;
  }
};

/**
 * 虚函数版, 测试性能
 */
class VStringable : public Stringable<VStringable> {
public:
  std::ostream& ToStringImpl(std::ostream& os) const {
    return VToStringImpl(os);
  }

  virtual ~VStringable() = default;
  virtual std::ostream& VToStringImpl(std::ostream& os) const =0;
};

class VPoint : public VStringable {
public:
  int x_{};
  int y_{};
  VPoint() = default;

  VPoint(int x, int y): x_(x), y_(y) {
  }

  std::ostream& VToStringImpl(std::ostream& os) const override {
    os << "y:" << x_;
    os << "y:" << y_;
    return os;
  }
};

template <class T>
void MakePoints(int count = 10000000) {
  std::vector<T> points{};
  TimeGap gap{};

  // --------
  for (int i = 0; i < count; ++i) {
    points.emplace_back(123, 456);
  }
  // 提前Cache time, 防止日志输出时造成误差
  gap.cacheTime();
  LOG_DEBUG(
      "make time :  "<<"type:"<<typeid(T).name()<<"\tcount:" << count <<
      "\ttime(us):"<<gap.gapCacheUs() <<",(ms)"<<gap.gapCacheMs())

  // --------
  gap.resetStartNow();
  std::vector<T> points1 = points;
  // 提前Cache time, 防止日志输出时造成误差
  gap.cacheTime();
  LOG_DEBUG(
      "copy time :  "<<"type:"<<typeid(T).name()<<"\tcount:" << count <<
      "\ttime(us):"<<gap.gapCacheUs() <<",(ms)"<<gap.gapCacheMs())

  // --------
  gap.resetStartNow();
  points.clear();
  // 提前Cache time, 防止日志输出时造成误差
  gap.cacheTime();
  LOG_DEBUG(
      "clear points free time :  "<<"type:"<<typeid(T).name()<<"\tcount:" <<
      count <<
      "\ttime(us):"<<gap.gapCacheUs() <<",(ms)"<<gap.gapCacheMs())

  // --------
  gap.resetStartNow();
  points1.clear();
  // 提前Cache time, 防止日志输出时造成误差
  gap.cacheTime();
  LOG_DEBUG(
      "clear points1 free time :  "<<"type:"<<typeid(T).name()<<"\tcount:" <<
      count <<
      "\ttime(us):"<<gap.gapCacheUs() <<",(ms)"<<gap.gapCacheMs())
}

TEST(speed_test, stringable) {
  /*
析构差别很大, 是因为析构时
travelCopyable 版本, 直接标记内存不再使用就行
非 travelCopyable 版本, 需要遍历调用析构函数
   */
  /*
debug 版本 构造 拷贝 析构 10000000 次
非虚函数版, 构造耗时1092ms, 拷贝耗时247ms, 析构耗时 0ms
虚函数版, 构造耗时1658ms, 拷贝耗时340ms, 析构耗时 221ms
   */
  /*
release O3 版本 构造 拷贝 析构 10000000 次
非虚函数版, 构造耗时127ms, 拷贝耗时52ms, 析构耗时 0ms
虚函数版, 构造耗时264ms, 拷贝耗时84ms, 析构耗时 24ms
   */
  for (int i = 0; i < 3; ++i) {
    TimeGap gap{};
    MakePoints<Point>();
    LOG_DEBUG(
        "make copy free*2 total time :" << "\ttime(us):"<<gap.gapUs() <<",(ms)"
        <<gap.gapMs())
    printf("\n");
  }
  printf("-------------\n\n");
  for (int i = 0; i < 3; ++i) {
    TimeGap gap{};
    MakePoints<VPoint>();
    LOG_DEBUG(
        "make copy free*2 total time :" << "\ttime(us):"<<gap.gapUs() <<
        ",(ms)"<<gap.gapMs())
    printf("\n");
  }
}

/*
debug 版

[14] [DEBUG] [2024-04-25 07:39:46 103ms:618µs:210ns] [make time :  type:5Point	count:10000000	time(us):1092356,(ms)1092] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:167  void MakePoints(int) [with T = Point]]
[15] [DEBUG] [2024-04-25 07:39:46 351ms:105µs:286ns] [copy time :  type:5Point	count:10000000	time(us):247336,(ms)247] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:176  void MakePoints(int) [with T = Point]]
[16] [DEBUG] [2024-04-25 07:39:46 351ms:173µs:594ns] [clear points free time :  type:5Point	count:10000000	time(us):0,(ms)0] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:185  void MakePoints(int) [with T = Point]]
[17] [DEBUG] [2024-04-25 07:39:46 351ms:266µs:299ns] [clear points1 free time :  type:5Point	count:10000000	time(us):0,(ms)0] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:195  void MakePoints(int) [with T = Point]]

-------------

[19] [DEBUG] [2024-04-25 07:39:48 24ms:144µs:567ns] [make time :  type:6VPoint	count:10000000	time(us):1658179,(ms)1658] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:167  void MakePoints(int) [with T = VPoint]]
[20] [DEBUG] [2024-04-25 07:39:48 364ms:850µs:419ns] [copy time :  type:6VPoint	count:10000000	time(us):340550,(ms)340] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:176  void MakePoints(int) [with T = VPoint]]
[21] [DEBUG] [2024-04-25 07:39:48 586ms:485µs:390ns] [clear points free time :  type:6VPoint	count:10000000	time(us):221555,(ms)221] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:185  void MakePoints(int) [with T = VPoint]]
[22] [DEBUG] [2024-04-25 07:39:48 808ms:390µs:64ns] [clear points1 free time :  type:6VPoint	count:10000000	time(us):221761,(ms)221] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:195  void MakePoints(int) [with T = VPoint]]
 */
/*
release O3 版

[14] [DEBUG] [2024-04-25 07:39:13 772ms:492µs:913ns] [make time :  type:5Point	count:10000000	time(us):127575,(ms)127] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:167  void MakePoints(int) [with T = Point]]
[15] [DEBUG] [2024-04-25 07:39:13 824ms:818µs:677ns] [copy time :  type:5Point	count:10000000	time(us):52236,(ms)52] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:176  void MakePoints(int) [with T = Point]]
[16] [DEBUG] [2024-04-25 07:39:13 824ms:962µs:835ns] [clear points free time :  type:5Point	count:10000000	time(us):0,(ms)0] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:185  void MakePoints(int) [with T = Point]]
[17] [DEBUG] [2024-04-25 07:39:13 824ms:991µs:764ns] [clear points1 free time :  type:5Point	count:10000000	time(us):0,(ms)0] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:195  void MakePoints(int) [with T = Point]]

-------------

[19] [DEBUG] [2024-04-25 07:39:14 103ms:867µs:919ns] [make time :  type:6VPoint	count:10000000	time(us):264105,(ms)264] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:167  void MakePoints(int) [with T = VPoint]]
[20] [DEBUG] [2024-04-25 07:39:14 188ms:880µs:846ns] [copy time :  type:6VPoint	count:10000000	time(us):84912,(ms)84] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:176  void MakePoints(int) [with T = VPoint]]
[21] [DEBUG] [2024-04-25 07:39:14 213ms:129µs:978ns] [clear points free time :  type:6VPoint	count:10000000	time(us):24091,(ms)24] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:185  void MakePoints(int) [with T = VPoint]]
[22] [DEBUG] [2024-04-25 07:39:14 239ms:807µs:433ns] [clear points1 free time :  type:6VPoint	count:10000000	time(us):26547,(ms)26] [/tmp/tmp.QIYvyIJf56/src_cpp_tools/q_stringable/main.cpp:195  void MakePoints(int) [with T = VPoint]]
 */
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}