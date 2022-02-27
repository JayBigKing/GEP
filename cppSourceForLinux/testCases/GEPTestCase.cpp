//
// Created by JAY on 2022/2/15.
//

#include "GEPTestCase.h"
#include "../SL_GEP.h"
#include "../ChromosomeShower.h"
#include "../dataSaveAndLoad/SL_GEP_dataProcessor.h"

/**
  * @brief  对应某一个函数，根据传入的自变量返回因变量值
  *
  * @param  args:自变量值
  *
  * @note
  *
  * @retval None
  */
double GEPTestCase::fitFunctionVec(const vector<double>&args) {
    //return sin(args[0]) + cos(args[1] * args[1]) - (args[0] - args[1]*args[1]);			//add sin minus x cos minus times  x times y y y y
    //return args[0] * args[0];
    return args[0] * sin(args[0]);
    //return sin(args[0]) * sin(args[1]) + cos(args[0]);			//add times cos sin cos x y x
    //return pow(args[0], 4) + pow(args[0], 3) + pow(args[0], 2) + args[0];
    //return sin(args[0]) + cos(args[0]) * cos(args[1]);			//add sin times x cos  cos x y
    //return args[0] * args[0] * args[0] + args[1];				//add times y x times x x
    //return args[0] * args[0] * args[0] + args[1] * sin(args[0]) + args[1];				//add times add x times times y x x y sin x
    //return args[0] * args[0] * args[0] + sin(args[1]+args[0]);				//add times sin x times add x x x y
    //return args[0] / (args[1] * tan(args[1]));
}
/**
  * @brief  产生训练集的自变量集和label集
  *
  * @param  dim:自变量的维度
  * @param  realTermVec:自变量集合
  * @param  ansVec:label集合
  *
  * @note   修改realTermVec和ansVec的内容
  *
  * @retval None
  */
void GEPTestCase::fitFunctionOutVec(vector<vector<double>>&realTermVec,vector<double>&ansVec) {
    int num = ansVec.size();
    int dim = realTermVec[0].size();
    for (int i = 0,k = 1; i < num; ++i)
        for(int j = 0 ; j < dim; ++j)
            realTermVec[i][j] = k++;
    for (int i = 0 ; i < num; ++i) {
        ansVec[i] = fitFunctionVec(realTermVec[i]);
    }
}
/**
  * @brief  测试输出vector的构造函数的SL_GEP
  *
  * @param
  *
  * @note
  *
  * @retval
  */
void GEPTestCase::testSL_GEP_vector() {
    int chroNum = 50;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 7;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 2000;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);
    vector<vector<double>> realTermVec;
    vector<double> ansVec(TAPairNum);

    for(int i = 0 ; i < TAPairNum ;++i){
        vector<double> tmp(numOfTerminals);
        realTermVec.push_back(tmp);
    }


    fitFunctionOutVec(realTermVec, ansVec);

    for (int i = 0, j = 0; i < numOfPresetFunctions; i++, j++) {
//        if (j == (int)W_divide)
//            j++;
        presetFunctions[i] = j;
    }
    //presetFunctions[0] = (int)W_times;
    //presetFunctions[1] = (int)W_add;
    //presetFunctions[2] = (int)W_sin;
    //presetFunctions[3] = (int)W_cos;
    //presetFunctions[4] = (int)W_minus;

    argsLenOfADFs[0] = 2;
    //argsLenOfADFs[1] = 3;


    vector<int> ADFH(numOfADFs);
    ADFH[0] = 5;
    //ADFH[1] = 8;


    SL_GEP slgep(chroNum, realTermVec, ansVec,needEpoch, numOfTerminals, presetFunctions,  argsLenOfADFs,
                        mainProgramH, ADFH);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);
}
/**
  * @brief  测试保存SL_GEP
  *
  * @param
  *
  * @note
  *
  * @retval
  */
void GEPTestCase::testSL_GEP_save1() {
    int chroNum = 5;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 7;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 100;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);
    vector<vector<double>> realTermVec;
    vector<double> ansVec(TAPairNum);

    for(int i = 0 ; i < TAPairNum ;++i){
        vector<double> tmp(numOfTerminals);
        realTermVec.push_back(tmp);
    }


    fitFunctionOutVec(realTermVec, ansVec);

    for (int i = 0, j = 0; i < numOfPresetFunctions; i++, j++) {
//        if (j == (int)W_divide)
//            j++;
        presetFunctions[i] = j;
    }
    //presetFunctions[0] = (int)W_times;
    //presetFunctions[1] = (int)W_add;
    //presetFunctions[2] = (int)W_sin;
    //presetFunctions[3] = (int)W_cos;
    //presetFunctions[4] = (int)W_minus;

    argsLenOfADFs[0] = 2;
    //argsLenOfADFs[1] = 3;


    vector<int> ADFH(numOfADFs);
    ADFH[0] = 5;
    //ADFH[1] = 8;


    SL_GEP slgep(chroNum, realTermVec, ansVec,needEpoch, numOfTerminals, presetFunctions,  argsLenOfADFs,
                 mainProgramH, ADFH);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);

    SL_GEP_dataProcessor::saveSL_GEP(slgep);
}

void GEPTestCase::testSL_GEP_load1() {
    int numOfTerminals = 2;
    int TAPairNum = 50;
    vector<vector<double>> realTermVec;
    vector<double> ansVec(TAPairNum);

    for(int i = 0 ; i < TAPairNum ;++i){
        vector<double> tmp(numOfTerminals);
        realTermVec.push_back(tmp);
    }


    fitFunctionOutVec(realTermVec, ansVec);




    SL_GEP slgep = SL_GEP_dataProcessor::loadSL_GEP("./theSL_GEPs/SL_GEP_2022_2_26_15_3_59.csv",realTermVec, ansVec,50,500);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);

}



void GEPTestCase::testLoadDataSet1() {
    SL_GEP_dataProcessor::testLoadDataSet();

}

void GEPTestCase::testTrainDataset1() {
    int chroNum = 50;
    int numOfPresetFunctions = 13;
    int numOfADFs = 2;

    int mainProgramH = 20;

    int needEpoch = 100000;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);

    int functionIndex = 0;
    for (;functionIndex < 11; ++functionIndex) {
//        if (j == (int)W_divide)
//            j++;
        presetFunctions[functionIndex] = functionIndex;
    }
    presetFunctions[functionIndex ++] =  (int)W_sqrt;
    presetFunctions[functionIndex ++] = (int)W_log2;


    argsLenOfADFs[0] = 2;
    argsLenOfADFs[1] = 2;

    vector<int> ADFH(numOfADFs);
    ADFH[0] = 6;
    ADFH[1] = 10;

    pair<vector<vector<double>>, vector<double>> theDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/trainDataSetCSV.csv",0);


    SL_GEP slgep(chroNum, theDataSet.first, theDataSet.second,needEpoch, theDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
                 mainProgramH, ADFH);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);

    SL_GEP_dataProcessor::saveSL_GEP(slgep);
}

void GEPTestCase::testTrainDataset2() {
    int chroNum = 60;
    int numOfPresetFunctions = 13;
    int numOfADFs = 2;

    int mainProgramH = 20;

    int needEpoch = 120000;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);

    int functionIndex = 0;
    for (;functionIndex < 11; ++functionIndex) {
//        if (j == (int)W_divide)
//            j++;
        presetFunctions[functionIndex] = functionIndex;
    }
    presetFunctions[functionIndex ++] =  (int)W_sqrt;
    presetFunctions[functionIndex ++] = (int)W_log2;


    argsLenOfADFs[0] = 2;
    argsLenOfADFs[1] = 3;

    vector<int> ADFH(numOfADFs);
    ADFH[0] = 8;
    ADFH[1] = 10;

    pair<vector<vector<double>>, vector<double>> theTrainDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/trainDataSetCSV.csv",0);

    pair<vector<vector<double>>, vector<double>> theTestDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/testDataSetCSV.csv",0);


    SL_GEP slgep(chroNum, theTrainDataSet.first, theTrainDataSet.second,needEpoch, theTrainDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
                 mainProgramH, ADFH);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);

    SL_GEP_dataProcessor::saveSL_GEP(slgep,"./theSL_GEPs/SL_GEP_WORK_DIM_1.csv");

    printf("\r\nperformance in test dataset:%f\r\n",slgep.testDataRunPerformance(theTestDataSet.first,theTrainDataSet.second));
}

void GEPTestCase::testTrainAndTestDataset1() {
    int chroNum = 50;

    int needEpoch = 80000;



    pair<vector<vector<double>>, vector<double>> theTrainDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/trainDataSetCSV.csv",0);

    pair<vector<vector<double>>, vector<double>> theTestDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/testDataSetCSV.csv",0);

//    SL_GEP slgep(chroNum, theTrainDataSet.first, theTrainDataSet.second,needEpoch, theTrainDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
//                 mainProgramH, ADFH);

    SL_GEP slgep = SL_GEP_dataProcessor::loadSL_GEP("./theSL_GEPs/SL_GEP_WORK_DIM_1.csv",
                                                    theTrainDataSet.first, theTrainDataSet.second,chroNum,needEpoch,
                                                    ANY_ONE_EQUAL_WAY);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);

    SL_GEP_dataProcessor::saveSL_GEP(slgep,"./theSL_GEPs/SL_GEP_WORK_DIM_1.csv");

    printf("\r\nperformance in test dataset:%f\r\n",slgep.testDataRunPerformance(theTestDataSet.first,theTrainDataSet.second));


}