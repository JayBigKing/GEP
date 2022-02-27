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
const char SL_GEP_dataProcessor::inTheSecondFlagChar = '+';
const char SL_GEP_dataProcessor::oneReadDoneFlagChar = '-';
const char SL_GEP_dataProcessor::setReadDoneFlagChar = '*';
const char SL_GEP_dataProcessor::mapKeyFlagChar = 's';
const char SL_GEP_dataProcessor::mapValFlagChar = 'c';
const char SL_GEP_dataProcessor::inTheLabelDataChar = 'l';
pair<vector<vector<double>>,vector<double>> SL_GEP_dataProcessor::theDataSet = pair<vector<vector<double>>,vector<double>>();

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
  * @note   ���ŵ�Ⱦɫ���mainProgram�ĸ���symbol
  * @note   ���ŵ�Ⱦɫ���ADFs�ĸ���symbol
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ���ž���
  * @note   count�ķ�ʽ
  * @note   ����Ϊһ�ԣ���һ��ΪmainProgramSymbolCount�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ����Ϊһ�ԣ���һ��ΪADFSymbolCounts�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ÿһ��ADFSymbolCount����֮�����һ�У��׸���ĸΪ��-���������ָ�
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
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


    //���ŵ�Ⱦɫ���mainProgram�ĸ���symbol
    for(auto item : bestChromosome.mainProgramEx){
        outFile<<item<<",";
    }
        outFile<<endl;

    //���ŵ�Ⱦɫ���ADFs�ĸ���symbol
    for(int i = 0 ; i < bestChromosome.ADFEx.size() ; ++i){
        for(auto item : bestChromosome.ADFEx[i])
            outFile<<item<<",";
        outFile<<endl;
    }

    outFile<<setReadDoneFlagChar<<endl;

    outFile<<minDistance<<endl;

    outFile<<(int)slGep.whichRenewSymbolCountWay<<endl;


    //mainProgramSymbolCount
    bool ifInSecond = false;
    for(int i = 0 ; i < mainProgramSymbolCount.size() ; ++i){
        if(!ifInSecond && i >= cr.getMainPR().h){
            outFile<<"+"<<endl;
            ifInSecond = !ifInSecond;
        }
        outFile<<mapKeyFlagChar<<",";
        if(i < cr.getMainPR().h){
            for(auto item : couldChooseSetOfMainProgramFirst)
                outFile<<item <<",";
        }else{
            for(auto item : terminalSet)
                outFile<<item.getNum()<<",";
        }
        outFile<<endl;
        outFile<<mapValFlagChar<<",";
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
    outFile<<setReadDoneFlagChar<<endl;
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
            outFile<<mapKeyFlagChar<<",";
            if(j < theExH){
                for(auto item : couldChooseSetOfADFFirst[i])
                    outFile<<item<<",";
            }else{
                for(auto item : couldChooseSetOfADFSecond[i])
                    outFile<<item<<",";
            }
            outFile<<endl;

            outFile<<mapValFlagChar<<",";
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
        outFile<<oneReadDoneFlagChar<<endl;
    }
    outFile<<setReadDoneFlagChar<<endl;

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
 *   * @note   ����Ϊһ�ԣ���һ��ΪmainProgramSymbolCount�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ����Ϊһ�ԣ���һ��ΪADFSymbolCounts�ĸ���λ�Ŀ�ѡ���ţ��ʼ�á�s����ʶ�����ڶ���Ϊ���Ӧ��count���ʼ��'c����ʶ����
  *         ÿһ��ADFSymbolCount����֮�����һ�У��׸���ĸΪ��-���������ָ�
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ���ŵ�Ⱦɫ���mainProgram�ĸ���symbol
  * @note   ���ŵ�Ⱦɫ���ADFs�ĸ���symbol
  *         ȫ������֮�����һ�У��׸���ĸΪ��*����������ʶ�洢���
  * @note   ���ž���
  * @note   count�ķ�ʽ
 * */


SL_GEP SL_GEP_dataProcessor::loadSL_GEP(const string &loadFileName,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
                                        const int &chroNum, const int &needEpoch ,
                                        const int8_t& whichRenewSymbolCountWay0) {
    try{
        vector<vector<string>> strArray = readCSV(loadFileName);

        int theChroNum = (chroNum == -1)? atoi(strArray[0][0].c_str()) : chroNum;
        int numOfTerminal = atoi(strArray[1][0].c_str());
        vector<int>PresetFunctions;
        vector<int>NumOfInputArgOfADF;
        vector<int>ADFHs;
        vector<unordered_map<int, double>>mainProgramSymbolCount ;
        vector<vector<unordered_map<int, double>>>ADFSymbolCount ;
        vector<int>bestChroMainProgram;
        vector<vector<int>>bestChroADFs;
        double minDistance;
        uint8_t whichRenewSymbolCountWay;

        for(auto item : strArray[2])
            PresetFunctions.push_back(atoi(item.c_str()));
        for(auto item : strArray[3])
            NumOfInputArgOfADF.push_back(atoi(item.c_str()));
        int mainProgramH = atoi(strArray[4][0].c_str());
        for(auto item : strArray[5])
            ADFHs.push_back(atoi(item.c_str()));
        int theNeedEpoch = (needEpoch == -1)  ? atoi(strArray[7][0].c_str()) : needEpoch;
        double maxWeightScore = atof(strArray[8][0].c_str());
        double maxDistanceByNow = atof(strArray[9][0].c_str());

        maxDistanceByNow = (isinf(maxDistanceByNow))?20000:maxDistanceByNow;


        int index = 10;
        int whichRenewSymbolCountWayIndex = -1;


        //����Ⱦɫ���mainProgram����symbols
        for(auto item : strArray[index])
            bestChroMainProgram.push_back(atoi(item.c_str()));
        index++;

        //����Ⱦɫ���ADF�ĸ���Symbols
        for(;strArray[index][0][0] != setReadDoneFlagChar;++index){
            vector<int>tmpADF;
            for(auto item : strArray[index])
                tmpADF.push_back(atoi(item.c_str()));
            bestChroADFs.push_back(tmpADF);
        }


        minDistance = atof(strArray[++index][0].c_str());                   //��Ϊ������setReadDoneFlagChar��������++
        whichRenewSymbolCountWayIndex = ++index;
        whichRenewSymbolCountWay = (whichRenewSymbolCountWay0 == -1) ?
                atoi(strArray[whichRenewSymbolCountWayIndex][0].c_str()) : whichRenewSymbolCountWay0;
        ++index;

        if(whichRenewSymbolCountWay == atoi(strArray[whichRenewSymbolCountWayIndex][0].c_str())){
            bool ifInSecond = false;
            for(; strArray[index][0][0] != setReadDoneFlagChar;++index){
                if(strArray[index][0][0] == inTheSecondFlagChar){
                    ifInSecond = !ifInSecond;
                    continue;
                }
                if(strArray[index][0][0] == mapKeyFlagChar){
                    unordered_map<int, double>tmpMap;
                    if(strArray[index+1][0][0] != mapValFlagChar || strArray[index].size() != strArray[index+1].size())
                        throw "error:no match the mainProgram map value";
                    for(int j = 1; j < strArray[index].size();++j){
                        tmpMap[atoi(strArray[index][j].c_str())] = atof(strArray[index+1][j].c_str());
                    }
                    mainProgramSymbolCount.push_back(tmpMap);
                    ++index;
                }else if(strArray[index][0][0] == mapValFlagChar){
                    ++index;
                }else{
                    throw "error:no match the mainProgram map value";
                }


            }

            ++index;                                                         //��Ϊ������setReadDoneFlagChar��������++
            vector<unordered_map<int, double>>tmpADFSymbolCount;
            for(; strArray[index][0][0] != setReadDoneFlagChar;++index){
                ifInSecond = false;
                if(strArray[index][0][0] == oneReadDoneFlagChar){
                    ADFSymbolCount.push_back(tmpADFSymbolCount);
                    tmpADFSymbolCount.clear();
                }else{
                    if(strArray[index][0][0] == inTheSecondFlagChar){
                        index++;
                    }
                    if(strArray[index][0][0] == mapKeyFlagChar){
                        unordered_map<int, double>tmpMap;
                        if(strArray[index+1][0][0] != mapValFlagChar || strArray[index].size() != strArray[index+1].size())
                            throw "error:no match the ADF map value";
                        for(int j = 1; j < strArray[index].size();++j){
                            tmpMap[atoi(strArray[index][j].c_str())] = atof(strArray[index+1][j].c_str());
                        }
                        tmpADFSymbolCount.push_back(tmpMap);
                        ++index;
                    }else if(strArray[index][0][0] == mapValFlagChar){
                        ++index;
                    }else{
                        throw "error:no match the ADF map value";
                    }

                }
            }
        }


        SL_GEP slGep(theChroNum,realTermVec,ansVec,theNeedEpoch,numOfTerminal,PresetFunctions,NumOfInputArgOfADF,mainProgramH,ADFHs);

        Chromosome bestChromosome(slGep.cr);
        bestChromosome.mainProgramEx = bestChroMainProgram;
        bestChromosome.ADFEx = bestChroADFs;
        pair<Chromosome, int>bestChromosomeAndIndex = make_pair(bestChromosome,0);
        if(whichRenewSymbolCountWay == atoi(strArray[whichRenewSymbolCountWayIndex][0].c_str())){
            slGep.mainProgramSymbolCount = mainProgramSymbolCount;
            slGep.ADFSymbolCount = ADFSymbolCount;
        }

        slGep.bestChromosomeAndIndex = bestChromosomeAndIndex;
        slGep.minDistance = minDistance;
        slGep.whichRenewSymbolCountWay = (uint8_t)whichRenewSymbolCountWay;
        slGep.maxWeightScore = maxWeightScore;
        slGep.maxDistanceByNow = maxDistanceByNow;

        slGep.chromosomes[0] = bestChromosome;
        return slGep;

    }catch (const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }

  }


SL_GEP SL_GEP_dataProcessor::loadSL_GEPAndDataSet(const string &loadFileName,const string &dataSetFileName,
                                                  const uint32_t &whichLabel,const int &chroNum,const int &needEpoch,
                                                  const uint8_t& whichRenewSymbolCountWay){
    loadDataSet(dataSetFileName,whichLabel);
    return loadSL_GEP(loadFileName,theDataSet.first,theDataSet.second,chroNum,needEpoch,whichRenewSymbolCountWay);

}

void SL_GEP_dataProcessor::loadDataSet(const string &dataSetFileName,const uint32_t &whichLabel) {
    try{
        vector<vector<string>> strArray = readCSV(dataSetFileName);
        theDataSet.first.clear();
        theDataSet.second.clear();
        for(auto item: strArray){
            int colIndex = 0;
            vector<double>tmpTerm;
            for(;item[colIndex][0] != inTheLabelDataChar;++colIndex)
                tmpTerm.push_back(atof(item[colIndex].c_str()));

            colIndex = colIndex + whichLabel * 2 + 1;           //����λ���ǵ�һ�� ��l�� eg:
                                                                // ��0����l x0 ��ӦcolIndex+1λ�ã�
                                                                // ��1����l x0 l x1 ��ӦcolIndex + 2 + 1
                                                                // ��2����l x0 l x1 l x2��ӦcolIndex + 2 + 2 + 1
            if(item.size() < colIndex)
                throw "error: data row `s len is not so len when read label";

            theDataSet.second.push_back(atof(item[colIndex].c_str()));
            theDataSet.first.push_back(tmpTerm);
        }
    }catch (const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }

}

pair<vector<vector<double>>, vector<double>> SL_GEP_dataProcessor::loadDataSetOut(const string &dataSetFileName,
                                                                                  const uint32_t &whichLabel) {

    loadDataSet(dataSetFileName,whichLabel);
    return theDataSet;
}

vector<vector<string>> SL_GEP_dataProcessor::readCSV(const string &csvFileName) {
    ifstream inFile(csvFileName, ios::in);
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
    return strArray;
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
void SL_GEP_dataProcessor::testLoadDataSet() {
    loadDataSet("./datasets/dataSetCSV.csv",1);
    for(int i = 0 ; i < theDataSet.second.size() ; ++i){

        for(int j = 0; j < theDataSet.first[i].size();++j)
            printf("%f   ",theDataSet.first[i][j]);
        printf("%f  \r\n",theDataSet.second[i]);
    }

}