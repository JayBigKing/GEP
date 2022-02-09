//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_CHROMOSOMESHOWER_H
#define CPPSOURCEFORLINUX_CHROMOSOMESHOWER_H


#include "Chromosome.h"
class ChromosomeShower
{
public:
    ChromosomeShower(){}
    ChromosomeShower(ChromosomeRule cr0):cr(cr0){}
    ~ChromosomeShower(){}
    void setCR(ChromosomeRule cr0) {
        cr = cr0;
    }
    void simpleShow(const Chromosome &c);


private:
    ChromosomeRule cr;
    int goodSeeOneLineNum = 10;
    int goodSeeOneLineCount = 0;
    int spaceTimes = 3;
    void printfOneSymbol(const string &s);
};


#endif //CPPSOURCEFORLINUX_CHROMOSOMESHOWER_H
