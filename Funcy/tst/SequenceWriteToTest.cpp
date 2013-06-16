//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/iterator_seq.h"

#include "AbstractVectorIntBasedTest.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

class SequenceWriteToTest : public AbstractVectorIntBasedTest
{ };

TEST_F(SequenceWriteToTest, writeToOutputIteratorOnCollection)
{
  TestVec v;
  make_seq(smallVec).writeTo(std::back_inserter(v));

  EXPECT_EQ(smallVec, v);
}

TEST_F(SequenceWriteToTest, writeToOutputIteratorOnStream)
{
  std::ostringstream ostr;
  make_seq(smallVec).writeTo(std::ostream_iterator<TestVec::value_type>(ostr));

  EXPECT_EQ(vecToString(smallVec), ostr.str());
}

TEST_F(SequenceWriteToTest, writeToOutputStream)
{
  std::ostringstream ostr;
  make_seq(smallVec).writeTo(ostr);

  EXPECT_EQ(vecToString(smallVec), ostr.str());
}

TEST_F(SequenceWriteToTest, writeToOutputStreamWithDelim)
{
  std::ostringstream ostr;
  make_seq(smallVec).writeTo(ostr, ",");

  EXPECT_EQ(vecToString(smallVec, ","), ostr.str());
}

TEST_F(SequenceWriteToTest, writeToCollection)
{
  TestVec v;
  make_seq(smallVec).writeTo(v);

  EXPECT_EQ(smallVec, v);
}
