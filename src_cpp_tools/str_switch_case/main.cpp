#include <mutex>

#include "common_includes.h"
void func_a(int value) { LOG_DEBUG("func a called " << value) }
void func_b(int value) { LOG_DEBUG("func b called " << value) }

namespace MapFunc {
// 可以结合运行时反射, 自动构造map
using MapFuncT = std::unordered_map<std::string, std::function<void(int)>>;
const MapFuncT& get_map_func() {
  static MapFuncT funcs{};
  static std::once_flag once{};
  std::call_once(once, []() {
    funcs["func_a"] = func_a;
    funcs["func_b"] = func_b;
  });
  return funcs;
}

void call_func(const std::string& name, int value) {
  const auto& funcs = get_map_func();
  auto it = funcs.find(name);
  if (it != funcs.end()) {
    it->second(value);
  } else {
    LOG_DEBUG("func not found " << name)
  }
}
TEST(map_func, 1) {
  call_func("func_a", 111);
  call_func("func_b", 22);
  call_func("func_c", 444);
}
}  // namespace MapFunc

namespace ArrayFind {
// __all 一定需要有序
static const std::array<std::string, 2> __all = {"func_a", "func_b"};

void call_func(const std::string& name, int value) {
  auto r = equal_range(__all.begin(), __all.end(), name);
  if (r.first == r.second) {
    LOG_DEBUG("func not found " << name)
    return;
  }
  // std::distance 更正确, 但是好像要遍历, 这里是字符串数组, 可以简单的-迭代器
  // std::array 的迭代器, 就是 value*, 因此, r.first __all.begin() 都是 string*
  //  switch (std::distance(__all.begin(), r.first))
  switch (r.first - __all.begin()) {
    case 0: {
      func_a(value);
      return;
    }
    case 1: {
      func_b(value);
    }
  }
}

TEST(array_func, 1) {
  call_func("func_a", 111);
  call_func("func_b", 22);
  call_func("func_c", 444);
}
}  // namespace ArrayFind

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}