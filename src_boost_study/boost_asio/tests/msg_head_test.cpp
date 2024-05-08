//
// Created by khalidzhang on 2023/2/22.
//
#include "common_includes.h"
#include "msg_def.h"
using namespace MsgHead;
TEST(msg_buf, 1) {
  using MsgBufT = MsgBuf;
  MsgBufT buf(100);
  ASSERT_EQ(buf.BufSize(), 100);

  std::string str("hello");
  MsgBufT buf1(str);
  ASSERT_TRUE(str == buf1.Buf());
  ASSERT_EQ(buf1.BufSize(), str.size());

  // copy
  auto buf2 = buf1;
  ASSERT_TRUE(str == buf2.Buf());
  ASSERT_EQ(buf2.BufSize(), str.size());
  ASSERT_NE(buf1.Buf(), buf2.Buf());

  // move
  auto buf3 = std::move(buf2);
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());

  LOG_DEBUG(std::string(buf3.Buf()))
}
struct CustomeHead {
  int i1{};
  char c2{};
  double d3{};
  char data[50]{};
  void ToBuf(char* dest, ssize_t len) const {
    assert(len >= sizeof(CustomeHead));
    memcpy(dest, this, sizeof(CustomeHead));
  }
  void FromBuf(const char* from, ssize_t len) {
    assert(len >= sizeof(CustomeHead));
    memcpy(this, from, sizeof(CustomeHead));
  }
};
static_assert(std::is_trivially_copyable_v<CustomeHead>);
TEST(pad_msg_buf, 1) {
  using MsgBufT = CustomStructHeadMsgBuf<CustomeHead>;
  CustomeHead pad{.i1 = 3, .d3 = 3.14, .data = "world"};

  MsgBufT buf(100);
  ASSERT_EQ(buf.BufSize(), 100);

  std::string str("hello");
  MsgBufT buf1(str);
  buf1.SetCustomHead(pad);
  ASSERT_TRUE(str == buf1.Buf());
  ASSERT_EQ(buf1.BufSize(), str.size());
  CustomeHead read_pad{};

  memset(&read_pad, 0, sizeof(CustomeHead));
  buf1.ReadCustomHead(read_pad);
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  // copy
  auto buf2 = buf1;
  ASSERT_TRUE(str == buf2.Buf());
  ASSERT_EQ(buf2.BufSize(), str.size());
  ASSERT_NE(buf1.Buf(), buf2.Buf());
  memset(&read_pad, 0, sizeof(CustomeHead));
  buf2.ReadCustomHead(read_pad);
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  // move
  auto buf3 = std::move(buf2);
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());
  memset(&read_pad, 0, sizeof(CustomeHead));
  buf3.ReadCustomHead(read_pad);
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  LOG_DEBUG(std::string(buf3.Buf()))
}

TEST(pad_buf, 1) {
  using MsgBufT = CustomHeadMsgBuf;
  CustomeHead pad{.i1 = 3, .d3 = 3.14, .data = "world"};

  MsgBufT buf(100, sizeof(CustomeHead));
  ASSERT_EQ(buf.BufSize(), 100);

  std::string str("hello");
  MsgBufT buf1(str, sizeof(CustomeHead));
  pad.ToBuf(buf1.CustomHead(), buf1.CustomHeadSize());
  ASSERT_TRUE(str == buf1.Buf());
  ASSERT_EQ(buf1.BufSize(), str.size());
  CustomeHead read_pad{};
  memset(&read_pad, 0, sizeof(CustomeHead));
  read_pad.FromBuf(buf1.CustomHead(), buf1.CustomHeadSize());
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  // copy
  auto buf2 = buf1;
  ASSERT_TRUE(str == buf2.Buf());
  ASSERT_EQ(buf2.BufSize(), str.size());
  ASSERT_NE(buf1.Buf(), buf2.Buf());
  memset(&read_pad, 0, sizeof(CustomeHead));
  read_pad.FromBuf(buf2.CustomHead(), buf2.CustomHeadSize());
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  // move
  auto buf3 = std::move(buf2);
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());
  memset(&read_pad, 0, sizeof(CustomeHead));
  read_pad.FromBuf(buf3.CustomHead(), buf3.CustomHeadSize());
  ASSERT_EQ(memcmp(&pad, &read_pad, sizeof(CustomeHead)), 0);

  LOG_DEBUG(std::string(buf3.Buf()))
}