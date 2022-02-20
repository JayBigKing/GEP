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
  * @brief  �洢SL_GEP
  *
  * @param  nameHeadStr:�ļ�����ǰ�沿�֣�������ʶ�洢������Щ����
  * @param  useRelativePath:�Ƿ�ʹ�����λ�ã�Ĭ��Ϊʹ��
  *
  * @note
  *
  * @retval �ļ���
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
  * @brief  �洢SL_GEP
  *
  * @param  slGep:SL_GEP����
  * @param  saveFileName:�洢���ļ���
  *
  * @note   �洢symbolSet������ݣ�����Ⱦɫ��
  *
  * @note   ��һ�У�chroNum���ڶ��У�numOfTerminals�������У�PresetFunctions�������
  * @note   �����У�ADF��Ҫ�Ĳ�����������������У�mainProgramH�������У�ADFHs�������
  * @note   �����У�TAPairNum�������ݼ��������ڰ��У�needEpoch
  * @note   �ڰ��У�maxWeightScore���ھ��У�maxDistanceByNow
  * @note   ����Ϊһ�ԣ���һ��ΪmainProgramSymbolCount�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ����Ϊһ�ԣ���һ��ΪADFSymbolCounts�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ÿһ��ADFSymbolCount����֮�����һ�У��׸���ĸΪ��-���������ָ�
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ���ŵ�Ⱦɫ���mainProgram�ĸ���symbol
  * @note   ���ŵ�Ⱦɫ���ADFs�ĸ���symbol
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ���ž���
  * @note   count�ķ�ʽ
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

    //���ŵ�Ⱦɫ���mainProgram�ĸ���symbol
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
  * @brief  �洢SL_GEP
  *
  * @param  chromNum:Ⱦɫ��������Ĭ����ȡ�ļ��е�(����-1)
  * @param  TAPairNum:dataset��������Ĭ��ȡ�ļ��е�(����-1)
  * @param  needEpoch:��Ҫѵ�������ڣ�Ĭ��ȡ�ļ��е�(����-1)
  * @param  useTheCount:�Ƿ�ѡ�ļ��д洢���ϴ�ѵ����count
  * @param  whichRenewSymbolCountWay:�Ƿ����ļ�����ʾ�ĸ���countֵ�ķ���(����-1)
  *
  *
  * @retval None
  */
  /*
   *   * @note   ��һ�У�chroNum���ڶ��У�numOfTerminals�������У�PresetFunctions�������
  * @note   �����У�ADF��Ҫ�Ĳ�����������������У�mainProgramH�������У�ADFHs�������
  * @note   �����У�TAPairNum�������ݼ��������ڰ��У�needEpoch
  * @note   �ڰ��У�maxWeightScore���ھ��У�maxDistanceByNow*/
SL_GEP SL_GEP_dataProcessor::loadSL_GEP(const string &loadFileName,const int &chroNum, const int &TAPairNum,
                                        const int &needEpoch ,const bool &useTheCount,const uint8_t& whichRenewSymbolCountWay) {
    ifstream inFile(loadFileName, ios::in);
    string lineStr;
    vector<vector<string>> strArray;
    while (getline(inFile, lineStr))
    {
        // ��ɶ�ά��ṹ
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // ���ն��ŷָ�
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
    // д�ļ�
    ofstream outFile;
    outFile.open("data.csv", ios::out); // ��ģʽ��ʡ��
    outFile << "name" << ',' << "age" << ',' << "hobby" <<"," <<endl;
    outFile << "Mike" << ',' << 18 << ',' << "paiting" << "," <<endl;
    outFile << "Tom" << ',' << 25 << ',' << "football" << "," <<endl;
    outFile << "Jack" << ',' << 21 << ',' << "music" << "," <<endl;
    outFile << "-" << endl;
    outFile.close();
}

void SL_GEP_dataProcessor::testLoad() {
// ���ļ�
    ifstream inFile("data.csv", ios::in);
    string lineStr;
    vector<vector<string>> strArray;
    while (getline(inFile, lineStr))
    {
        // ��ӡ�����ַ���
        cout << lineStr << endl;
        // ��ɶ�ά��ṹ
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // ���ն��ŷָ�
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