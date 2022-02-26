//
// Created by JAY on 2022/2/15.
//

#ifndef CPPSOURCEFORLINUX_GEPTESTCASE_H
#define CPPSOURCEFORLINUX_GEPTESTCASE_H
#include <vector>

using namespace std;

class GEPTestCase {
public:
    static void testSL_GEP_vector();
    static void testSL_GEP_save1();
    static void testSL_GEP_load1();
    static void testLoadDataSet1();
    static void testTrainDataset1();

private:
    static double fitFunctionVec(const vector<double>&args);
    static void fitFunctionOutVec(vector<vector<double>>&realTermVec,vector<double>&ansVec);

};


#endif //CPPSOURCEFORLINUX_GEPTESTCASE_H
