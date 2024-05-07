//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

/**
 * 拷贝参数
 */
namespace copy_lRef {
class Funcs {
  public:
  void IntParaFunc(int func) { LOG_DEBUG("int i_func " << func) }
  void IntParaFunc(int &func) { LOG_DEBUG("int &i_func " << func) }
  //    void IntParaFunc(int &&func) { LOG_DEBUG("int &&func " << func) }
};
}  // namespace copy_lRef

namespace copy_rRef {
class Funcs {
  public:
  void IntParaFunc(int func) { LOG_DEBUG("int i_func " << func) }
  //    void IntParaFunc(int &func) { LOG_DEBUG("int &func " << func) }
  void IntParaFunc(int &&func) { LOG_DEBUG("int &&i_func " << func) }
};
}  // namespace copy_rRef

namespace lRef_rRef {
class Funcs {
  public:
  //    void IntParaFunc(int func) { LOG_DEBUG("int func " << func) }
  void IntParaFunc(int &func) { LOG_DEBUG("int &i_func " << func) }
  void IntParaFunc(int &&func) { LOG_DEBUG("int &&i_func " << func) }
};
}  // namespace lRef_rRef

/**
 * 传递立即数,实际上是右值引用,没有改函数时退化为拷贝,且只能为拷贝,所以不冲突
 * 但是传递变量名时,既可以理解为拷贝,也可以理解为引用,冲突
 */
TEST(reference, copy_lRef) {
  copy_lRef::Funcs funcs;
  //    funcs.IntParaFunc(1);       //int func 1
  int i = 2;
  //    funcs.IntParaFunc(i);     // err
  int &j = i;  //调用时退化为普通变量(有名字了)
  //    funcs.IntParaFunc(j);     // err
  int &&k = 3;  //调用时退化为普通变量(有名字了)
  //    funcs.IntParaFunc(k);      // err
  funcs.IntParaFunc(std::move(4));  // int func 4
}

/**
 * 传递立即数或右值引用时,既可以理解为零时变量,然后拷贝,也可以理解为真的右值调用,冲突
 * 传递变量时,无论什么引用,只要有了名字,那么它在参数中只能被逻辑为普通的变量
 */
TEST(reference, copy_rRef) {
  copy_rRef::Funcs funcs;
  //    funcs.IntParaFunc(1);// err
  int i = 2;
  funcs.IntParaFunc(i);  // int func 2
  int &j = i;            //调用时退化为普通变量(有名字了)
  funcs.IntParaFunc(j);  // int func 2
  int &&k = 3;           //调用时退化为普通变量(有名字了)
  funcs.IntParaFunc(k);  // int func 3
                         //    funcs.IntParaFunc(std::move(4)); // err
}
/**
 * 左值引用和右值引用完全不冲突
 * 只有真的没有名字,或者使用std::move强制取消名字,才会匹配为右值引用函数
 * 在右值引用的调用中,优先找右值引用函数,找不到退化为一次临时变量拷贝
 */
TEST(ref_rRef, lRef_rRef) {
  lRef_rRef::Funcs funcs;
  funcs.IntParaFunc(1);  // int &&func 1
  int i = 2;
  funcs.IntParaFunc(i);  // int &func 2
  int &j = i;            //调用时退化为普通变量(有名字了)
  funcs.IntParaFunc(j);  // int &func 2
  int &&k = 3;           //调用时退化为普通变量(有名字了)
  funcs.IntParaFunc(k);  // int &func 2
  funcs.IntParaFunc(std::move(4));  // int &&func 4
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}