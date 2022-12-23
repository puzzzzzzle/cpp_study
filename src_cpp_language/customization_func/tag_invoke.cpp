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

// 先转发到 base 的operator()上, 再到
/*
 * _ZN10tag_invoke9view_base6detail6Show_tclINS_13customization7ImgViewEEEvRT_  对应
 * void tag_invoke::view_base::detail::Show_t::operator()<tag_invoke::customization::ImgView>(tag_invoke::customization::ImgView&)
 */
/*
 0000000000011dae <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv>:
  11dae:	f3 0f 1e fa          	endbr64
  11db2:	55                   	push   %rbp
  11db3:	48 89 e5             	mov    %rsp,%rbp
  11db6:	48 83 ec 20          	sub    $0x20,%rsp
  11dba:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  11dbe:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  11dc5:	00 00
  11dc7:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  11dcb:	31 c0                	xor    %eax,%eax
  11dcd:	48 8d 45 f6          	lea    -0xa(%rbp),%rax
  11dd1:	48 89 c6             	mov    %rax,%rsi
  11dd4:	48 8d 05 c6 e2 04 00 	lea    0x4e2c6(%rip),%rax        # 600a1 <_ZN10tag_invoke9view_base4ShowE>
  11ddb:	48 89 c7             	mov    %rax,%rdi
  11dde:	e8 1d 04 00 00       	call   12200 <_ZN10tag_invoke9view_base6detail6Show_tclINS_13customization7ImgViewEEEvRT_>
  11de3:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
  11de7:	48 89 c6             	mov    %rax,%rsi
  11dea:	48 8d 05 b0 e2 04 00 	lea    0x4e2b0(%rip),%rax        # 600a1 <_ZN10tag_invoke9view_base4ShowE>
  11df1:	48 89 c7             	mov    %rax,%rdi
  11df4:	e8 2b 04 00 00       	call   12224 <_ZN10tag_invoke9view_base6detail6Show_tclINS_13customization8VoidViewEEEvRT_>
  11df9:	48 8d 45 f6          	lea    -0xa(%rbp),%rax
  11dfd:	48 89 c6             	mov    %rax,%rsi
  11e00:	48 8d 05 9a e2 04 00 	lea    0x4e29a(%rip),%rax        # 600a1 <_ZN10tag_invoke9view_base4ShowE>
  11e07:	48 89 c7             	mov    %rax,%rdi
  11e0a:	e8 f1 03 00 00       	call   12200 <_ZN10tag_invoke9view_base6detail6Show_tclINS_13customization7ImgViewEEEvRT_>
  11e0f:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
  11e13:	48 89 c6             	mov    %rax,%rsi
  11e16:	48 8d 05 84 e2 04 00 	lea    0x4e284(%rip),%rax        # 600a1 <_ZN10tag_invoke9view_base4ShowE>
  11e1d:	48 89 c7             	mov    %rax,%rdi
  11e20:	e8 ff 03 00 00       	call   12224 <_ZN10tag_invoke9view_base6detail6Show_tclINS_13customization8VoidViewEEEvRT_>
  11e25:	90                   	nop
  11e26:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  11e2a:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  11e31:	00 00
  11e33:	74 05                	je     11e3a <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x8c>
  11e35:	e8 b6 83 ff ff       	call   a1f0 <__stack_chk_fail@plt>
  11e3a:	c9                   	leave
  11e3b:	c3                   	ret
 */
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