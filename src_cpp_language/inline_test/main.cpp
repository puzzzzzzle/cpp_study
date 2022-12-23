//
// Created by tao on 19-1-17.
//
#include <cstdio>

#if true
#define print_i printf("%d", i);
#else
#define print_i
#endif
#define BODY() \
  int i = 0;   \
  i += 10;     \
  print_i

void no_inline_func() { BODY() }
inline void inline_func() { BODY() }
class Holder {
  public:
  void no_inline_class_func() { BODY() }
  inline void inline_class_func() { BODY() }
  template <class T>
  void template_no_inline_class_func() {
    BODY()
  }
  template <class T>
  inline void template_inline_class_func() {
    BODY()
  }
};
int main(int argc, char **argv) {
  no_inline_func();
  inline_func();
  Holder h{};
  h.no_inline_class_func();
  h.inline_class_func();
  h.template_no_inline_class_func<int>();
  h.template_inline_class_func<int>();

  return 0;
}