//
// Created by JAY on 2022/2/9.
//

#include"ChromosomeDecoder.h"
#include <queue>
#include <stack>
#include<boost/smart_ptr.hpp>
void ChromosomeDecoder::setSymbolSetTerminals() {
    vector<Symbol>& terms = symbolSet.getTerminalSet();
    try {
        if (terms.size() != realTerminals.size())
            throw  "terminal size is not equal!";

        for (int i = 0; i < terms.size(); ++i) {
            terms[i].setVal(realTerminals[i]);
        }
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }

}
//为染色体表达式解码
//三个参数
//使用vector（方便C++）
double ChromosomeDecoder::decode(vector<double>& realTerm, Chromosome &chromosome1, ChromosomeRule &cr1) {
    decodeHelpIn(chromosome1, cr1);
    return decode(realTerm);

}
//为染色体表达式解码
//一个参数
//使用vector（方便C++）
double ChromosomeDecoder::decode(vector<double>& realTerm) {
    realTerminals = realTerm;
    return decodeHelpOut();
}
//初始化染色体表达式，表达式规则的时候，有重复代码，集成起来
void ChromosomeDecoder::decodeHelpIn(Chromosome &chromosome1, ChromosomeRule &cr1) {
    setChromosomeRule(cr1);
    //symbolSet = cr.getSymbolSet();

    setChromosome(chromosome1);


}
//计算表达式值的时候有重复代码，集成起来
double ChromosomeDecoder::decodeHelpOut() {
    setSymbolSetTerminals();
    return mainProgramDecode();
}
//为染色体表达式解码
//三个参数
//使用数组指针（方便作为api调用）
double ChromosomeDecoder::decode(double* realTerm, Chromosome &chromosome1, ChromosomeRule &cr1) {
    decodeHelpIn(chromosome1, cr1);
    return decode(realTerm);
}
//为染色体表达式解码
//一个参数
//使用数组指针（方便作为api调用）
double ChromosomeDecoder::decode(double* realTerm) {
    setRealTerm(realTerm);
    return decodeHelpOut();
}

void ChromosomeDecoder::setRealTerm(double* realTerm) {
    if (!realTerminals.size()) {
        int termLen = cr.getSymbolSet().getTerminalSet().size();
        for (int i = 0; i < termLen; ++i)
            realTerminals.push_back(0);
    }
    for (int i = 0; i < realTerminals.size(); ++i)
        realTerminals[i] = realTerm[i];
}


DecodeElement ChromosomeDecoder::makeDecodElement(int index, int chroIndex , int &globalPointIndex) {
    Symbol tmpSym = symbolSet.getSymbol(index);
    DecodeElement tmpDe;
    tmpDe.symbolSetIndex = index;
    tmpDe.chroIndex = chroIndex;
    tmpDe.symbolType = tmpSym.getSymbolType();

    if (tmpDe.symbolType == FUNCTION || tmpDe.symbolType == SUB_FUNCTION) {
        tmpDe.pointIndex = globalPointIndex + 1;
        tmpDe.opNum = tmpSym.getNumOfInputArg();
        globalPointIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
    }
    else {
        tmpDe.pointIndex = tmpDe.opNum = -1;
        ++globalPointIndex;
    }


    return tmpDe;
}


void ChromosomeDecoder::setSymbolSetInputArgs(int num, double* args) {
    vector<Symbol>& inputArgs = symbolSet.getInputArgSet();
    try {
        if (inputArgs.size() < num)
            throw  "error!num is longer than the size of inputArgs set!";
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
    for (int i = 0; i < inputArgs.size(); ++i) {
        inputArgs[i].setVal(args[i]);
    }
}
