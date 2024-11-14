#include <cmath>
#include <csignal>

#include "common_includes.h"

TEST(double, 1) {
  double a = 3.14;
  double b = 0;
  double c = a / b;
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isinf(c));

  c = -a / b;
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isinf(c));

  c = std::sqrt(-3.14);
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isnan(c));

  c = 0.0 / 0;
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isnan(c));

  c = 0 / 0.0;
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isnan(c));
}
TEST(double, ordering) {
  double c = std::sqrt(-3.14);
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isnan(c));

  // 全部返回false, 不可比较, 类似 std::partial_ordering::unordered
  // 这意味着, float 作为key, 存在nan时, 会导致map crash, 因为不可比
  ASSERT_FALSE((c > 3.14));
  ASSERT_FALSE((c >= 3.14));
  ASSERT_FALSE((c == 3.14));
  ASSERT_FALSE((c <= 3.14));
  ASSERT_FALSE((c < 3.14));

  c = 3.14 / 0;
  LOG_DEBUG(c)
  ASSERT_TRUE(std::isinf(c));

  ASSERT_TRUE((c > 3.14));
  ASSERT_TRUE((c >= 3.14));
  ASSERT_FALSE((c == 3.14));
  ASSERT_FALSE((c <= 3.14));
  ASSERT_FALSE((c < 3.14));
  // 任何inf, 只要正负号相同, 那就相同
  ASSERT_TRUE((c == c));
  ASSERT_TRUE((c == 2.2/0));
  ASSERT_FALSE((c == -2.2/0));
  ASSERT_TRUE((-c == -2.2/0));

}

// 会报signal, crash
void int_divide_zero(int arg) {
  int i;
  i = 666 / 0;
  LOG_DEBUG(i)
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}