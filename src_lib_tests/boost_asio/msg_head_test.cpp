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
  ASSERT_NE(buf1.Buf(),buf2.Buf());

  // move
  char * buf2_addr = buf2.Buf();
  auto buf3 = std::move(buf2);
  ASSERT_EQ(buf2_addr,buf3.Buf());
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());

  LOG_DEBUG(std::string(buf3.Buf()))
}
struct Padding{
  int i1{};
  char c2{};
  double d3{};
  char data[50]{};
  void ToBuf(char* dest,ssize_t len) const {
    assert(len>=sizeof (Padding));
    memcpy(dest, this, sizeof(Padding));
  }
  void FromBuf(const char* from,ssize_t len) {
    assert(len>=sizeof (Padding));
    memcpy(this, from, sizeof(Padding));
  }
};
static_assert(std::is_trivially_copyable_v<Padding>);
TEST(pad_msg_buf,1)
{
  using MsgBufT = PadStructMsgBuf<Padding>;
  Padding pad{.i1=3,.d3=3.14,.data="world"};


  MsgBufT buf(100);
  ASSERT_EQ(buf.BufSize(), 100);
  
  std::string str("hello");
  MsgBufT buf1(str);
  buf1.SetPad(pad);
  ASSERT_TRUE(str == buf1.Buf());
  ASSERT_EQ(buf1.BufSize(), str.size());
  Padding read_pad{};

  memset(&read_pad,0,sizeof (Padding));
  buf1.ReadPad(read_pad);
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);

  // copy
  auto buf2 = buf1;
  ASSERT_TRUE(str == buf2.Buf());
  ASSERT_EQ(buf2.BufSize(), str.size());
  ASSERT_NE(buf1.Buf(),buf2.Buf());
  memset(&read_pad,0,sizeof (Padding));
  buf2.ReadPad(read_pad);
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);

  // move
  char * buf2_addr = buf2.Buf();
  auto buf3 = std::move(buf2);
  ASSERT_EQ(buf2_addr,buf3.Buf());
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());
  memset(&read_pad,0,sizeof (Padding));
  buf3.ReadPad(read_pad);
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);


  LOG_DEBUG(std::string(buf3.Buf()))
}

TEST(pad_buf,1)
{
  using MsgBufT = PadMsgBuf<sizeof (Padding)>;
  Padding pad{.i1=3,.d3=3.14,.data="world"};


  MsgBufT buf(100);
  ASSERT_EQ(buf.BufSize(), 100);

  std::string str("hello");
  MsgBufT buf1(str);
  pad.ToBuf(buf1.PadBuf(),buf1.PadBufSize());
  ASSERT_TRUE(str == buf1.Buf());
  ASSERT_EQ(buf1.BufSize(), str.size());
  Padding read_pad{};
  memset(&read_pad,0,sizeof (Padding));
  read_pad.FromBuf(buf1.PadBuf(),buf1.PadBufSize());
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);

  // copy
  auto buf2 = buf1;
  ASSERT_TRUE(str == buf2.Buf());
  ASSERT_EQ(buf2.BufSize(), str.size());
  ASSERT_NE(buf1.Buf(),buf2.Buf());
  memset(&read_pad,0,sizeof (Padding));
  read_pad.FromBuf(buf2.PadBuf(),buf2.PadBufSize());
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);

  // move
  char * buf2_addr = buf2.Buf();
  auto buf3 = std::move(buf2);
  ASSERT_EQ(buf2_addr,buf3.Buf());
  ASSERT_TRUE(str == buf3.Buf());
  ASSERT_EQ(buf3.BufSize(), str.size());
  memset(&read_pad,0,sizeof (Padding));
  read_pad.FromBuf(buf3.PadBuf(),buf3.PadBufSize());
  ASSERT_EQ(memcmp(&pad,&read_pad,sizeof (Padding)),0);


  LOG_DEBUG(std::string(buf3.Buf()))
}