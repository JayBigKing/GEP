//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_H
#define CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_H


#include "ChromosomeDecoder.h"
#include <stack>
class SL_ChromosomeDecoder : public ChromosomeDecoder
{
public:
    SL_ChromosomeDecoder(){}
    ~SL_ChromosomeDecoder(){}
    void setChromosome(Chromosome &chromosome);
private:
    void clearGlobalData();
    void recordMainProgramStackAndVec(vector<bool> &needADF);
    void recordADFStackAndVec(const vector<bool> &needADF);
    double mainProgramDecode();
    double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal);



    double mainProgramDecodeOrigin();
    double ADFProgramDecodeOrigin(Symbol &subFunctionSym, double* inputArgsVal);


    stack<DecodeElement> mainOpStack;
    vector<stack<DecodeElement>>ADFOpStacks;

    vector<DecodeElement> mainOcVector;			//oc means operate code
    vector<vector<DecodeElement>>ADFOcVector;



};

#endif //CPPSOURCEFORLINUX_SL_CHROMOSOMEDECODER_H
