/*
 * Problem6SumSquareDifference.cpp
 *
 *  Created on: 16.07.2013
 *      Author: schickin
 */

#include "funcy/filter.h"
#include "funcy/map.h"
#include "funcy/range_seq.h"

#include "gtest/gtest.h"

#include <iostream>

namespace {

  int divisorSum(int n)
  {
    return make_range_closed(1,n/2)
        .filter([=](int x) { return n%x == 0; })
        .sum();
  }

  bool isAmicable(int n)
  {
    int d = divisorSum(n);
    return d != n && divisorSum(d) == n;
  }

}

TEST(FuncyEuler, problem21AmicableNumbers)
{
  int sumOfAmicableNumbers =
      make_range_closed(1, 10000).filter([](int x) { return isAmicable(x); }).sum();

  EXPECT_TRUE(isAmicable(220));
  EXPECT_TRUE(isAmicable(284));
  EXPECT_EQ(31626, sumOfAmicableNumbers);
}
