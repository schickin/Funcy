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

  checkIncreasingSeq(1, 4, conc);
}

TEST_F(ConcatenatedSeqTest, concatenateTwoSequencesOfDifferentTypes)
{
  auto seq1 = make_seq({1, 2});
  auto seq2 = make_seq({3.0, 4.0});

  auto conc = seq1 << seq2;

  static_assert(std::is_same<decltype(conc.cval()), double>::value,
                "common type of concated sequences must be double");

  checkIncreasingSeq(1.0, 4.0, conc);
}

TEST_F(ConcatenatedSeqTest, concatenateThreeSimpleSequences)
{
  auto seq1 = make_seq({1, 2});
  auto seq2 = make_seq({3, 4});
  auto seq3 = make_seq({5, 6});

  auto conc = seq1 << seq2 << seq3;

  checkIncreasingSeq(1, 6, conc);
}

TEST_F(ConcatenatedSeqTest, concatenateThreeUntypedSequences)
{
  Sequence<int> seq1 = make_seq({1, 2});
  Sequence<int> seq2 = make_seq({3, 4});
  Sequence<int> seq3 = make_seq({5, 6});

  Sequence<int> conc = seq1 << seq2 << seq3;

  checkIncreasingSeq(1, 6, conc);
}

TEST_F(ConcatenatedSeqTest, modificationOfOriginalSequenceDoesntModifyConcatenatedSequence)
{
  auto seq1 = make_seq({1, 2});
  auto seq2 = make_seq({3, 4});

  auto conc = seq1 << seq2;

  checkIncreasingSeq(1, 2, seq1);
  checkIncreasingSeq(3, 4, seq2);
  checkIncreasingSeq(1, 4, conc);
}

TEST_F(ConcatenatedSeqTest, modificationOfOriginalUntypedSequenceDoesntModifyConcatenatedSequence)
{
  Sequence<int> seq1 = make_seq({1, 2});
  Sequence<int> seq2 = make_seq({3, 4});

  Sequence<int> conc = seq1 << seq2;

  checkIncreasingSeq(1, 2, seq1);
  checkIncreasingSeq(3, 4, seq2);
  checkIncreasingSeq(1, 4, conc);
}
