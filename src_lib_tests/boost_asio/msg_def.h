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
#include <stdexcept>
#include <string>
namespace MsgHead {
#define bswap_16(value) ((((value)&0xff) << 8) | ((value) >> 8))

#define bswap_32(value)                                     \
  (((uint32_t)bswap_16((uint16_t)((value)&0xffff)) << 16) | \
   (uint32_t)bswap_16((uint16_t)((value) >> 16)))

inline void WriteUint32(char* pos, uint32_t val) {
  if constexpr (std::endian::native != std::endian::little) {
    val = bswap_32(val);
  }
  memcpy(pos, &val, sizeof(uint32_t));
}
inline uint32_t ReadUint32(char* pos) {
  uint32_t val;
  memcpy(&val, pos, sizeof(uint32_t));
  if constexpr (std::endian::native != std::endian::little) {
    val = bswap_32(val);
  }
  return val;
}

enum class MsgType : uint8_t {
  kReq = 0,
  kRsp,
  kNotify,
};
enum class Flags {
  // 分包标记， 读到 如果被分包， 前面的都有这个标记， 最后一个没有
  kSplit = 0x1,
  // 自定义包头是否存在， 如果被分包， 前面的包优先填充自定义包头，
  // 完成后后面才是包体
  kCustomHead = 0x2,
  // 最多8个标记 0x80
};
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
      uint16_t s = bswap_16(seq);
      memcpy(dest, &s, sizeof(seq));
    }
  }
  void FromBuf(const char* from) {
    memcpy(this, from, sizeof(MsgHead));
    if constexpr (std::endian::native != std::endian::little) {
      seq = bswap_16(seq);
    }
  }
};
static_assert(sizeof(MsgHead) == 4);

class MsgException : public std::runtime_error {
  public:
  using runtime_error::runtime_error;
};
class MsgBufBase {
  protected:
  std::string buf_{};
  // custom_head_size_ 已经写在buff中了， 这里冗余了一份， 用来加速
  uint32_t custom_head_size_{};
  static constexpr ssize_t kCustomHeadLen = 4;
  void Init(ssize_t size, ssize_t custom_head_size) {
    // 自定义包头长度
    auto real_size = sizeof(MsgHead) + size;
    custom_head_size_ = custom_head_size;
    if (custom_head_size > 0) {
      real_size += (custom_head_size + kCustomHeadLen);
    }
    buf_.resize(real_size);
    MsgHead head{};
    if (custom_head_size > 0) {
      head.flags |= (uint8_t)Flags::kCustomHead;
      WriteUint32(buf_.data() + sizeof(MsgHead), custom_head_size);
    }
    SetHead(head);
  }
  void ReDecode() {
    if (buf_.size() < sizeof(MsgHead)) {
      throw MsgException("invalid msg: too short");
    }
    MsgHead head;
    ReadHead(head);
    if (head.flags & (uint8_t)Flags::kCustomHead) {
      if (buf_.size() < sizeof(MsgHead) + sizeof(uint32_t)) {
        throw MsgException("invalid msg: too short");
      }
      custom_head_size_ = ReadUint32(buf_.data() + sizeof(MsgHead));
      if (buf_.size() < ExternSize() + custom_head_size_) {
        throw MsgException("invalid msg: too short");
      }
    } else {
      custom_head_size_ = 0;
    }
  }

  public:
  void SetHead(const MsgHead& head) { head.ToBuf(buf_.data()); }
  void ReadHead(MsgHead& head) const { head.FromBuf(buf_.data()); }
  char* Buf() { return buf_.data() + ExternSize(); }
  ssize_t BufSize() const { return buf_.size() - ExternSize(); }

  bool HadCustomHead() const { return custom_head_size_ > 0; }
  char* CustomHead() {
    if (!HadCustomHead()) {
      return nullptr;
    }
    return buf_.data() + sizeof(MsgHead) + kCustomHeadLen;
  }
  ssize_t CustomHeadSize() const { return custom_head_size_; }
  ssize_t ExternSize() const {
    if (HadCustomHead()) {
      return sizeof(MsgHead) + CustomHeadSize() + kCustomHeadLen;
    }
    return sizeof(MsgHead);
  }

  void Resize(ssize_t size) {
    auto extern_size = ExternSize();
    if (size < extern_size) {
      throw MsgException("invalid msg");
    }
    buf_.resize(ExternSize() + size);
  }

  public:
  MsgBufBase() {}
  MsgBufBase(ssize_t size, ssize_t custom_head_size) {
    Init(size, custom_head_size);
  }
  MsgBufBase(const char* buf, ssize_t size, ssize_t custom_head_size) {
    Init(size, custom_head_size);
    memcpy(buf_.data() + ExternSize(), buf, size);
  }
  MsgBufBase(const std::string& buf, ssize_t custom_head_size) {
    Init(buf.size(), custom_head_size);
    memcpy(buf_.data() + ExternSize(), buf.data(), buf.size());
  }
  void Decode(const std::string& data) {
    MsgBufBase buf;
    buf.buf_ = data;
    buf.ReDecode();
  }
  void Decode(std::string&& data) {
    MsgBufBase buf;
    buf.buf_ = std::move(data);
    buf.ReDecode();
  }
  void CopyFrom(const MsgBufBase& buf) {
    buf_ = buf.buf_;
    custom_head_size_ = buf.custom_head_size_;
  }
  MsgBufBase(const MsgBufBase& buf) { CopyFrom(buf); }
  MsgBufBase& operator=(const MsgBufBase& buf) {
    CopyFrom(buf);
    return *this;
  }

  void MoveFrom(MsgBufBase& buf) noexcept {
    buf_ = std::move(buf.buf_);
    custom_head_size_ = buf.custom_head_size_;
  }
  MsgBufBase(MsgBufBase&& buf) noexcept { MoveFrom(buf); }
  MsgBufBase& operator=(MsgBufBase&& buf) noexcept {
    MoveFrom(buf);
    return *this;
  }
};
class CustomHeadMsgBuf : public MsgBufBase {
  public:
  using BufBaseT = MsgBufBase;
  using MsgBufBase::MsgBufBase;
};

template <class T>
class CustomStructHeadMsgBuf : public MsgBufBase {
  public:
  using BufBaseT = MsgBufBase;
  using MsgBufBase::MsgBufBase;
  CustomStructHeadMsgBuf(ssize_t size) : MsgBufBase(size, sizeof(T)) {}
  CustomStructHeadMsgBuf(const char* buf, ssize_t size)
      : MsgBufBase(buf, size, sizeof(T)) {}
  CustomStructHeadMsgBuf(const std::string& buf) : MsgBufBase(buf, sizeof(T)) {}
  void SetCustomHead(const T& head) {
    head.ToBuf(CustomHead(), CustomHeadSize());
  }
  void ReadCustomHead(T& head) { head.FromBuf(CustomHead(), CustomHeadSize()); }
};
class MsgBuf : public MsgBufBase {
  public:
  using BufBaseT = MsgBufBase;
  MsgBuf(ssize_t size) : MsgBufBase(size, 0) {}
  MsgBuf(const char* buf, ssize_t size) : MsgBufBase(buf, size, 0) {}
  MsgBuf(const std::string& buf) : MsgBufBase(buf, 0) {}
};
}  // namespace MsgHead
