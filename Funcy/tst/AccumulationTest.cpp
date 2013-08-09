/*
 * AccumulationTest.cpp
 *
 *  Created on: 16.07.2013
 *      Author: schickin
 */


#include "funcy/iterator_seq.h"
#include "funcy/range_seq.h"

#include "gtest/gtest.h"

#include <string>
#include <limits>

class AccumulationTest : public testing::Test
{

};

TEST_F(AccumulationTest, count)
{
  auto seq = make_seq({1, 2, 3});
  EXPECT_EQ(3, seq.count());
}

TEST_F(AccumulationTest, sumOfInts)
{
  auto seq = make_seq({1, 2, 3, 4});
  EXPECT_EQ(10, seq.sum());
}

TEST_F(AccumulationTest, sumOfIntsWithInitialVal10)
{
  auto seq = make_seq({1, 2, 3, 4});
  EXPECT_EQ(10 + 10, seq.sum(10));
}

TEST_F(AccumulationTest, sumOfIntsWithConversion)
{
  int lim = std::numeric_limits<int>::max();
  auto seq = make_range(lim-9, lim);
  long long llim = lim;
  // the explicitly given type prevents an integer overflow
  EXPECT_EQ((llim-10)*9L + (9L*10L) / 2, seq.sum<long long>());
}

TEST_F(AccumulationTest, sumOfStrings)
{
  auto seq = make_seq<std::string>({"hello", "world"});
  EXPECT_EQ("helloworld", seq.sum());
}

TEST_F(AccumulationTest, prodOfInts)
{
  auto seq = make_seq({1, 2, 3, 4});
  EXPECT_EQ(24, seq.prod());
}

TEST_F(AccumulationTest, prodOfIntsWithInitialVal2)
{
  auto seq = make_seq({1, 2, 3, 4});
  EXPECT_EQ(2*24, seq.prod(2));
}

TEST_F(AccumulationTest, countOddNumbers)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  EXPECT_EQ(3, seq.accumulate([] (int& counter, int val) { counter += val % 2; }));
}

TEST_F(AccumulationTest, multiplyOddNumbers)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  EXPECT_EQ(15, seq.accumulate([] (int& counter, int val) { counter *= (val % 2) ? val : 1; },
                               1));
}

TEST_F(AccumulationTest, multiplyOddNumbersWithDifferentReturnType)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  ASSERT_TRUE(14 < std::numeric_limits<long long>::digits10)
    << "This test only makes sense if the calculations don't overflow.";
  EXPECT_EQ(15000000000000L, seq.accumulate<long long>([] (long long& counter, long long val) { counter *= (val % 2) ? val : 1000000L; },
                               1));
}
