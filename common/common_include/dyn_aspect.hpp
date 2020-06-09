#pragma once

namespace aop {
class NonCopyable {
  public:
  NonCopyable(const NonCopyable &) = delete;             // Deleted
  NonCopyable &operator=(const NonCopyable &) = delete;  // Deleted
  NonCopyable() = default;                               // Available
};

#define HAS_MEMBER(member)                                               \
                                                                         \
  template <typename T, typename... Args>                                \
  struct has_member_##member {                                           \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().member(std::declval<Args>()...),   \
                    std::true_type());                                   \
                                                                         \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  }

HAS_MEMBER(Before);  // Add BeforeUpdate aspect
HAS_MEMBER(After);   // Add After aspect

template <typename Ret, typename Func, typename... Args>
struct Aspect : NonCopyable {
  Aspect(Func &&f) : m_func(std::forward<Func>(f)) {}

  template <typename T>
  typename std::enable_if<has_member_Before<T, Args...>::value &&
                          has_member_After<T, Args...>::value>::type
  Invoke(Args &&... args, T &&aspect) {
    aspect.Before(std::forward<Args>(args)...);   // Run codes before core codes
    m_ret = m_func(std::forward<Args>(args)...);  // Run core codes
    aspect.After(std::forward<Args>(args)...);    // Run codes after core codes
  }

  template <typename T>
  typename std::enable_if<has_member_Before<T, Args...>::value &&
                          !has_member_After<T, Args...>::value>::type
  Invoke(Args &&... args, T &&aspect) {
    aspect.Before(std::forward<Args>(args)...);   // Run codes before core codes
    m_ret = m_func(std::forward<Args>(args)...);  // Run core codes
  }

  template <typename T>
  typename std::enable_if<!has_member_Before<T, Args...>::value &&
                          has_member_After<T, Args...>::value>::type
  Invoke(Args &&... args, T &&aspect) {
    m_ret = m_func(std::forward<Args>(args)...);  // Run core codes
    aspect.After(std::forward<Args>(args)...);    // Run codes after core codes
  }

  template <typename Head, typename... Tail>
  void Invoke(Args &&... args, Head &&headAspect, Tail &&... tailAspect) {
    headAspect.Before(std::forward<Args>(args)...);
    Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
    headAspect.After(std::forward<Args>(args)...);
  }

  Ret GetReturn() { return m_ret; }

  private:
  Func m_func;  // Function that be invoked
  Ret m_ret;    // Core codes return value
};

//    template<typename T> using identity_t = T;

// AOP function, for export
template <typename Ret, typename... AP, typename... Args, typename Func>
Ret AOP(Func &&f, Args &&... args) {
  Aspect<Ret, Func, Args...> asp(std::forward<Func>(f));
  asp.Invoke(std::forward<Args>(args)..., AP()...);
  return asp.GetReturn();
}

//    template<typename... AP, typename... Args, typename Func>
//    void VAOP(Func &&f, Args &&... args)
//    {
//        Aspect<int, Func, Args...> asp(std::forward<Func>(f));
//        asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
//    }
}  // namespace aop

using aop::AOP;
// using aop::VAOP;

/* --- AOP user manual ---
  If you need to add aspects to a function and then call this function,
  you can call the function as follows:
    [func_return_value] AOP<[func_return_type],
[aspect_struct...]>([fixedUpdateTimeOutCallBackFunc], [func_params...]);
  [func_return_value] : the original function return value
  [func_return_type]  : the original function return type, must not be "void"
type [aspect_struct...]  : aspects list that will be added to original function
  [fixedUpdateTimeOutCallBackFunc]              : the original function pointer
  [func_params...]    : the original function params list
  Aspect struct needs to be coded as follows:
  struct [aspect_struct_name]
  {
      void BeforeUpdate(...)
      {
          // TODO
      }

      void After(...)
      {
          // TODO
      }

      [vars]

      private:

      [private_vars]
  };
------------------------*/