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

};

TEST_F(SeqDefTest, defineSequenceBasedOnIteratorSequence)
{
  const std::vector<int> v = {1, 2, 3};
  typedef IteratorSeq<std::vector<int>::const_iterator> VecSeq;

  SeqDef<VecSeq> sdef([&] { return make_seq(v); });

  EXPECT_EQ(v, sdef.newInstance().toVec());
}

TEST_F(SeqDefTest, defineSequenceBasedOnIteratorSequenceWithAssignment)
{
  const std::vector<int> v = {1, 2, 3};
  typedef IteratorSeq<std::vector<int>::const_iterator> VecSeq;

  SeqDef<VecSeq> sdef;
  sdef = [&] { return make_seq(v); };

  EXPECT_EQ(v, sdef.newInstance().toVec());
}
