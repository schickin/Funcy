//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/iterator_seq.h"

#include "AbstractVectorIntBasedTest.h"

#include <iterator>
#include <memory>
#include <vector>

class IteratorSeqTest : public AbstractVectorIntBasedTest
{
protected:
  typedef IteratorSeq<TestVec::const_iterator> TestVecSeq;

  template <typename Iter>
  void checkSeqAgainstRange(Iter from, Iter to, IteratorSeq<Iter>& seq)
  {
    for (auto it = from; it != to; ++it) {
      ASSERT_FALSE(seq.empty());
      ASSERT_EQ(*it, seq.cval());
      ASSERT_FALSE(seq.empty());
      seq.next();
    }
    ASSERT_TRUE(seq.empty());
  }

  template <typename Iter>
  void checkSeqAgainstVector(const TestVec& expected, IteratorSeq<Iter>& seq)
  {
    checkSeqAgainstRange(expected.begin(), expected.end(), seq);
  }

  template <typename Seq>
  void checkIncreasingIntSeq(int from, int to, Seq& seq)
  {
    for (int i = from; i <= to; ++i) {
        ASSERT_FALSE(seq.empty());
        ASSERT_EQ(i, seq.cval());
        ASSERT_FALSE(seq.empty());
        seq.next();
    }
    ASSERT_TRUE(seq.empty());
  }
};

TEST_F(IteratorSeqTest, emptySequence)
{
  auto seq1 = make_seq(emptyVec);
  ASSERT_TRUE(seq1.empty());

  auto seq2 = make_seq(emptyVec.begin(), emptyVec.end());
  ASSERT_TRUE(seq2.empty());
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
