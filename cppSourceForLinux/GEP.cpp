//
// Created by JAY on 2022/2/9.
//

#include "initHelp.h"
#include "GEP.h"
GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
         WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum,
         double similarValue) :
        ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
        realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch) ,ifUseSuspendNum(ifUseSuspendNum),similarValue(similarValue),generator(time(NULL)),
        minDistance(numeric_limits<double>::max()),minDistanceOfThisEpoch(minDistance){

    //初始化symbolSet
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    initHelp(realTermVec, ansVec,inputADFHs);
}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, WhichFunction* presetFunctions,
         int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
    realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
    minDistance(numeric_limits<double>::max()),minDistanceOfThisEpoch(minDistance) {

    //初始化symbolSet
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    initHelp(realTermVec, ansVec, inputADFHs);

}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
         int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
         bool ifUseSuspendNum , double similarValue
) :
        ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
        realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
        minDistance(numeric_limits<double>::max()) ,minDistanceOfThisEpoch(minDistance){

    //初始化symbolSet
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    initHelp(realTermVec, ansVec, inputADFHs);
}


GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, int* presetFunctions,
         int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
    realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
    minDistance(numeric_limits<double>::max()) ,minDistanceOfThisEpoch(minDistance){

    //初始化symbolSet
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    initHelp(realTermVec, ansVec, inputADFHs);

}

GEP::GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
    const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
    const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
    const bool &ifUseSuspendNum ,const double &similarValue
):mainProgramH(mainPH),chromosomesNum(chroNum), chromosomes(chroNum),termAnsPairNum(ansVec.size()),numOfValInTerm(realTermVec[0].size()),
    epoch(0),needEpoch(needEpoch),ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),minDistance(numeric_limits<double>::max())
        ,minDistanceOfThisEpoch(minDistance)
{

    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants,presetFunctions, argsLenOfADFs);
    initHelp(realTermVec,ansVec,inputADFHs);
}

GEP::GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
    const int &needEpoch, const int &numOfTerminals,
    const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
    const bool &ifUseSuspendNum ,const double &similarValue
):mainProgramH(mainPH),chromosomesNum(chroNum), chromosomes(chroNum),termAnsPairNum(ansVec.size()),numOfValInTerm(realTermVec[0].size()),
  epoch(0),needEpoch(needEpoch),ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),minDistance(numeric_limits<double>::max())
        ,minDistanceOfThisEpoch(minDistance)
{
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions, argsLenOfADFs);
    initHelp(realTermVec,ansVec,inputADFHs);
}

GEP::GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
    const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
    const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
    const bool &ifUseSuspendNum ,const double &similarValue
):mainProgramH(mainPH),chromosomesNum(chroNum), chromosomes(chroNum),termAnsPairNum(ansVec.size()),numOfValInTerm(realTermVec[0].size()),
  epoch(0),needEpoch(needEpoch),ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),minDistance(numeric_limits<double>::max())
        ,minDistanceOfThisEpoch(minDistance)
  {
      SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals,constants, presetFunctions, argsLenOfADFs);
      initHelp(realTermVec,ansVec,inputADFHs);
  }

GEP::GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
    const int &needEpoch, const int &numOfTerminals,
    const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
    const bool &ifUseSuspendNum ,const double &similarValue
):mainProgramH(mainPH),chromosomesNum(chroNum), chromosomes(chroNum),termAnsPairNum(ansVec.size()),numOfValInTerm(realTermVec[0].size()),
  epoch(0),needEpoch(needEpoch),ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),minDistance(numeric_limits<double>::max())
        ,minDistanceOfThisEpoch(minDistance)
{
    SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals,presetFunctions, argsLenOfADFs);
    initHelp(realTermVec,ansVec,inputADFHs);
}

void GEP::initHelp(double *realTermVec, double *ansVec , int* inputADFHs) {
    //初始化ADFH
    for (int i = 0; i < ADFH.size(); ++i)
        ADFH[i] = inputADFHs[i];


    //初始化ChromosomeRule
    cr.init(mainProgramH, ADFH, symbolSet);

    //初始化各Chromosome
    for (int i = 0; i < chromosomesNum; ++i)
        chromosomes[i].init(cr);

//	bestChromosome.init(cr);

    //初始化realTermSet 和 ansSet
    for (int i = 0, j = 0; i < termAnsPairNum; ++i) {
        vector<double>tmp(numOfValInTerm);
        for (int k = 0; k < numOfValInTerm; ++k, ++j)
            tmp[k] = realTermVec[j];
        realTermSet[i] = tmp;
        ansSet[i] = ansVec[i];
    }



    initCouldChooseSet();
    initChromosomeSymbolCount2();

}
void GEP::initHelp(const vector<vector<double>> &realTermVec, const vector<double> &ansVec,
                   const vector<int> &inputADFHs) {
    //初始化ADFH、realTermSet 和 ansSet
    ADFH = inputADFHs;
    this->realTermSet = realTermVec;
    this->ansSet = ansVec;

    //初始化ChromosomeRule
    cr.init(mainProgramH, ADFH, symbolSet);

    //初始化各Chromosome
    for (int i = 0; i < chromosomesNum; ++i)
        chromosomes[i].init(cr);

    initCouldChooseSet();
    initChromosomeSymbolCount2();
}




void GEP::initChromosomeSymbolCount() {
    int theExLen = 0;
    int theExH = 0;
    int theExU = 0;
    int theExL = 0;
    vector<Symbol> &functionSet = cr.getSymbolSet().getFunctionSet();
    vector<Symbol> &subFunctionSet = cr.getSymbolSet().getSubFunctionSet();
    vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
    vector<Symbol> &inputArgSet = cr.getSymbolSet().getInputArgSet();
    unordered_map<int, double> tmpMap;

    //首先是mainProgram

    //前面H位
    theExLen = cr.getMainPR().totalLen;
    theExH = cr.getMainPR().h;
    theExL = cr.getMainPR().l;

    for (int i = 0; i < functionSet.size(); ++i)
        tmpMap[functionSet[i].getNum()] = 0;

    for (int i = 0; i < subFunctionSet.size(); ++i)
        tmpMap[subFunctionSet[i].getNum()] = 0;

    for (int i = 0; i < terminalSet.size(); ++i)
        tmpMap[terminalSet[i].getNum()] = 0;



    for (int i = 0; i < theExH; ++i)
        mainProgramSymbolCount.push_back(tmpMap);


    //后面L位

    tmpMap.clear();
    for (int i = 0; i < terminalSet.size(); ++i)
        tmpMap[terminalSet[i].getNum()] = 0;

    for (int i = 0; i < theExL; ++i)
        mainProgramSymbolCount.push_back(tmpMap);



    //然后是ADF
    int numOfADF = cr.getADFPR().size();
    initVectorHelp(ADFSymbolCount, numOfADF);

    for (int i = 0; i < numOfADF; ++i) {
        theExLen = cr.getADFPR(i).totalLen;
        theExH = cr.getADFPR(i).h;
        theExL = cr.getADFPR(i).l;
        theExU = cr.getADFPR(i).u;

        tmpMap.clear();
        for (int j = 0; j < functionSet.size(); ++j)
            tmpMap[functionSet[j].getNum()] = 0;

        for (int j = 0; j < theExU; ++j)
            tmpMap[inputArgSet[j].getNum()] = 0;

        for (int j = 0; j < theExH; ++j)
            ADFSymbolCount[i].push_back(tmpMap);


        tmpMap.clear();
        for (int j = 0; j < theExU; ++j)
            tmpMap[inputArgSet[j].getNum()] = 0;

        for (int j = 0; j < theExL; ++j)
            ADFSymbolCount[i].push_back(tmpMap);


    }




}

void GEP::initChromosomeSymbolCount2() {
    int theExH = 0;
//    int theExU = 0;
    int theExL = 0;
    //double meanVal = 1.0 / chromosomesNum;
    theMinSymbolCount = 1.0 / chromosomesNum;
    unordered_map<int,double> tmpMap;
    try {
        if (!couldChooseSetOfMainProgramFirst.size())
            throw "error : CouldChooseSet is not ininted!";
    }
    catch (const char *e) {
        printf("%s\r\n", e);
        exit(-1);
    }


    vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
    //首先是mainProgram

    //前面H位
    theExH = cr.getMainPR().h;
    theExL = cr.getMainPR().l;

    for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i)
        tmpMap[couldChooseSetOfMainProgramFirst[i]] = theMinSymbolCount;



    //将map存入vec
    for (int i = 0; i < theExH; ++i)
        mainProgramSymbolCount.push_back(tmpMap);


    //后面L位

    tmpMap.clear();
    for (int i = 0; i < terminalSet.size(); ++i)
        tmpMap[terminalSet[i].getNum()] = theMinSymbolCount;

    //将map存入vec
    for (int i = 0; i < theExL; ++i)
        mainProgramSymbolCount.push_back(tmpMap);

    //然后是ADF
    int numOfADF = cr.getADFPR().size();
    initVectorHelp(ADFSymbolCount, numOfADF);

    for (int i = 0; i < numOfADF; ++i) {
        theExH = cr.getADFPR(i).h;
        theExL = cr.getADFPR(i).l;

        tmpMap.clear();

        for (int j = 0; j < couldChooseSetOfADFFirst[i].size(); ++j)
            tmpMap[couldChooseSetOfADFFirst[i][j]] = theMinSymbolCount;

        for (int j = 0; j < theExH; ++j)
            ADFSymbolCount[i].push_back(tmpMap);


        tmpMap.clear();
        for (int j = 0; j < couldChooseSetOfADFSecond[i].size(); ++j)
            tmpMap[couldChooseSetOfADFSecond[i][j]] = theMinSymbolCount;

        for (int j = 0; j < theExL; ++j)
            ADFSymbolCount[i].push_back(tmpMap);


    }

}


//初始化可选集合
void GEP::initCouldChooseSet() {
    vector<Symbol> &functionSet = cr.getSymbolSet().getFunctionSet();
    vector<Symbol> &subFunctionSet = cr.getSymbolSet().getSubFunctionSet();
    vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
    vector<Symbol> &inputArgSet = cr.getSymbolSet().getInputArgSet();
    int numOfADF = cr.getADFPR().size();
    //首先是mainProgram
    for (int i = 0; i < functionSet.size(); ++i)
        couldChooseSetOfMainProgramFirst.push_back(functionSet[i].getNum());

    for (int i = 0; i < subFunctionSet.size(); ++i)
        couldChooseSetOfMainProgramFirst.push_back(subFunctionSet[i].getNum());

    for (int i = 0; i < terminalSet.size(); ++i)
        couldChooseSetOfMainProgramFirst.push_back(terminalSet[i].getNum());

    //然后是每一个ADF
    initVectorHelp(couldChooseSetOfADFFirst, numOfADF);
    initVectorHelp(couldChooseSetOfADFSecond, numOfADF);

    for (int i = 0; i < numOfADF; ++i) {
        int inputArgSetSize = inputArgSet.size();
        for (int j = 0; j < functionSet.size(); ++j)
            couldChooseSetOfADFFirst[i].push_back(functionSet[j].getNum());

        for (int j = 0; j < inputArgSetSize; ++j) {
            couldChooseSetOfADFFirst[i].push_back(inputArgSet[j].getNum());
            couldChooseSetOfADFSecond[i].push_back(inputArgSet[j].getNum());
        }

    }

}


void GEP::resetSymbolCount() {
    int numOfADF = cr.getADFPR().size();
    for (int i = 0; i < mainProgramSymbolCount.size(); ++i) {
        unordered_map<int, double> &refMap = mainProgramSymbolCount[i];
        for (auto it = refMap.begin(); it != refMap.end(); it++)
            it->second = theMinSymbolCount;
    }
    for (int i = 0; i < numOfADF; ++i) {
        for (int j = 0; j < ADFSymbolCount[i].size(); ++j) {
            unordered_map<int, double> &refMap = ADFSymbolCount[i][j];
            for (auto it = refMap.begin(); it != refMap.end(); it++)
                it->second = theMinSymbolCount;
        }

    }

}


int GEP::getRandSymbolNum(ChromosomePos cp, int ADFIndex) {
    using Range = std::uniform_int_distribution<>::param_type;
    vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
    uniform_int_distribution<int>distribution;
    switch (cp)
    {
        case MAIN_PROGRAM_FIRST:
            distribution.param(Range{ 0, (int)couldChooseSetOfMainProgramFirst.size() - 1 });
            return couldChooseSetOfMainProgramFirst[distribution(generator)];
        case MAIN_PROGRAM_SECOND:
            distribution.param(Range{ 0, (int)terminalSet.size() - 1 });
            return terminalSet[distribution(generator)].getNum();
        case ADF_FIRST:
            distribution.param(Range{ 0, (int)couldChooseSetOfADFFirst[ADFIndex].size() - 1 });
            return couldChooseSetOfADFFirst[ADFIndex][distribution(generator)];
        case ADF_SECOND:
            distribution.param(Range{ 0, (int)couldChooseSetOfADFSecond[ADFIndex].size() - 1 });
            return couldChooseSetOfADFSecond[ADFIndex][distribution(generator)];
        default:
            break;
    }


}

bool GEP::shouldContiue() {
    if (epoch < needEpoch) {
        epoch++;
        return true;
    }
    else {
        epoch++;
        return false;
    }
}
void GEP::recordBestChromosome(const int &chroIndex, const double & nowMinDistance) {
    if (nowMinDistance < minDistance) {
        minDistance = nowMinDistance;
        bestChromosomeAndIndex.first = chromosomes[chroIndex];
        bestChromosomeAndIndex.second = chroIndex;
    }


}


void GEP::recordSymbolCount(const int & symbolNum, const int &FragmentIndex, const double &score, const int & ADFIndex ) {
    try {
        if (ADFIndex == -1) {
            if (this->mainProgramSymbolCount[FragmentIndex].find(symbolNum) == this->mainProgramSymbolCount[FragmentIndex].end())
                throw "error : invaild symbol!";
            else
                this->mainProgramSymbolCount[FragmentIndex][symbolNum] = this->mainProgramSymbolCount[FragmentIndex][symbolNum] + score;
        }
        else {
            if (this->ADFSymbolCount[ADFIndex][FragmentIndex].find(symbolNum) == this->ADFSymbolCount[ADFIndex][FragmentIndex].end())
                throw "error : invaild symbol!";
            else
                this->ADFSymbolCount[ADFIndex][FragmentIndex][symbolNum] = this->ADFSymbolCount[ADFIndex][FragmentIndex][symbolNum] + score;
        }
    }
    catch (const char *e) {
        printf("%s\r\n", e);
        exit(-1);
    }

}

void GEP::setSymbolCountByRandVal(const int & symbolNum, const int &FragmentIndex, const double &randVal, const int & ADFIndex) {
    try {
        if (ADFIndex == -1) {
            if (this->mainProgramSymbolCount[FragmentIndex].find(symbolNum) == this->mainProgramSymbolCount[FragmentIndex].end())
                throw "error : invaild symbol!";
            else
                this->mainProgramSymbolCount[FragmentIndex][symbolNum] = (1 - randVal) * this->mainProgramSymbolCount[FragmentIndex][symbolNum] + randVal * theMinSymbolCount;
        }
        else {
            if (this->ADFSymbolCount[ADFIndex][FragmentIndex].find(symbolNum) == this->ADFSymbolCount[ADFIndex][FragmentIndex].end())
                throw "error : invaild symbol!";
            else
                this->ADFSymbolCount[ADFIndex][FragmentIndex][symbolNum] = (1 - randVal) * this->ADFSymbolCount[ADFIndex][FragmentIndex][symbolNum] + randVal * theMinSymbolCount;
        }
    }
    catch (const char *e) {
        printf("%s\r\n", e);
        exit(-1);
    }


}

