#include "./include/Logistic_Regr.hpp"

#include <bits/stdc++.h>
using namespace std;


int main(void){
	/*
	 * Testing dataset we found online.
	*/
	// string train = "./data/train.txt";
	// string test = "./data/test.txt";

	/*
	 * Our own dataset
	*/
	string train = "./data/250_Train_Set.csv";
	string test = "./data/250_Test_Set.csv";

	LogisticRegression lr(LEARNING_RATE, ITERATIONS);
	Matrix training_exp = lr.readFromInputFile(train);
	Matrix test_exp = lr.readFromInputFile(test);
	double bias = 1;
	Point4d weights = Point4d(NUM_OF_FEATURES, 1);

	// Point5d optimal_weights = lr.gradientDesent(bias, weights, training_exp);
	// lr.testAndPrint(optimal_weights, test_exp);

	// lr.create_new_training_Set(optimal_weights, training_exp);
	
	Point5d optimal_weights = train_model(&lr,&training_exp,bias,BATCH_SIZE);
	test_model(&test_exp, optimal_weights.first, optimal_weights.second);



	return 0;
}

// for (int i = 0; i < NUM_OF_FEATURES; i++){
// 		cout << optimal_weights.second[i]<< nl;
// 	}