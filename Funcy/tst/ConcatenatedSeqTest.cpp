/*
 * ConcatenatedSeqTest.cpp
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#include "funcy/concat.h"
#include "funcy/iterator_seq.h"
#include "funcy/sequence.h"

#include "SeqTestHelper.h"

#include "gtest/gtest.h"

using namespace SeqTestHelper;

class ConcatenatedSeqTest : public ::testing::Test
{

};

TEST_F(ConcatenatedSeqTest, concatenateTwoSimpleSequences)
{
  auto seq1 = make_seq({1, 2});
  auto seq2 = make_seq({3, 4});

  auto conc = seq1 << seq2;

  checkIncreasingIntSeq(1, 4, conc);
}

//! @todo doesn't work yet because ConcatenatedSequence cannot take copies of the
//! given sequences and thus cannot work with temporary objects.
TEST_F(ConcatenatedSeqTest, concatenateThreeSimpleSequences)
{
  auto seq1 = make_seq({1, 2});
  auto seq2 = make_seq({3, 4});
  auto seq3 = make_seq({5, 6});

  auto conc = seq1 << seq2 << seq3;

  checkIncreasingIntSeq(1, 6, conc);
}
