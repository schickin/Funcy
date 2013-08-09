/*
 * Problem6SumSquareDifference.cpp
 *
 *  Created on: 16.07.2013
 *      Author: schickin
 */

#include "funcy/map.h"
#include "funcy/range_seq.h"

#include "gtest/gtest.h"

TEST(FuncyEuler, problem6SumSquareDifference)
{
  long long sumOfSquares =
      make_range_closed(1, 100).
      map([](int x) { return x*x; }).
      sum<long long>();
  long long sum =
      make_range_closed(1, 100).
      sum<long long>();
  long long squareOfSum = sum * sum;

  EXPECT_EQ(25164150, squareOfSum - sumOfSquares);
}
