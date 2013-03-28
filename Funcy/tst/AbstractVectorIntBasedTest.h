//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ABSTRACTVECTORINTBASEDTEST_H_
#define ABSTRACTVECTORINTBASEDTEST_H_

#include "gtest/gtest.h"

#include <algorithm>
#include <sstream>

class AbstractVectorIntBasedTest : public ::testing::Test
{
protected:
  typedef std::vector<int> TestVec;

  AbstractVectorIntBasedTest() :
    smallVec({1, 1, 2, 3, 5, 8}),
    oneElemVec({10}),
    emptyVec()
  { }

  const TestVec smallVec;
  const TestVec oneElemVec;
  const TestVec emptyVec;

  static std::string vecToString(const TestVec& vec, const char* delim = "")
  {
    std::ostringstream ostr;
    std::copy(vec.begin(), vec.end(),
        std::ostream_iterator<TestVec::value_type>(ostr, delim));
    return ostr.str();
  }
};

#endif /* ABSTRACTVECTORINTBASEDTEST_H_ */
