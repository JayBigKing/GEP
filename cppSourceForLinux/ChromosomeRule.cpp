//
// Created by JAY on 2022/2/9.
//

#include "ChromosomeRule.h"
#include "initHelp.h"
int getExpressionL(int h, int u) {
    return h * (u - 1) + 1;
}
ChromosomeRule::ChromosomeRule(int mainProgramH, vector<int>&ADFH, SymbolSet sSet):
        ADFPR(ADFH.size()),mainU(0),ADFU(0), symbolSet(sSet)
{
    initHelp(mainProgramH, ADFH);
}

void ChromosomeRule::init(int mainProgramH, vector<int>&ADFH, SymbolSet sSet) {
    initVectorHelp(ADFPR, ADFH.size());
    mainU = 0;
    ADFU = 0;
    symbolSet = sSet;
    initHelp(mainProgramH,ADFH);
}

void ChromosomeRule::initHelp(int mainProgramH, vector<int>&ADFH) {
    mainU = ADFU = 0;
    vector<Symbol> *fs = &symbolSet.getFunctionSet();
    vector<Symbol> *sfs = &symbolSet.getSubFunctionSet();
    //first find the u
    for (int i = 0; i < fs->size(); ++i)
        if ((*fs)[i].getNumOfInputArg() > ADFU)
            ADFU = (*fs)[i].getNumOfInputArg();

    mainU = ADFU;

    for (int i = 0; i < sfs->size(); ++i)
        if ((*sfs)[i].getNumOfInputArg() > mainU)
            mainU = (*sfs)[i].getNumOfInputArg();

    //second initial the mainProgram rules
    mainPR.h = mainProgramH;
    mainPR.u = mainU;
    mainPR.l = getExpressionL(mainPR.h, mainPR.u);
    mainPR.totalLen = mainPR.h + mainPR.l;

    //third initail the ADF rules
    for (int i = 0; i < ADFH.size(); ++i) {
        ProgramRule tmpPR;
        tmpPR.h = ADFH[i];
        tmpPR.u = ADFU;
        tmpPR.l = getExpressionL(tmpPR.h, tmpPR.u);
        tmpPR.totalLen = tmpPR.h + tmpPR.l;
        ADFPR[i] = tmpPR;
    }

}

ChromosomeRule& ChromosomeRule::operator = (const ChromosomeRule &cr) {
    this->mainPR = cr.mainPR;
    this->ADFPR = cr.ADFPR;
    this->mainU = cr.mainU;
    this->ADFU = cr.ADFU;
    this->symbolSet = cr.symbolSet;
    return *this;
}
