#include "common_includes.h"
#include "stdarg.h"
namespace test_1 {
void print_va_arg(const char *first, ...) {
  LOG_DEBUG(" -- start va arg print :")

  const char *v = first;
  int cnt{};

  va_list arg_ptr;
  va_start(arg_ptr, first);
  while (v != nullptr) {
    LOG_DEBUG("arg at " << cnt << "\t:\t" << v)
    ++cnt;
    v = va_arg(arg_ptr, const char *);
  }
  va_end(arg_ptr);
}
TEST(test_test, 1) {
  print_va_arg(nullptr);
  print_va_arg("hello", nullptr);
  print_va_arg("hello", "world", nullptr);
}
}  // namespace test_1

namespace test_2 {
void print_va_arg(const char *first, ...) {
  LOG_DEBUG(" -- start va arg print :")
  const char *v = first;
  int cnt{};

  va_list arg_ptr;
  va_start(arg_ptr, first);
  while (strcmp(v, "") != 0) {
    LOG_DEBUG("arg at " << cnt << "\t:\t" << v)
    ++cnt;
    v = va_arg(arg_ptr, const char *);
  }
  va_end(arg_ptr);
}
TEST(test_test, 2) {
  print_va_arg("");
  print_va_arg("hello", "");
  print_va_arg("hello", "world", "");
}
}  // namespace test_2

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}