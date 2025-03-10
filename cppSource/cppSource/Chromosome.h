#pragma once
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