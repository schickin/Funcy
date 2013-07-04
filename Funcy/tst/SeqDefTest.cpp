/*
 * SeqDefTest.cpp
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */

#include "funcy/seq_def.h"

#include "funcy/iterator_seq.h"

#include "gtest/gtest.h"

class SeqDefTest : public ::testing::Test
{
protected:
  typedef IteratorSeq<std::vector<int>::const_iterator> VecSeq;
  static const std::vector<int> oneTwoThree;
};

const std::vector<int> SeqDefTest::oneTwoThree({1, 2, 3});

TEST_F(SeqDefTest, defineSequenceBasedOnIteratorSequence)
{
  SeqDef<VecSeq> sdef([&] { return make_seq(oneTwoThree); });

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineSequenceBasedOnIteratorSequenceWithAssignment)
{
  SeqDef<VecSeq> sdef;
  sdef = [&] { return make_seq(oneTwoThree); };

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineSequenceUsingFactoryFunction)
{
  auto sdef = def_seq([&] { return make_seq(oneTwoThree); });

  EXPECT_EQ(oneTwoThree, sdef.newInstance().toVec());
}
