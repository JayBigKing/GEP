//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_SL_GEPTEST_H
#define CPPSOURCEFORLINUX_SL_GEPTEST_H

#include "SL_GEP.h"
#include<boost/smart_ptr.hpp>
class SL_GEP;
class SL_GEPTester
{
public:
    SL_GEPTester() {}
    ~SL_GEPTester() {}
    void testTrainingZeroCostEpo(SL_GEP& sl_gep,const int& times = 5);
    void testTrainingEqaulTimeRes(double(*)(double *, int),const int& numOfFunctionCase, const int & chroNum, const vector<int> &numOfTerminals,
                                  double *constants,const int & numOfConstants,
                                  int* presetFunctions, const int &  numOfPresetFunctions, int *argsLenOfADFs, const int & numOfADFs, const int &  mainPH, int* inputADFHs,
                                  const int & trainTAPairNum = 80, const int &testTAPairNum = 30, const int & trainingEpo = 5000,
                                  bool ifUseSuspendNum = true, double similarValue = 1e-6);


    void testTime();
    void testFile();
    void testDirectory();

    string zeroCostFileNameHead = "resFiles/zeroCost/costEpo";
    string equalTimeResFileNameHead = "/resFiles/equalTimeRes/";
private:
    int testTrainingZeroCostEpoHelp(SL_GEP& sl_gep,const int& whichTime);
    string getFileNameByDateTime(string nameHeadStr, bool useRelativePath = true);
    void zeroCostResSaveToFile(const vector<int> &costEpos, const  vector<bool> &ifDoneToZero, vector<double> lastDistance,double costSec);
    string getCostMinAndSec(double costSec);


    vector<pair<double, double>> testTrainingEqaulTimeResHelp(const uint8_t&, const vector<double> &, const vector<double> &,double(*)(double *, int), const int& numOfFunctionCase, const int & chroNum, const vector<int> &numOfTerminals,
                                                              double *constants, const int & numOfConstants,int* presetFunctions, const int &  numOfPresetFunctions, int *argsLenOfADFs, const int & numOfADFs,
                                                              const int &  mainPH, int* inputADFHs,const int & trainTAPairNum = 80, const int &testTAPairNum = 30, const int & trainingEpo = 5000,
                                                              bool ifUseSuspendNum = true, double similarValue = 1e-6);
    double  EuclideanDis(const ChromosomeRule &cr,const Chromosome &c, double *terms, double *ans ,const int& numOfTerminals,const int &size);

    string getDiretoryNameByDateTime(const string &nameHeadStr , const bool &useRelativePath = true);
    string getFileNameEqualTimeRse(const uint8_t&);
    void eqaulTimeResSaveToFile(const vector<vector<pair<double, double>>>&, const vector<double>&);
};


#endif //CPPSOURCEFORLINUX_SL_GEPTEST_H
