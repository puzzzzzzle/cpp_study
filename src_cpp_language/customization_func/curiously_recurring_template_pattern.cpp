//
// Created by khalidzhang on 2022/12/22.
//
#include "common_includes.h"
// 静态多态
namespace crtp {
namespace view_base {
template <typename T>
class View {
  public:
  void Show() noexcept { static_cast<T*>(this)->ShowImpl(); }
};
template <typename T>
void Show(View<T>& v) noexcept {
  v.Show();
}
}  // namespace view_base
namespace view_impl {
class ImgView : public view_base::View<ImgView> {
  public:
  void ShowImpl() noexcept { LOG_DEBUG("show img") }
};
class AnotherViewImpl : public view_base::View<AnotherViewImpl> {
  public:
  void ShowImpl() noexcept { LOG_DEBUG("another show img") }
};
}  // namespace view_impl

TEST(crtp, 1) {
  view_impl::ImgView v{};
  view_impl::AnotherViewImpl v2{};
  v.Show();
  v2.Show();
  Show(v);
  Show(v2);
}
}  // namespace crtp