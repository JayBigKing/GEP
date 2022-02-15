//
// Created by JAY on 2022/2/15.
//

#ifndef CPPSOURCEFORLINUX_THREADVERSIONTESTCASE_H
#define CPPSOURCEFORLINUX_THREADVERSIONTESTCASE_H
#include "testThread.h"
#include "SL_ChromosomeDecoder_Thread.h"
#include "SL_GEP_Thread.h"
#include <vector>

class ThreadVersionTestCase {
public:
    static void testTestThread1();
    static void testSymbolSetVector();
    static void testSgVector();
    static void testSL_GEP_Thread();

private:
    static double fitFunction(const vector<double>&args);
    static void fitFunctionOut(vector<vector<double>>&realTermVec,vector<double>&ansVec);
};


#endif //CPPSOURCEFORLINUX_THREADVERSIONTESTCASE_H
