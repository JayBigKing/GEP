//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_GA_HELPFUNC_H
#define CPPSOURCEFORLINUX_GA_HELPFUNC_H


#include <math.h>
#include <vector>
using namespace std;
//#include "MyGA.h"
//#if CODING_MODE == BINARY_CODING_MODE
int myBinaryPow(int i);
int getTheBits(double val , int low = 0 , int high = 30);
//#endif
int getTheBits(double val , double *array , int len);

int getTheGambleIndex(const double &val, const vector<double> &vec);

double LimitHighandLow(double val,double high , double low);


#endif //CPPSOURCEFORLINUX_GA_HELPFUNC_H
