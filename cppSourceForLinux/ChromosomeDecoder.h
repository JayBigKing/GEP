//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_CHROMOSOMEDECODER_H
#define CPPSOURCEFORLINUX_CHROMOSOMEDECODER_H


#include "Chromosome.h"
struct DecodeElement {
    int symbolSetIndex;
    SymbolType symbolType;
    int chroIndex;
    int pointIndex;
    int opNum;
};

class ChromosomeDecoder
{
public:
    ChromosomeDecoder(){}
    ~ChromosomeDecoder(){}

    //传入vector，主要是方便C++使用
    double decode(vector<double>& realTerm, Chromosome &chromosome1, ChromosomeRule &cr1);
    double decode(vector<double>& realTerm);

    //上下的decode()都得用，封装出来，方便调用
    void decodeHelpIn(Chromosome &chromosome1, ChromosomeRule &cr1);
    double decodeHelpOut();

    //传入数组指针，主要是方便调用
    double decode(double* realTerm, Chromosome &chromosome1, ChromosomeRule &cr1);
    double decode(double* realTerm);

    virtual void setChromosome(Chromosome &chromosome) = 0;
    //{ this->chromosome = chromosome; }
    void setChromosomeRule(ChromosomeRule &cr) { this->cr = cr;	symbolSet = cr.getSymbolSet();}

protected:
    vector<double> realTerminals;
    Chromosome chromosome;
    ChromosomeRule cr;
    SymbolSet symbolSet;

    virtual double mainProgramDecode() = 0;
    virtual double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal) = 0;
    DecodeElement makeDecodElement(int index, int chroIndex , int &globalPointIndex);
    void setSymbolSetTerminals();
    void setSymbolSetInputArgs(int num, double* args);
    void setRealTerm(double* realTerm);


};


#endif //CPPSOURCEFORLINUX_CHROMOSOMEDECODER_H
