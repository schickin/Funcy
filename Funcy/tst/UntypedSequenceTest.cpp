/*
 * UntypedSequenceTest.cpp
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#include "funcy/iterator_seq.h"
#include "funcy/sequence.h"

#include "gtest/gtest.h"


class UntypedSequenceTest : public ::testing::Test
{
protected:

  template <typename ElemType>
  void checkOneElementSequence(const ElemType& expected, Sequence<ElemType>& seq)
  {
    EXPECT_TRUE(seq.initialized());

    EXPECT_FALSE(seq.empty());
    EXPECT_EQ(expected, seq.cval());
    seq.next();
    EXPECT_TRUE(seq.empty());
  }
};

TEST_F(UntypedSequenceTest, createWithoutInitialization)
{
  Sequence<int> seq;
  EXPECT_FALSE(seq.initialized());
};

TEST_F(UntypedSequenceTest, createFromOtherSequence)
{
  auto otherSeq = make_seq({1});

  Sequence<int> seq(otherSeq);

  checkOneElementSequence(1, seq);
};

TEST_F(UntypedSequenceTest, createFromOtherSequenceWithElemTypeConversion)
{
  auto otherSeq = make_seq({2.5});

  Sequence<int> seq(otherSeq);

  checkOneElementSequence(2, seq);
};

TEST_F(UntypedSequenceTest, defaultCopyConstructor)
{
  auto otherSeq = make_seq({1});

  Sequence<int> seq(otherSeq);
  Sequence<int> copiedSeq(seq);

  checkOneElementSequence(1, copiedSeq);
};

TEST_F(UntypedSequenceTest, defaultAssignmentOperator)
{
  auto otherSeq = make_seq({'a'});

  Sequence<char> seq(otherSeq);
  Sequence<char> copiedSeq;
  EXPECT_FALSE(copiedSeq.initialized());

  copiedSeq = seq;

  checkOneElementSequence('a', copiedSeq);
};

TEST_F(UntypedSequenceTest, assignmentFromOtherSequence)
{
  auto otherSeq = make_seq({10});

  Sequence<int> seq;
  EXPECT_FALSE(seq.initialized());

  seq = otherSeq;

  checkOneElementSequence(10, seq);
};
