//
// Created by user on 5/7/24.
//
#include "boost/format.hpp"
#include "common_includes.h"

namespace ClassInitTests {
// 类对象初始化测试
class TestFieldNameClass {
  public:
  TestFieldNameClass() { LOG_DEBUG("init test class " << (size_t)this); }
  int value;
  int i_value{};
  void print() const {
    LOG_DEBUG(boost::format("value %d  i_value  %d\n") % value % i_value);
  }
};
TestFieldNameClass g_val;  // 全局默认初始化, 在main函数前初始化,
                           // 即使没有声明要初始化的变量value也会被置为默认值
TestFieldNameClass g_i_val{};  // 全局默认初始化
// static 全局变量只能在本文件中访问 , 初始化上没区别 , 只是为了格式统一
static TestFieldNameClass g_s_val;      // 全局默认初始化
static TestFieldNameClass g_s_i_val{};  // 全局默认初始化

void testFunc() {
  printf("==== start i_func \n");

  int a;                     // 局部基础变量不会初始化
  int i_a{};                 // 局部变量调用默认初始化函数初始化
  TestFieldNameClass l_val;  // 类变量总是初始化, i_value 会被初始化, 但是 value
                             // 不会, 因为不在构造函数初始化表中
  TestFieldNameClass l_i_val{};  // 类变量初始化
  static TestFieldNameClass
      l_s_val;  // 局部静态变量在第一次调用函数时初始化 i_value 和 value
                // 都会初始化,和全局变量的初始化规则类似, 只是时机晚一些
  static TestFieldNameClass
      l_s_i_val{};  // 局部静态变量在第一次调用函数时初始化

#define PRINT_C(name)                                                    \
  LOG_DEBUG(((boost::format("now check [%s]  [%p] ") % #name % &name))); \
  name.print();

  LOG_DEBUG(((boost::format("test int [a : %d]  [i_a : %d]\n") % a % i_a)));

  PRINT_C(g_val)
  PRINT_C(g_i_val)
  PRINT_C(g_s_val)
  PRINT_C(g_s_i_val)
  PRINT_C(l_val)
  PRINT_C(l_i_val)
  PRINT_C(l_s_val)
  PRINT_C(l_s_i_val)
#undef PRINT_C
}
TEST(ClassInitTests, class_init) { testFunc(); }


// struct  初始化测试
struct StructInit {
  // 这种无论是否调初始化函数, 实际都会调&初始化
  // 相当于在构造函数中赋值了
  int v1 = 1;
  double v2 = 3.14;
  std::string v3 = "hello";
  // 这种在栈/堆上没有显示调用初始化函数, 是不会初始化的
  // 但是在全局变量中, 会被初始化为0
  // 相当于在构造函数中没有管
  int uv1;
  double uv2;
  // 这个比较特殊, 目前看到的无论什么情况, 都初始化了
  std::string uv3;
  // 这种类似第一种情况
  int dv1{};
  double dv2{};
  std::string dv3{};
  std::string ToString() const {
    std::ostringstream oss{};
#define TO_STREAM_VAR(name) oss << #name << ":" << name << "; ";
    TO_STREAM_VAR(v1)
    TO_STREAM_VAR(v2)
    TO_STREAM_VAR(v3)
    TO_STREAM_VAR(uv1)
    TO_STREAM_VAR(uv2)
    TO_STREAM_VAR(uv3)
    TO_STREAM_VAR(dv1)
    TO_STREAM_VAR(dv2)
    TO_STREAM_VAR(dv3)
    return oss.str();
  }
};
StructInit g_init{};
void struct_init_test_1() {
  StructInit u1;
  StructInit i1{};
  StructInit s3{.uv3 = "world"};
  StructInit s4{.uv3 = "world",.dv3="sss"};

  //  LOG_DEBUG(g_init.ToString())
  //  LOG_DEBUG(u1.ToString())
  //  LOG_DEBUG(i1.ToString())
  //  LOG_DEBUG(s3.ToString())
}
// 反汇编
/*
StructInit g_init{};
void struct_init_test_1() {
   139a2:	f3 0f 1e fa          	endbr64
   139a6:	55                   	push   %rbp
   139a7:	48 89 e5             	mov    %rsp,%rbp
   139aa:	41 54                	push   %r12
   139ac:	53                   	push   %rbx
   139ad:	48 81 ec d0 01 00 00 	sub    $0x1d0,%rsp
   139b4:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
   139bb:	00 00
   139bd:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
   139c1:	31 c0                	xor    %eax,%eax
  StructInit u1;
   139c3:	48 8d 85 30 fe ff ff 	lea    -0x1d0(%rbp),%rax
   139ca:	48 89 c7             	mov    %rax,%rdi
   139cd:	e8 44 57 00 00       	call   19116 <_ZN10StructInitC1Ev>
  StructInit i1{};
   139d2:	48 8d 95 c0 fe ff ff 	lea    -0x140(%rbp),%rdx
   139d9:	b8 00 00 00 00       	mov    $0x0,%eax
   139de:	b9 12 00 00 00       	mov    $0x12,%ecx
   139e3:	48 89 d7             	mov    %rdx,%rdi
   139e6:	f3 48 ab             	rep stos %rax,%es:(%rdi)
   139e9:	c7 85 c0 fe ff ff 01 	movl   $0x1,-0x140(%rbp)
   139f0:	00 00 00
   139f3:	f2 0f 10 05 65 a8 04 	movsd  0x4a865(%rip),%xmm0        # 5e260 <_ZTSZN17class_type_2_Test8TestBodyEvEUlP13TestTemplateTI6TClassEE_+0x80>
   139fa:	00
   139fb:	f2 0f 11 85 c8 fe ff 	movsd  %xmm0,-0x138(%rbp)
   13a02:	ff
   13a03:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13a0a:	48 89 c7             	mov    %rax,%rdi
   13a0d:	e8 ae a0 ff ff       	call   dac0 <_ZNSaIcEC1Ev@plt>
   13a12:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13a19:	48 8d 95 c0 fe ff ff 	lea    -0x140(%rbp),%rdx
   13a20:	48 8d 4a 10          	lea    0x10(%rdx),%rcx
   13a24:	48 89 c2             	mov    %rax,%rdx
   13a27:	48 8d 05 3f 99 04 00 	lea    0x4993f(%rip),%rax        # 5d36d <_ZN7testingL19kMaxStackTraceDepthE+0x185>
   13a2e:	48 89 c6             	mov    %rax,%rsi
   13a31:	48 89 cf             	mov    %rcx,%rdi
   13a34:	e8 85 51 00 00       	call   18bbe <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_>
   13a39:	48 8d 85 c0 fe ff ff 	lea    -0x140(%rbp),%rax
   13a40:	48 83 c0 40          	add    $0x40,%rax
   13a44:	48 89 c7             	mov    %rax,%rdi
   13a47:	e8 fc 4f 00 00       	call   18a48 <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev>
   13a4c:	48 8d 85 c0 fe ff ff 	lea    -0x140(%rbp),%rax
   13a53:	48 83 c0 70          	add    $0x70,%rax
   13a57:	48 89 c7             	mov    %rax,%rdi
   13a5a:	e8 e9 4f 00 00       	call   18a48 <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev>
   13a5f:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13a66:	48 89 c7             	mov    %rax,%rdi
   13a69:	e8 c2 9a ff ff       	call   d530 <_ZNSaIcED1Ev@plt>
  StructInit s3{.uv3 = "world"};
   13a6e:	48 8d 95 50 ff ff ff 	lea    -0xb0(%rbp),%rdx
   13a75:	b8 00 00 00 00       	mov    $0x0,%eax
   13a7a:	b9 12 00 00 00       	mov    $0x12,%ecx
   13a7f:	48 89 d7             	mov    %rdx,%rdi
   13a82:	f3 48 ab             	rep stos %rax,%es:(%rdi)
   13a85:	c7 85 50 ff ff ff 01 	movl   $0x1,-0xb0(%rbp)
   13a8c:	00 00 00
   13a8f:	f2 0f 10 05 c9 a7 04 	movsd  0x4a7c9(%rip),%xmm0        # 5e260 <_ZTSZN17class_type_2_Test8TestBodyEvEUlP13TestTemplateTI6TClassEE_+0x80>
   13a96:	00
   13a97:	f2 0f 11 85 58 ff ff 	movsd  %xmm0,-0xa8(%rbp)
   13a9e:	ff
   13a9f:	48 8d 85 2e fe ff ff 	lea    -0x1d2(%rbp),%rax
   13aa6:	48 89 c7             	mov    %rax,%rdi
   13aa9:	e8 12 a0 ff ff       	call   dac0 <_ZNSaIcEC1Ev@plt>
   13aae:	48 8d 85 2e fe ff ff 	lea    -0x1d2(%rbp),%rax
   13ab5:	48 8d 95 50 ff ff ff 	lea    -0xb0(%rbp),%rdx
   13abc:	48 8d 4a 10          	lea    0x10(%rdx),%rcx
   13ac0:	48 89 c2             	mov    %rax,%rdx
   13ac3:	48 8d 05 a3 98 04 00 	lea    0x498a3(%rip),%rax        # 5d36d <_ZN7testingL19kMaxStackTraceDepthE+0x185>
   13aca:	48 89 c6             	mov    %rax,%rsi
   13acd:	48 89 cf             	mov    %rcx,%rdi
   13ad0:	e8 e9 50 00 00       	call   18bbe <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_>
   13ad5:	41 bc 01 00 00 00    	mov    $0x1,%r12d
   13adb:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13ae2:	48 89 c7             	mov    %rax,%rdi
   13ae5:	e8 d6 9f ff ff       	call   dac0 <_ZNSaIcEC1Ev@plt>
   13aea:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13af1:	48 8d 95 50 ff ff ff 	lea    -0xb0(%rbp),%rdx
   13af8:	48 8d 4a 40          	lea    0x40(%rdx),%rcx
   13afc:	48 89 c2             	mov    %rax,%rdx
   13aff:	48 8d 05 7c 9a 04 00 	lea    0x49a7c(%rip),%rax        # 5d582 <_ZN7testingL19kMaxStackTraceDepthE+0x39a>
   13b06:	48 89 c6             	mov    %rax,%rsi
   13b09:	48 89 cf             	mov    %rcx,%rdi
   13b0c:	e8 ad 50 00 00       	call   18bbe <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_>
   13b11:	48 8d 85 50 ff ff ff 	lea    -0xb0(%rbp),%rax
   13b18:	48 83 c0 70          	add    $0x70,%rax
   13b1c:	48 89 c7             	mov    %rax,%rdi
   13b1f:	e8 24 4f 00 00       	call   18a48 <_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev>
   13b24:	48 8d 85 2f fe ff ff 	lea    -0x1d1(%rbp),%rax
   13b2b:	48 89 c7             	mov    %rax,%rdi
   13b2e:	e8 fd 99 ff ff       	call   d530 <_ZNSaIcED1Ev@plt>
   13b33:	48 8d 85 2e fe ff ff 	lea    -0x1d2(%rbp),%rax
   13b3a:	48 89 c7             	mov    %rax,%rdi
   13b3d:	e8 ee 99 ff ff       	call   d530 <_ZNSaIcED1Ev@plt>

//  LOG_DEBUG(g_init.ToString())
//  LOG_DEBUG(u1.ToString())
//  LOG_DEBUG(i1.ToString())
//  LOG_DEBUG(s3.ToString())
}
 */
TEST(ClassInitTests, struct_init) { struct_init_test_1(); }
}  // namespace ClassInitTests