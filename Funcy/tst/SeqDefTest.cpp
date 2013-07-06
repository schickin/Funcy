/*
 * SeqDefTest.cpp
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */

#include "funcy/seq_def.h"
#include "funcy/sequence.h"

#include "funcy/concat.h"
#include "funcy/iterator_seq.h"

#include "gtest/gtest.h"

class SeqDefTest : public ::testing::Test
{
protected:
  typedef IteratorSeq<std::vector<int>::const_iterator> VecSeq;
  static const std::vector<int> oneTwoThree;
};

const std::vector<int> SeqDefTest::oneTwoThree({1, 2, 3});

TEST_F(SeqDefTest, defineTypedSequenceFromDefiningFunction)
{
  TypedSeqDef<VecSeq> sdef([&] { return make_seq(oneTwoThree); });

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineTypedSequenceWithAssignmentOfDefiningFunction)
{
  TypedSeqDef<VecSeq> sdef;
  sdef = [&] { return make_seq(oneTwoThree); };

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineTypedSequenceUsingFactoryFunction)
{
  auto sdef = def_seq([&] { return make_seq(oneTwoThree); });

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, copyOfTypedSequence)
{
  TypedSeqDef<VecSeq> sdef;
  {
    auto innerSDef = def_seq([&] { return make_seq(oneTwoThree); });
    sdef = innerSDef;
  }

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineSequenceFromDefiningFunction)
{
  SeqDef<int> sdef([&] { return make_seq(oneTwoThree); });

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineSequenceWithAssignmentOfDefiningFunction)
{
  SeqDef<int> sdef;
  sdef = [&] { return make_seq(oneTwoThree); };

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, copyOfTypedSequenceToUntypedSequence)
{
  TypedSeqDef<VecSeq> innerSDef = def_seq([&] { return make_seq(oneTwoThree); });
  SeqDef<int> sdef(innerSDef);

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, assignmentOfTypedSequenceToUntypedSequence)
{
  SeqDef<int> sdef;
  {
    auto innerSDef = def_seq([&] { return make_seq(oneTwoThree); });
    sdef = innerSDef;
  }

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, assignToUntypedSequence)
{
  auto sdef = def_seq([&] { return make_seq(oneTwoThree); });

  Sequence<int> seq;

  for (int i = 0; i < 2; ++i)
  {
    seq = sdef;
    EXPECT_EQ(oneTwoThree, seq.toVec());
  }
}

TEST_F(SeqDefTest, recursiveSequenceDef)
{
  SeqDef<int> sdef;
  sdef = [&] { return make_seq({1}) << sdef.lazy(); };

  Sequence<int> seq = sdef.newInstance();
  for (int i = 0; i < 5; ++i)
  {
    EXPECT_FALSE(seq.empty());
    EXPECT_EQ(1, seq.cval());
    seq.next();
  }
}
