//
// Created by JAY on 2022/2/15.
//

#include "ThreadVersionTestCase.h"
#include "../ChromosomeShower.h"
double addHandler_1(const double *args, const int len) {
    return args[0] + args[1];
}

void ThreadVersionTestCase::testTestThread1(){
    //testThread1();
    testThread2(3000);
}
/**
  * @brief  测试传入Vector参数的SymbolSet的构造函数
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void ThreadVersionTestCase::testSymbolSetVector(){
    return;
}
/**
  * @brief  测试传入Vector参数的SymbolSet、SymbolSetGenerator、ChromosomeDecoder的构造函数
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void ThreadVersionTestCase::testSgVector(){
    //a  0
    //b  1
    //add 2
    //times 3
    //G1 4
    //G2  5
    //x   6
    //y  7
    int numOfTerminals = 2;
    int numOfPresetFunctions = 2;
    int numOfADFs = 2;

    int mainProgramH = 10;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);
    vector<double> args(2);
    args[0] = 1;
    args[1] = 2;

    presetFunctions[0] = 0;
    presetFunctions[1] = 2;

    argsLenOfADFs[0] = 2;
    argsLenOfADFs[1] = 2;

    SymbolSetGenerator sg;
    SymbolSet symbolSet;
    sg.setSymbolSet(symbolSet, numOfTerminals, presetFunctions,  argsLenOfADFs);




    vector<int>ADFH;
    ADFH.push_back(1);
    ADFH.push_back(2);
    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    Chromosome chromosome(cr);
    SL_ChromosomeDecoder cd;
    //	vector<double>input(2);
    vector<double> input(2);

    //G1 times G2 a a b a
    //add x y
    //add times  y y  x
    //G1(a*a,G2(b,a))
    //(a*a) + G(b,a)
    //(a*a) + y * (y+x)
    //(a*a) + a + (a*b)
    //(a*a) + (a+b)
    chromosome.mainProgramEx[0] = 4;
    chromosome.mainProgramEx[1] = 3;
    chromosome.mainProgramEx[2] = 5;
    chromosome.mainProgramEx[3] = 0;
    chromosome.mainProgramEx[4] = 0;
    chromosome.mainProgramEx[5] = 1;
    chromosome.mainProgramEx[6] = 0;

    chromosome.ADFEx[0][0] = 2;
    chromosome.ADFEx[0][1] = 6;
    chromosome.ADFEx[0][2] = 7;

    //
    chromosome.ADFEx[1][0] = 2;
    chromosome.ADFEx[1][1] = 6;
    chromosome.ADFEx[1][2] = 7;
    chromosome.ADFEx[1][3] = 7;
    chromosome.ADFEx[1][4] = 6;

    input[0] = 1;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input, chromosome, cr));
    printf("%f\r\n", cd.decode(input, chromosome, cr));

    input[0] = 2;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input, chromosome, cr));
}
/**
  * @brief  对应某一个函数，根据传入的自变量返回因变量值
  *
  * @param  args:自变量值
  *
  * @note
  *
  * @retval None
  */
double ThreadVersionTestCase::fitFunction(const vector<double>&args) {
    //return sin(args[0]) + cos(args[1] * args[1]) - (args[0] - args[1]*args[1]);			//add sin minus x cos minus times  x times y y y y
    //return args[0] * args[0];
    //return args[0] * sin(args[0]);
    //return sin(args[0]) * sin(args[1]) + cos(args[0]);			//add times cos sin cos x y x
    //return pow(args[0], 4) + pow(args[0], 3) + pow(args[0], 2) + args[0];
    //return sin(args[0]) + cos(args[0]) * cos(args[1]);			//add sin times x cos  cos x y
    //return args[0] * args[0] * args[0] + args[1];				//add times y x times x x
    //return args[0] * args[0] * args[0] + args[1] * sin(args[0]) + args[1];				//add times add x times times y x x y sin x
    //return args[0] * args[0] * args[0] + sin(args[1]+args[0]);				//add times sin x times add x x x y
    return args[0] / (args[1] * tan(args[1]));
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
void ThreadVersionTestCase::fitFunctionOut(vector<vector<double>>&realTermVec,vector<double>&ansVec) {
    int num = ansVec.size();
    int dim = realTermVec[0].size();
    for (int i = 0,k = 1; i < num; ++i)
        for(int j = 0 ; j < dim; ++j)
        realTermVec[i][j] = k++;
    for (int i = 0 ; i < num; ++i) {
        ansVec[i] = fitFunction(realTermVec[i]);
    }
}

/**
  * @brief  测试SL_GEP_Thread
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void ThreadVersionTestCase::testSL_GEP_Thread() {
    int chroNum = 50;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 7;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 10000;

    vector<int> presetFunctions(numOfPresetFunctions);
    vector<int> argsLenOfADFs(numOfADFs);
    vector<vector<double>> realTermVec;
    vector<double> ansVec(TAPairNum);

    for(int i = 0 ; i < TAPairNum ;++i){
        vector<double> tmp(numOfTerminals);
        realTermVec.push_back(tmp);
    }


    fitFunctionOut(realTermVec, ansVec);

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


    SL_GEP_Thread slgep(chroNum, realTermVec, ansVec,needEpoch, numOfTerminals, presetFunctions,  argsLenOfADFs,
                  mainProgramH, ADFH,4);

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);
}