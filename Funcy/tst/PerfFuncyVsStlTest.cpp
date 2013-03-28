//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/*
 * PerfFuncyVsStlTest.cpp
 *
 *  Created on: 25.10.2012
 *      Author: schickin
 */

#include "funcy/iterator_seq.h"

#include "gtest/gtest.h"

#include <chrono>
#include <tuple>
#include <string>
#include <memory>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

class DISABLED_PerfFuncyVsStlTest : public ::testing::Test {
protected:
  typedef std::chrono::high_resolution_clock clock_t;
  typedef std::tuple<std::string, std::string, std::string> Data;
  typedef std::shared_ptr<Data> DataPtr;
  typedef std::vector<DataPtr> DataPtrs;

  static const std::size_t numRep = 3;

  static const std::size_t numDataPtrs = 500000;
  DataPtrs dataPtrs_;

  virtual void SetUp()
  {
    fillDataPtrs(numDataPtrs);
  }

  void showDataPtrs()
  {
    std::transform(dataPtrs_.cbegin(), dataPtrs_.cend(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        [] (DataPtr pData) {
      return std::get<0>(*pData) + "," +
          std::get<1>(*pData) + "," +
          std::get<2>(*pData); });
  }

protected:
  void fillDataPtrs(std::size_t numEntries)
  {
    dataPtrs_.clear();
    dataPtrs_.reserve(numEntries);
    std::generate_n(std::back_inserter(dataPtrs_), numEntries, randData);
    std::sort(dataPtrs_.begin(), dataPtrs_.end(),
        [] (const DataPtr& pLeft, const DataPtr& pRight)
        { return *pLeft < *pRight; } );
  }

  static std::string randString(std::size_t len)
  {
    static std::default_random_engine dre;
    static std::uniform_int_distribution<int> di(0, 23);

    std::string result;
    result.reserve(len);
    std::generate_n(std::back_inserter(result), len,
        [] { return 'a' + di(dre); });

    return result;
  }

  static DataPtr randData()
  {
    return std::make_shared<Data>(randString(10), randString(5), randString(10));
  }
};

//TEST_F(PerfFuncyVsStlTest, showData)
//{
//	fillDataPtrs(3);
//	showDataPtrs();
//}


TEST_F(DISABLED_PerfFuncyVsStlTest, extractUniqueInitialsUsingSingleIter)
{
  using namespace std::chrono;

  for (std::size_t rep = 0; rep < numRep; ++rep) {
      fillDataPtrs(numDataPtrs);
      clock_t::time_point startOfExec(clock_t::now());

      std::size_t cnt = std::count_if(dataPtrs_.cbegin(), dataPtrs_.cend(),
          [] (const DataPtr& pData) {
        return std::toupper(std::get<2>(*pData)[0]) == 'A';
      });
      //	initials.erase(std::unique(initials.begin(), initials.end()));

      clock_t::time_point endOfExec(clock_t::now());
      clock_t::duration durationOfExec(endOfExec - startOfExec);

      std::cout << "Number of matches: " << cnt << std::endl;
      std::cout << "Duration (ms): "
          << duration_cast<milliseconds>(durationOfExec).count()
          << std::endl;
  }
}

TEST_F(DISABLED_PerfFuncyVsStlTest, extractUniqueInitialsUsingStlAlgorithms)
{
  using namespace std::chrono;

  for (std::size_t rep = 0; rep < numRep; ++rep) {
      fillDataPtrs(numDataPtrs);
      clock_t::time_point startOfExec(clock_t::now());

      std::vector<char> initials;
      initials.reserve(dataPtrs_.size());
      std::transform(dataPtrs_.cbegin(), dataPtrs_.cend(),
          std::back_inserter(initials),
          [] (const DataPtr& pData) {
        return std::get<2>(*pData)[0];
      }
      );
      std::size_t cnt = std::count_if(initials.cbegin(), initials.cend(),
          [] (const char ch) {
        return std::toupper(ch) == 'A';
      });
      //	initials.erase(std::unique(initials.begin(), initials.end()));

      clock_t::time_point endOfExec(clock_t::now());
      clock_t::duration durationOfExec(endOfExec - startOfExec);

      std::cout << "Number of matches: " << cnt << std::endl;
      std::cout << "Duration (ms): "
          << duration_cast<milliseconds>(durationOfExec).count()
          << std::endl;
  }

  //	std::copy(initials.cbegin(), initials.cend(),
  //			std::ostream_iterator<std::string>(std::cout, "\n"));
}


TEST_F(DISABLED_PerfFuncyVsStlTest, extractUniqueInitialsUsingSequences)
{
  using namespace std::chrono;

  for (std::size_t rep = 0; rep < numRep; ++rep) {
      fillDataPtrs(numDataPtrs);
      clock_t::time_point startOfExec(clock_t::now());

      std::vector<std::string> result;
      result.reserve(dataPtrs_.size());
      std::size_t cnt =
          make_seq(dataPtrs_.cbegin(), dataPtrs_.cend())
          .map([] (const DataPtr& pData) {
            return std::get<2>(*pData)[0];
          })
          .filter([] (const char ch) {
            return std::toupper(ch) == 'A';
          })
          .count();
      //			.unique()
      //			.writeTo(std::back_inserter(result));

      clock_t::time_point endOfExec(clock_t::now());
      clock_t::duration durationOfExec(endOfExec - startOfExec);

      std::cout << "Number of matches: " << cnt << std::endl;
      std::cout << "Duration (ms): "
          << duration_cast<milliseconds>(durationOfExec).count()
          << std::endl;
  }
}
