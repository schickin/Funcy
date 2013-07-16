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

  template <typename Seq>
  void checkPredecessorInSeqOneToFive(Seq& seq)
  {
    for (int i = 0; i < 4; ++i) {
      seq.next();
      EXPECT_EQ(i+1, seq.cpred());
    }
    for (int i = 1; i < 5; ++i) {
      EXPECT_EQ(5-i, seq.cpred(i));
    }
  }

  template <typename Seq>
  void checkIndexAccessInSeqOneToFive(Seq& seq)
  {
    for (int i = 0; i < 5; ++i) {
      EXPECT_EQ(i+1, seq[i]);
    }
    for (int i = 1; i < 4; ++i) {
      seq.next();
    }
    for (int i = 0; i < 5; ++i) {
      EXPECT_EQ(i+1, seq[i]);
    }
  }
};

TEST_F(IteratorSeqTest, emptySequence)
{
  auto seq1 = make_seq(emptyVec);
  EXPECT_TRUE(seq1.empty());
  EXPECT_FALSE(seq1);

  auto seq2 = make_seq(emptyVec.begin(), emptyVec.end());
  EXPECT_TRUE(seq2.empty());
  EXPECT_FALSE(seq2);
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

TEST_F(IteratorSeqTest, predecessorInVectorSequence)
{
  std::vector<int> v({1, 2, 3, 4, 5});
  auto seq = make_seq(v);
  checkPredecessorInSeqOneToFive(seq);
}

TEST_F(IteratorSeqTest, indexAccessInVectorSequence)
{
  std::vector<int> v({1, 2, 3, 4, 5});
  auto seq = make_seq(v);
  checkIndexAccessInSeqOneToFive(seq);
}

TEST_F(IteratorSeqTest, initializerListSequence)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  checkIncreasingSeq(1, 5, seq);
}

TEST_F(IteratorSeqTest, initializerListSequenceWithTypeConversion)
{
  auto seq = make_seq<std::string>({"hello", "world"});
  ::testing::StaticAssertTypeEq<const std::string&, decltype(seq.cval())>();
  EXPECT_EQ(std::string("hello"), seq.cval());
  seq.next();
  EXPECT_EQ("world", seq.cval());
  seq.next();
  EXPECT_TRUE(seq.empty());
}

TEST_F(IteratorSeqTest, initializerListSequenceByConstructor)
{
  InitializerListSeq<int> seq = {1, 2, 3, 4, 5};
  checkIncreasingSeq(1, 5, seq);
}

TEST_F(IteratorSeqTest, copiedInitializerListSequence)
{
  typedef InitializerListSeq<int> InitializerListSeq;
  std::unique_ptr<InitializerListSeq> pSeq;
  {
    InitializerListSeq seq = make_seq({1, 2, 3, 4, 5});
    pSeq = std::unique_ptr<InitializerListSeq>(new InitializerListSeq(seq));
  }

  checkIncreasingSeq(1, 5, *pSeq);
}

TEST_F(IteratorSeqTest, predecessorInInitializerListSequence)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  checkPredecessorInSeqOneToFive(seq);
}

TEST_F(IteratorSeqTest, indexAccessInInitializerListSequence)
{
  auto seq = make_seq({1, 2, 3, 4, 5});
  checkIndexAccessInSeqOneToFive(seq);
}
