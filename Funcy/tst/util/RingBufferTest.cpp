/*
 * RingBufferTest.cpp
 *
 *  Created on: 14.06.2013
 *      Author: schickin
 */


#include "funcy/util/ring_buffer.h"

#include "gtest/gtest.h"

class RingBufferTest : public ::testing::Test
{
protected:

  template <std::size_t Capacity>
  void checkAccessToFirstElement(RingBuffer<int, Capacity>& buf)
  {
    EXPECT_EQ(0, buf[0]);
    for (std::size_t i = 0; i < 3; ++i) {
      buf.push_back(17);
      EXPECT_EQ(17, buf[0]);
      EXPECT_EQ(17, buf(i));
      buf[0] *= 2;
      EXPECT_EQ(34, buf[0]);
    }
  }

};


TEST_F(RingBufferTest, oneElementBuffer)
{
  RingBuffer<int, 1> buf;
  checkAccessToFirstElement(buf);
}

TEST_F(RingBufferTest, multipleElementBuffer_initialization)
{
  RingBuffer<int, 3> buf;
  EXPECT_EQ(0, buf[0]);
  EXPECT_EQ(0, buf[-1]);
  EXPECT_EQ(0, buf[-2]);
}

TEST_F(RingBufferTest, multipleElementBuffer_accessFirstElement)
{
  RingBuffer<int, 3> buf;
  checkAccessToFirstElement(buf);
}

TEST_F(RingBufferTest, multipleElementBuffer_accessAllElementsInBatches)
{
  RingBuffer<int, 3> buf;
  for (int i = 1; i < 10; i += 3) {
    buf.push_back(i);
    buf.push_back(i+1);
    buf.push_back(i+2);

    EXPECT_EQ(i+2, buf[0]);
    EXPECT_EQ(i+1, buf[-1]);
    EXPECT_EQ(i, buf[-2]);

    EXPECT_EQ(i+2, buf(i+1));
    EXPECT_EQ(i+1, buf(i));
    EXPECT_EQ(i, buf(i-1));
  }
}

TEST_F(RingBufferTest, multipleElementBuffer_accessAllElements)
{
  RingBuffer<int, 3> buf;
  for (int i = 1; i < 10; ++i) {
    buf.push_back(i);

    EXPECT_EQ(i, buf[0]);
    EXPECT_EQ(std::max(0, i-1), buf[-1]);
    EXPECT_EQ(std::max(0, i-2), buf[-2]);

    EXPECT_EQ(i, buf(i-1));
  }
}

TEST_F(RingBufferTest, multipleElementBuffer_pushbackMultipleElements)
{
  RingBuffer<int, 3> buf;
  for (int i = 1; i < 10; i += 3) {
    buf.push_back({i, i+1, i+2});

    EXPECT_EQ(i+2, buf[0]);
    EXPECT_EQ(i+1, buf[-1]);
    EXPECT_EQ(i, buf[-2]);

    EXPECT_EQ(i+2, buf(i+1));
    EXPECT_EQ(i+1, buf(i));
    EXPECT_EQ(i, buf(i-1));
  }
}
