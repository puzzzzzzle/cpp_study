//
// Created by tao on 19-1-17.
//

#include <new>

#include "common_includes.h"
char buff[4096]{0};

TEST(test_test, 1) {
  EXPECT_EQ(1, 1);
  int *arr = new (buff) int[50];
  ASSERT_TRUE(buff == (char *)arr);
}

struct HasArgType {
  int OnTimeOut(int) { return 0; }

  int OtherFunc1(int) { return 0; }
  int OtherFunc2() { return 0; }
};
struct NoArgType {
  int OnTimeOut() { return 0; }

  int OtherFunc1(int) { return 0; }
  int OtherFunc2() { return 0; }
};
// 判断有没有 int  OnTimeOut(int nActionID);
// 有就调用 int  OnTimeOut(int nActionID);, 否则调用int  OnTimeOut();
template <typename T>
struct HasOnTimeOutWithInt
{
  typedef char yes[1];
  typedef char no[2];

  // 这个模板函数会匹配任何类型
  template <typename U, U>
  struct type_check;

  // 这个模板函数会匹配有 OnTimeOut(int) 函数的类型
  template <typename U>
  static yes& chk(type_check<int (U::*)(int), &U::OnTimeOut>*);

  // 这个模板函数会匹配没有 OnTimeOut(int) 函数的类型
  template <typename>
  static no& chk(...);

  // 如果 T 有 OnTimeOut(int) 函数，chk 函数会返回 yes&，否则返回 no&
  static const bool value = sizeof(chk<T>(0)) == sizeof(yes);
};
template <class T, bool withArg>
struct CallOnTimeOutSelector {};
template <class T>
struct CallOnTimeOutSelector<T, false> {
  static int Invoke(T &obj) { return obj.OnTimeOut(); }
};
template <class T>
struct CallOnTimeOutSelector<T, true> {
  static int Invoke(T &obj) { return obj.OnTimeOut(0); }
};
template <typename T>
struct CallOnTimeOutForward
    : public CallOnTimeOutSelector<T, HasOnTimeOutWithInt<T>::value> {};
template <typename T>
int CallOnTimeOut(T &obj) {
  return CallOnTimeOutForward<T>::Invoke(obj);
};

// 判断有没有 int  OnError(int nActionID);
// 有就调用 int  OnError(int nActionID);, 否则调用int  OnError();
template <typename T>
struct HasOnErrorWithInt
{
  typedef char yes[1];
  typedef char no[2];

  // 这个模板函数会匹配任何类型
  template <typename U, U>
  struct type_check;

  // 这个模板函数会匹配有 OnError(int) 函数的类型
  template <typename U>
  static yes& chk(type_check<int (U::*)(int), &U::OnError>*);

  // 这个模板函数会匹配没有 OnError(int) 函数的类型
  template <typename>
  static no& chk(...);

  // 如果 T 有 OnError(int) 函数，chk 函数会返回 yes&，否则返回 no&
  static const bool value = sizeof(chk<T>(0)) == sizeof(yes);
};
template <class T, bool withArg>
struct CallOnErrorSelector {};
template <class T>
struct CallOnErrorSelector<T, false> {
  static int Invoke(T &obj) { return obj.OnError(); }
};
template <class T>
struct CallOnErrorSelector<T, true> {
  static int Invoke(T &obj) { return obj.OnError(0); }
};
template <typename T>
struct CallOnErrorForward
    : public CallOnErrorSelector<T, HasOnErrorWithInt<T>::value> {};
template <typename T>
int CallOnError(T &obj) {
  return CallOnErrorForward<T>::Invoke(obj);
};

int main(int argc, char **argv) {
  HasArgType t1;
  NoArgType t2;
  static_assert(HasOnTimeOutWithInt<HasArgType>::value==true,"true");
  static_assert(HasOnTimeOutWithInt<NoArgType>::value== false,"false");

  CallOnTimeOut(t1);
  CallOnTimeOut(t2);

  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}