#include <iostream>
#include "Symbol.h"
#include "ChromosomeRule.h"
#include "Chromosome.h"
#include "SL_ChromosomeDecoder.h"
#include "SymbolSetGenerator.h"
#include "FunctionPreset.h"
#include "initHelp.h"
#include "SL_GEP.h"
#include "GA_HelpFunc.h"
#include "ChromosomeShower.h"
#include "testCases/ThreadVersionTestCase.h"
#include "testCases/GEPTestCase.h"
#include "testCases/dataProcessorTestCase.h"
#include<boost/smart_ptr.hpp>

using namespace std;
double addHandler(const double *args, const int len) {
    return args[0] + args[1];
}
double  minusHandler(const double *args, const int len) {
    return args[0] - args[1];
}
double timesHandler(const double *args, const int len) {
    return args[0] * args[1];
}
/**
  * @brief  测试SymbolSet
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void test1() {
    SymbolSet symbolSet;
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;
    symbolSet.pushFunctionSymbol("add", 2, addHandler);
    symbolSet.pushFunctionSymbol("add0", 2, addHandler);
    symbolSet.pushTerminalSymbol("v0", 10);
    symbolSet.pushSubFunctionSymbol("minus", 2, 1);
    symbolSet.pushInputArgSymbol("a");
    vector<Symbol> functionSet = symbolSet.getFunctionSet();
    vector<Symbol> subFuncSet = symbolSet.getSubFunctionSet();
    vector<Symbol> terminal = symbolSet.getTerminalSet();
    vector<Symbol> symbolSet2 = symbolSet.getInputArgSet();
    unordered_map<string, SymbolMapInfo> symbolMap = symbolSet.getSymbolMap();
    Symbol fs = symbolSet.getSymbol("add");
    Symbol ts = symbolSet.getSymbol("v0");
    printf("%f\r\n", functionSet[0].callFunctionHandler(args.get(), 2));
    printf("%f\r\n", subFuncSet[0].callFunctionHandler(args.get(), 2));
    printf("%f\r\n", terminal[0].getVal());
    cout << symbolSet2[0].getSymbolName() << endl;

    printf("%f\r\n", functionSet[symbolMap["add"].index].callFunctionHandler(args.get(), 2));
    printf("%f\r\n", fs.callFunctionHandler(args.get(), 2));
    printf("%f\r\n", ts.getVal());
    //printf("%s\r\n", symbolSet2[0].getSymbolName());


    //printf("%f\r\n", symbolSet.getSymbolMap["add"].callFunctionHandler(args.get(), 2));

    //printf("%f\r\n", symbolSet.getSymbolMap["minus"].callFunctionHandler(args.get(), 2));
}
/**
  * @brief  测试ChromosomeRule
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void test2() {
    SymbolSet symbolSet;
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;
    symbolSet.pushFunctionSymbol("add", 2, minusHandler);
    symbolSet.pushFunctionSymbol("add0", 2, addHandler);
    symbolSet.pushTerminalSymbol("v0", 10);
    symbolSet.pushSubFunctionSymbol("G", 2, 1);
    symbolSet.pushInputArgSymbol("a");
    vector<Symbol> functionSet = symbolSet.getFunctionSet();
    vector<Symbol> subFuncSet = symbolSet.getSubFunctionSet();
    vector<Symbol> terminal = symbolSet.getTerminalSet();
    vector<Symbol> symbolSet2 = symbolSet.getInputArgSet();


    int mainProgramH = 10;
    vector<int>ADFH;
    ADFH.push_back(10);
    ADFH.push_back(8);

    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    printf("%d\r\n", cr.getADFPR(0).l);
}

void test3() {
    SymbolSet symbolSet;
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;


    symbolSet.pushFunctionSymbol("add", 2, addHandler);	//0
    symbolSet.pushFunctionSymbol("times", 2, timesHandler); //1
    symbolSet.pushTerminalSymbol("a", 10);	//2
    symbolSet.pushTerminalSymbol("b", 10);	//3
    symbolSet.pushSubFunctionSymbol("G", 2, 0);	//4
    symbolSet.pushInputArgSymbol("x");		//5
    symbolSet.pushInputArgSymbol("y");		//6

    int mainProgramH = 10;
    vector<int>ADFH;
    ADFH.push_back(1);
    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    Chromosome chromosome(cr);
    SL_ChromosomeDecoder cd;
    vector<double>input(2);


    chromosome.mainProgramEx[0] = 4;
    chromosome.mainProgramEx[1] = 1;
    chromosome.mainProgramEx[2] = 2;
    chromosome.mainProgramEx[3] = 2;
    chromosome.mainProgramEx[4] = 2;
    chromosome.mainProgramEx[5] = 3;
    chromosome.mainProgramEx[6] = 2;

    chromosome.ADFEx[0][0] = 0;
    chromosome.ADFEx[0][1] = 5;
    chromosome.ADFEx[0][2] = 6;


    input[0] = 1;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input, chromosome, cr));


}
void test4() {
    SymbolSet symbolSet;
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;


    symbolSet.pushFunctionSymbol(W_add);	//0
    symbolSet.pushFunctionSymbol(W_times); //1
    symbolSet.pushTerminalSymbol("a", 10);	//2
    symbolSet.pushTerminalSymbol("b", 10);	//3
    symbolSet.pushSubFunctionSymbol("G", 2, 0);	//4
    symbolSet.pushInputArgSymbol("x");		//5
    symbolSet.pushInputArgSymbol("y");		//6

    int mainProgramH = 10;
    vector<int>ADFH;
    ADFH.push_back(1);
    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    Chromosome chromosome(cr);
    SL_ChromosomeDecoder cd;
    vector<double>input(2);


    chromosome.mainProgramEx[0] = 4;
    chromosome.mainProgramEx[1] = 1;
    chromosome.mainProgramEx[2] = 0;
    chromosome.mainProgramEx[3] = 2;
    chromosome.mainProgramEx[4] = 2;
    chromosome.mainProgramEx[5] = 3;
    chromosome.mainProgramEx[6] = 2;

    chromosome.ADFEx[0][0] = 0;
    chromosome.ADFEx[0][1] = 5;
    chromosome.ADFEx[0][2] = 6;


    input[0] = 1;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input, chromosome, cr));

}


void test6() {
    //a  0
    //b  1
    //add 2
    //times 3
    //G 4
    //x  5
    //y  6
    int numOfTerminals = 2;
    int numOfPresetFunctions = 2;
    int numOfADFs = 1;

    int mainProgramH = 10;

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;

    presetFunctions[0] = 0;
    presetFunctions[1] = 2;

    argsLenOfADFs[0] = 2;

    SymbolSetGenerator sg;
    SymbolSet symbolSet;
    sg.setSymbolSet(symbolSet, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs);
    //SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs);
    //boost::shared_array<SymbolSet> symbolSetSA(sg.makeSymbolSet(numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs));
    //SymbolSet *symbolSet = symbolSetSA.get();



    vector<int>ADFH;
    ADFH.push_back(1);
    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    Chromosome chromosome(cr);
    SL_ChromosomeDecoder cd;
    //	vector<double>input(2);
    boost::shared_array<double> input(new double[2]);

    //G times add a a b a
    //add x y
    //(2*2 + (2+2)) = 8
    chromosome.mainProgramEx[0] = 4;
    chromosome.mainProgramEx[1] = 3;
    chromosome.mainProgramEx[2] = 2;
    chromosome.mainProgramEx[3] = 0;
    chromosome.mainProgramEx[4] = 0;
    chromosome.mainProgramEx[5] = 1;
    chromosome.mainProgramEx[6] = 1;

    chromosome.ADFEx[0][0] = 2;
    chromosome.ADFEx[0][1] = 5;
    chromosome.ADFEx[0][2] = 6;


    input[0] = 1;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));
    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

    input[0] = 2;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

}

/**
  * @brief  测试SymbolSet、SymbolSetGenerator、ChromosomeDecoder
  *
  * @param  None
  *
  * @note
  *
  * @retval None
  */
void test6_5() {

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

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
    boost::shared_array<double> args(new double[2]);
    args[0] = 1;
    args[1] = 2;

    presetFunctions[0] = 0;
    presetFunctions[1] = 2;

    argsLenOfADFs[0] = 2;
    argsLenOfADFs[1] = 2;

    SymbolSetGenerator sg;
    SymbolSet symbolSet;
    sg.setSymbolSet(symbolSet, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs);




    vector<int>ADFH;
    ADFH.push_back(1);
    ADFH.push_back(2);
    ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
    Chromosome chromosome(cr);
    SL_ChromosomeDecoder cd;
    //	vector<double>input(2);
    boost::shared_array<double> input(new double[2]);

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

    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));
    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

    input[0] = 2;
    input[1] = 2;

    printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

}
void test7() {
    vector<double> tmp(10);
    initVectorHelp(tmp, 20);
    printf("%ld\r\n", tmp.size());
}

void test8() {
    //(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
    //	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
    //	bool ifUseSuspendNum = true, double similarValue = 1e-6)
    //a  0
    //b  1
    //add 2
    //times 3
    //G 4
    //x  5
    //y  6
    int chroNum = 1;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 2;
    int numOfADFs = 1;

    int mainProgramH = 10;

    int TAPairNum = 1;
    int needEpoch = 1000;

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
    boost::shared_array<double> realTermVec(new double[2]);
    boost::shared_array<double> ansVec(new double[2]);
    realTermVec[0] = 1;
    realTermVec[1] = 2;
    ansVec[0] = 0;
    ansVec[1] = 0;



    presetFunctions[0] = 0;
    presetFunctions[1] = 2;

    argsLenOfADFs[0] = 2;


    boost::shared_array<int> ADFH(new int[1]);
    ADFH[0] = 1;


    SL_GEP slgep(chroNum, realTermVec.get(), ansVec.get(), TAPairNum, needEpoch, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(),
                 numOfADFs, mainProgramH, ADFH.get());


    printf("%f\r\n", slgep.test1());
}

void test9() {
    vector<double> tmp(7);
    tmp[0] = 0.142;
    tmp[1] = 0.142;
    tmp[2] = 0.357;
    tmp[3] = 0.357;
    tmp[4] = 0.357;
    tmp[5] = 0.643;
    tmp[6] = 1;
    double t = 0.1;
    for (int i = 0; i < 50; ++i) {
        printf("%d\r\n", getTheGambleIndex(t, tmp));
        t += 0.012;
    }

}

double fitFunction(double *args) {
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

void fitFunctionOut(int num,int dim,double *realTermVec,double *ansVec) {
    for (int i = 0; i < num * dim; ++i)
        realTermVec[i] = i + 1;
    for (int i = 0 , j = 0; i < num; ++i,j += dim) {
        ansVec[i] = fitFunction(&realTermVec[j]);
    }
}

void beforeTest10() {
    int TAPairNum = 10;
    int numOfValInTerm = 2;
    boost::shared_array<double> realTermVec(new double[TAPairNum * numOfValInTerm]);
    boost::shared_array<double> ansVec(new double[TAPairNum]);

    fitFunctionOut(TAPairNum, numOfValInTerm, realTermVec.get(), ansVec.get());
    for (int i = 0; i < TAPairNum; ++i)
        printf("%f   ", ansVec[i]);
    printf("\r\n");
}

void test10() {
    int chroNum = 50;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 7;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 10000;

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
    boost::shared_array<double> realTermVec(new double[TAPairNum * numOfTerminals]);
    boost::shared_array<double> ansVec(new double[TAPairNum]);


    fitFunctionOut(TAPairNum, numOfTerminals, realTermVec.get(), ansVec.get());

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


    boost::shared_array<int> ADFH(new int[numOfADFs]);
    ADFH[0] = 5;
    //ADFH[1] = 8;


    SL_GEP slgep(chroNum, realTermVec.get(), ansVec.get(), TAPairNum, needEpoch, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(),
                 numOfADFs, mainProgramH, ADFH.get());

    ChromosomeShower cs(slgep.getChromosomeRule());

    pair<Chromosome, ChromosomeRule> thePair = slgep.train();

    cs.simpleShow(thePair.first);


}

void test11() {
    int chroNum = 50;
    int numOfTerminals = 2;
    int numOfPresetFunctions = 5;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 2400;

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
    boost::shared_array<double> realTermVec(new double[TAPairNum * numOfTerminals]);
    boost::shared_array<double> ansVec(new double[TAPairNum]);


    fitFunctionOut(TAPairNum, numOfTerminals, realTermVec.get(), ansVec.get());

    for (int i = 0, j = 0; i < numOfPresetFunctions; i++, j++) {
        if (j == (int)W_divide)
            j++;
        presetFunctions[i] = j;
    }
    //presetFunctions[0] = (int)W_times;
    //presetFunctions[1] = (int)W_add;
    //presetFunctions[2] = (int)W_sin;
    //presetFunctions[3] = (int)W_cos;
    //presetFunctions[4] = (int)W_minus;

    argsLenOfADFs[0] = 2;
    //argsLenOfADFs[1] = 3;


    boost::shared_array<int> ADFH(new int[numOfADFs]);
    ADFH[0] = 5;
    //ADFH[1] = 8;


    SL_GEP slgep(chroNum, realTermVec.get(), ansVec.get(), TAPairNum, needEpoch, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(),
                 numOfADFs, mainProgramH, ADFH.get());


    SL_GEPTester  sl_gepTest;
    sl_gepTest.testTrainingZeroCostEpo(slgep);


}
void test12() {
    SL_GEPTester  sl_gepTest;
    //sl_gepTest.testFile();
    sl_gepTest.testDirectory();

}
double functionOut(double *args, int whichFunc) {
    switch (whichFunc)
    {
//        case 0:
//            return (args[0] + cos(args[3]) - sin(args[4]))  * sin(args[0] * args[0] + args[1]) - sin(cos(args[2]));
        case 0:
            return args[0] * sin(args[0] * args[0] + args[0]) ;         //x * sin(x^2 + x)
        case 1:
            return sin(args[0]) + cos(args[0] * args[1]) * cos(args[1]);        //sin(x) + cos(x*y) + cos(y)
        case 2:
            return args[0] * args[0] * args[0] + sin(args[1] + args[0]) * args[0] * args[1];    //x^3 + sin(x+y)*y*y    add times times times x sin times x x add y y x y
        case 3:
            return sin(args[0]) + cos(args[1] * args[1]) - (args[0] - args[1] * args[1]);
        case 4:
            return pow(args[0],6) + pow(args[1],5);         //x^6 + y^5
        case 5:
            return pow(args[0],4) * pow(args[1],3);
        case 6:
            return sin(args[0]+args[1]) * cos(args[2] * args[3]);
        default:
            return 0;
    }
}

void test13() {
    int chroNum = 50;
    int numOfPresetFunctions = 5;
    int numOfADFs = 1;

    int mainProgramH = 16;

    int TAPairNum = 50;
    int needEpoch = 2400;

    int functionOutNum = 6;

    vector<int>numOfTerminals;

    boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
    boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);

    for (int i = 0, j = 0; i < numOfPresetFunctions; i++, j++) {
        if (j == (int)W_divide)
            j++;
        presetFunctions[i] = j;
    }
    //presetFunctions[0] = (int)W_times;
    //presetFunctions[1] = (int)W_add;
    //presetFunctions[2] = (int)W_sin;
    //presetFunctions[3] = (int)W_cos;
    //presetFunctions[4] = (int)W_minus;

    argsLenOfADFs[0] = 2;
    //argsLenOfADFs[1] = 3;


    boost::shared_array<int> ADFH(new int[numOfADFs]);
    ADFH[0] = 5;
    //ADFH[1] = 8;

    numOfTerminals.push_back(1);
    numOfTerminals.push_back(2);
    numOfTerminals.push_back(2);
    numOfTerminals.push_back(2);
    numOfTerminals.push_back(2);
    numOfTerminals.push_back(2);
    numOfTerminals.push_back(4);



    SL_GEPTester  sl_gepTest;
    sl_gepTest.testTrainingEqaulTimeRes(functionOut, functionOutNum, chroNum, numOfTerminals, nullptr, 0, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(),
                                        numOfADFs, mainProgramH, ADFH.get(), 100, 50, 8000);



}
void test14(){
    random_device rd;
    for(int i = 0 ; i < 40;++i)
        printf("%d\r\n",rd());
}

void test15(const int &argc,char** argv){
    printf("%d\r\n",argc);
    for(int i = 1 ; i < argc ; ++i)
        printf("%s\r\n",argv[i]);

}

int main(int argc, char** argv) {
//    cout<<"hh"<<endl;
//    test1();
//    test2();
//    test3();
//    test4();
//    test6();
//    test6_5();
//    test7();
//    test8();
//    test9();
//    beforeTest10();
//    test10();
//    test11();
//    test12();
//    test13();
//    test14();
//    ThreadVersionTestCase::testTestThread1();
//    ThreadVersionTestCase::testSgVector();
//    ThreadVersionTestCase::testSL_GEP_Thread();
//    GEPTestCase::testSL_GEP_vector();
//    dataProcessorTestCase::testSaveCSV();
//    dataProcessorTestCase::testLoadCSV();
//    GEPTestCase::testSL_GEP_save1();
//    GEPTestCase::testSL_GEP_load1();
//    GEPTestCase::testLoadDataSet1();
//    GEPTestCase::testTrainDataset1();
    GEPTestCase::testTrainOrReTrainByArgv(argc,argv);
//    GEPTestCase::testEvaluateDistance();


    return 0;
}
