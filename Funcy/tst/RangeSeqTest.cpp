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
