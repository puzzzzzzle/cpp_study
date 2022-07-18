/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc 萃取类中是否有某个函数/变量, 支持参数但是类型时严格的, 不会自动转换
 * 先使用宏定义出模板函数
 * 再使用模板函数来判断
 *
 * 也可以实现在判断函数是否存在后, 进行调用
 * @time 2021/5/24
 * @file has_member.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#pragma once
// 检测是否有成员函数的基础模板
// 支持多个参数
#define HAS_MEMBER_BASE(prefix, name)                                    \
  template <typename T, typename... Args>                                \
  struct _HasMemberS_##name##prefix {                                    \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().name(std::declval<Args>()...),     \
                    std::true_type());                                   \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };
// 检测是否有参数不为空的成员函数
// 支持多个参数
#define HAS_MEMBER_FUNC(prefix, name, args...) \
  HAS_MEMBER_BASE(prefix, name)                \
  template <typename T>                        \
  using _HasMember_##name##prefix = _HasMemberS_##name##prefix<T, args>;
// 检测是否有参数为空的成员函数
#define HAS_MEMBER_FUNC_VOID(prefix, name) \
  HAS_MEMBER_BASE(prefix, name)            \
  template <typename T>                    \
  using _HasMember_##name##prefix = _HasMemberS_##name##prefix<T>;
// 检测是否有可以访问的成员变量
#define HAS_MEMBER_VARIABLE_BASE(name)                                   \
  template <typename T>                                                  \
  struct _HasMemberVar_##name {                                          \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().name, std::true_type());           \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };
// 如果存在某个函数就调用, 不存在, 就忽略
// 目前只支持一个参数, 多个参数在递归展开时, 不兼容enable_if, 还在找方案
// 多个参数的需要手动实现下调用器
#define CALL_IF_EXISTS_FUNC(prefix, name, ret, Arg)                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, ret>::type   \
      CALL_##name##prefix(T &para, Arg arg) {                               \
    return para.name(arg);                                                  \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, ret>::type  \
      CALL_##name##prefix(T &para, Arg arg) {                               \
    return {};                                                              \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, void>::type  \
      CALL_##name##prefix##_no_return(T &para, Arg arg) {                   \
    para.name(arg);                                                         \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, void>::type \
      CALL_##name##prefix##_no_return(T &para, Arg arg) {}

// 如果存在某个函数就调用, 不存在, 就忽略, 参数为空版
// 目前只支持一个参数, 多个参数在递归展开时, 不兼容enable_if, 还在找方案
// 多个参数的需要手动实现下调用器
#define CALL_IF_EXISTS_FUNC_VOID(prefix, name, ret)                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, ret>::type   \
      CALL_##name##prefix(T &para) {                                        \
    return para.name();                                                     \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, ret>::type  \
      CALL_##name##prefix(T &para) {                                        \
    return {};                                                              \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, void>::type  \
      CALL_##name##prefix##_no_return(T &para) {                            \
    para.name();                                                            \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, void>::type \
      CALL_##name##prefix##_no_return(T &para) {}

// 只支持单个参数的
// 多个参数的需要手动实现下调用器
#define HAS_MEMBER_CALL_VOID(prefix, name, ret) \
  HAS_MEMBER_FUNC_VOID(prefix, name)            \
  CALL_IF_EXISTS_FUNC_VOID(prefix, name, ret)
// 只支持单个参数的
// 多个参数的需要手动实现下调用器
#define HAS_MEMBER_CALL(prefix, name, ret, args...) \
  HAS_MEMBER_FUNC(prefix, name, args)               \
  CALL_IF_EXISTS_FUNC(prefix, name, ret, args)
