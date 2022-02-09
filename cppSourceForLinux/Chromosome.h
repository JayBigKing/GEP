//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_CHROMOSOME_H
#define CPPSOURCEFORLINUX_CHROMOSOME_H

#include "ChromosomeRule.h"
class Chromosome
{
public:
    Chromosome(){}
    Chromosome(ChromosomeRule &cr);
    void init(ChromosomeRule &cr);
    ~Chromosome(){}
    vector<int> mainProgramEx;
    vector<vector<int>> ADFEx;

    Chromosome& operator = (const Chromosome &c);

private:
    void initHelp(ChromosomeRule &cr);
    //vector<int> mainProgramEx;
    //vector<vector<int>> ADFEx;

};

#endif //CPPSOURCEFORLINUX_CHROMOSOME_H
