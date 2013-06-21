//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/*
 * MultipleOperationsTest.cpp
 *
 *  Created on: 06.10.2012
 *      Author: schickin
 */



#include "funcy/filter.h"
#include "funcy/iterator_seq.h"

#include "gtest/gtest.h"

#include <vector>
#include <iterator>
#include <algorithm>

class MultipleOperationsTest : public ::testing::Test {
protected:
	typedef std::vector<int> TestVec;

	MultipleOperationsTest() :
		oneToTen_({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
	{ }

	static int multiplyByTwo(int n)
	{
		return 2*n;
	}

	static bool isDivisibleByFour(int n)
	{
		return n % 4 == 0;
	}

	const TestVec oneToTen_;
};

TEST_F(MultipleOperationsTest, doubleElemsAndThenFilterDivisibleByFour)
{
	TestVec tmpVec;
	std::transform(oneToTen_.begin(), oneToTen_.end(), std::back_inserter(tmpVec),
			multiplyByTwo);
	TestVec expected;
	std::copy_if(tmpVec.begin(), tmpVec.end(), std::back_inserter(expected),
			isDivisibleByFour);

	TestVec result;
	make_seq(oneToTen_)
		.map(multiplyByTwo)
		.filter(isDivisibleByFour)
		.writeTo(std::back_inserter(result));

	EXPECT_EQ(expected, result);
}
