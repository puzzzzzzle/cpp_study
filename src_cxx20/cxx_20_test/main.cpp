//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

/**
 * if constexpr 可以用来替代 SFINAE (substitution is not an error) 做动态绑定
 * 以前需要一堆enable_if 来实现的能力, 现在只需要几行很符合直觉的就可以了
 * @tparam T
 * @param i
 * @return
 */
template <typename T>
auto get_i(const T &i) {
  if constexpr (std::is_integral_v<T>) {
    return i;
  } else if constexpr (std::is_floating_point_v<T>) {
    return i;
  } else if constexpr (std::is_same_v<char *, std::decay_t<T>>) {
    return std::strlen(i);
  } else if constexpr (std::is_same_v<std::string, std::decay_t<T>>) {
    return i.length();
  } else {
    throw std::runtime_error(std::string("unknown type ") + typeid(i).name());
  }
}

TEST(if_constexpr, 1) {
  using namespace std::string_literals;

  LOG_DEBUG(get_i(0))
  // 甚至可以有不同的返回值
  LOG_DEBUG(get_i(4.2))
  // 用用户定义字面量 (后缀表达式) 强制转换成 std::string
  LOG_DEBUG(get_i("sdfadfasdf"s))
  LOG_DEBUG(get_i("sdfadfasdf"))
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