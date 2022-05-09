//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "concepts"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
struct Test {
  int _i{};
  double _d{};
};

// 概念的基本定义
template <typename T>
concept Hashable = requires(T a) {
                     { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
                   };
static_assert(Hashable<int>);
static_assert(Hashable<std::string>);
static_assert(!Hashable<Test>);

template <typename T>
concept AddConcept = requires(T a) { a + a; };

template <typename T>
  requires requires(T a) { std::is_same_v<decltype(a - a), T>; }
T sub(const T &a) {
  return a - a;
}
template <typename T>
  requires requires(T a) {
             { a - a } -> std::same_as<T>;
           }
T sub1(const T &a) {
  return a - a;
}
TEST(concept_test, 1) {
  sub(1);
  sub1(1);
  int i = 1;
  sub(i);
  sub1(i);
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