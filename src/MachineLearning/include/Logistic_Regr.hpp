#ifndef LOGISTIC_REGR_H
#define LOGISTIC_REGR_H
#include "queue.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define NUM_OF_FEATURES 250
#define LEARNING_RATE 0.001
#define ITERATIONS 100
#define NUM_OF_THREADS 5
#define STOCHASTIC_PORTION 1
// #define NUM_OF_BATCHES 10
#define BATCH_SIZE 500
/*
 * So in this directory we have this Logistic Regression Binary Classifier implementation with gradient descent. 
*/

#define nl '\n'

typedef vector<double> Point4d;
typedef pair<double, vector<double>> Point5d;
typedef vector<Point4d> Matrix;
/*
Point4d: Stores a data point having 4 features.
		To store a specific example.
Point5d: Stores a 1d point value and a Point4d.
		To store bias and weights.
Matrix:  Stores multiple Point4d.
		To store training and test examples.
		Although it contains Points4d, their size is
		modified to 5 where 5th position contains class
		label of that data point.
*/

class LogisticRegression
{
private:
  int features;
  int iterations;
  double learning_rate;

public:
  LogisticRegression(){} // default constructor for the ml_test unit testing.
  LogisticRegression(double, int);
  Matrix readFromInputFile(string);
  Point5d gradientDesent(double, Point4d, Matrix);
  void testAndPrint(Point5d, Matrix);
  void create_new_training_Set(Point5d, Matrix);

  /*getters for the constructor unit testing*/
  int GetIterations() {return iterations;}
  double GetLearningRate() {return learning_rate;}
  int GetFeatures() {return features;}
};

typedef struct job{
  
  int id;
  int type;
  int batch_size;
  double bias;
  Point4d *weights;

  Matrix* array;
}job;

class Job_Scheduler{
private:

public:
  int num_of_threads;
  queuestruct* queue_struct;
  pthread_t* threads;
  pthread_mutex_t* dequeue_mutex;

  Job_Scheduler(int);
  void submit_job(job* job);
};


void* ThreadJob(void* );
Point5d train_model(LogisticRegression*, Matrix*, double);    //parallel training
void test_model(Matrix*,double, Point4d);                     //parallel testing

#endif /* LOGISTIC_REGR_H */