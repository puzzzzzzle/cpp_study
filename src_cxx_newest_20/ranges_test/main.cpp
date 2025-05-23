
#include <algorithm>
#include <ranges>

#include "common_includes.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
TEST(simple_test, 1) {
  std::vector<int> vec = {5, 2, 3, 4, 1, 7};
  LOG_DEBUG(vec);
  auto vec1 = vec;
  LOG_DEBUG(vec1);
  std::ranges::sort(vec1);
  LOG_DEBUG(vec1);

  auto vec2 = vec;
  std::sort(vec2.begin(), vec2.end());
  LOG_DEBUG(vec2);
}
TEST(simple_test, 2) {
  // views::iota 只是 ranges::iota_view 的一个包装
  // xxx_view 是最终实现的类, view中只是一个CPO包装
  //  std::views::iota(1,100);
  auto view = std::ranges::iota_view(1, 10) |
              std::views::transform([](int i) { return i * i; }) |
              std::views::filter([](int i) { return i % 2 == 0; });
  //  auto vec = view | std::ranges::to<std::vector>();  // c++23
  auto vec = std::vector<int>(view.begin(), view.end());
  LOG_DEBUG(vec)
}

TEST(simple_test, 3) {
  // 注意: transform 的结果用于filter时并不会被保存
  // !!! 每次 filter 需要检查元素时, 都会重新计算前面的变换操作 !!!

  // 这意味着如果一个元素通过filter, 那么它对应的transform会被执行 filter
  // 数量+1次

  // eg: 对于 6,transform 打印 "transformd: 6",结果是 36,通过第一个 filter
  // 和第二个 filter,被 for_each 打印 "+++ get 36". 总共访问3次,

  // 所以 transform 6 会被执行3次, filter 同理,次数递增

  auto result = std::ranges::iota_view(1, 10) |
                std::views::transform([](int i) {
                  STD_LINE("transformd: " << i);
                  return i * i;
                }) |
                std::views::filter([](int i) { return i % 2 == 0; }) |
                std::views::filter([](int i) { return i % 3 == 0; });

  // foreach 执行时才会求值
  STD_LINE("start for_each");
  std::ranges::for_each(result, [](int n) { STD_LINE("+++ get " << n) });
}
TEST(simple_test, 4) {
  // 每次filter, 都是从头开始求值的...
  auto result = std::ranges::iota_view(1, 10) |
                std::views::transform([](int i) {
                  LOG_DEBUG("transformd: " << i);
                  return i * i;
                }) |
                std::views::filter([](int i) { return i % 2 == 0; }) |
                std::views::transform([](int i) {
                  LOG_DEBUG("transformd 2: " << i);
                  return -i;
                }) |
                std::views::filter([](int i) { return i % 3 == 0; });

  // foreach 执行时才会求值
  LOG_DEBUG("start for_each");
  std::ranges::for_each(result, [](int n) { LOG_DEBUG("+++ get " << n) });
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}