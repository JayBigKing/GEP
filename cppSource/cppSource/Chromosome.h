#pragma once
#include "ChromosomeRule.h"
class Chromosome
{
public:
	Chromosome(){}
	Chromosome(ChromosomeRule cr);
	~Chromosome(){}
	vector<int> mainProgramEx;
	vector<vector<int>> ADFEx;
private:
	//vector<int> mainProgramEx;
	//vector<vector<int>> ADFEx;

};