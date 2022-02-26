//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_CHROMOSOMERULE_H
#define CPPSOURCEFORLINUX_CHROMOSOMERULE_H

#include <vector>
#include "Symbol.h"
using namespace std;
int getExpressionL(int h, int u);
struct ProgramRule
{
    int h;
    int u;
    int l;
    int totalLen;
};
class ChromosomeRule
{
public:
    ChromosomeRule(){}
    ChromosomeRule(int mainProgramH,vector<int>& ADFH, SymbolSet sSet);
    ~ChromosomeRule(){}
    void init(int mainProgramH, vector<int>& ADFH, SymbolSet sSet);
    ProgramRule& getMainPR() { return mainPR; }
    vector<ProgramRule>& getADFPR() { return ADFPR; }
    ProgramRule& getADFPR(int index) {
        try {
            if (index < 0 || index > ADFPR.size() || !ADFPR.size())
                throw "out of the index";
        }
        catch (const char* &e) {
            printf("%s\r\n", e);
            exit(-1);
        }
        return ADFPR[index];
    }
    int getMainU() { return mainU; }
    int getADFU()   {return ADFU ; }
    SymbolSet& getSymbolSet() { return symbolSet; }

    ChromosomeRule& operator = (const ChromosomeRule &cr);
private:
    ProgramRule mainPR;
    vector<ProgramRule> ADFPR;
    int mainU;
    int ADFU;
    //int u;
    SymbolSet symbolSet;

    void initHelp(int mainProgramH, vector<int>&ADFH);

};


#endif //CPPSOURCEFORLINUX_CHROMOSOMERULE_H
