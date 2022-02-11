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
#include "SL_ChromosomeDecoder_Thread.h"

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
    vector<SL_ChromosomeDecoder_Thread>chromosomeDecoderThreads;
    vector<vector<Chromosome>>chromosomeThreads;
    vector<double>minDistanceThreads;




    void initThread(const int &threadNum0);
};


#endif //CPPSOURCEFORLINUX_SL_GEP_THREAD_H
