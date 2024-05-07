//
// Created by user on 5/7/24.
//
#include "common_includes.h"
namespace TemplateConstVarTest {
template <class T, T v>
struct intellij_constant {
  static constexpr T value = v;
};
intellij_constant<int, 5> FIVE;

TEST(TemplateConstVarTest, 1) { LOG_DEBUG(FIVE.value) }
}  // namespace TemplateConstVarTest
