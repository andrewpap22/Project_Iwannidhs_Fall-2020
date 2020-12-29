#include "include/Logistic_Regr.hpp"
#include "./source/Logistic_Regr.cpp"

#include <bits/stdc++.h>
using namespace std;

#define features 100
#define learning_rate 0.001
#define iterations 111

int main(void)
{
	/*
	 * Testing dataset we found online.
	*/
	// string train = "./data/train.txt";
	// string test = "./data/test.txt";

	/*
	 * Our own dataset
	*/
	// string train = "./data/Train_Set.csv";
	// string test = "./data/Test_Set.csv";

	/*
	 * Our own (improved) dataset
	*/
	string train = "./data/Train_Set_Improved.csv";
	string test = "./data/Test_Set_Improved.csv";

	LogisticRegression lr(learning_rate, iterations);
	Matrix training_exp = lr.readFromInputFile(train);
	Matrix test_exp = lr.readFromInputFile(test);

	double bias = 1;
	Point4d weights = Point4d(features, 1);
	Point5d optimal_weights = lr.gradientDesent(bias, weights, training_exp);

	lr.testAndPrint(optimal_weights, test_exp);

	return 0;
}