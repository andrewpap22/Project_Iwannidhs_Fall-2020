#include "../include/Logistic_Regr.hpp"

#include <bits/stdc++.h>
using namespace std;

int flag = 0;
int train_size = 0;
int test_size = 0;

int true_negatives = 0;
int false_negatives = 0;
int true_positives = 0;
int false_positives = 0;


Point5d batch_gd_grad;

LogisticRegression::LogisticRegression(double learning_rate, int iterations)
{
  this->features = NUM_OF_FEATURES;
  this->iterations = iterations;
  this->learning_rate = learning_rate;
}

/*
Read input from the test file whose path is passed as argument
and store it in Matrix.
*/
Matrix LogisticRegression::readFromInputFile(string input_file){
  Matrix examples;
  string line;
  ifstream infile(input_file);
  int num_of_elements = 0;

  while (getline(infile, line))
  {
    if (line.length() == 0)
      continue;
    stringstream ss(line);
    string word;
    vector<double> tmp;
    while (getline(ss, word, ','))
    {
      double value = stod(word);
      tmp.push_back(value);
    }
    num_of_elements++;
    examples.push_back(tmp);
  }
  if(flag==0){
    train_size = num_of_elements;
    flag = 1;
    // cout << train_size << nl;
  }
  else{
    test_size = num_of_elements;
    // cout << test_size << nl;
  }
  return examples;
}

/*
Returns the value correspoinding to logistic sigmoid fuction applied on 
bias, wieghts and input point example. 
*/
double sigmoid(double bias, Point4d weights, Point4d example, int features)
{
  double a = bias;
  for (int i = 0; i < features; i++)
  {
    a += weights[i] * example[i];
  }
  return (double)1.0 / (1.0 + exp(-a));
}

/*
Calculate and return gradient of logistic error function
for given value of bias, weights.
*/
Point5d calculateGradient(double bias, Point4d weights, Matrix examples, int features,int start, int end){
  // cout<<"calculating gradient from "<<start<<" to "<<end<< nl;
  double sum = 0;
  double bias_grad = 0;
  Point4d grad = Point4d(features, 0);
  for (int j = start; j < end; j++){  
  // for (auto example : examples){
    double y = sigmoid(bias, weights, examples[j], features);
    double y_minus_t = y - examples[j][features];
    bias_grad += y_minus_t;
    for (int i = 0; i < features; i++)
    {
      grad[i] += y_minus_t * examples[j][i];
    }
  }
  return {bias_grad, grad};
}

/*
Calculate and return value of error of logistic function which is
negative logarithm of likelihood function. 
*/
double findError(double bias, Point4d weights, Matrix examples, int features)
{
  double error = 0;
  for (auto example : examples)
  {
    if (example[features] == 1)
    {
      error += log(sigmoid(bias, weights, example, features));
    }
    else
    {
      error += log(1 - sigmoid(bias, weights, example, features));
    }
  }
  return -error;
}

/*
Apply gradient descent on weights and bias for given number of 
iterations.
*/
Point5d LogisticRegression::gradientDesent(double bias, Point4d weights, Matrix examples)
{
  cout << "\nTraining model using batch stochastic descent..\n";
  cout<<"STOCHASTIC_PORTION: "<<STOCHASTIC_PORTION<<nl<<nl;
  int iterations = this->iterations;
  int features = this->features;
  double lr = this->learning_rate;

  for (int iter = 0; iter < iterations; iter++)
  {
    // double error = findError(bias, weights, examples, features);
    // cout << "error: " << error << nl;

    Point5d grad = calculateGradient(bias, weights, examples, features, 0, train_size/STOCHASTIC_PORTION);
    bias = bias - lr * grad.first;
    for (int i = 0; i < features; i++)
    {
      weights[i] = weights[i] - lr * grad.second[i];
    }
  }
  return {bias, weights};
}

void LogisticRegression::testAndPrint(Point5d optimal_weights, Matrix testing_exp)
{
  int tp = 0, fp = 0, tn = 0, fn = 0;
  int features = this->features;
  for (auto example : testing_exp)
  {
    double bias = optimal_weights.first;
    // cout << "bias: "<< bias <<nl;
    Point4d weights = optimal_weights.second;
    double sigmoid_ = sigmoid(bias, weights, example, features);
    bool predicted = (sigmoid_ >= 0.5);
    bool actual = example[features];
    if (!predicted && !actual)
      tn++;
    if (!predicted && actual)
      fn++;
    if (predicted && actual)
      tp++;
    if (predicted && !actual)
      fp++;
  }
  cout <<"Model tested.\n";
  cout << nl << "True Positives:  " << true_positives << nl;
  cout << "True Negatives:  " << tn << nl;
  cout << "False Positives: " << fp << nl;
  cout << "False Negatives: " << fn << nl;
  cout << nl;
  cout << "Accuracy:  " << (double)(tp + tn) / (tp + fp + tn + fn) << nl;
  cout << "Precision: " << (double)(tp) / (tp + fp) << nl;
  cout << "Recall:    " << (double)(tp) / (tp + fn) << nl;
  cout << "F1 Score:  " << (2 * (((double)(tp) / (tp + fp)) * ((double)(tp) / (tp + fn))) / (((double)(tp) / (tp + fp)) + ((double)(tp) / (tp + fn)))) << nl;
  cout << nl << nl << "Confusion Matrix:" << nl;
  cout << "\t\t"
       << "Predicted: 0\tPredicted: 1" << nl;
  cout << "Actual: 0\t" << tn << "\t\t" << fp << nl;
  cout << "Actual: 1\t" << fn << "\t\t" << tp << nl;

  /*
   * The F1 Score is the 2*((precision*recall)/(precision+recall)) 
   * What is a good f1 score?
   * That is, a good F1 score means that you have low false positives and low false negatives, so you're correctly
   * identifying real threats and you are not disturbed by false alarms. An F1 score is considered perfect when it's 1,
   * while the model is a total failure when it's 0 .
   */
}
Job_Scheduler::Job_Scheduler(int numofthreads){
  this->num_of_threads = numofthreads;
  this->queue_struct = (queuestruct*)malloc(sizeof(queuestruct));
  this->queue_struct->front=NULL;
  this->queue_struct->end=NULL;
  this->threads = (pthread_t*)malloc(num_of_threads*sizeof(pthread_t));
  this->dequeue_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
}
void Job_Scheduler::submit_job(job* j){
  enqueue(this->queue_struct, j);
}

void* ThreadJob(void* sch){
  Job_Scheduler* scheduler;
  scheduler = (Job_Scheduler*)sch;
  job* j;
    //access queue and take jobs
    while(1){
      pthread_mutex_lock(scheduler->dequeue_mutex);
      if (isempty(scheduler->queue_struct)==1){
        pthread_mutex_unlock(scheduler->dequeue_mutex);
        break;
      }
      //take job and free the node from the queue
      j = scheduler->queue_struct->end->job;
      // cout<<"removing job "<< j->id <<" from the queue\n";
      dequeue(scheduler->queue_struct);
      pthread_mutex_unlock(scheduler->dequeue_mutex);

      //training job
      if(j->type == 0){
        Matrix* train_matrix = j->array;
        //calculate its gradient
        LogisticRegression lr(LEARNING_RATE, ITERATIONS);
        Point5d grad;
        grad = calculateGradient(j->bias, *(j->weights), *train_matrix, NUM_OF_FEATURES, (j->id)*(j->batch_size), (j->id + 1)*(j->batch_size));
        //remove comments to do batch gradient descent with batch_size=train_size (no reason to do it besides debugging, it should return the same results as full gradient descent)
        // grad = calculateGradient(j->bias, *(j->weights), *train_matrix, NUM_OF_FEATURES, 0, train_size);
        for (int i = 0; i < NUM_OF_FEATURES; i++){
          batch_gd_grad.second[i] += grad.second[i];
        }  
        batch_gd_grad.first += grad.first;
      }
      //testing job
      if(j->type == 1){
        // cout<< "thread job id: "<<j->id<<nl;
        Matrix* test_matrix = j->array;
        int thread_test_size = test_size/scheduler->num_of_threads;
        // cout << "test_size: "<< test_size <<nl;
        // cout << "thread_test_size: "<< thread_test_size <<nl;
        double bias = j->bias;
        // cout << "bias: "<< bias <<nl;
        Point4d weights = *(j->weights);

        //fill the job matrix
        for (int i = (j->id)*(thread_test_size); i < (j->id + 1)*(thread_test_size); i++){       
          double sigmoid_ = sigmoid(bias, weights, (*test_matrix)[i], NUM_OF_FEATURES);
          bool predicted = (sigmoid_ >= 0.5);
          bool actual = (*test_matrix)[i][NUM_OF_FEATURES];
          if (!predicted && !actual)
            true_negatives++;
          if (!predicted && actual)
            false_negatives++;
          if (predicted && actual)
            true_positives++;
          if (predicted && !actual)
            false_positives++;
        }
      }
    }
    // cout <<"thread exiting\n";
    pthread_exit(NULL);
    return NULL;
}


Point5d train_model(LogisticRegression* lr, Matrix* train_set, double bias){
  cout << "\nTraining model using batch gradient descent..\n";
 	cout<<"NUM_OF_THREADS: "<<NUM_OF_THREADS<<nl;
  cout<<"BATCH_SIZE: "<<BATCH_SIZE<<nl<<nl;
  Point4d weights = Point4d(NUM_OF_FEATURES, 1);
  double learning_rate = LEARNING_RATE;
  int iterations = ITERATIONS;
  double error;
  
  //create scheduler
  cout << "Creating scheduler handling "<< NUM_OF_THREADS <<" threads..\n";
  Job_Scheduler sch(NUM_OF_THREADS);
  cout << "Scheduler created.\n\n";
  if (pthread_mutex_init(sch.dequeue_mutex, NULL) != 0) { 
    printf("\n mutex init has failed\n"); 
    return {bias, weights};
  } 
  int total_batches = train_size/BATCH_SIZE;
  // cout <<  <<nl;
  // cout << batch_size <<nl<<nl;
  cout <<"train size:"<< train_size <<nl;
  cout <<"batch size:"<< BATCH_SIZE <<nl;
  cout <<"total batches:"<< total_batches <<nl<<nl;

  //initialize batch_gd_grad
  batch_gd_grad.second = Point4d(NUM_OF_FEATURES,0);
  batch_gd_grad.first = 0;

  //batch gradient descent
  for (int iteration = 0; iteration < iterations; iteration++){ 
    // cout << "\niteration "<< iteration+1<< nl;
    //set batch_gd_grad to 0
    for (int i = 0; i < NUM_OF_FEATURES; i++){
      batch_gd_grad.second[i] = 0;
    }
    batch_gd_grad.first = 0;
    //add batch gradient calculation jobs in queue
    // cout<< "adding jobs to queue"<<nl;
    for (int i = 0; i < total_batches; i++){
      job* new_job = (job*)malloc(sizeof(job));
      new_job->type = 0;
      new_job->id = i;
      new_job->batch_size = BATCH_SIZE;
      new_job->bias = bias;
      new_job->weights = &weights;
      new_job->array = train_set;
      sch.submit_job(new_job);
    }
    // printqueue(sch.queue_struct);
    // create threads to calculate the batch gradients
    // cout<< "executing jobs jobs"<<nl;
    for(int i=0; i<sch.num_of_threads; i++) {
      // cout << "create thread "<< i <<nl;
      pthread_create(&sch.threads[i], NULL, ThreadJob, (void*)(&sch));
    }
    // join the threads
    for(int j=0; j<sch.num_of_threads; j++) {
      pthread_join(sch.threads[j], NULL);
    }
    // cout<< "calculating average gradient"<<nl;
    //calculate average gradient of batch gradients
    for (int i = 0; i < NUM_OF_FEATURES; i++){
      batch_gd_grad.second[i] /= total_batches;
    }
    batch_gd_grad.first /= total_batches;
    // calculate new weights and bias
    for (int i = 0; i < NUM_OF_FEATURES; i++){
      weights[i] -= learning_rate * batch_gd_grad.second[i];
    }
    bias = bias - learning_rate * batch_gd_grad.first;
    // error = findError(bias, weights, *train_set, NUM_OF_FEATURES);
    // cout << "error: " << error << nl << nl;
  }
  cout <<"Model trained.\n\n";
  //return optimal weights and bias
  return {bias, weights};
}

void test_model(Matrix* test_set, double bias,Point4d optimal_weights){
  cout <<"Testing model in parallel..\n";
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
    new_job->weights = &optimal_weights;
    new_job->array = test_set;
    sch.submit_job(new_job);
  }
    // printqueue(sch.queue_struct);
    // create threads to calculate the batch gradients
  for(int i=0; i<sch.num_of_threads; i++) {
    pthread_create(&sch.threads[i], NULL, ThreadJob, (void*)(&sch));
  }
    // join the threads
  for(int j=0; j<sch.num_of_threads; j++) {
    pthread_join(sch.threads[j], NULL);
  }
  cout <<"Model tested.\n";
  cout << nl << "True Positives:  " << true_positives << nl;
  cout << "True Negatives:  " << true_negatives << nl;
  cout << "False Positives: " << false_positives << nl;
  cout << "False Negatives: " << false_negatives << nl;
  cout << nl;
  cout << "Accuracy:  " << (double)(true_positives + true_negatives) / (true_positives + false_positives + true_negatives + false_negatives) << nl;
  cout << "Precision: " << (double)(true_positives) / (true_positives + false_positives) << nl;
  cout << "Recall:    " << (double)(true_positives) / (true_positives + false_negatives) << nl;
  cout << "F1 Score:  " << (2 * (((double)(true_positives) / (true_positives + false_positives)) * ((double)(true_positives) / (true_positives + false_negatives))) / (((double)(true_positives) / (true_positives + false_positives)) + ((double)(true_positives) / (true_positives + false_negatives)))) << nl;
  cout << nl << nl << "Confusion Matrix:" << nl;
  cout << "\t\t"
       << "Predicted: 0\tPredicted: 1" << nl;
  cout << "Actual: 0\t" << true_negatives << "\t\t" << false_positives << nl;
  cout << "Actual: 1\t" << false_negatives << "\t\t" << true_positives << nl;

}

// void LogisticRegression::create_new_training_Set(Point5d optimal_weights, Matrix training_set){
//   double threshold = 0.5;
//   int tp = 0, fp = 0, tn = 0, fn = 0;
//   int features = this->features;
//   while (threshold >= 0){
//     for (auto example : training_set){
//       double bias = optimal_weights.first;
//       Point4d weights = optimal_weights.second;
//       double sigmoid_ = sigmoid(bias, weights, example, features);
//       if((sigmoid_ <= threshold) || (sigmoid_ >= 1 - threshold)){
//         //add to set
//         // cout << sigmoid_ << nl;
//       }
//     }
//     cout << nl;
//     threshold -= 0.01;
//   }
// }