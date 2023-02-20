/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/2/17
 * @file msg_head.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#pragma once
#include <cstdint>
namespace MsgHead {
enum class MsgType : uint8_t {
  kReq = 0,
  kRsp,
  kNotify,
};
enum class Flags {
  // 分包标记， 读到 如果被分包， 前面的都有这个标记， 最后一个没有
  kSplit = 0x1,

  // 最多8个标记 0x80
};
struct MsgHead {
  uint16_t seq;      // 2b
  MsgType msg_type;  // 1b
  // 分包标记
  uint8_t flags;  // 1b
};
static_assert(sizeof(MsgHead) == 4);
}  // namespace MsgHead
