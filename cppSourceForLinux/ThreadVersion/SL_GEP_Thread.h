//
// Created by JAY on 2022/2/11.
//

#ifndef CPPSOURCEFORLINUX_SL_GEP_THREAD_H
#define CPPSOURCEFORLINUX_SL_GEP_THREAD_H

#include "../FunctionPreset.h"
#include "../Symbol.h"
#include "../ChromosomeRule.h"
#include "../Chromosome.h"
#include "../GEP.h"
#include "../SL_GEP.h"
#include "SL_ChromosomeDecoder_Thread.h"
#include <mutex>

struct SL_GEP_Thread_Index{
    int i;
    int j;
    SL_GEP_Thread_Index(int a,int b):i(a),j(b){}
    SL_GEP_Thread_Index():i(0),j(0){}
};

class SL_GEP_Thread : public GEP{
    SL_GEP_Thread(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
                  const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
                  const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
                  const int &threadNum = -1 , const bool &ifUseSuspendNum = true,const double &similarValue = 1e-6
            );

    SL_GEP_Thread(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
                  const int &needEpoch, const int &numOfTerminals,
                  const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
                  const int &threadNum = -1 , const bool &ifUseSuspendNum = true,const double &similarValue = 1e-6
    );

    SL_GEP_Thread(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
                  const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
                  const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
                  const int &threadNum = -1 , const bool &ifUseSuspendNum = true,const double &similarValue = 1e-6
    );

    SL_GEP_Thread(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
                  const int &needEpoch, const int &numOfTerminals,
                  const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
                  const int &threadNum = -1 , const bool &ifUseSuspendNum = true,const double &similarValue = 1e-6
    );

private:
    int threadNum;
    uint8_t whichRenewSymbolCountWay = ANY_ONE_EQUAL_WAY;
    vector<SL_ChromosomeDecoder_Thread>chromosomeDecoderThreads;        //染色体解码器
    vector<vector<Chromosome>>chromosomeThreads;                        //染色体
    vector<SL_GEP_Thread_Index>chromosomeNumThreads;
    vector<Chromosome>UChromosomeThreads;                               //染色体中间体
    vector<double>minDistanceThreads;                                   //最佳距离
    double minDistance ;
    double nowMinDistance;
    vector<pair<Chromosome, SL_GEP_Thread_Index>>bestChromosomeAndIndexThreads;                //最佳染色体和其编号
    pair<Chromosome,SL_GEP_Thread_Index>bestChromosomeAndIndex;


    //各随机数生成器
    vector<default_random_engine> FGeneratorThreads;
    vector<default_random_engine> BetaGeneratorThreads;
    vector<default_random_engine> SelectGeneratorThreads;
    vector<default_random_engine> YGeneratorThreads;
    vector<default_random_engine> GambleGeneratorThreads;
    vector<default_random_engine> CRGeneratorThreads;
    vector<default_random_engine> KGeneratorThreads;
    vector<default_random_engine> ACSGeneratorThreads;

    //最大权值
    vector<long double> totalWeightThreads;

    //每轮的权值相关
    vector<vector<double>>chromosomeWeightThreads;
    double maxWeightScore = 0;

    //锁相关
    mutex recordOneSymbolCountMutex;
    mutex setChromosomeWeightMutex;






    //类初始化相关函数
    void initThread(const int &threadNum0);
    void initRandGenerator();

    //train相关函数
    //种群初始化相关函数
    void initChromosomes();					//初始化染色体
    void initChromosomesThreadHelp(const int &index,int &detachDoneCount,mutex &detachDoneCountMutex );

    virtual void mutation() {}					//变异
    double getPsi(const int &a, const int &b);
    double getPhi(const int &bestSymbolNum, const int &chroIndexSymbolNum, const int &r1SymbolNum, const int &r2SymbolNum,
                  const double &F, const double &beta);
    void individualMutationThread(const int &threadIndex,const int &chroIndex, const int &r1, const int &r2, const double &F, const double &beta);
    void mainProgramFragmentMutationThread(const int &threadIndex,const int &chroIndex, const int &FragmentIndex, const int &r1, const int &r2,
                                     const double &F, const double &beta , const double  &yRandVal);
    void ADFFragmentMutationThread(const int &threadIndex,const int &chroIndex, const int &ADFIndex , const int &FragmentIndex, const int &r1,
                             const int &r2, const double &F, const double &beta, const double  &yRandVal);
    void mainProgramGetNewFragmentThread(const int &threadIndex,const int &chroIndex, const int &FragmentIndex );
    void ADFGetNewFragmentMutationThread(const int &threadIndex,const int &chroIndex, const int &ADFIndex, const int &FragmentIndex,bool authorType = true);

    virtual void crossover() {}						//交叉
    void individualCrossoverThread(const int &threadIndex,const int &chroIndex , const double &CR);
    void mainProgramFragmentCrossover(const int &chroIndex, const int &FragmentIndex, const double &CR, const int &K ,
                                      const double &randVal , const int &theJVal);
    void ADFFragmentCrossover(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const double &CR, const int &K,
                              const double &randVal, const int &theJVal);
    int getTotalExpressionLen();
    int getTotalExpressionIndex(int inThisExIndex, int ADFIndex = -1);

    virtual void selection() {}					//自然选择
    void individualSelection(const int &threadIndex,const int &chroIndex);
    void individualSelection(const int &threadIndex,const int &chroIndex,const double &randVal);


    void inheritanceProcess();				//遗传过程，优化单线程的程序，将突变，交叉，自然选择放在一起
    void inheritanceProcessThreadHelp(const int &index,int &detachDoneCount,mutex &detachDoneCountMutex);


    //基因库相关函数
    //某个位点的基因被选择的频繁程度的相关函数
    void recordOneSymbolCountThread(const int &threadIndex,const int &chroIndex, const double &score  = 1);               //选择程度的权值相同
    void setChromosomeWeightThread(const int &threadIndex,const int & chroIndex, const double& distance);            //选择程度权值有区别

    void recordOneSymbolCount(const int &threadIndex,const int &chroIndex, const double &score  = 1);               //选择程度的权值相同
    double setChromosomeWeight(const int &threadIndex,const int & chroIndex, const double& distance);            //选择程度权值有区别
    double adjustTotalWeight(const double &val);

    void recordAllCount();

    //距离相关函数
    double calculateDistance(const 	Chromosome &c);
    double EuclideanDis(const Chromosome &c);

    //记录最优解
    void clearBestChromosomeThread();
    void recordBestChromosomeThread(const int &threadIndex,const int &chroIndex,const double &dis);
    void recordBestChromosomeGlobal();
};


#endif //CPPSOURCEFORLINUX_SL_GEP_THREAD_H
