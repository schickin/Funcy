/*
 * MemoryTest.cpp
 *
 *  Created on: 14.06.2013
 *      Author: schickin
 */


#include "funcy/memory.h"

#include "funcy/iterator_seq.h"

#include "AbstractVectorIntBasedTest.h"

#include "gtest/gtest.h"

class MemoryTest : public AbstractVectorIntBasedTest
{
protected:

};

TEST_F(MemoryTest, createSequenceWithMemoryForCurrentElement)
{
  auto seq = make_seq({1, 2, 3, 4, 5, 6, 7}).withMemory<1>();

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(i+1, seq.cval());
    EXPECT_EQ(i+1, seq.cval());
    seq.next();
  }
}

TEST_F(MemoryTest, createSequenceWithMemoryForPredecessor)
{
  auto seq = make_seq({1, 2, 3, 4, 5, 6, 7}).withMemory<2>();

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(i+1, seq.cval());
    EXPECT_EQ(i+1, seq[i]);
    EXPECT_EQ(i, seq.cpred());
    if (i > 0) {
        EXPECT_EQ(i, seq[i-1]);
    }
    seq.next();
  }
}

TEST_F(MemoryTest, createSequenceWithMemoryForMultiplePredecessors)
{
  auto seq = make_seq({1, 2, 3, 4, 5, 6, 7}).withMemory<3>();

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(i+1, seq.cval());
    EXPECT_EQ(i+1, seq[i]);
    EXPECT_EQ(i, seq.cpred(1));
    if (i > 0) {
        EXPECT_EQ(i, seq[i-1]);
    }
    EXPECT_EQ(std::max(0, i-1), seq.cpred(2));
    if (i > 1) {
        EXPECT_EQ(i-1, seq[i-2]);
    }
    seq.next();
  }
}
