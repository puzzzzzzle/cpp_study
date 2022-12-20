#include <cstdio>

#include "class2_define.h"
class Class1 {
  public:
  void fun() { printf("main::Class1\n"); }
};
void test();
/**
 * 输出:
 *
main start
main::Class1
Class2
test start
main::Class1
Class2

 分析:
 同一个类, 无论是通过头文件定义, 还是重复定义, 只要在不同的翻译单元中, 就会独立翻译
 编译.o的时候是独立的, 也无法知道其他的.o的情况

 所以main.cpp.o 和 test.cpp.o 中, 对class1 class2 的fun, 有独立的两套编译结果
 这时候是不一样的

 但是, 等到链接的时候, 相同符号的函数, 只会保留一个, 所以在最终的可执行文件中 ,就都只有一个了

 test.cpp 中定义的字符串, 虽然没被用到, 但是在最终的可执行文件中, 还有保留
 注意: 任何 cpp中的.data/.rodata/.bss不会被裁减, 都会保留
 * @return
 */
int main() {
  printf("main start \n");
  Class1 c1{};
  c1.fun();
  Class2 c2{};
  c2.fun();
  test();
}