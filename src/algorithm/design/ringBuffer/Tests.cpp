//
// Created by tao zhang on 2020/2/17.
//
#include "RingBufferArrayImpl.h"
#include "RingBufferBoostWarperImpl.h"
#include "RingBufferInterface.h"
#include "common_includes.h"

TEST(ringbuffer, boost_1) {
  //    RingBufferBoostWarper<int> ringBuffer(5);
  RingBufferArrayImpl<int> ringBuffer(5);

  ASSERT_EQ(ringBuffer.Empty(), true);
  ASSERT_EQ(ringBuffer.Full(), false);
  ASSERT_EQ(ringBuffer.Size(), 0);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  // 对空的buffer做读取是未定义的
  //    ASSERT_NE(ringBuffer.Front(),0);
  //    ASSERT_NE(ringBuffer.Back(),0);

  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(ringBuffer.Push(i), 0);
  }
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), false);
  ASSERT_EQ(ringBuffer.Size(), 4);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  ASSERT_EQ(ringBuffer.Front(), 0);

  ASSERT_EQ(ringBuffer.Push(4), 0);
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), true);
  ASSERT_EQ(ringBuffer.Size(), 5);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  ASSERT_EQ(ringBuffer.Front(), 0);

  auto ret = ringBuffer.Push(5);
  ASSERT_NE(ret, 0);
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), true);
  ASSERT_EQ(ringBuffer.Size(), 5);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  ASSERT_EQ(ringBuffer.Front(), 0);

  ringBuffer.Pop();
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), false);
  ASSERT_EQ(ringBuffer.Size(), 4);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  ASSERT_EQ(ringBuffer.Front(), 1);

  ret = ringBuffer.Push(5);
  ASSERT_EQ(ret, 0);
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), true);
  ASSERT_EQ(ringBuffer.Size(), 5);
  ASSERT_EQ(ringBuffer.Capacity(), 5);

  ASSERT_EQ(ringBuffer.Front(), 1);

  ringBuffer.Pop();
  ASSERT_EQ(ringBuffer.Empty(), false);
  ASSERT_EQ(ringBuffer.Full(), false);
  ASSERT_EQ(ringBuffer.Size(), 4);
  ASSERT_EQ(ringBuffer.Capacity(), 5);
  ASSERT_EQ(ringBuffer.Front(), 2);

  ringBuffer.Pop();
  ASSERT_EQ(ringBuffer.Front(), 3);

  ringBuffer.Pop();
  ASSERT_EQ(ringBuffer.Front(), 4);

  ringBuffer.Pop();
  ASSERT_EQ(ringBuffer.Front(), 5);
}
