/*
 * ParallelTest.cpp
 *
 *  Created on: 17.11.2013
 *      Author: schickin
 */

#include "funcy/filter.h"
#include "funcy/iterator_seq.h"
#include "funcy/map.h"

#include "gtest/gtest.h"

class ParallelTest : public ::testing::Test
{
protected:

};

TEST_F(ParallelTest, simpleAsyncPipeWithMap)
{
  auto s1 = make_seq({1,2,3,4,5})
      .filter([] (int i) { return i%2 == 0; })
      .map([] (int i) { return 2*i; });
  auto s2 = make_seq({1,2,3,4,5})
      .filter([] (int i) { return i%2 == 0; })
      .map([] (int i) { return 2*i; });

  EXPECT_EQ(s1.toVec(), s2.toVec());
}
