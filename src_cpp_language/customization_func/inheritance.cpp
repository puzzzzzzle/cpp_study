//
// Created by khalidzhang on 2022/12/22.
//
#include "common_includes.h"

// 接口可以放在.h中暴露
namespace inheritance {
namespace view_base {
class View {
  public:
  void Show() noexcept { ShowImpl(); }
  virtual void ShowImpl() noexcept = 0;
  ~View() {}
};
}  // namespace view_base

// 实现放在其他的.cpp中, 通过工厂之类的创建
namespace customize_impl {
class ImgView : public view_base::View {
  public:
  void ShowImpl() noexcept override { LOG_DEBUG("show img") }
};
}  // namespace customize_impl

TEST(inheritance, 1) {
  customize_impl::ImgView v{};
  view_base::View& view = v;
  view.Show();
}
}  // namespace inheritance
