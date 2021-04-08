//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

/*
 w_ptr :
 *w_ptr :
 this :  SvrAOIObjectInnerData *const 会翻译为
 PN8BigWorld21SvrAOIObjectInnerDataE , 指针不可变, 内容可变 obj : const
 SvrAOIObjectInnerData *const 会翻译为 PKN8BigWorld21SvrAOIObjectInnerDataE ,
 指针不可变, 内容不可变 *this : SvrAOIObjectInnerData & :
 SvrAOIObjectInnerData 会翻译为 N8BigWorld22ArmyAOIObjectInnerDataE *obj :
 const SvrAOIObjectInnerData & : const SvrAOIObjectInnerData 会翻译为
 N8BigWorld22ArmyAOIObjectInnerDataE
*/
//
// class Parent {
//  virtual ~Parent() = default;
//  virtual std::string Hello() { return "hello from parent"; }
//  virtual void CopyFrom(const Parent * const obj){
//
//  }
//};
// class Child {
//  virtual std::string Hello() { return "hello from Child"; }
//  virtual void CopyFrom(const Parent * const obj){
//
//  }
//};
// inline static void printTypeIdInfo() {
//#define PRINT_TYPE(type)                                       \
//  LOG_DEBUG(#type << "\t" << typeid(type).name() << "\t" \
//                    << typeid(type).hash_code())
//    //
//  PRINT_TYPE(Parent)
//  PRINT_TYPE(Child)
//  //
//  PRINT_TYPE(const Parent)
//  PRINT_TYPE(const Child)
//  //
//  PRINT_TYPE(const Parent&)
//  PRINT_TYPE(const Child&)
//  //
//  PRINT_TYPE(const Parent&&)
//  PRINT_TYPE(const Child&&)
//    //
//  PRINT_TYPE(Parent*)
//  PRINT_TYPE(Child*)
//    // 下面这两组等价
//  PRINT_TYPE(const Parent*)
//  PRINT_TYPE(const Child*)
//  PRINT_TYPE( Parent const*)
//  PRINT_TYPE( Child const*)
//    //this 指针就是这种类型
//  PRINT_TYPE(Parent * const)
//  PRINT_TYPE(Child * const)
//    //
//  PRINT_TYPE(const Parent * const)
//  PRINT_TYPE(const Child * const)
//}
TEST(test_test, 1) {
  ASSERT_EQ(0, 0);
  //  printTypeIdInfo();
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