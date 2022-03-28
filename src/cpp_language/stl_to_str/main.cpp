//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "stl_to_str.h"
#define STL_TO_STR_WITH_COUNT

class TestPayload {
  static int Count;

  public:
  int v1{};
  std::string s2{};
  const std::string& ToString() const { return s2; }
  static TestPayload Get() {
    TestPayload p{};
    p.v1 = Count;
    p.s2 = "TestPayload_" + std::to_string(p.v1);
    ++Count;
    return p;
  }
};
int TestPayload::Count = 0;
inline bool operator<(const TestPayload& lhs, const TestPayload& rhs) {
  return lhs.v1 < rhs.v1;
}
inline bool operator==(const TestPayload& lhs, const TestPayload& rhs) {
  return lhs.v1 == rhs.v1;
}
std::ostream& operator<<(std::ostream& os, const TestPayload& p) {
  os << p.ToString();
  return os;
}
struct TestPayloadHash {
  size_t operator()(TestPayload t) const { return static_cast<size_t>(t.v1); }
};
class TestPayloadValueToStream {
  public:
  void operator()(std::ostream& os, const TestPayload& v) {
    os << v << "@" << &v;
  }
};

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(vec, int) {
  std::vector<int> v1{1, 2, 3, 4};
  vec_like_to_string(v1);
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
}
TEST(array, TestPayload) {
  std::array<TestPayload, 5> v1{};
  for (int i = 0; i < 5; ++i) {
    v1[i] = TestPayload::Get();
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(vec, TestPayload) {
  std::set<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(set, TestPayload) {
  std::set<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(unordered_set, TestPayload) {
  std::unordered_set<TestPayload, TestPayloadHash> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(map, TestPayload) {
  std::map<int, TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1[i] = TestPayload::Get();
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(map_like_to_string(v1))
  LOG_DEBUG((map_like_to_string<decltype(v1), default_value_to_stream<int>,
                                TestPayloadValueToStream>(v1)))
}
TEST(unordered_map, TestPayload) {
  std::unordered_map<int, TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1[i] = TestPayload::Get();
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(map_like_to_string(v1))
  LOG_DEBUG((map_like_to_string<decltype(v1), default_value_to_stream<int>,
                                TestPayloadValueToStream>(v1)))
}
TEST(pair, TestPayload) {
  auto v1 = std::make_pair(1, TestPayload::Get());
  LOG_DEBUG(v1)
  LOG_DEBUG(pair_to_string(v1))
}
int main(int argc, char** argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}