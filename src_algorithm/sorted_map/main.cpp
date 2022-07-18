//
// Created by tao on 19-1-17.
//
#include "SortedMap.h"
#include "common_includes.h"
struct Payload {
  int key{};
  int v1{};
  int v2{};
  Payload() = default;
  static Payload Rand(int max = 1000) {
    Payload p{};
    p.key = rand() % max;
    p.v1 = rand() % max;
    p.v2 = rand() % max;
    return p;
  }
  std::string ToString() const {
    std::ostringstream oss{};
    oss << "key:" << key << "\tv1:" << v1 << "\tv2:" << v2;
    return oss.str();
  }
};
using MapT = std::map<int, Payload>;
struct SortedComparePayload {
  bool operator()(const MapT::const_iterator &lhs,
                  const MapT::const_iterator &rhs) {
    return std::tie(rhs->second.v1, rhs->second.v2) <
           std::tie(lhs->second.v1, lhs->second.v2);
  }
};
using SortedMapT = SortedMap<MapT, SortedComparePayload>;
TEST(test_test, 1) {
  SortedMapT map{};
  for (int k = 0; k < 5; ++k) {
    for (int i = 0; i < 10; ++i) {
      auto p = Payload::Rand();
      map.MutableData()[p.key] = p;
    }
    LOG_DEBUG("===================")
    for (const auto &item : map.Data()) {
      LOG_DEBUG("map : " << item.second.ToString())
    }
    for (const auto &item : map.Sorted()) {
      LOG_DEBUG("sorted: " << item->second.ToString())
    }
    LOG_DEBUG("===================")
  }
  auto map1 = map;
  for (const auto &item : map1.Sorted()) {
    LOG_DEBUG("sorted: " << item->second.ToString())
  }
}

template <typename Vec1, typename Vec2,
          typename CompareItem = std::equal_to<typename Vec1::value_type>>
bool VecLikeSame(const Vec1 &v1, const Vec2 &v2) {
  CompareItem comp{};
  if (v1.size() != v2.size()) {
    return false;
  }
  auto v1It = v1.cbegin();
  auto v2It = v2.cbegin();
  for (; v1It != v1.cend() && v2It != v2.cend(); ++v1It, ++v2It) {
    if (!comp(*v1It, *v2It)) {
      return false;
    }
  }
  return true;
}
TEST(vec_same, 1) {
  std::vector<int> v1{1, 2, 5, 6};
  std::vector<int> v2{1, 2, 5, 6};
  std::vector<int> v3{1, 2, 5, 7};
  std::vector<int> v4{1, 2, 5, 7, 8};
  ASSERT_TRUE(VecLikeSame(v1, v2));
  ASSERT_TRUE(VecLikeSame(v1, v1));
  ASSERT_FALSE(VecLikeSame(v1, v3));
  ASSERT_FALSE(VecLikeSame(v4, v3));
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}