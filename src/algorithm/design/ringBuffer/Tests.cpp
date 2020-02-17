//
// Created by tao zhang on 2020/2/17.
//
#include "common_includes.h"
#include "RingBufferBoostWarperImpl.h"
#include "RingBufferInterface.h"
#include "RingBufferArrayImpl.h"

TEST(ringbuffer,boost_1){
    RingBufferBoostWarper<int> ringBuffer(5);
    ASSERT_EQ(ringBuffer.empty(),true);
    ASSERT_EQ(ringBuffer.full(),false);
    ASSERT_EQ(ringBuffer.size(),0);
    ASSERT_EQ(ringBuffer.capacity(),5);

    // 对空的buffer做读取是未定义的
    ASSERT_NE(ringBuffer.front(),0);
    ASSERT_NE(ringBuffer.back(),0);

    for(int i=0;i<4;++i){
        ringBuffer.push(i);
    }
    ASSERT_EQ(ringBuffer.empty(), false);
    ASSERT_EQ(ringBuffer.full(),false);
    ASSERT_EQ(ringBuffer.size(),4);
    ASSERT_EQ(ringBuffer.capacity(),5);

    ASSERT_EQ(ringBuffer.front(),0);
    ASSERT_EQ(ringBuffer.back(),3);

    ringBuffer.push(4);
    ASSERT_EQ(ringBuffer.empty(), false);
    ASSERT_EQ(ringBuffer.full(), true);
    ASSERT_EQ(ringBuffer.size(),5);
    ASSERT_EQ(ringBuffer.capacity(),5);

    ASSERT_EQ(ringBuffer.front(),0);
    ASSERT_EQ(ringBuffer.back(),4);

    auto ret = ringBuffer.push(5);
    ASSERT_NE(ret,0);
    ASSERT_EQ(ringBuffer.empty(), false);
    ASSERT_EQ(ringBuffer.full(), true);
    ASSERT_EQ(ringBuffer.size(),5);
    ASSERT_EQ(ringBuffer.capacity(),5);

    ASSERT_EQ(ringBuffer.front(),0);
    ASSERT_EQ(ringBuffer.back(),4);

    ringBuffer.pop();
    ASSERT_EQ(ringBuffer.empty(), false);
    ASSERT_EQ(ringBuffer.full(), false);
    ASSERT_EQ(ringBuffer.size(),4);
    ASSERT_EQ(ringBuffer.capacity(),5);

    ASSERT_EQ(ringBuffer.front(),1);
    ASSERT_EQ(ringBuffer.back(),4);

    ret = ringBuffer.push(5);
    ASSERT_EQ(ret,0);
    ASSERT_EQ(ringBuffer.empty(), false);
    ASSERT_EQ(ringBuffer.full(), true);
    ASSERT_EQ(ringBuffer.size(),5);
    ASSERT_EQ(ringBuffer.capacity(),5);

    ASSERT_EQ(ringBuffer.front(),1);
    ASSERT_EQ(ringBuffer.back(),5);

}
