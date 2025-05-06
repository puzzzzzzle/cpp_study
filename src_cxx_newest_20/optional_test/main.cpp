#include <optional>

#include "common_includes.h"

std::optional<int> get_val_over_10(int val) {
  if (val > 10) {
    return val;
  } else {
    return std::nullopt;
  }
}
TEST(test_test, 1) {
  ASSERT_EQ(get_val_over_10(5),std::nullopt);
  ASSERT_EQ(get_val_over_10(5).has_value(), false);

  ASSERT_EQ(get_val_over_10(20).value(),20);
  ASSERT_EQ(get_val_over_10(5).has_value(), true);

  LOG_DEBUG(" " << get_val_over_10(20).value())

}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}