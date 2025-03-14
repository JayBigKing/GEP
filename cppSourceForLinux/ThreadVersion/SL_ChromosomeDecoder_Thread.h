//
// Created by JAY on 2022/2/11.
//

#ifndef CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_THREAD_H
#define CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_THREAD_H

#include "../ChromosomeDecoder.h"
#include <stack>
class SL_ChromosomeDecoder_Thread :public ChromosomeDecoder{
public:
    SL_ChromosomeDecoder_Thread(){}
    SL_ChromosomeDecoder_Thread(ChromosomeRule &cr){
        setChromosomeRule(cr);
    }
    ~SL_ChromosomeDecoder_Thread(){}
    void setChromosome(Chromosome &chromosome);
private:
    void clearGlobalData();
    void recordMainProgramStackAndVec(vector<bool> &needADF);
    void recordADFStackAndVec(const vector<bool> &needADF);
    double mainProgramDecode();
    double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal);
    double ADFProgramDecode(Symbol &subFunctionSym, vector<double> inputArgsVal);
    void setSymbolSetInputArgs(int num, vector<double> args);




    stack<DecodeElement> mainOpStack;
    vector<stack<DecodeElement>>ADFOpStacks;

    vector<DecodeElement> mainOcVector;			//oc means operate code
    vector<vector<DecodeElement>>ADFOcVector;
};


#endif //CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_THREAD_H
