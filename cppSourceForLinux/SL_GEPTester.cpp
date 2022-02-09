//
// Created by JAY on 2022/2/9.
//

#include "SL_GEPTester.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include<boost/filesystem.hpp>
using namespace std;
const int startYear = 1900;
const int startMon = 1;
int SL_GEPTester::testTrainingZeroCostEpoHelp(SL_GEP& sl_gep, const int& whichTime) {
    sl_gep.initChromosomes();
    uint64_t count = 0;
    for (; sl_gep.shouldContiue();) {

        sl_gep.inheritanceProcess();
        if (sl_gep.minDistance < 1e-6)
            return sl_gep.epoch;
        if (count % 100 == 0) {
            printf("%d time,   epoch %d:%f\r\n", whichTime, sl_gep.epoch, sl_gep.minDistance);		//602  (>2200)
        }
        count++;
    }

    return sl_gep.needEpoch;

}

void SL_GEPTester::testTrainingZeroCostEpo(SL_GEP& sl_gep, const int& times) {
    vector<int> costEpos;
    vector<bool> ifDoneToZero;
    vector<double> lastDistance;
    double costSec;
    clock_t startClock, endClock;
    startClock = clock();
    for (int i = 0; i < times; i++) {
        int nowCostEpo = testTrainingZeroCostEpoHelp(sl_gep, i);
        costEpos.push_back(nowCostEpo);
        ifDoneToZero.push_back(sl_gep.minDistance < 1e-6);
        lastDistance.push_back(sl_gep.minDistance);
        if(ifDoneToZero[i])
            printf("time  %d need epo : %d\r\n", i, costEpos[i]);
        else
            printf("time  %d need epo more than : %d\r\n", i, costEpos[i]);
        printf("------------------------------------------------------------------\r\n");
        sl_gep.reInit();
    }
    endClock = clock();
    costSec = (double)(endClock - startClock) / CLOCKS_PER_SEC;
    //printf("------------------------------------------------------------------\r\n");
    //printf("------------------------------------------------------------------\r\n");
    //printf("------------------------------------------------------------------\r\n");
    //for (int i = 0; i < times; ++i) {
    //	printf("time  %d need epo : %d\r\n", i, costEpos[i]);
    //}
    printf("Cost total time is %s\r\n", getCostMinAndSec(costSec).c_str());
    zeroCostResSaveToFile(costEpos, ifDoneToZero, lastDistance, costSec);
}

void SL_GEPTester::zeroCostResSaveToFile(const vector<int> &costEpos, const  vector<bool> &ifDoneToZero, vector<double> lastDistance, double costSec) {
    ofstream outfile;
    string theFileName = getFileNameByDateTime(zeroCostFileNameHead);
    outfile.open(theFileName);
    for (int i = 0; i < costEpos.size(); ++i) {
        outfile << "time " << i << " need epo : " << costEpos[i] << "             ";
        outfile << lastDistance[i] << "             ";
        if (ifDoneToZero[i])
            outfile << "Done";
        else
            outfile << "didn`t Done";
        outfile << endl;
    }
    outfile <<"cost time : " <<getCostMinAndSec(costSec) << endl;
    outfile.close();
}

void SL_GEPTester::testTime() {
    time_t now = time(NULL);
    tm *nowTm = localtime(&now);
    printf("%d,%d,%d,%d,%d,%d\r\n", nowTm->tm_year + startYear, nowTm->tm_mon + startMon, nowTm->tm_mday,
           nowTm->tm_hour, nowTm->tm_min, nowTm->tm_sec);
}
string SL_GEPTester::getFileNameByDateTime(string nameHeadStr, bool useRelativePath) {
    time_t now = time(NULL);
    tm *nowTm = localtime(&now);
    if(useRelativePath)
        return "./"+ nameHeadStr + "_" + to_string(nowTm->tm_year + startYear) + "_" + to_string(nowTm->tm_mon + startMon) + "_" +
               to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec) + ".txt";
    else
        return  nameHeadStr + "_" + to_string(nowTm->tm_year + startYear) + "_" + to_string(nowTm->tm_mon + startMon) + "_" +
                to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec) + ".txt";

}
void SL_GEPTester::testFile() {
    ofstream outfile;
    string theFileName = getFileNameByDateTime(zeroCostFileNameHead);
    outfile.open(theFileName);
    vector<int> costEpos;
    costEpos.push_back(213);
    costEpos.push_back(21213);
    for (int i = 0; i < costEpos.size(); ++i) {
        outfile << "time " << i << " need epo : " << costEpos[i] << endl;
    }

    outfile.close();
}
string SL_GEPTester::getCostMinAndSec(double costSec) {
    long integerSec = (long)costSec;
    double remainSec = costSec - (double)integerSec;
    long theMin = integerSec / 60;
    double theSec = (double)(integerSec % 60);
    theSec += remainSec;
    string theCostMinAndSec = to_string(theMin) + " min " + to_string(theSec) + "s";
    return theCostMinAndSec;



}


double  SL_GEPTester::EuclideanDis(const ChromosomeRule &cr,const Chromosome &c, double *terms, double *ans , const int& numOfTerminals, const int &size) {
    //double count = 0.0;
    //cdPtr->setChromosome(const_cast<Chromosome&>(c));
    //for (int i = 0; i < termAnsPairNum; ++i)
    //	count += pow((cdPtr->decode(realTermSet[i]) - ansSet[i]), 2);
    //return  sqrt(count);

    SL_ChromosomeDecoder slCD;
    slCD.setChromosomeRule(const_cast<ChromosomeRule&>(cr));
    slCD.setChromosome(const_cast<Chromosome&>(c));
    long double count = 0.0;

    for (int i = 0,k = 0; i < size; ++i,k+= numOfTerminals) {
        count += pow((slCD.decode(&terms[k]) - ans[i]), 2);
    }

    return sqrt(count);




}

vector<pair<double, double>> SL_GEPTester::testTrainingEqaulTimeResHelp(const uint8_t &wrsc, const vector<double> &startReals, const vector<double> &nowSteps, double(*functionOut)(double *, int),
                                                                        const int& numOfFunctionCase, const int & chroNum, const vector<int> &numOfTerminals,double *constants, const int & numOfConstants, int* presetFunctions,
                                                                        const int &  numOfPresetFunctions, int *argsLenOfADFs, const int & numOfADFs,const int &  mainPH, int* inputADFHs, const int & trainTAPairNum ,
                                                                        const int &testTAPairNum , const int & trainingEpo ,bool ifUseSuspendNum , double similarValue ) {


    vector<pair<double, double>>trainAndTestDisVec;
    boost::shared_array<double> trainAns(new double[trainTAPairNum]);
    boost::shared_array<double> testAns(new double[testTAPairNum]);
    //printf("------------------------------------------------------------------------------------------\r\n");
    printf("-----------------------------------%s------------------------------------\r\n", getFileNameEqualTimeRse(wrsc).c_str());
    for (int i = 0; i < numOfFunctionCase; ++i) {
        //vector<double>trainTerms(trainTAPairNum *  numOfTerminals[i]);
        //vector<double>testTerms(testTAPairNum * numOfTerminals[i]);
        printf("%d^^^^^^\r\n", i);
        pair<double, double>trainAndTestDis;
        boost::shared_array<double> trainTerms(new double[trainTAPairNum *  numOfTerminals[i]]);
        boost::shared_array<double> testTerms(new double[testTAPairNum * numOfTerminals[i]]);
        double startReal = startReals[i];
        double nowStep = nowSteps[i];
        double realPtr = startReal;

        //double trainingDis;
        //double testDis;

        for (int j = 0; j < trainTAPairNum * numOfTerminals[i]; ++j) {
            trainTerms[j] = realPtr;
            realPtr += nowStep;
        }

        for (int j = 0; j < testTAPairNum * numOfTerminals[i]; ++j) {
            testTerms[j] = realPtr;
            realPtr += nowStep;
        }

        for (int j = 0, k = 0; j < trainTAPairNum; ++j, k += numOfTerminals[i])
            trainAns[j] = functionOut(&trainTerms[k], i);

        for (int j = 0, k = 0; j < testTAPairNum; ++j, k += numOfTerminals[i])
            testAns[j] = functionOut(&testTerms[k], i);

        SL_GEP slgep(chroNum, trainTerms.get(), trainAns.get(), trainTAPairNum, trainingEpo, numOfTerminals[i],
                     presetFunctions, numOfPresetFunctions, argsLenOfADFs,
                     numOfADFs, mainPH, inputADFHs);

        slgep.whichRenewSymbolCountWay = wrsc;

        pair<Chromosome, ChromosomeRule> thePair = slgep.train();

        trainAndTestDis.first = slgep.minDistance;

        trainAndTestDis.second = EuclideanDis(thePair.second, thePair.first, testTerms.get(), testAns.get(), numOfTerminals[i], testTAPairNum);

        printf("test res : %f\r\n", trainAndTestDis.second);

        trainAndTestDisVec.push_back(trainAndTestDis);

        printf("^^^^^^\r\n");
    }
    printf("------------------------------------------------------------------------------------------\r\n");
    return trainAndTestDisVec;



}


void SL_GEPTester::testTrainingEqaulTimeRes(double(*functionOut)(double *,int), const int& numOfFunctionCase,
                                            const int & chroNum, const vector<int> &numOfTerminals,double *constants, const int & numOfConstants,
                                            int* presetFunctions, const int &  numOfPresetFunctions, int *argsLenOfADFs, const int & numOfADFs, const int &  mainPH, int* inputADFHs,
                                            const int & trainTAPairNum, const int &testTAPairNum , const int & trainingEpo,
                                            bool ifUseSuspendNum , double similarValue ) {

    //ANY_ONE_EQUAL_WAY
    default_random_engine testGenerator;
    testGenerator.seed(time(NULL));
    uniform_real_distribution<double> startDistribution(0.0, 50);
    uniform_int_distribution<int> stepDistribution(0, 2);

    clock_t startClock, endClock;


    //vector<double>trainAns(trainTAPairNum);
    //vector<double>testAns(testTAPairNum);
    vector<double> startReals;
    vector<double> steps;

    vector<vector<pair<double, double>>>trainAndTestDisVecVec;
    vector<double>costSec;


    for (int i = 0; i < numOfFunctionCase; ++i) {
        startReals.push_back(startDistribution(testGenerator));
        steps.push_back(stepDistribution(testGenerator));
    }


    for (uint8_t i = ANY_ONE_EQUAL_WAY; i <= ANY_ONE_COUNT_BY_WEIGHT; i++) {
        startClock = clock();
        trainAndTestDisVecVec.push_back(testTrainingEqaulTimeResHelp(i, startReals, steps, functionOut, numOfFunctionCase, chroNum, numOfTerminals, constants,
                                                                     numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs, mainPH, inputADFHs, trainTAPairNum, testTAPairNum,
                                                                     trainingEpo, ifUseSuspendNum, similarValue));
        endClock = clock();
        costSec.push_back((double)(endClock - startClock) / CLOCKS_PER_SEC);
    }

    try {
        if (trainAndTestDisVecVec.size() != 4) {
            throw "error : test is not enough!";
        }
        else {
            eqaulTimeResSaveToFile(trainAndTestDisVecVec, costSec);
        }
    }
    catch (const char * &e) {
        printf("%s\r\n", e);
        exit(-1);
    }


    /*
    boost::shared_array<double> trainAns(new double[trainTAPairNum]);
    boost::shared_array<double> testAns(new double[testTAPairNum]);
    for (int i = 0; i < numOfFunctionCase; ++i) {
        //vector<double>trainTerms(trainTAPairNum *  numOfTerminals[i]);
        //vector<double>testTerms(testTAPairNum * numOfTerminals[i]);
        boost::shared_array<double> trainTerms(new double[trainTAPairNum *  numOfTerminals[i]]);
        boost::shared_array<double> testTerms(new double[testTAPairNum * numOfTerminals[i]]);
        double startReal = startDistribution(testGenerator);
        double nowStep = stepDistribution(testGenerator);
        double realPtr = startReal;

        double trainingDis;
        double testDis;

        for (int j = 0; j < trainTAPairNum * numOfTerminals[i]; ++j) {
            trainTerms[j] = realPtr;
            realPtr += nowStep;
        }

        for (int j = 0; j < testTAPairNum * numOfTerminals[i]; ++j) {
            testTerms[j] = realPtr;
            realPtr += nowStep;
        }

        for (int j = 0, k = 0; j < trainTAPairNum; ++j, k += numOfTerminals[i])
            trainAns[j] = functionOut(&trainTerms[k], i);

        for (int j = 0, k = 0; j < testTAPairNum; ++j, k += numOfTerminals[i])
            testAns[j] = functionOut(&testTerms[k], i);

        SL_GEP slgep(chroNum, trainTerms.get(), trainAns.get(), trainTAPairNum, trainingEpo, numOfTerminals[i],
            presetFunctions, numOfPresetFunctions, argsLenOfADFs,
            numOfADFs, mainPH, inputADFHs);

        slgep.whichRenewSymbolCountWay = ANY_ONE_EQUAL_WAY;

        pair<Chromosome, ChromosomeRule> thePair = slgep.train();

        trainingDis = slgep.minDistance;

        testDis = EuclideanDis(thePair.second,thePair.first, testTerms.get(), testAns.get(), numOfTerminals[i], testTAPairNum);



    }*/



}

void SL_GEPTester::eqaulTimeResSaveToFile(const vector<vector<pair<double, double>>>&trainAndTestDisVecVec, const  vector<double>&costSec) {
    namespace bf = boost::filesystem;
    int testFunctionNum;
    int theSetWs[2] = { 30,30 };
    try {
        if (!trainAndTestDisVecVec.size())
            throw "error: trainAndTestDisVecVec no data";
        else
            testFunctionNum = trainAndTestDisVecVec[0].size();
    }
    catch (const char * &e) {
        printf("%s\r\n", e);
        exit(-1);
    }

    string directoryName = "."+ equalTimeResFileNameHead + getDiretoryNameByDateTime("equalTimeRes",false);
    bf::path path(directoryName);
    //bf::path file_path = path / "file.txt";
    if (!bf::exists(path)) {
        bf::create_directory(path);
    }

    for (uint8_t i = 0; i <= ANY_ONE_COUNT_BY_WEIGHT; ++i) {
        string thisFileName = getFileNameEqualTimeRse(i);
        bf::path file_path = path / thisFileName;
        ofstream out(file_path.generic_path().c_str());
        const vector<pair<double, double>> &trainAndTestDisVec = trainAndTestDisVecVec[i];
        out << "num" << setw(theSetWs[0]) << "trainRes" << setw(theSetWs[1]) << "testRes" << endl;
        for (int j = 0; j < testFunctionNum; ++j) {
            out << j << setw(theSetWs[0]) << trainAndTestDisVec[j].first << setw(theSetWs[1]) << trainAndTestDisVec[j].second << endl;
        }
        out <<"cost time : " << getCostMinAndSec(costSec[i]) << endl;

        out.close();
    }


}

string SL_GEPTester::getDiretoryNameByDateTime(const string &nameHeadStr, const bool &useRelativePath) {
    time_t now = time(NULL);
    tm *nowTm = localtime(&now);
    if (useRelativePath)
        return "./" + nameHeadStr + "_" + to_string(nowTm->tm_year + startYear) + "_" + to_string(nowTm->tm_mon + startMon) + "_" +
               to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec);
    else
        return "./" + nameHeadStr + "_" + to_string(nowTm->tm_year + startYear) + "_" + to_string(nowTm->tm_mon + startMon) + "_" +
               to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec);
}

void SL_GEPTester::testDirectory() {
    namespace bf = boost::filesystem;
    string directoryName = "./66";
    bf::path path(directoryName);
    bf::path file_path = path / "file.txt";

    if (bf::exists(path)) {
        ofstream out(file_path.generic_path().c_str());
        out << "hhh" << endl;
        out.close();
    }
    else {
        bf::create_directory(path);
        ofstream out(file_path.generic_path().c_str());
        out << "hhh" << endl;
        out.close();

    }
    cout << "hhhhh" << endl;
}

string SL_GEPTester::getFileNameEqualTimeRse(const uint8_t &whichType) {
    switch (whichType)
    {
        case ANY_ONE_EQUAL_WAY:
            return "any_one_equal_way.txt";
        case LOW_ONE_FIRST:
            return "low_one_first.txt";
        case BEST_ONE_ONLY:
            return "best_one_first.txt";
        case ANY_ONE_COUNT_BY_WEIGHT:
            return "any_one_count_by_weight.txt";
        default:
            return "unknown";
    }

}
