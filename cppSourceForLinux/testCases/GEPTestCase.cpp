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

void GEPTestCase::testTrainAndTestDataset1(int whichLabel,string trainDataLoadFileName,
                                           string testDataLoadFileName,string chromosomeSaveFileNameHead) {
    try{
        int chroNum = 100;
        int numOfPresetFunctions = 13;
        int numOfADFs = 3;

        int mainProgramH = 30;

        int needEpoch = 1000000;

        vector<int> presetFunctions(numOfPresetFunctions);
        vector<int> argsLenOfADFs(numOfADFs);

        int functionIndex = 0;

        string chromosomeSaveFileName;
        if(whichLabel < 0 || whichLabel > 2)
            throw "error: the dim out of size";
        chromosomeSaveFileName = chromosomeSaveFileNameHead + to_string(whichLabel) + ".csv";

        for (;functionIndex < 11; ++functionIndex) {
//        if (j == (int)W_divide)
//            j++;
            presetFunctions[functionIndex] = functionIndex;
        }
        presetFunctions[functionIndex ++] =  (int)W_sqrt;
        presetFunctions[functionIndex ++] = (int)W_log2;


        argsLenOfADFs[0] = 4;
        argsLenOfADFs[1] = 3;
        argsLenOfADFs[2] = 2;

        vector<int> ADFH(numOfADFs);
        ADFH[0] = 12;
        ADFH[1] = 10;
        ADFH[2] = 8;

        pair<vector<vector<double>>, vector<double>> theTrainDataSet = SL_GEP_dataProcessor::loadDataSetOut(trainDataLoadFileName,whichLabel);  //"./datasets/testDataSetCSV.csv"

        pair<vector<vector<double>>, vector<double>> theTestDataSet = SL_GEP_dataProcessor::loadDataSetOut(testDataLoadFileName,whichLabel);


        SL_GEP slgep(chroNum, theTrainDataSet.first, theTrainDataSet.second,needEpoch, theTrainDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
                     mainProgramH, ADFH);

        ChromosomeShower cs(slgep.getChromosomeRule());

        pair<Chromosome, ChromosomeRule> thePair = slgep.train();

        cs.simpleShow(thePair.first);

        SL_GEP_dataProcessor::saveSL_GEP(slgep,chromosomeSaveFileName);

        printf("\r\nperformance in test dataset:%f\r\n",slgep.testDataRunPerformance(theTestDataSet.first,theTestDataSet.second));
    }  catch (const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }
}

void GEPTestCase::testReTrainAndTestDataset1(int whichLabel,string trainDataLoadFileName,
                                             string testDataLoadFileName,string chromosomeSaveFileNameHead) {
    try{
        int chroNum = 100;

        int needEpoch = 610000;

        string chromosomeSaveFileName;
        if(whichLabel < 0 || whichLabel > 2)
            throw "error: the dim out of size";
        chromosomeSaveFileName = chromosomeSaveFileNameHead + to_string(whichLabel) + ".csv";          //chromosomeSaveFileName = "./theSL_GEPs/SL_GEP_WORK_DIM_0.csv";"./datasets/testDataSetCSV.csv"


        pair<vector<vector<double>>, vector<double>> theTrainDataSet = SL_GEP_dataProcessor::loadDataSetOut(trainDataLoadFileName,whichLabel);

        pair<vector<vector<double>>, vector<double>> theTestDataSet = SL_GEP_dataProcessor::loadDataSetOut(testDataLoadFileName,whichLabel);

//    SL_GEP slgep(chroNum, theTrainDataSet.first, theTrainDataSet.second,needEpoch, theTrainDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
//                 mainProgramH, ADFH);
        SL_GEP slgep = SL_GEP_dataProcessor::loadSL_GEP(chromosomeSaveFileName,
                                                        theTrainDataSet.first, theTrainDataSet.second,chroNum,needEpoch,
                                                        ANY_ONE_EQUAL_WAY);

        ChromosomeShower cs(slgep.getChromosomeRule());

        pair<Chromosome, ChromosomeRule> thePair = slgep.train();

        cs.simpleShow(thePair.first);

        SL_GEP_dataProcessor::saveSL_GEP(slgep,chromosomeSaveFileName);
        printf("\r\nperformance in test dataset:%f\r\n",slgep.testDataRunPerformance(theTestDataSet.first,theTestDataSet.second));
    }catch (const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }


}

void GEPTestCase::testTrainOrReTrainByArgv(int argc, char** argv){
    try{
        if(argc >= 3){
            if((argv[1][0] - '0') < 0 || (argv[1][0] - '0') > 1)
                throw "error:index out of size";
            if(argc == 3){
                //./datasets/testDataSetCSV.csv
                if((argv[1][0] - '0') == 0)
                    GEPTestCase::testTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV.csv",
                                                          "./datasets/testDataSetCSV.csv","./theSL_GEPs/SL_GEP_WORK_DIM_");
                else
                    GEPTestCase::testReTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV.csv",
                                                            "./datasets/testDataSetCSV.csv","./theSL_GEPs/SL_GEP_WORK_DIM_");
            }else{
                int whichLabel = 0;
                string trainDataLoadFileName = "";
                string testDataLoadFileName = "";
                string chromosomeSaveFileNameHead = "";
                switch ((argv[3][0] - '0')) {
                    case 0:
                        whichLabel = (argv[2][0] - '0');
                        trainDataLoadFileName = "./datasets/trainDataSetCSV2.csv";
                        testDataLoadFileName = "./datasets/testDataSetCSV2.csv";
                        chromosomeSaveFileNameHead = "./theSL_GEPs/SL_GEP_WORK2_DIM_";
                        break;
                    case 1:
                        whichLabel = (argv[2][0] - '0');
                        trainDataLoadFileName = "./datasets/trainDataSetCSV_no_Ob.csv";
                        testDataLoadFileName = "./datasets/testDataSetCSV_no_Ob.csv";
                        chromosomeSaveFileNameHead = "./theSL_GEPs/SL_GEP_WORK_NO_OB_DIM_";
                        break;
                    case 2:
                        whichLabel = 2;
                        trainDataLoadFileName = "./datasets/trainDataSetCSV3.csv";
                        testDataLoadFileName = "./datasets/testDataSetCSV3.csv";
                        chromosomeSaveFileNameHead = "./theSL_GEPs/SL_GEP_WORK_ANGLE_DIM_";
                        break;
                    case 3:
                        whichLabel = 2;
                        trainDataLoadFileName = "./datasets/trainDataSetCSV4.csv";
                        testDataLoadFileName = "./datasets/testDataSetCSV4.csv";
                        chromosomeSaveFileNameHead = "./theSL_GEPs/SL_GEP_WORK_MANY1_ANGLE_DIM_";
                        break;
                    default:
                        throw "error:no enough Input arg";
                        break;
                }
                if((argv[1][0] - '0') == 0)
                    GEPTestCase::testTrainAndTestDataset1(whichLabel,trainDataLoadFileName,
                                                          testDataLoadFileName,chromosomeSaveFileNameHead);
                else
                    GEPTestCase::testReTrainAndTestDataset1(whichLabel,trainDataLoadFileName,
                                                            testDataLoadFileName,chromosomeSaveFileNameHead);
//                if(!(argv[3][0] - '0')){
//                    if((argv[1][0] - '0') == 0)
//                        GEPTestCase::testTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV2.csv",
//                                                              "./datasets/testDataSetCSV2.csv","./theSL_GEPs/SL_GEP_WORK2_DIM_");
//                    else
//                        GEPTestCase::testReTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV2.csv",
//                                                                "./datasets/testDataSetCSV2.csv","./theSL_GEPs/SL_GEP_WORK2_DIM_");
//                }else if((argv[3][0] - '0') == 1){
//                    if((argv[1][0] - '0') == 0)
//                        GEPTestCase::testTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV_no_Ob.csv",
//                                                              "./datasets/testDataSetCSV_no_Ob.csv","./theSL_GEPs/SL_GEP_WORK_NO_OB_DIM_");
//                    else
//                        GEPTestCase::testReTrainAndTestDataset1((argv[2][0] - '0'),"./datasets/trainDataSetCSV_no_Ob.csv",
//                                                                "./datasets/testDataSetCSV_no_Ob.csv","./theSL_GEPs/SL_GEP_WORK_NO_OB_DIM_");
//                }else{
//                    if((argv[1][0] - '0') == 0)
//                        GEPTestCase::testTrainAndTestDataset1(2,"./datasets/trainDataSetCSV3.csv",
//                                                              "./datasets/testDataSetCSV3.csv","./theSL_GEPs/SL_GEP_WORK_ANGLE_DIM_");
//                    else
//                        GEPTestCase::testReTrainAndTestDataset1(2,"./datasets/trainDataSetCSV3.csv",
//                                                                "./datasets/testDataSetCSV3.csv","./theSL_GEPs/SL_GEP_WORK_ANGLE_DIM_");
//                }
            }

        }else{
            throw "error:no enough Input arg";
        }
    }catch(const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }
}

void GEPTestCase::testEvaluateDistance(){
    int chroNum = 1;

    int needEpoch = 1;

    string chromosomeSaveFileName;


    pair<vector<vector<double>>, vector<double>> theTrainDataSet = SL_GEP_dataProcessor::loadDataSetOut("./datasets/trainDataSetCSV2.csv",0);


//    SL_GEP slgep(chroNum, theTrainDataSet.first, theTrainDataSet.second,needEpoch, theTrainDataSet.first[0].size(), presetFunctions,  argsLenOfADFs,
//                 mainProgramH, ADFH);
    SL_GEP slgep = SL_GEP_dataProcessor::loadSL_GEP("./theSL_GEPs/SL_GEP_WORK2_DIM_0.csv",
                                                    theTrainDataSet.first, theTrainDataSet.second,chroNum,needEpoch,
                                                    ANY_ONE_EQUAL_WAY);

    slgep.train();

    double disVal = 0.0;
    for (int i = 0 ; i < theTrainDataSet.second.size(); ++i){
        double predictVal = slgep.predict(theTrainDataSet.first[i]);
        disVal += pow((predictVal - theTrainDataSet.second[i]),2);
    }
    printf("distance:%f\r\n", sqrt(disVal));

}