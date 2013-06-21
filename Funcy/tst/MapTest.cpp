//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/iterator_seq.h"
#include "funcy/map.h"

#include "gtest/gtest.h"

#include <vector>
#include <iterator>
#include <algorithm>

class MapTest : public ::testing::Test {
protected:
	typedef std::vector<int> TestVec;

	MapTest() :
		oneToTen_({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
	{ }

	static int multiplyByTwo(int n)
	{
		return 2*n;
	}

	static int divideByTwo(int n)
	{
		return n/2;
	}

	const TestVec oneToTen_;
};

TEST_F(MapTest, doubleElems)
{
	TestVec oneToTenDoubled;
	std::transform(oneToTen_.cbegin(), oneToTen_.cend(),
			std::back_inserter(oneToTenDoubled), multiplyByTwo);

	TestVec result;
	make_seq(oneToTen_).map(multiplyByTwo).writeTo(result);

	EXPECT_EQ(oneToTenDoubled, result);
}

TEST_F(MapTest, doubleThenDivideByTwo)
{
	TestVec result;
	make_seq(oneToTen_)
		.map(multiplyByTwo).map(divideByTwo)
		.writeTo(result);

	EXPECT_EQ(oneToTen_, result);
}

TEST_F(MapTest, convertNumberToString)
{
	auto doubleToString = [] (double d) -> std::string {
		return std::to_string(d);
	};
	typedef std::vector<std::string> StringVec;

	StringVec expected;
	std::transform(oneToTen_.cbegin(), oneToTen_.cend(),
			std::back_inserter(expected), doubleToString);

	StringVec result;
	make_seq(oneToTen_).map(doubleToString).writeTo(result);

	EXPECT_EQ(expected, result);
}
