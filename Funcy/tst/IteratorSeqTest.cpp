//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/iterator_seq.h"

#include "AbstractVectorIntBasedTest.h"
#include "SeqTestHelper.h"

#include <iterator>
#include <memory>
#include <vector>

using namespace SeqTestHelper;


class IteratorSeqTest : public AbstractVectorIntBasedTest
{
protected:
  typedef IteratorSeq<TestVec::const_iterator> TestVecSeq;
};

TEST_F(IteratorSeqTest, emptySequence)
{
  auto seq1 = make_seq(emptyVec);
  ASSERT_TRUE(seq1.empty());
  ASSERT_FALSE(seq1);

  auto seq2 = make_seq(emptyVec.begin(), emptyVec.end());
  ASSERT_TRUE(seq2.empty());
  ASSERT_FALSE(seq2);
}

TEST_F(IteratorSeqTest, oneElementSequence)
{
  auto seq = make_seq(oneElemVec);
  checkSeqAgainstVector(oneElemVec, seq);
}

TEST_F(IteratorSeqTest, arbitraryVectorSequence)
{
  auto seq = make_seq(smallVec);
  checkSeqAgainstVector(smallVec, seq);
}

TEST_F(IteratorSeqTest, reverseVectorSequence)
{
  auto seq = make_seq(smallVec.rbegin(), smallVec.rend());
  checkSeqAgainstRange(smallVec.rbegin(), smallVec.rend(), seq);
}

TEST_F(IteratorSeqTest, copiedVectorSequence)
{
  std::unique_ptr<TestVecSeq> pSeq;
  {
    auto seq = make_seq(smallVec);
    pSeq = std::unique_ptr<TestVecSeq>(new TestVecSeq(seq));
  }
  checkSeqAgainstVector(smallVec, *pSeq);
}

TEST_F(IteratorSeqTest, initializerListSequence)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  checkIncreasingIntSeq(1, 5, seq);
}

TEST_F(IteratorSeqTest, initializerListSequenceByConstructor)
{
  InitializerListSeq<int> seq = {1, 2, 3, 4, 5};
  checkIncreasingIntSeq(1, 5, seq);
}

TEST_F(IteratorSeqTest, copiedInitializerListSequence)
{
  typedef InitializerListSeq<int> InitializerListSeq;
  std::unique_ptr<InitializerListSeq> pSeq;
  {
    InitializerListSeq seq = make_seq({1, 2, 3, 4, 5});
    pSeq = std::unique_ptr<InitializerListSeq>(new InitializerListSeq(seq));
  }

  checkIncreasingIntSeq(1, 5, *pSeq);
}
