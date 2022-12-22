//
// Created by khalidzhang on 2022/12/22.
//
#include "common_includes.h"

namespace pimpl {

// 接口可以放在.h中暴露
namespace view_define {
class View {
  public:
  // ViewImpl 不全, 构造和析构必须在 ViewImpl 声明后才能实现
  View();
  ~View();

  public:
  void Show() noexcept;

  private:
  class ViewImpl;
  std::unique_ptr<ViewImpl> pimpl_;
};
}  // namespace view_define

// view 的实现 cpp
// 注意: 必须和 ViewImpl 声明处于统一命名空间中
namespace view_define {
class View::ViewImpl {
  public:
  void Show() noexcept { LOG_DEBUG("show img") }
};
view_define::View::View() {}
view_define::View::~View() {}
void view_define::View::Show() noexcept { pimpl_->Show(); }
}  // namespace view_define

TEST(pimpl, 1) {
  view_define::View view{};
  view.Show();
}
}  // namespace pimpl