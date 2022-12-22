//
// Created by khalidzhang on 2022/12/22.
//
#include <type_traits>

#include "common_includes.h"

namespace tag_invoke {

namespace view_base {
namespace detail {
void tag_invoke();
// noexcept (true) 表示不会抛出异常, 同时返回是否抛出异常
// noexcept (noexcept(func())) 则表示 func() 如果不抛出异常,
// 那么当前函数也不抛出异常
struct tag_invoke_t {
  template <typename Tag, typename... Args>
  constexpr auto operator()(Tag tag, Args &&...args) const
      noexcept(noexcept(tag_invoke(static_cast<Tag &&>(tag),
                                   static_cast<Args &&>(args)...)))
          -> decltype(tag_invoke(static_cast<Tag &&>(tag),
                                 static_cast<Args &&>(args)...)) {
    return tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...);
  }
};
}  // namespace detail
inline constexpr detail::tag_invoke_t tag_invoke{};
template <auto &Tag>
using tag_t = std::decay_t<decltype(Tag)>;
}  // namespace view_base

namespace view_base {
namespace detail {
struct Show_t {
  template <typename T>
  void operator()(T &t) noexcept {
    tag_invoke(Show_t{}, t);
  }
};
template <typename T>
void tag_invoke(Show_t, T &t) noexcept {
  LOG_DEBUG("show nothing")
}
}  // namespace detail
inline detail::Show_t Show{};
}  // namespace view_base

// 用户可以定制Show, 即使强制指定使用 base里面的
namespace customization {
struct ImgView {
  friend void tag_invoke(view_base::tag_t<view_base::Show>,
                         ImgView &v) noexcept {
    LOG_DEBUG("show image")
  }
};
struct VoidView {};
}  // namespace customization

TEST(tag_invoke, 1) {
  customization::ImgView v{};
  customization::VoidView vv{};

  // 如果 customization 中有定义, 那么无论怎么指定, 都使用 customization中的
  // 否则, 使用 base中的
  // 但是 这意味着, customization 中的Show被占用, 基本 成为一个关键字了
  view_base::Show(v);
  view_base::Show(vv);
  using namespace view_base;
  Show(v);
  Show(vv);
}
}  // namespace tag_invoke