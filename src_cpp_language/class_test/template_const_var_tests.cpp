//
// Created by user on 5/7/24.
//
#include "common_includes.h"
namespace TemplateConstVarTest {
// constexpr 可以在编译期求值, 相当于常数
template <class T, T v>
struct intellij_constant {
  static constexpr T value = v;
};
intellij_constant<int, 5> FIVE;

// 非 constexpr 要在外部初始化
template <class T, T v>
struct intellij_constant_old {
  static T value;
};
template <class T, T v>
T intellij_constant_old<T, v>::value = v;
intellij_constant_old<int, 6> SIX;

//template <class T, T v>
//struct intellij_constant_err {
//  static T value = v;
//};
//intellij_constant_err<int, 8> EIGHT;


TEST(TemplateConstVarTest, 1) {
  LOG_DEBUG(FIVE.value);
  LOG_DEBUG(SIX.value);
}
}  // namespace TemplateConstVarTest
