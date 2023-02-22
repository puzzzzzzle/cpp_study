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
template <ssize_t PadSize>
class MsgBufBase {
  public:
  static constexpr ssize_t PadSize_ = PadSize;
  static constexpr ssize_t ExternSize_ = PadSize_ + sizeof(MsgHead);

  protected:
  char* buf_;
  ssize_t size_{};

  void Init(ssize_t size) {
    size_ = ExternSize_ + size;
    buf_ = new char[size_];
  }

  public:
  MsgBufBase(ssize_t size) { Init(size); }
  MsgBufBase(const char* buf, ssize_t size) {
    Init(size);
    memcpy(buf_ + ExternSize_, buf, size);
  }
  MsgBufBase(const std::string& buf) {
    Init(buf.size());
    memcpy(buf_ + ExternSize_, buf.data(), buf.size());
  }
  ~MsgBufBase() { delete[] buf_; }

  void CopyFrom(const MsgBufBase& buf) {
    size_ = buf.size_;
    buf_ = new char[size_];
    memcpy(buf_, buf.buf_, size_);
  }
  MsgBufBase(const MsgBufBase& buf) { CopyFrom(buf); }
  MsgBufBase& operator=(const MsgBufBase& buf) { CopyFrom(buf); }

  void MoveFrom(MsgBufBase& buf) noexcept {
    size_ = buf.size_;
    buf_ = buf.buf_;
    buf.size_ = 0;
    buf.buf_ = nullptr;
  }
  MsgBufBase(MsgBufBase&& buf) noexcept { MoveFrom(buf); }
  MsgBufBase& operator=(MsgBufBase&& buf) noexcept { MoveFrom(buf); }

  void SetHead(const MsgHead& head) { head.ToBuf(buf_); }
  void ReadHead(MsgHead& head) const { head.FromBuf(buf_); }

  char* Buf() { return buf_ + ExternSize_; }
  ssize_t BufSize() const { return size_ - ExternSize_; }
};
template <ssize_t PadSize>
class PadMsgBuf : public MsgBufBase<PadSize> {
  public:
  using BufBaseT = MsgBufBase<PadSize>;
  using MsgBufBase<PadSize>::MsgBufBase;
  char* PadBuf() {
    if constexpr (PadSize == 0) {
      return nullptr;
    }
    return BufBaseT::buf_ + sizeof(MsgHead);
  }
  ssize_t PadBufSize() const { return PadSize; }
};
template <class T>
class PadStructMsgBuf : public MsgBufBase<sizeof(T)> {
  public:
  using BufBaseT = MsgBufBase<sizeof(T)>;
  using MsgBufBase<sizeof(T)>::MsgBufBase;
  void SetPad(const T& pad) {
    pad.ToBuf(BufBaseT::buf_ + sizeof(MsgHead), BufBaseT::PadSize_);
  }
  void ReadPad(T& pad) {
    pad.FromBuf(BufBaseT::buf_ + sizeof(MsgHead), BufBaseT::PadSize_);
  }
};
class MsgBuf : public MsgBufBase<0> {
  public:
  using BufBaseT = MsgBufBase<0>;
  using BufBaseT::MsgBufBase;
};
}  // namespace MsgHead
