#include "common_includes.h"
#include "has_member.h"

bool call_flag{false};

struct myStruct {
  private:
  int val{};

  public:
  void foo() { call_flag = true; }
  int get_val() {
    call_flag = true;
    return val;
  }
  int set_val(int t) {
    call_flag = true;
    val = t;
    return val;
  }
  int set_val(int t, int) {
    call_flag = true;
    val = t;
    return val;
  }
  void set_long(long t) {
    call_flag = true;
    val = t;
  }
};

struct another {
  public:
  void test() { call_flag = true; }
  void set_long(int t) {
    call_flag = true;
    val = t;
  }

  public:
  int val{};
};
HAS_MEMBER_VARIABLE_BASE(val)

HAS_MEMBER_CALL_VOID(_, foo, void)
HAS_MEMBER_CALL_VOID(_, get_val, int)

HAS_MEMBER_CALL(_1int, set_val, int, int)

// HAS_MEMBER_CALL(_2int, set_val, int, int, int) // error
HAS_MEMBER_FUNC(_2int, set_val, int, int)
// 多个参数的需要手动实现下调用器
template <typename T>
using _HasMember_set_val_1int = _HasMemberS_set_val_1int<T, int>;
template <typename T>
typename std::enable_if<_HasMember_set_val_1int<T>::value, int>::type
CALL_set_val_2int(T& para, int arg1, int arg2) {
  return para.set_val(arg1, arg2);
}
template <typename T>
typename std::enable_if<!_HasMember_set_val_1int<T>::value, int>::type
CALL_set_val_2int(T& para, int arg1, int arg2) {
  return {};
}
template <typename T>
typename std::enable_if<_HasMember_set_val_1int<T>::value, void>::type
CALL_set_val_2int_no_return(T& para, int arg1, int arg2) {
  para.set_val(arg1, arg2);
}
template <typename T>
typename std::enable_if<!_HasMember_set_val_1int<T>::value, void>::type
CALL_set_val_2int_no_return(T& para, int arg1, int arg2) {}

HAS_MEMBER_CALL(_, set_long, void, long)

HAS_MEMBER_CALL_VOID(_, test, void)

TEST(test, 1) {
#define STATIC_ASSERT_MGS(cond) static_assert((cond), #cond)

  // 编译期检测函数是否存在
  STATIC_ASSERT_MGS((_HasMember_foo_<myStruct>::value));
  STATIC_ASSERT_MGS((!_HasMember_foo_<another>::value));

  STATIC_ASSERT_MGS((_HasMember_set_val_1int<myStruct>::value));
  STATIC_ASSERT_MGS((!_HasMember_set_val_1int<another>::value));

  STATIC_ASSERT_MGS((_HasMember_set_val_2int<myStruct>::value));
  STATIC_ASSERT_MGS((!_HasMember_set_val_2int<another>::value));

  STATIC_ASSERT_MGS((_HasMember_get_val_<myStruct>::value));
  STATIC_ASSERT_MGS((!_HasMember_get_val_<another>::value));

  STATIC_ASSERT_MGS((_HasMember_set_long_<myStruct>::value));
  STATIC_ASSERT_MGS((_HasMember_set_long_<another>::value));

  STATIC_ASSERT_MGS((!_HasMember_test_<myStruct>::value));
  STATIC_ASSERT_MGS((_HasMember_test_<another>::value));

  STATIC_ASSERT_MGS((_HasMember_get_val_<myStruct>::value));
  STATIC_ASSERT_MGS((!_HasMember_get_val_<another>::value));
  // 如果存在就调用
  myStruct m{};
  another a{};
#define TEST_CALL(obj, func, called) \
  call_flag = false;                 \
  func(obj);                         \
  ASSERT_EQ(call_flag, called);

  TEST_CALL(m, CALL_foo_, true)  // not suggested
  TEST_CALL(m, CALL_foo__no_return, true)
  //  TEST_CALL(a, CALL_foo_, false) // compile error
  TEST_CALL(a, CALL_foo__no_return, false)

#define TEST_CALL_ARGS(obj, func, called, args...) \
  call_flag = false;                               \
  func(obj, args);                                 \
  ASSERT_EQ(call_flag, called);

  TEST_CALL_ARGS(m, CALL_set_val_1int, true, 42)            // m = 42
  TEST_CALL_ARGS(m, CALL_set_val_1int_no_return, true, 43)  // m = 43
  TEST_CALL_ARGS(a, CALL_set_val_1int, false, 44)
  TEST_CALL_ARGS(a, CALL_set_val_1int_no_return, false, 45)

  // 多个参数
  TEST_CALL_ARGS(m, CALL_set_val_2int, true, 46, -100)            // m = 46
  TEST_CALL_ARGS(m, CALL_set_val_2int_no_return, true, 47, -100)  // m = 47
  TEST_CALL_ARGS(a, CALL_set_val_2int, false, 44, -100)
  TEST_CALL_ARGS(a, CALL_set_val_2int_no_return, false, 45, -100)

#define TEST_CALL_RET(obj, func, called, ret) \
  call_flag = false;                          \
  {                                           \
    auto r = func(obj);                       \
    ASSERT_EQ(r, ret);                        \
  }                                           \
  ASSERT_EQ(call_flag, called);
  TEST_CALL_RET(m, CALL_get_val_, true, 47)
  //  TEST_CALL_RET(m, CALL_get_val__no_return, true, 47)// compile error
  TEST_CALL_RET(a, CALL_get_val_, false, 0)
  //  TEST_CALL_RET(a, CALL_get_val__no_return, false, 0)// compile error
}
int main(int argc, char** argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}