//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/iterator_seq.h"

#include "gtest/gtest.h"

#include <vector>
#include <iterator>
#include <algorithm>

class FilterTest : public ::testing::Test {
protected:
	typedef std::vector<int> TestVec;

	FilterTest() :
		oneToTen_({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
	{ }

	static bool isEven(int n)
	{
		return n % 2 == 0;
	}

	static bool greaterTen(int n)
	{
		return n > 10;
	}

	const TestVec oneToTen_;
};

TEST_F(FilterTest, filterEvenElements)
{
	TestVec evenInOneToTen;
	std::copy_if(oneToTen_.cbegin(), oneToTen_.cend(),
			std::back_inserter(evenInOneToTen), isEven);

	TestVec result;
	make_seq(oneToTen_).filter(isEven).writeTo(std::back_inserter(result));

	ASSERT_EQ(evenInOneToTen, result);
}

TEST_F(FilterTest, emptyInput)
{
	TestVec empty;
	ASSERT_FALSE(make_seq(empty).filter(isEven));
}

TEST_F(FilterTest, noMatches)
{
	ASSERT_FALSE(make_seq(oneToTen_).filter(greaterTen));
}
