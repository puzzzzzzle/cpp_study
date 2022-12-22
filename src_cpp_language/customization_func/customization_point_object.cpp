//
// Created by khalidzhang on 2022/12/22.
//
#include "common_includes.h"

// 本质上还是为了取代ADL而设计的

namespace cpo {

// 定义show方法
namespace view_base {
namespace detail {
template <typename T>
void Show(T& t) noexcept {
  LOG_DEBUG("show nothing")
}
struct Show_t {
  template <typename T>
  void operator()(T& t) noexcept {
    Show(t);
  }
};
}  // namespace detail
inline detail::Show_t Show{};
}  // namespace view_base

// 用户可以定制Show, 即使强制指定使用 base里面的
namespace customization {
struct ImgView {
  friend void Show(ImgView& v) noexcept { LOG_DEBUG("show img") }
};
struct VoidView {};
}  // namespace customization
TEST(cpo, 1) {
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
}  // namespace cpo