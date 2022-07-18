//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "use_var.h"
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
struct Empty {};
void to_leaf()
{
}
/*
   0x0000000000405098 <+0>:	push   %rbp
   0x0000000000405099 <+1>:	mov    %rsp,%rbp
   0x000000000040509c <+4>:	sub    $0x70,%rsp
   0x00000000004050a0 <+8>:	callq  0x405092 <to_leaf()>
=> 0x00000000004050a5 <+13>:	leaveq
   0x00000000004050a6 <+14>:	retq
 */
void test() {
  Empty arr[100]{};
  to_leaf();
}
/*
   0x00000000004050a7 <+0>:	push   %rbp
   0x00000000004050a8 <+1>:	mov    %rsp,%rbp
   0x00000000004050ab <+4>:	sub    $0x70,%rsp
   0x00000000004050af <+8>:	callq  0x405092 <to_leaf()>
=> 0x00000000004050b4 <+13>:	leaveq
   0x00000000004050b5 <+14>:	retq
 */
void test_1() {
  Empty arr[112]{};
  to_leaf();
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();

  LOG_DEBUG(sizeof(Empty))
  test();
  test_1();
  return iRet;
}