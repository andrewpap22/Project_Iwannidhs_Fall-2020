/*
 * Compile with: g++ ML_test.cpp -lgtest -lgtest_main -pthread
 * Run with: ./a.out
*/

#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "../include/Logistic_Regr.hpp"
#include "../include/queue.hpp"

using namespace std;
/*
 * So in this directory we have this Logistic Regression Binary Classifier implementation with gradient descent. 
*/

/* Creating a test fixture to avoid creating the lr object on each and every test. */

struct MachineLearningTest : testing::Test
{
  LogisticRegression* lr;

  MachineLearningTest()
  {
    lr = new LogisticRegression(LEARNING_RATE, ITERATIONS);
  }
};

TEST_F(MachineLearningTest, constructor_test1)
{
  EXPECT_EQ(0.001, lr->GetLearningRate());
}

TEST_F(MachineLearningTest, constructor_test2)
{
  EXPECT_EQ(100, lr->GetIterations());
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
	Point4d weights = Point4d(NUM_OF_FEATURES, 1);

  Matrix training_exp_test = lr->readFromInputFile("../data/250_Test_set.csv");
  double bias_test = 2;
	Point4d weights_test = Point4d(NUM_OF_FEATURES, 1);

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
	Point4d weights = Point4d(NUM_OF_FEATURES, 1);
  Point4d weights_test = Point4d(NUM_OF_FEATURES, 1);

  // act
	Point5d optimal_weights = lr->gradientDesent(bias, weights, training_exp);

  // assert
  ASSERT_EQ(optimal_weights, lr->gradientDesent(bias_test, weights_test, training_exp_test));
}

TEST_F(MachineLearningTest, QueryJob_test1)
{
  // arrange 
  Matrix training_exp_test = lr->readFromInputFile("../data/250_Train_set.csv");
  LogisticRegression lr(LEARNING_RATE, ITERATIONS);

  Point4d weights = Point4d(NUM_OF_FEATURES, 1);
  double learning_rate = LEARNING_RATE;
  int iterations = ITERATIONS;
  int error;
  double bias = 1;
  
  // act
  Job_Scheduler sch(NUM_OF_THREADS);
  if (pthread_mutex_init(sch.dequeue_mutex, NULL) != 0) { 
    printf("\n mutex init has failed\n"); 
    return;
  }
  for (int i = 0; i < NUM_OF_THREADS; i++){
    job* new_job = (job*)malloc(sizeof(job));
    new_job->type = 1;
    new_job->id = i;
    new_job->bias = bias;
    new_job->batch_size = BATCH_SIZE;
    new_job->weights = &weights;
    new_job->array = &training_exp_test;
    sch.submit_job(new_job);
  }

  for(int i=0; i<sch.num_of_threads; i++) {
    error = pthread_create(&sch.threads[i], NULL, ThreadJob, (void*)(&sch));
  }
  for(int j=0; j<sch.num_of_threads; j++) {
    pthread_join(sch.threads[j], NULL);
  }

  // assert
  // cout << "true_negatives: "<< true_negatives <<nl;
  // cout << "false_negatives: "<< true_negatives <<nl;
  // cout << "true_positives: "<< true_negatives <<nl;
  // cout << "false_positives: "<< true_negatives <<nl;
  ASSERT_EQ(error, 0);
}

TEST_F(MachineLearningTest, Train_model_test1)
{
  // arrange 
  Matrix training_exp = lr->readFromInputFile("../data/250_Train_set.csv");
  Matrix training_exp_test = lr->readFromInputFile("../data/250_Test_set.csv");
  double bias = 1;
  double bias_test = 1;
  double error_1,error_2;
  Point4d weights = Point4d(NUM_OF_FEATURES, 1);
  Point4d weights_test = Point4d(NUM_OF_FEATURES, 1);

  // act
  Point5d optimal_weights = lr->gradientDesent(bias, weights, training_exp);
  Point5d optimal_weights_t = train_model(lr,&training_exp,bias);
  //error_1 = findError(optimal_weights.first, optimal_weights.second, training_exp,NUM_OF_FEATURES);
  //error_2 = findError(optimal_weights_t.first, optimal_weights_t.second, training_exp,NUM_OF_FEATURES);

  // cout << "error_optimal_weights: "<< optimal_weights.second[5] <<nl;
  // cout << "error_optimal_weights_t: "<< error_2 <<nl;

  // for (int i = 0; i < NUM_OF_FEATURES; i++){
  //  cout << optimal_weights_t.second[i]<< nl;
  // }

  // assert
  ASSERT_NE(optimal_weights, optimal_weights_t);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}