#ifndef LOGISTIC_REGR_H
#define LOGISTIC_REGR_H

#include <bits/stdc++.h>
using namespace std;

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
  LogisticRegression(double, int);
  Matrix readFromInputFile(string);
  Point5d gradientDesent(double, Point4d, Matrix);
  void testAndPrint(Point5d, Matrix);
};

#endif /* LOGISTIC_REGR_H */