//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "funcy/generator_seq.h"

#include "SeqTestHelper.h"

#include "gtest/gtest.h"

using namespace SeqTestHelper;

class GeneratorSeqTest : public ::testing::Test {
protected:
  static int increment(int x)
  {
    return x+1;
  }
};

TEST_F(GeneratorSeqTest, counterSeqWithLambda)
{
  GeneratorSeq<int> seq([](int x) { return x+1; });

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, counterSeqWithFunction)
{
  GeneratorSeq<int> seq(increment);

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, counterSeqWithFunctionPointer)
{
  int (*pFunc)(int) = increment;
  GeneratorSeq<int> seq(pFunc);

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, generateSeqWithLambda)
{
  auto seq = generate_seq<int>([](int x) { return x+1; });

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, generateSeqWithFunction)
{
  auto seq = generate_seq<int>(increment);

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, generateSeqWithFunctionPointer)
{
  int (*pFunc)(int) = increment;
  auto seq = generate_seq<int>(pFunc);

  checkIncreasingIntSeq(0, 5, seq, OpenSeq);
}

TEST_F(GeneratorSeqTest, generateSeqWithLambdaAndInitialValue)
{
  auto seq = generate_seq<int>([](int x) { return x+1; }, 10);

  checkIncreasingIntSeq(10, 15, seq, OpenSeq);
}
