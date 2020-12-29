/*
 * Compile with: g++ exampleTest.cpp -lgtest -lgtest_main -pthread
*/

#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

// example test case (always true)
TEST(TestName, Subtest_1)
{
  ASSERT_TRUE(1 == 1);
}

/*
   * the assert_true expects the result to be true, so if it is false, the test will not pass. 
   * but we could use assert_false as well to expect false output and then if we had a false statement the test would've passed. (see below)
*/

TEST(TestName, Subtest_2)
{
  ASSERT_FALSE(1 == 2);
}

/*
 * Any Unit test must consist of 3 things:
 * 1. Arrange
 * 2. Act
 * 3. Assert
 * 1. arrange everything required to run the test.
 * 2. run the test
 * 3. verify the output
*/

TEST(TestName2, increment_by_5)
{
  // Arrange
  int value = 100;
  int increment = 5;

  // Act
  value += increment;

  // Assert
  ASSERT_EQ(value, 105); // value must equal 105.
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}