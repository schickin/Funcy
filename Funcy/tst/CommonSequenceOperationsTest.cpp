/*
 * CommonSequenceOperationsTest.cpp
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */


#include "funcy/iterator_seq.h"
#include "funcy/impl/sequence_crtp.h"

#include "gtest/gtest.h"

class CommonSequenceOperationsTest : public ::testing::Test
{
protected:
  static const std::vector<int> emptyVec;
};

const std::vector<int> CommonSequenceOperationsTest::emptyVec = {};

TEST_F(CommonSequenceOperationsTest, compareEqualSequences)
{
  auto s1 = make_seq({1, 2, 3});
  auto s2 = make_seq({1, 2, 3});

  ASSERT_EQ(0, s1.compareWith(s2));
}

TEST_F(CommonSequenceOperationsTest, compareEmptySequences)
{
  auto s1 = make_seq(emptyVec);
  auto s2 = make_seq(emptyVec);

  ASSERT_EQ(0, s1.compareWith(s2));
}

TEST_F(CommonSequenceOperationsTest, compareEmptyToNonEmptySequence)
{
  auto s1 = make_seq(emptyVec);
  auto s2 = make_seq({1, 2, 3});

  ASSERT_EQ(-1, s1.compareWith(s2));
  ASSERT_EQ(1, s2.compareWith(s1));
}

TEST_F(CommonSequenceOperationsTest, compareWithSubSequence)
{
  auto s1 = make_seq({1, 2});
  auto s2 = make_seq({1, 2, 3});

  ASSERT_EQ(-1, s1.compareWith(s2));
  ASSERT_EQ(1, s2.compareWith(s1));
}

TEST_F(CommonSequenceOperationsTest, compareSequencesWithDifferentElementsAtEnd)
{
  auto s1 = make_seq({1, 2, 2});
  auto s2 = make_seq({1, 2, 3});

  ASSERT_EQ(-1, s1.compareWith(s2));
  ASSERT_EQ(1, s2.compareWith(s1));
}

TEST_F(CommonSequenceOperationsTest, compareSequencesWithDifferentElementsInTheMiddle)
{
  auto s1 = make_seq({1, 1, 4});
  auto s2 = make_seq({1, 2, 3});

  ASSERT_EQ(-1, s1.compareWith(s2));
  ASSERT_EQ(1, s2.compareWith(s1));
}

TEST_F(CommonSequenceOperationsTest, convertToVector)
{
  auto s = make_seq({1, 2, 3});
  std::vector<int> expected({1, 2, 3});

  ASSERT_EQ(expected, s.toVec());
}
