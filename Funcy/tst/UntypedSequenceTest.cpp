/*
 * UntypedSequenceTest.cpp
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */


#include "funcy/sequence.h"

#include "gtest/gtest.h"


class UntypedSequenceTest : public ::testing::Test
{

};

TEST_F(UntypedSequenceTest, DISABLED_createWithoutInitialization)
{
  Sequence seq;
  EXPECT_FALSE(seq);
};
