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
  std::vector<int> v = {1, 2, 3};
  typedef IteratorSeq<std::vector<int>::iterator> VecSeq;

  SeqDef<VecSeq> sdef;
  sdef = [&] { return make_seq(v); };

  VecSeq seq(sdef.newInstance());

  EXPECT_EQ(v, seq.toVec());
}
