//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

/*
 [1]    [warning]    [Parent	N10TestTypeID8ClassDef6ParentE	13888289143273616310]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:37    void printTypeIdInfo()]     [2021-04-08 19:46:46.200666]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [2]    [warning]    [Child	N10TestTypeID8ClassDef5ChildE	281579981607273881]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:38    void printTypeIdInfo()]     [2021-04-08 19:46:46.200714]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [3]    [warning]    [const Parent	N10TestTypeID8ClassDef6ParentE	13888289143273616310]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:40    void printTypeIdInfo()]     [2021-04-08 19:46:46.200791]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [4]    [warning]    [const Child	N10TestTypeID8ClassDef5ChildE	281579981607273881]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:41    void printTypeIdInfo()]     [2021-04-08 19:46:46.200802]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [5]    [warning]    [const Parent &	N10TestTypeID8ClassDef6ParentE	13888289143273616310]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:43    void printTypeIdInfo()]     [2021-04-08 19:46:46.200807]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [6]    [warning]    [const Child &	N10TestTypeID8ClassDef5ChildE	281579981607273881]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:44    void printTypeIdInfo()]     [2021-04-08 19:46:46.200812]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [7]    [warning]    [const Parent &&	N10TestTypeID8ClassDef6ParentE	13888289143273616310]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:46    void printTypeIdInfo()]     [2021-04-08 19:46:46.200820]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [8]    [warning]    [const Child &&	N10TestTypeID8ClassDef5ChildE	281579981607273881]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:47    void printTypeIdInfo()]     [2021-04-08 19:46:46.200832]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [9]    [warning]    [Parent *	PN10TestTypeID8ClassDef6ParentE	6222248450804906692]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:49    void printTypeIdInfo()]     [2021-04-08 19:46:46.200843]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [10]    [warning]    [Child *	PN10TestTypeID8ClassDef5ChildE	15623637030535351372]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:50    void printTypeIdInfo()]     [2021-04-08 19:46:46.200852]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [11]    [warning]    [const Parent *	PKN10TestTypeID8ClassDef6ParentE	402975985570091798]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:52    void printTypeIdInfo()]     [2021-04-08 19:46:46.200861]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [12]    [warning]    [const Child *	PKN10TestTypeID8ClassDef5ChildE	8521000854627404144]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:53    void printTypeIdInfo()]     [2021-04-08 19:46:46.200868]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [13]    [warning]    [Parent const *	PKN10TestTypeID8ClassDef6ParentE	402975985570091798]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:54    void printTypeIdInfo()]     [2021-04-08 19:46:46.200873]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [14]    [warning]    [Child const *	PKN10TestTypeID8ClassDef5ChildE	8521000854627404144]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:55    void printTypeIdInfo()]     [2021-04-08 19:46:46.200904]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [15]    [warning]    [Parent *const	PN10TestTypeID8ClassDef6ParentE	6222248450804906692]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:57    void printTypeIdInfo()]     [2021-04-08 19:46:46.200914]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [16]    [warning]    [Child *const	PN10TestTypeID8ClassDef5ChildE	15623637030535351372]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:58    void printTypeIdInfo()]     [2021-04-08 19:46:46.200919]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [17]    [warning]    [const Parent *const	PKN10TestTypeID8ClassDef6ParentE	402975985570091798]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:60    void printTypeIdInfo()]     [2021-04-08 19:46:46.200925]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]
 [18]    [warning]    [const Child *const	PKN10TestTypeID8ClassDef5ChildE	8521000854627404144]   [/data/root/cpp_study/src/cpp_language/typeid/main.cpp:61    void printTypeIdInfo()]     [2021-04-08 19:46:46.200931]    [0x00002841]    [0x00007f3144fa3840]    [MySink1]

 */
/*
typeid 返回中:
Parent, const Parent,  const Parent &, const Parent && 全部一样, 会退化掉各种修饰 -> N10TestTypeID8ClassDef6ParentE
 (const Parent *, Parent const *) , const Parent *const 一样, 都是个指针(P), 且指针不可变(const*, PK), 会忽略掉执行对象的可变性 -> PKN10TestTypeID8ClassDef6ParentE
 Parent *, Parent *const 一样,都是个指针(P), 指针可变(*, P), 会忽略掉执行对象的可变性 -> PN10TestTypeID8ClassDef6ParentE
 总结: 首先退化掉class 对象的各种const限定
 然后就有三种类型: 原始对象, 指针对象, const指针对象(指针不可变, 指向的对象不管)
 当然, 二级指针, 三级指针也是类似的
*/
namespace TestTypeID {
namespace ClassDef {

class Parent {
  virtual ~Parent() = default;
  virtual std::string Hello() { return "hello from parent"; }
  virtual void CopyFrom(const Parent *const obj) {}
};
class Child {
  virtual std::string Hello() { return "hello from Child"; }
  virtual void CopyFrom(const Parent *const obj) {}
};
}  // namespace ClassDef
}  // namespace TestTypeID
using namespace TestTypeID::ClassDef;
inline static void printTypeIdInfo(){
#define PRINT_TYPE(type)                                   \
  LOG_WARNING(#type << "\t" << typeid(type).name() << "\t" \
                    << typeid(type).hash_code())
    //
    PRINT_TYPE(Parent)
    PRINT_TYPE(Child)
    //
    PRINT_TYPE(const Parent)
    PRINT_TYPE(const Child)
    //
    PRINT_TYPE(const Parent &)
    PRINT_TYPE(const Child &)
    //
    PRINT_TYPE(const Parent &&)
    PRINT_TYPE(const Child &&)
    //
    PRINT_TYPE(Parent *)
    PRINT_TYPE(Child *)
    // 下面这两组等价
    PRINT_TYPE(const Parent *)
    PRINT_TYPE(const Child *)
    PRINT_TYPE(Parent const *)
    PRINT_TYPE(Child const *)
    // this 指针就是这种类型
    PRINT_TYPE(Parent *const)
    PRINT_TYPE(Child *const)
    //
    PRINT_TYPE(const Parent *const)
    PRINT_TYPE(const Child *const)}

//
TEST(test_test, 1) {
  ASSERT_EQ(0, 0);

  printTypeIdInfo();
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}