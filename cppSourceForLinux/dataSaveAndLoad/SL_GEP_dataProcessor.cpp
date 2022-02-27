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
  * @note   最优的染色体的mainProgram的各个symbol
  * @note   最优的染色体的ADFs的各个symbol
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   最优距离
  * @note   count的方式
  * @note   两行为一对，第一行为mainProgramSymbolCount的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   两行为一对，第一行为ADFSymbolCounts的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         每一个ADFSymbolCount结束之后，输出一行，首个字母为’-‘，用来分割
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
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


    //最优的染色体的mainProgram的各个symbol
    for(auto item : bestChromosome.mainProgramEx){
        outFile<<item<<",";
    }
        outFile<<endl;

    //最优的染色体的ADFs的各个symbol
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
 *   * @note   两行为一对，第一行为mainProgramSymbolCount的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   两行为一对，第一行为ADFSymbolCounts的各点位的可选符号（最开始用‘s’标识），第二行为其对应的count（最开始用'c‘标识），
  *         每一个ADFSymbolCount结束之后，输出一行，首个字母为’-‘，用来分割
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   最优的染色体的mainProgram的各个symbol
  * @note   最优的染色体的ADFs的各个symbol
  *         全部结束之后输出一行，首个字母为’*‘，用来标识存储完毕
  * @note   最优距离
  * @note   count的方式
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


        //最优染色体的mainProgram各个symbols
        for(auto item : strArray[index])
            bestChroMainProgram.push_back(atoi(item.c_str()));
        index++;

        //最优染色体的ADF的各个Symbols
        for(;strArray[index][0][0] != setReadDoneFlagChar;++index){
            vector<int>tmpADF;
            for(auto item : strArray[index])
                tmpADF.push_back(atoi(item.c_str()));
            bestChroADFs.push_back(tmpADF);
        }


        minDistance = atof(strArray[++index][0].c_str());                   //因为现在是setReadDoneFlagChar，所以先++
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

            ++index;                                                         //因为现在是setReadDoneFlagChar，所以先++
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

            colIndex = colIndex + whichLabel * 2 + 1;           //现在位置是第一个 ‘l’ eg:
                                                                // 第0个，l x0 对应colIndex+1位置，
                                                                // 第1个，l x0 l x1 对应colIndex + 2 + 1
                                                                // 第2个，l x0 l x1 l x2对应colIndex + 2 + 2 + 1
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
        // 存成二维表结构
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // 按照逗号分隔
        while (getline(ss, str, ','))
            lineArray.push_back(str);
        strArray.push_back(lineArray);
    }
    return strArray;
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
void SL_GEP_dataProcessor::testLoadDataSet() {
    loadDataSet("./datasets/dataSetCSV.csv",1);
    for(int i = 0 ; i < theDataSet.second.size() ; ++i){

        for(int j = 0; j < theDataSet.first[i].size();++j)
            printf("%f   ",theDataSet.first[i][j]);
        printf("%f  \r\n",theDataSet.second[i]);
    }

}