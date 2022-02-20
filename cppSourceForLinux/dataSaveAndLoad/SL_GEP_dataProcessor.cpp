//
// Created by JAY on 2022/2/20.
//

#include "SL_GEP_dataProcessor.h"
#include <iostream>

#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>


/**
  * @brief  存储SL_GEP
  *
  * @param  nameHeadStr:文件名的前面部分，用来标识存储的是哪些数据
  * @param  useRelativePath:是否使用相对位置，默认为使用
  *
  * @note
  *
  * @retval 文件名
  */
const int SL_GEP_dataProcessor::startYearInSLDat = 1900;
const int SL_GEP_dataProcessor::startMonInSLDat = 1;
const string SL_GEP_dataProcessor::defaultSL_GEPNameHeadStr = "theSL_GEPs/SL_GEP";

string SL_GEP_dataProcessor::getFileNameByDateTime(string nameHeadStr, bool useRelativePath) {
    time_t now = time(NULL);
    tm *nowTm = localtime(&now);
    if(useRelativePath)
        return "./"+ nameHeadStr + "_" + to_string(nowTm->tm_year + startYearInSLDat) + "_" + to_string(nowTm->tm_mon + startMonInSLDat) + "_" +
               to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec) + ".csv";
    else
        return  nameHeadStr + "_" + to_string(nowTm->tm_year + startYearInSLDat) + "_" + to_string(nowTm->tm_mon + startMonInSLDat) + "_" +
                to_string(nowTm->tm_mday) + "_" + to_string(nowTm->tm_hour) + "_" + to_string(nowTm->tm_min) + "_" + to_string(nowTm->tm_sec) + ".csv";

}

/**
  * @brief  存储SL_GEP
  *
  * @param  slGep:SL_GEP对象
  * @param  saveFileName:存储的文件名
  *
  * @note   存储symbolSet相关数据，最优染色体
  *
  * @note   第一行：chroNum，第二行：numOfTerminals，第三行：PresetFunctions（多个）
  * @note   第四行：ADF需要的参数（多个），第五行：mainProgramH，第六行：ADFHs（多个）
  * @note   第七行：TAPairNum，即数据集条数，第八行：needEpoch
  * @note   第八行：maxWeightScore，第九行：maxDistanceByNow
  * @note   两行为一对，第一行为mainProgramSymbolCount的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   两行为一对，第一行为ADFSymbolCounts的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         每一个ADFSymbolCount结束之后，输出一行，首个字母为’-‘，用来分割
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   最优的染色体的mainProgram的各个symbol
  * @note   最优的染色体的ADFs的各个symbol
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   最优距离
  * @note   count的方式
  *
  * @retval None
  */
void SL_GEP_dataProcessor::saveSL_GEP(const SL_GEP &slGep,const string &saveFileName) {
    ofstream outFile;
    string theSaveFileName = (saveFileName.compare("")) ? saveFileName : getFileNameByDateTime(defaultSL_GEPNameHeadStr);
    //(!saveFileName.compare("")) ? saveFileName : getFileNameByDateTime("sl_gep")
    outFile.open(theSaveFileName,ios::out);
    ChromosomeRule cr = slGep.cr;
    SymbolSet &symbolSet = cr.getSymbolSet();
    vector<Symbol> &functionSet = symbolSet.getFunctionSet();
    vector<Symbol> &subFunctionSet = symbolSet.getSubFunctionSet();
    vector<ProgramRule> &ADFPR = cr.getADFPR();
    Chromosome bestChromosome = slGep.bestChromosomeAndIndex.first;
    const double minDistance = slGep.minDistance;

    vector<unordered_map<int, double>>mainProgramSymbolCount = slGep.mainProgramSymbolCount;
    const vector<int>&couldChooseSetOfMainProgramFirst = slGep.couldChooseSetOfMainProgramFirst;
    vector<Symbol>&terminalSet = cr.getSymbolSet().getTerminalSet();

    vector<vector<unordered_map<int, double>>>ADFSymbolCount = slGep.ADFSymbolCount;
    const vector<vector<int>>&couldChooseSetOfADFFirst = slGep.couldChooseSetOfADFFirst;
    const vector<vector<int>>&couldChooseSetOfADFSecond = slGep.couldChooseSetOfADFSecond;


    outFile<<slGep.chromosomesNum<<endl;
    outFile<<slGep.numOfValInTerm<<endl;
    for(auto item : functionSet)
        outFile<<item.getWhichFunction()<<",";
    outFile<<endl;

    for(auto item : subFunctionSet )
        outFile<<item.getNumOfInputArg()<<",";
    outFile<<endl;

    outFile<<cr.getMainPR().h<<endl;
    for(auto item : ADFPR)
        outFile<<item.h<<",";
    outFile<<endl;

    outFile<<slGep.termAnsPairNum<<endl;
    outFile<<slGep.needEpoch<<endl;

    outFile<<slGep.maxWeightScore<<endl;
    outFile<<slGep.maxDistanceByNow<<endl;

    //mainProgramSymbolCount
    bool ifInSecond = false;
    for(int i = 0 ; i < mainProgramSymbolCount.size() ; ++i){
        if(!ifInSecond && i >= cr.getMainPR().h){
            outFile<<"+"<<endl;
            ifInSecond = !ifInSecond;
        }
        outFile<<"s"<<",";
        if(i < cr.getMainPR().h){
            for(auto item : couldChooseSetOfMainProgramFirst)
                outFile<<item <<",";
        }else{
            for(auto item : terminalSet)
                outFile<<item.getNum()<<",";
        }
        outFile<<endl;
        outFile<<"c"<<",";
        if(i < cr.getMainPR().h){
            for(int j = 0 ; j <couldChooseSetOfMainProgramFirst.size(); ++j)
                outFile<<mainProgramSymbolCount[i][couldChooseSetOfMainProgramFirst[j]] <<",";
//            for(auto item : couldChooseSetOfMainProgramFirst)
//                outFile<<mainProgramSymbolCount[i][item] <<",";
        }else{
            for(auto item : terminalSet)
                outFile<<mainProgramSymbolCount[i][item.getNum()]<<",";
        }
        outFile<<endl;
    }
    outFile<<"*"<<endl;
    //ADFSymbolCounts
    int numOfADF = cr.getADFPR().size();
    for (int i = 0; i < numOfADF; ++i) {
        int theExH = cr.getADFPR(i).h;
        ifInSecond = false;
        //int theExL = cr.getADFPR(i).l;
        for (int j = 0; j < ADFSymbolCount[i].size(); ++j){
            if(!ifInSecond && j >= theExH){
                outFile<<"+"<<endl;
                ifInSecond = !ifInSecond;
            }
            outFile<<"s"<<",";
            if(j < theExH){
                for(auto item : couldChooseSetOfADFFirst[i])
                    outFile<<item<<",";
            }else{
                for(auto item : couldChooseSetOfADFSecond[i])
                    outFile<<item<<",";
            }
            outFile<<endl;

            outFile<<"c"<<",";
            if(j < theExH){
                for(int k = 0 ; k < couldChooseSetOfADFFirst[i].size() ; ++k)
                    outFile << ADFSymbolCount[i][j][couldChooseSetOfADFFirst[i][k]]<<",";
//                for(auto item : couldChooseSetOfADFFirst[i])
//                    outFile<<ADFSymbolCount[i][j][item]<<",";
            }else{
                for(int k = 0 ; k < couldChooseSetOfADFSecond[i].size() ; ++k)
                    outFile << ADFSymbolCount[i][j][couldChooseSetOfADFSecond[i][k]]<<",";
//                for(auto item : couldChooseSetOfADFSecond[i])
//                    outFile<<ADFSymbolCount[i][j][item]<<",";
            }
            outFile<<endl;
        }
        outFile<<"-"<<endl;
    }
    outFile<<"*"<<endl;

    //最优的染色体的mainProgram的各个symbol
    for(auto item : bestChromosome.mainProgramEx){
        outFile<<item<<",";
    }
        outFile<<endl;
    for(int i = 0 ; i < bestChromosome.ADFEx.size() ; ++i){
        for(auto item : bestChromosome.ADFEx[i])
            outFile<<item<<",";
        outFile<<endl;
    }

    outFile<<"*"<<endl;

    outFile<<minDistance<<endl;

    outFile<<slGep.whichRenewSymbolCountWay<<endl;

    outFile.close();
}

/**
  * @brief  存储SL_GEP
  *
  * @param  chromNum:染色体数量，默认是取文件中的(输入-1)
  * @param  TAPairNum:dataset的数量，默认取文件中的(输入-1)
  * @param  needEpoch:需要训练的周期，默认取文件中的(输入-1)
  * @param  useTheCount:是否选文件中存储的上次训练的count
  * @param  whichRenewSymbolCountWay:是否用文件中所示的更新count值的方法(输入-1)
  *
  *
  * @retval None
  */
  /*
   *   * @note   第一行：chroNum，第二行：numOfTerminals，第三行：PresetFunctions（多个）
  * @note   第四行：ADF需要的参数（多个），第五行：mainProgramH，第六行：ADFHs（多个）
  * @note   第七行：TAPairNum，即数据集条数，第八行：needEpoch
  * @note   第八行：maxWeightScore，第九行：maxDistanceByNow*/
SL_GEP SL_GEP_dataProcessor::loadSL_GEP(const string &loadFileName,const int &chroNum, const int &TAPairNum,
                                        const int &needEpoch ,const bool &useTheCount,const uint8_t& whichRenewSymbolCountWay) {
    ifstream inFile(loadFileName, ios::in);
    string lineStr;
    vector<vector<string>> strArray;
    while (getline(inFile, lineStr))
    {
        // 存成二维表结构
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // 按照逗号分隔
        while (getline(ss, str, ','))
            lineArray.push_back(str);
        strArray.push_back(lineArray);
    }
    int theChroNum = (chroNum == -1)? atoi(strArray[0][0]):chroNum;
    int numOfTerminal = atoi(strArray[1][0]);
    vector<int>PresetFunctions;
    vector<int>NumOfInputArgOfADF;
    vector<int>ADFHs;
    for(auto item : strArray[2])
        PresetFunctions.push_back(atoi(item));
    for(auto item : strArray[3])
        NumOfInputArgOfADF.push_back(atoi(item));
    int mainProgramH = atoi(strArray[4][0]);
    for(auto item : strArray[5])
        ADFHs.push_back(atoi(item));
    int theTAPairNum = (TAPairNum == -1)? atoi(strArray[6][0]) : TAPairNum;
    int theNeedEpoch = (needEpoch == -1)  ? atoi(strArray[7][0]) : needEpoch;
    double maxWeightScore = atof(strArray[8][0]);
    double maxDistanceByNow = atof(strArray[9][0]);

  }

void SL_GEP_dataProcessor::testSave() {
    // 写文件
    ofstream outFile;
    outFile.open("data.csv", ios::out); // 打开模式可省略
    outFile << "name" << ',' << "age" << ',' << "hobby" <<"," <<endl;
    outFile << "Mike" << ',' << 18 << ',' << "paiting" << "," <<endl;
    outFile << "Tom" << ',' << 25 << ',' << "football" << "," <<endl;
    outFile << "Jack" << ',' << 21 << ',' << "music" << "," <<endl;
    outFile << "-" << endl;
    outFile.close();
}

void SL_GEP_dataProcessor::testLoad() {
// 读文件
    ifstream inFile("data.csv", ios::in);
    string lineStr;
    vector<vector<string>> strArray;
    while (getline(inFile, lineStr))
    {
        // 打印整行字符串
        cout << lineStr << endl;
        // 存成二维表结构
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // 按照逗号分隔
        while (getline(ss, str, ','))
            lineArray.push_back(str);
        strArray.push_back(lineArray);
    }
    for (int i = 0; i < strArray.size(); ++i) {
        for (int j = 0; j < strArray[i].size(); j++)
            cout << strArray[i][j] << " ";

        cout << endl;

    }
}