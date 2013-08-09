/*
 * RangeSeqTest.cpp
 *
 *  Created on: 16.07.2013
 *      Author: schickin
 */

#include "funcy/range_seq.h"

#include <vector>

#include "gtest/gtest.h"

class RangeSeqTest : public ::testing::Test
{

};

TEST_F(RangeSeqTest, makeRangeOfInts)
{
  auto seq = make_range(1, 5);
  std::vector<int> expected({1, 2, 3, 4});
  EXPECT_EQ(expected, seq.toVec());
}

TEST_F(RangeSeqTest, makeClosedRangeOfInts)
{
  auto seq = make_range_closed(1, 5);
  std::vector<int> expected({1, 2, 3, 4, 5});
  EXPECT_EQ(expected, seq.toVec());
}

TEST_F(RangeSeqTest, makeEmptyRange)
{
  auto seq = make_range(1, 1);
  EXPECT_TRUE(seq.empty());

  auto seq2 = make_range(2, 1);
  EXPECT_TRUE(seq2.empty());
}
