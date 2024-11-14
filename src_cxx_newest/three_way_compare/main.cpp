//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

[[deprecated("foo has beed deprecated")]]
void test_foo()
{

}
struct ComparableClass {
  int i_{};
  int j_{};
  std::weak_ordering operator<=>(const ComparableClass &rhs) const {
    return std::tie(i_, j_) <=> std::tie(rhs.i_, rhs.j_);
  }
  bool operator==(const ComparableClass &rhs) const {
    return std::tie(i_, j_) == std::tie(rhs.i_, rhs.j_);
  }
};

TEST(test_test, 1) {
  LOG_DEBUG("test three way compare ")
  ComparableClass t1{1, 1};
  ComparableClass t2{1, 0};
  ASSERT_TRUE(t1 != t2);
  ASSERT_TRUE(t1 > t2);
  ASSERT_FALSE(t1 < t2);
}
struct MyKey {
  int  id;
  std::string name;

  // 实现三路比较运算符
  std::weak_ordering operator<=>(const MyKey& other) const {
    // 首先比较 id (equivalent 等价于0)
    if (auto cmp = id <=> other.id; cmp != std::weak_ordering::equivalent) {
      return cmp;
    }
    // 如果 id 相等，则比较 name
    return name <=> other.name;
  }
};

int main(int argc, char **argv) {
  int iRet = 0;
  test_foo();

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}