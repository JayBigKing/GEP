//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_SYMBOLSETGENERATOR_H
#define CPPSOURCEFORLINUX_SYMBOLSETGENERATOR_H

#include "Symbol.h"
//生成SymbolSet
class SymbolSetGenerator
{
public:
    SymbolSetGenerator(){}
    ~SymbolSetGenerator(){}
    static SymbolSet* makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants,
                                    WhichFunction* presetFunctions, int numOfPresetFunctions,int *argsLenOfADFs, int numOfADFs);
    static SymbolSet* makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants,
                                    int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);


    static SymbolSet* makeSymbolSet(int numOfTerminals,
                                    WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
    static SymbolSet* makeSymbolSet(int numOfTerminals,
                                    int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

    static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                             WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
    static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                             int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);


    static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
                             WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
    static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
                             int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

    static void setSymbolSet(SymbolSet &symbolSet,const int &numOfTerminals,const vector<double>&constants,
                                          const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs);
    static void setSymbolSet(SymbolSet &symbolSet, const int &numOfTerminals,const vector<double>&constants,
                                          const vector<int> &presetFunctions, const vector<int> &argsLenOfADFs) ;
    static void setSymbolSet(SymbolSet &symbolSet,const int &numOfTerminals,
                                          const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs);
    static void setSymbolSet(SymbolSet &symbolSet, const int &numOfTerminals,
                                          const vector<int> &presetFunctions, const vector<int> &argsLenOfADFs) ;
private:
    static const int startAlpha = 'a', endAlpha = 'z';
    static void pushTerminals(SymbolSet &symbolSet,int numOfTerminals);
    //专供数组
    static void pushConstans(SymbolSet &symbolSet, double *constants,int numOfConstants);
    static void pushPresetFunctions(SymbolSet &symbolSet, WhichFunction* presetFunctions, int numOfPresetFunctions);
    static void pushADFandInputArgs(SymbolSet &symbolSet, int *argsLenOfADFs, int numOfADFs);
    //专供vector
    static void pushConstans(SymbolSet &symbolSet, const vector<double>&constants);
    static void pushPresetFunctions(SymbolSet &symbolSet, const vector<WhichFunction> &presetFunctions);
    static void pushADFandInputArgs(SymbolSet &symbolSet, const vector<int> &argsLenOfADFs);

    static void makeSymbolSetHelp1(SymbolSet &symbolSet,int numOfTerminals, double *constants, int numOfConstants,
                                   int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
    static void makeSymbolSetHelp1(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                                   WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

    static void makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
                                   int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
    static void makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
                                   WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

    static void makeSymbolSetHelp3(SymbolSet &symbolSet,const int &numOfTerminals,const vector<double>&constants,
                                                const vector<WhichFunction> &presetFunctions,const vector<int> &argsLenOfADFs);

};


#endif //CPPSOURCEFORLINUX_SYMBOLSETGENERATOR_H
