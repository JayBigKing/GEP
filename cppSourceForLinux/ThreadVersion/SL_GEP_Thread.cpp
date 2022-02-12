//
// Created by JAY on 2022/2/11.
//

#include "SL_GEP_Thread.h"
#include "unistd.h"
#include"FunctionPreset.h"
#include "../GA_HelpFunc.h"
#include <thread>
SL_GEP_Thread::SL_GEP_Thread(const int &chroNum, const vector<vector<double>> &realTermVec, const vector<double> &ansVec,
                             const int &needEpoch, const int &numOfTerminals, const vector<double> &constants,
                             const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs,
                             const int &mainPH, const vector<int> &inputADFHs, const int &threadNum,
                             const bool &ifUseSuspendNum, const double &similarValue)
                             :GEP(chroNum,realTermVec,ansVec,needEpoch,numOfTerminals,constants,presetFunctions,
                                  argsLenOfADFs,mainPH,inputADFHs,ifUseSuspendNum,similarValue)
{

}
SL_GEP_Thread::SL_GEP_Thread(const int &chroNum, const vector<vector<double>> &realTermVec, const vector<double> &ansVec,
                             const int &needEpoch, const int &numOfTerminals,
                             const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs,
                             const int &mainPH, const vector<int> &inputADFHs, const int &threadNum,
                             const bool &ifUseSuspendNum, const double &similarValue) {

}
SL_GEP_Thread::SL_GEP_Thread(const int &chroNum, const vector<vector<double>> &realTermVec, const vector<double> &ansVec,
                             const int &needEpoch, const int &numOfTerminals, const vector<double> &constants,
                             const vector<int> &presetFunctions, const vector<int> &argsLenOfADFs, const int &mainPH,
                             const vector<int> &inputADFHs, const int &threadNum, const bool &ifUseSuspendNum,
                             const double &similarValue) {

}

SL_GEP_Thread::SL_GEP_Thread(const int &chroNum, const vector<vector<double>> &realTermVec, const vector<double> &ansVec,
                             const int &needEpoch, const int &numOfTerminals, const vector<int> &presetFunctions,
                             const vector<int> &argsLenOfADFs, const int &mainPH, const vector<int> &inputADFHs,
                             const int &threadNum, const bool &ifUseSuspendNum, const double &similarValue) {



}

void SL_GEP_Thread::initThread(const int &threadNum0) {
    try{
        if(threadNum0 ==  -1)
            threadNum = sysconf( _SC_NPROCESSORS_CONF);         //默认就是有多少核心就分多少线程
        else if(threadNum0 >= 0)
            threadNum = (threadNum0 == 0 ? 1 : threadNum0);
        else
            throw "error: thread num can not be low than zero!";

        int oneThreadChromosomeNum = chromosomesNum / threadNum;
        int lastThreadChromosomeNum = chromosomesNum - threadNum * oneThreadChromosomeNum;
        if(threadNum == 1){
            chromosomeDecoderThreads.push_back(SL_ChromosomeDecoder_Thread(cr));
            minDistanceThreads.push_back(0.0);
            bestChromosomeAndIndexThreads.push_back(bestChromosomeAndIndex);

            chromosomeThreads.push_back(chromosomes);
            for(int i = 0; i < chromosomesNum ; ++i)
                chromosomeNumThreads.push_back(SL_GEP_Thread_Index(0,i));
            UChromosomeThreads.push_back(chromosomes[0]);

            //初始化每轮的权值相关的函数
            vector<double>tmpWeightVec(chromosomesNum);
            chromosomeWeightThreads.push_back(tmpWeightVec);

        }else{
            vector<Chromosome>().swap(chromosomes);             //清空原来的空间
            for(int i = 0 ; i < threadNum ; ++i){
                int nowThreadChromosomeNum;
                chromosomeDecoderThreads.push_back(SL_ChromosomeDecoder_Thread(cr));

                if(i != threadNum - 1)
                    nowThreadChromosomeNum = oneThreadChromosomeNum;
                else
                    nowThreadChromosomeNum = (lastThreadChromosomeNum == 0) ? oneThreadChromosomeNum : lastThreadChromosomeNum;

                //初始化染色体群
                vector<Chromosome> tmpChromosome(nowThreadChromosomeNum);
                for(int k = 0; k < nowThreadChromosomeNum ;++k ){
                    tmpChromosome[k].init(cr);
                    chromosomeNumThreads.push_back(SL_GEP_Thread_Index(i,k));
                }

                chromosomeThreads.push_back(tmpChromosome);

                //初始化染色体中间体
                UChromosomeThreads.push_back(Chromosome());
                UChromosomeThreads[i].init(cr);

                //初始化最佳距离和相关的索引与染色体
                minDistanceThreads.push_back(0.0);
                bestChromosomeAndIndexThreads.push_back(bestChromosomeAndIndex);

                //初始化最大权值
                totalWeightThreads.push_back(0);

                //初始化每轮的权值相关的函数
                vector<double>tmpWeightVec(nowThreadChromosomeNum);
                chromosomeWeightThreads.push_back(tmpWeightVec);
            }
        }

        initRandGenerator();

    }catch (const char * &e){
        printf("%s\r\n",e);
    }


}

void SL_GEP_Thread::initRandGenerator() {
    uniform_int_distribution<uint64_t>initDistribution(0, numeric_limits<uint64_t>::max());
    for(int i = 0 ; i < threadNum ; ++i){
        FGeneratorThreads[i].seed(initDistribution(generator));
        BetaGeneratorThreads[i].seed(initDistribution(generator));
        SelectGeneratorThreads[i].seed(initDistribution(generator));
        YGeneratorThreads[i].seed(initDistribution(generator));
        GambleGeneratorThreads[i].seed(initDistribution(generator));
        CRGeneratorThreads[i].seed(initDistribution(generator));
        KGeneratorThreads[i].seed(initDistribution(generator));
        ACSGeneratorThreads[i].seed(initDistribution(generator));
    }

}
void SL_GEP_Thread::initChromosomes() {
    int detachDoneCount = 0;
    mutex detachDoneCountMutex;
    vector<thread>initChromosomesThreadHandler;
    clearBestChromosomeThread();
    for(int i = 0 ; i < threadNum; ++i){
        initChromosomesThreadHandler.push_back(
                thread(&SL_GEP_Thread::initChromosomesThreadHelp,
                       this,std::ref(i),std::ref(detachDoneCount),std::ref(detachDoneCountMutex)));
        initChromosomesThreadHandler[i].detach();
    }


    for(;detachDoneCount < threadNum;){}

    recordBestChromosomeGlobal();
    if(whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
        recordAllCount();

}

void SL_GEP_Thread::initChromosomesThreadHelp(const int &index, int &detachDoneCount,mutex &detachDoneCountMutex) {

    int theMExH = cr.getMainPR().h;
    int theMExL = cr.getMainPR().l;
    int theAExH = 0;
    int theAExL = 0;
    int numOfADF = cr.getADFPR().size();
    double nowDis = 0.0;

    for (int i = 0; i < chromosomeThreads[index].size(); ++i) {
        //先mainProgram
        int k = 0;
        for (int j = 0; j < theMExH; ++j, ++k)
            chromosomeThreads[index][i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
        for(int j = 0 ; j < theMExL ; ++j ,++k)
            chromosomeThreads[index][i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


        //后ADFs
        for (int t = 0; t < numOfADF; ++t) {
            k = 0;
            theAExH = cr.getADFPR(t).h;
            theAExL = cr.getADFPR(t).l;
            for (int j = 0; j < theAExH; ++j, ++k)
                chromosomeThreads[index][i].ADFEx[t][k] = getRandSymbolNum(ADF_FIRST,t);

            for (int j = 0; j < theAExL; ++j, ++k)
                chromosomeThreads[index][i].ADFEx[t][k] = getRandSymbolNum(ADF_SECOND,t);

        }

        nowDis = calculateDistance(chromosomes[i]);
        if(whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
            setChromosomeWeightThread(index,i, nowDis);


        recordBestChromosomeThread(index,i,nowDis);

        if(whichRenewSymbolCountWay == ANY_ONE_EQUAL_WAY)
            recordOneSymbolCountThread(index,i);
    }


    detachDoneCountMutex.lock();
    detachDoneCount++;
    detachDoneCountMutex.unlock();
}

void SL_GEP_Thread::inheritanceProcess() {
    int detachDoneCount = 0;
    mutex detachDoneCountMutex;
    vector<thread>inheritanceProcessThreadHandler;
    clearBestChromosomeThread();
    for(int i = 0 ; i < threadNum ;++i)
        inheritanceProcessThreadHandler.emplace_back(&SL_GEP_Thread::inheritanceProcessThreadHelp,
                                                     this,std::ref(i),std::ref(detachDoneCount),std::ref(detachDoneCountMutex));

    for(;detachDoneCount < threadNum;){}

    if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
        recordAllCount();
}
void SL_GEP_Thread::inheritanceProcessThreadHelp(const int &index, int &detachDoneCount, mutex &detachDoneCountMutex) {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    uniform_int_distribution<int> indexDistribution(0, chromosomesNum);
    for(int i = 0; i < chromosomeThreads[index].size();++i){
        double F = distribution(FGeneratorThreads[index]);
        double beta = distribution(BetaGeneratorThreads[index]);
        int r1 = indexDistribution(SelectGeneratorThreads[index]),
                r2 = indexDistribution(SelectGeneratorThreads[index]);
        double CR = distribution(CRGeneratorThreads[index]);
        double ACSRandVal = distribution(ACSGeneratorThreads[index]);

        individualMutationThread(index,i, r1, r2, F, beta);			//遗传

        individualCrossoverThread(index,i,CR);						//交叉

        if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
            individualSelection(index,i, ACSRandVal);							//自然选择
        else if (whichRenewSymbolCountWay == ANY_ONE_EQUAL_WAY) {
            individualSelection(index,i);
            recordOneSymbolCount(index,i);
        }
    }

    detachDoneCountMutex.lock();
    detachDoneCount++;
    detachDoneCountMutex.unlock();
}

//变异相关
void SL_GEP_Thread::individualMutationThread(const int &threadIndex, const int &chroIndex, const int &r1, const int &r2,
                                             const double &F, const double &beta) {

    int mainProgramExLen = chromosomeThreads[threadIndex][chroIndex].mainProgramEx.size();

    int numOfADFs = chromosomeThreads[threadIndex][chroIndex].ADFEx.size();

    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < mainProgramExLen; ++i)
        mainProgramFragmentMutationThread(chroIndex, i, r1, r2, F, beta,distribution(YGeneratorThreads[threadIndex]));

    for (int i = 0; i < numOfADFs; ++i) {
        int thisADFLen = chromosomeThreads[threadIndex][chroIndex].ADFEx[i].size();
        for (int j = 0; j < thisADFLen; ++j) {
            ADFFragmentMutationThread(chroIndex, i, j, r1, r2, F, beta, distribution(YGeneratorThreads[threadIndex]));
        }
    }
}

//变异相关
//变异系数
double SL_GEP_Thread::getPsi(const int &a, const int &b) {
    return (a != b) ? 1 : 0;
}
double SL_GEP_Thread::getPhi(const int &bestSymbolNum, const int &chroIndexSymbolNum, const int &r1SymbolNum,
                             const int &r2SymbolNum, const double &F, const double &beta) {
    return 1 - (1 - F * getPsi(bestSymbolNum, chroIndexSymbolNum)) * (1 - beta * getPsi(r1SymbolNum, r2SymbolNum));
}


//变异相关
//主程序变异
void SL_GEP_Thread::mainProgramFragmentMutationThread(const int &threadIndex,const int &chroIndex, const int &FragmentIndex, const int &r1,
                                                      const int &r2, const double &F, const double &beta,
                                                      const double &yRandVal) {
    double Phi = getPhi(chromosomeThreads[threadIndex][chroIndex].mainProgramEx[FragmentIndex],
                        chromosomeThreads[bestChromosomeAndIndex.second.i][bestChromosomeAndIndex.second.j].mainProgramEx[FragmentIndex],
                        chromosomeThreads[chromosomeNumThreads[r1].i][chromosomeNumThreads[r1].j].mainProgramEx[FragmentIndex],
                        chromosomeThreads[chromosomeNumThreads[r2].i][chromosomeNumThreads[r2].j].mainProgramEx[FragmentIndex],
                        F, beta);
    if (yRandVal <= Phi)
        mainProgramGetNewFragmentThread(threadIndex,chroIndex, FragmentIndex);
    else
        UChromosomeThreads[threadIndex].mainProgramEx[FragmentIndex] = chromosomeThreads[threadIndex][chroIndex].mainProgramEx[FragmentIndex];
}
void SL_GEP_Thread::mainProgramGetNewFragmentThread(const int &threadIndex, const int &chroIndex,
                                                    const int &FragmentIndex) {
    int theMExH = cr.getMainPR().h;
    double probabilityDenominator = 0.0;
    double probabilityCount = 0.0;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    if (FragmentIndex < theMExH) {
        vector<double>symbolProbability(couldChooseSetOfMainProgramFirst.size());
        for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i) {
            symbolProbability[i] = (double)this->mainProgramSymbolCount[FragmentIndex][couldChooseSetOfMainProgramFirst[i]];			//只是暂存，后面会分布在0-1
            probabilityDenominator += symbolProbability[i];
        }


//		if (probabilityDenominator == 0.0) {
        if (distribution(YGeneratorThreads[threadIndex]) > 0.9) {
            UChromosomeThreads[threadIndex].mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
        }
        else {
            for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i)
                symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


            UChromosomeThreads[threadIndex].mainProgramEx[FragmentIndex] =
                    couldChooseSetOfMainProgramFirst[getTheGambleIndex(distribution(GambleGeneratorThreads[threadIndex]), symbolProbability)];

        }

    }
    else {
        vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
        vector<double>symbolProbability(terminalSet.size());
        for (int i = 0 ; i < terminalSet.size(); ++i) {
            symbolProbability[i] = this->mainProgramSymbolCount[FragmentIndex][terminalSet[i].getNum()];			//只是暂存，后面会分布在0-1
            probabilityDenominator += symbolProbability[i];
        }


//		if (probabilityDenominator == 0.0) {
        if (distribution(YGeneratorThreads[threadIndex]) > 0.9){
            UChromosomeThreads[threadIndex].mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


        }
        else {
            for (int i = 0; i < terminalSet.size(); ++i)
                symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


            UChromosomeThreads[threadIndex].mainProgramEx[FragmentIndex] =
                    terminalSet[getTheGambleIndex(distribution(GambleGeneratorThreads[threadIndex]), symbolProbability)].getNum();
        }



    }
}

//变异相关
//ADF变异
void SL_GEP_Thread::ADFFragmentMutationThread(const int &threadIndex, const int &chroIndex, const int &ADFIndex,
                                              const int &FragmentIndex, const int &r1, const int &r2, const double &F,
                                              const double &beta, const double &yRandVal) {
    double Phi = getPhi(chromosomeThreads[threadIndex][chroIndex].ADFEx[ADFIndex][FragmentIndex],
                        chromosomeThreads[bestChromosomeAndIndex.second.i][bestChromosomeAndIndex.second.j].ADFEx[ADFIndex][FragmentIndex],
                        chromosomeThreads[chromosomeNumThreads[r1].i][chromosomeNumThreads[r1].j].ADFEx[ADFIndex][FragmentIndex],
                        chromosomeThreads[chromosomeNumThreads[r1].i][chromosomeNumThreads[r1].j].ADFEx[ADFIndex][FragmentIndex],
                        F, beta);
    if (yRandVal <= Phi)
        ADFGetNewFragmentMutationThread(threadIndex,chroIndex,ADFIndex,FragmentIndex);
    else
        UChromosomeThreads[threadIndex].ADFEx[ADFIndex][FragmentIndex] = chromosomeThreads[threadIndex][chroIndex].ADFEx[ADFIndex][FragmentIndex];

}
//变异相关
//ADF变异
void SL_GEP_Thread::ADFGetNewFragmentMutationThread(const int &threadIndex, const int &chroIndex, const int &ADFIndex,
                                                    const int &FragmentIndex, bool authorType) {
    if (authorType) {
        int theAExH = cr.getADFPR(ADFIndex).h;
        if (FragmentIndex < theAExH)
            UChromosomeThreads[threadIndex].ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_FIRST, ADFIndex);
        else
            UChromosomeThreads[threadIndex].ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_SECOND, ADFIndex);
    }
}


void SL_GEP_Thread::recordOneSymbolCountThread(const int &threadIndex,const int &chroIndex, const double &score) {
    recordOneSymbolCountMutex.lock();
    recordOneSymbolCount(threadIndex,chroIndex,score);
    recordOneSymbolCountMutex.unlock();

}

void SL_GEP_Thread::recordOneSymbolCount(const int &threadIndex, const int &chroIndex, const double &score) {
    int mainPSize = chromosomeThreads[threadIndex][chroIndex].mainProgramEx.size();
    int numOfADF = chromosomeThreads[threadIndex][chroIndex].ADFEx.size();
    for (int i = 0; i < mainPSize; ++i) {
        recordSymbolCount(chromosomeThreads[threadIndex][chroIndex].mainProgramEx[i], i,score);
    }

    for (int i = 0; i < numOfADF; ++i) {
        int ADFLen = chromosomeThreads[threadIndex][chroIndex].ADFEx[i].size();
        for (int j = 0; j < ADFLen; ++j) {
            recordSymbolCount(chromosomeThreads[threadIndex][chroIndex].ADFEx[i][j], j, score, i);
        }
    }
}

void SL_GEP_Thread::setChromosomeWeightThread(const int &threadIndex, const int &chroIndex, const double &distance) {
//    setChromosomeWeightMutex.lock();
    setChromosomeWeight(threadIndex,chroIndex,distance);
//    setChromosomeWeightMutex.unlock();

}
double SL_GEP_Thread::setChromosomeWeight(const int &threadIndex, const int &chroIndex, const double &distance) {
    chromosomeWeightThreads[threadIndex][chroIndex] = distance;
    totalWeightThreads[threadIndex] = adjustTotalWeight(totalWeightThreads[threadIndex] + distance );
}

double SL_GEP_Thread::adjustTotalWeight(const double &val) {
    if(isinf(val))
        return getTheMaxReal();
    else
        return val;
}

void SL_GEP_Thread::recordAllCount() {
    double totalWeight = 0;
    for(int i = 0 ; i < threadNum ;++i){
        totalWeight = adjustTotalWeight(totalWeight + totalWeightThreads[i]);
        totalWeightThreads[i] = 0.0;
    }

    if (totalWeight) {
        if (whichRenewSymbolCountWay == LOW_ONE_FIRST) {
            for(int i = 0 ; i < threadNum ; ++i)
                for(int j = 0 ; j < chromosomeWeightThreads[i].size();++j)
                    recordOneSymbolCount(i,j,chromosomeWeightThreads[i][j] / totalWeight);

        }
        else {
            int theBestIndex_i = 0;
            int theBestIndex_j = 0;
            long double adjustTotalWeight = 0.0;
            double lastBestWeightScore = -1;
            for(int i = 0 ; i < threadNum ;++i)
                for(int j = 0 ; j < chromosomeWeightThreads[i].size();++j){
                    double inputWeightScore = (chromosomeWeightThreads[i][j] == 0.0 ?
                            maxWeightScore : (totalWeight / chromosomeWeightThreads[i][j]) / chromosomesNum);
                    adjustTotalWeight += inputWeightScore;
                    if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT)
                        chromosomeWeightThreads[i][j] = inputWeightScore;

                    if (whichRenewSymbolCountWay == BEST_ONE_ONLY) {
                        if (inputWeightScore > lastBestWeightScore) {
                            lastBestWeightScore = inputWeightScore;
                            theBestIndex_i = i;
                            theBestIndex_j = j;
                        }
                    }

                    if (inputWeightScore > maxWeightScore)
                        maxWeightScore = inputWeightScore;
                }

            if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT) {
                for(int i = 0 ; i < threadNum ; ++i)
                    for(int j = 0 ; j < chromosomeWeightThreads[i].size();++j)
                    recordOneSymbolCount(i,j, chromosomeWeightThreads[i][j] / adjustTotalWeight);
            }
            else if (whichRenewSymbolCountWay == BEST_ONE_ONLY) {
                recordOneSymbolCount(theBestIndex_i,theBestIndex_j, lastBestWeightScore / adjustTotalWeight);
            }


        }

    }
    else {
        int meanVal = 1 / chromosomesNum;
        for(int i = 0 ; i < threadNum ; ++i)
            for(int j = 0 ; j < chromosomeWeightThreads[i].size();++j)
                recordOneSymbolCount(i,j,meanVal);
    }

}

//每轮先将各线程当前最优的距离都设置成最差的
void SL_GEP_Thread::clearBestChromosomeThread() {
    const double &maxRealVal = getTheMaxReal();
    minDistance = maxRealVal;
    for(int i = 0; i < threadNum;++i)
        minDistanceThreads[i] = maxRealVal;

}

//多线程：记录各线程当前最优的染色体和距离
void SL_GEP_Thread::recordBestChromosomeThread(const int &threadIndex, const int &chroIndex, const double &dis) {
    if(dis < minDistanceThreads[threadIndex]){
        minDistanceThreads[threadIndex] = dis;
        bestChromosomeAndIndexThreads[threadIndex] = pair<Chromosome, SL_GEP_Thread_Index>(chromosomeThreads[threadIndex][chroIndex],SL_GEP_Thread_Index(threadIndex,chroIndex));
    }
}
//单线程：多线程记录以后，再依次比较各线程中最优染色体和距离，记录当前最优染色体并更新历史最优染色体
void SL_GEP_Thread::recordBestChromosomeGlobal() {
    pair<Chromosome,SL_GEP_Thread_Index> bestPair;
    for(int i = 0 ; i < threadNum ;++i){
        if(minDistanceThreads[i] < nowMinDistance){
            nowMinDistance = minDistanceThreads[i];
            bestPair = bestChromosomeAndIndexThreads[i];
        }
    }
    if(nowMinDistance < minDistance){
        minDistance = nowMinDistance;
        bestChromosomeAndIndex = bestPair;
    }
}