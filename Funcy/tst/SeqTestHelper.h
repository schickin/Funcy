//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "gtest/gtest.h"


namespace SeqTestHelper {

  enum SeqEnd { OpenSeq, ClosedSeq };

  template <typename Seq>
  static void checkSeqEnd(Seq& seq, SeqEnd end = ClosedSeq)
  {
    switch (end) {
    case ClosedSeq:
      EXPECT_TRUE(seq.empty());
      EXPECT_FALSE(seq);
      break;
    case OpenSeq:
      EXPECT_FALSE(seq.empty());
      EXPECT_TRUE(seq);
      break;
    default:
      FAIL();
    }
  }

  template <typename Iter, typename Seq>
  static void checkSeqAgainstRange(Iter from, Iter to, Seq& seq, SeqEnd end = ClosedSeq)
  {
    for (auto it = from; it != to; ++it) {
      EXPECT_FALSE(seq.empty());
      EXPECT_EQ(*it, seq.cval());
      EXPECT_FALSE(seq.empty());
      seq.next();
    }
    checkSeqEnd(seq, end);
  }

  template <typename Vec, typename Seq>
  static void checkSeqAgainstVector(const Vec& expected, Seq& seq)
  {
    checkSeqAgainstRange(expected.begin(), expected.end(), seq);
  }

  template <typename Elem, typename Seq>
  static void checkIncreasingSeq(const Elem& from, const Elem& to, Seq& seq,
                                 SeqEnd end = ClosedSeq)
  {
    for (Elem i = from; i <= to; ++i) {
        EXPECT_FALSE(seq.empty());
        EXPECT_EQ(i, seq.cval());
        EXPECT_FALSE(seq.empty());
        seq.next();
    }
    checkSeqEnd(seq, end);
  }
};
