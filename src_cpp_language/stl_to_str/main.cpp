//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "stl_to_steam.h"

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
  size_t operator()(const TestPayload& t) const {
    return static_cast<size_t>(t.v1);
  }
};
class TestPayloadValueToStream {
  public:
  static void to_stream(std::ostream& os, const TestPayload& v) {
    os << v << "@" << &v;
  }
};

TEST(vec, int) {
  std::vector<int> v1{1, 2, 3, 4};
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
}

TEST(vec, recursive) {
  std::vector<int> v1{};
  std::vector<std::vector<int>> vv1{};
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
    vv1.push_back(v1);
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vv1)
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
TEST(forward_list, TestPayload) {
  std::forward_list<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push_front(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(list, TestPayload) {
  std::list<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push_front(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(deque, TestPayload) {
  std::deque<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push_front(TestPayload::Get());
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
TEST(multiset, TestPayload) {
  std::multiset<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert(TestPayload::Get());
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(unordered_multiset, TestPayload) {
  std::unordered_multiset<TestPayload, TestPayloadHash> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert(TestPayload::Get());
  }
  std::cout << v1;
  LOG_DEBUG(v1)
  LOG_DEBUG(vec_like_to_string(v1))
  LOG_DEBUG((vec_like_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(stack, TestPayload) {
  std::stack<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push(TestPayload::Get());
  }
  std::cout << v1;
  LOG_DEBUG(v1)
  LOG_DEBUG(adaptor_to_string(v1))
  LOG_DEBUG((adaptor_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(queue, TestPayload) {
  std::queue<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push(TestPayload::Get());
  }
  std::cout << v1;
  LOG_DEBUG(v1)
  LOG_DEBUG(adaptor_to_string(v1))
  LOG_DEBUG((adaptor_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
}
TEST(priority_queue, TestPayload) {
  std::priority_queue<TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.push(TestPayload::Get());
  }
  std::cout << v1;
  LOG_DEBUG(v1)
  LOG_DEBUG(adaptor_to_string(v1))
  LOG_DEBUG((adaptor_to_string<decltype(v1), TestPayloadValueToStream>(v1)))
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
TEST(map, recursive) {
  std::map<int, TestPayload> v1{};
  std::map<int, std::map<int, TestPayload>> vv1{};

  for (int i = 0; i < 5; ++i) {
    v1[i] = TestPayload::Get();
    vv1[i * 10000] = v1;
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(vv1)
}
TEST(multimap, TestPayload) {
  std::multimap<int, TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert({i, TestPayload::Get()});
  }
  LOG_DEBUG(v1)
  LOG_DEBUG(map_like_to_string(v1))
  LOG_DEBUG((map_like_to_string<decltype(v1), default_value_to_stream<int>,
                                TestPayloadValueToStream>(v1)))
}
TEST(unordered_multimap, TestPayload) {
  std::unordered_multimap<int, TestPayload> v1{};
  for (int i = 0; i < 5; ++i) {
    v1.insert({i, TestPayload::Get()});
  }
  //  LOG_DEBUG(v1)
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
TEST(tuple, TestPayload) {
  LOG_DEBUG(std::make_tuple(1))
  LOG_DEBUG(std::make_tuple(1, TestPayload::Get()))
  LOG_DEBUG(std::make_tuple(1, TestPayload::Get(), TestPayload::Get()))
  LOG_DEBUG(std::make_tuple(1, TestPayload::Get(),
                            std::make_tuple(1, TestPayload::Get())))
}
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}