/*
 * Compile with: g++ ML_test.cpp -lgtest -lgtest_main -pthread
 * Run with: ./a.out
*/

#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "../include/Logistic_Regr.hpp"
#include "../source/Logistic_Regr.cpp"

using namespace std;

#define features 250
#define learning_rate 0.001
#define iterations 222

/* Creating a test fixture to avoid creating the lr object on each and every test. */

struct MachineLearningTest : testing::Test
{
  LogisticRegression* lr;

  MachineLearningTest()
  {
    lr = new LogisticRegression(learning_rate, iterations);
  }
};

TEST_F(MachineLearningTest, constructor_test1)
{
  EXPECT_EQ(0.001, lr->GetLearningRate());
}

TEST_F(MachineLearningTest, constructor_test2)
{
  EXPECT_EQ(222, lr->GetIterations());
}

TEST_F(MachineLearningTest, constructor_test3)
{
  EXPECT_EQ(250, lr->GetFeatures());
}

TEST_F(MachineLearningTest, read_from_file_test1)
{
  // arrange
  string train = "../data/250_Train_set.csv";

  // act
  Matrix training_exp = lr->readFromInputFile(train);

  // assert
  ASSERT_EQ(training_exp, lr->readFromInputFile("../data/250_Train_set.csv"));
}

TEST_F(MachineLearningTest, read_from_file_test2)
{
  // arrange
	string test = "../data/250_Test_set.csv";

  // act
	Matrix test_exp = lr->readFromInputFile(test);

  // assert
  ASSERT_EQ(test_exp, lr->readFromInputFile("../data/250_Test_set.csv"));
}

TEST_F(MachineLearningTest, gradientDescent_test)
{
  // arrange 
  Matrix training_exp = lr->readFromInputFile("../data/250_Train_set.csv");
  double bias = 1;
	Point4d weights = Point4d(features, 1);

  Matrix training_exp_test = lr->readFromInputFile("../data/250_Test_set.csv");
  double bias_test = 2;
	Point4d weights_test = Point4d(features, 1);

  // act
	Point5d optimal_weights = lr->gradientDesent(bias, weights, training_exp);

  // assert
  ASSERT_NE(optimal_weights, lr->gradientDesent(bias_test, weights_test, training_exp_test));
}

TEST_F(MachineLearningTest, gradientDescent_test2)
{
  // arrange 
  Matrix training_exp = lr->readFromInputFile("../data/250_Train_set.csv");
  Matrix training_exp_test = lr->readFromInputFile("../data/250_Test_set.csv");
  double bias = 1;
  double bias_test = 1;
	Point4d weights = Point4d(features, 1);
  Point4d weights_test = Point4d(features, 1);

  // act
	Point5d optimal_weights = lr->gradientDesent(bias, weights, training_exp);

  // assert
  ASSERT_EQ(optimal_weights, lr->gradientDesent(bias_test, weights_test, training_exp_test));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}