//
// Created by JAY on 2022/2/11.
//

#include "SL_GEP_Thread.h"
#include "unistd.h"
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
            chromosomeThreads.push_back(chromosomes);
        }else{
            vector<Chromosome>().swap(chromosomes);             //清空原来的空间
            for(int i = 0 ; i < threadNum ; ++i){
                int nowThreadChromosomeNum;
                chromosomeDecoderThreads.push_back(SL_ChromosomeDecoder_Thread(cr));
                minDistanceThreads.push_back(0.0);
                if(i != threadNum - 1)
                    nowThreadChromosomeNum = oneThreadChromosomeNum;
                else
                    nowThreadChromosomeNum = lastThreadChromosomeNum;

                vector<Chromosome> tmpChromosome(nowThreadChromosomeNum);
                for(int k = 0; k < nowThreadChromosomeNum ;++k )
                    tmpChromosome[k].init(cr);
                chromosomeThreads.push_back(tmpChromosome);
            }
        }

    }catch (const char * &e){
        printf("%s\r\n",e);
    }


}