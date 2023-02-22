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
#include <bit>
#include <cstdint>
#include <cstring>
#include <string>
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
#define BIG_LITTLE_ENDIAN_SWAP_16(A) \
  ((((uint16_t)(A)&0xff00) >> 8) | (((uint16_t)(A)&0x00ff) << 8))
struct MsgHead {
  uint16_t seq;      // 2b
  MsgType msg_type;  // 1b
  // 分包标记
  uint8_t flags;  // 1b
  void ToBuf(char* dest) const {
    memcpy(dest, this, sizeof(MsgHead));
    // 网络序一般使用大端序, 但是 一般主流平台都是使用小端序
    // x86 是小端序, arm虽然可配置, 但是一般也是小端序
    // 这里使用小端序来存储
    if constexpr (std::endian::native != std::endian::little) {
      uint16_t s = BIG_LITTLE_ENDIAN_SWAP_16(seq);
      memcpy(dest, &s, sizeof(seq));
    }
  }
  void FromBuf(const char* from) {
    memcpy(this, from, sizeof(MsgHead));
    if constexpr (std::endian::native != std::endian::little) {
      seq = BIG_LITTLE_ENDIAN_SWAP_16(seq);
    }
  }
#undef BIG_LITTLE_ENDIAN_SWAP_16
};
static_assert(sizeof(MsgHead) == 4);
// template <typename T>
class MsgBuf {
  char* buf_;
  ssize_t size_{};

  void Init(ssize_t size) {
    size_ = sizeof(MsgHead) + size;
    buf_ = new char[size_];
  }

  public:
  MsgBuf(ssize_t size) { Init(size); }
  MsgBuf(const char* buf, ssize_t size) {
    Init(size);
    memcpy(buf_ + sizeof(MsgHead), buf, size);
  }
  MsgBuf(const std::string& buf) {
    Init(buf.size());
    memcpy(buf_ + sizeof(MsgHead), buf.data(), buf.size());
  }
  ~MsgBuf() { delete[] buf_; }

  void CopyFrom(const MsgBuf& buf) {
    size_ = buf.size_;
    buf_ = new char[size_];
    memcpy(buf_, buf.buf_, size_);
  }
  MsgBuf(const MsgBuf& buf) { CopyFrom(buf); }
  MsgBuf& operator=(const MsgBuf& buf) { CopyFrom(buf); }

  void MoveFrom(MsgBuf& buf) noexcept {
    size_ = buf.size_;
    buf_ = buf.buf_;
    buf.size_ = 0;
    buf.buf_ = nullptr;
  }
  MsgBuf(MsgBuf&& buf) noexcept { MoveFrom(buf); }
  MsgBuf& operator=(MsgBuf&& buf) noexcept { MoveFrom(buf); }

  void SetHead(const MsgHead& head) { head.ToBuf(buf_); }
  void ReadHead(MsgHead& head) { head.FromBuf(buf_); }

  char* Buf() { return buf_ + sizeof(MsgHead); }
  ssize_t Size() { return size_ - sizeof(MsgHead); }
};
}  // namespace MsgHead
