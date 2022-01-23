#include "Chromosome.h"
Chromosome::Chromosome(ChromosomeRule cr) :
	mainProgramEx(cr.getMainPR().totalLen), ADFEx(cr.getADFPR().size()) 
{
	//first init ADFPR`s element ex`s lenth
	vector<ProgramRule>& ADFPR = cr.getADFPR();
	for (int i = 0; i < ADFPR.size(); ++i) {
		vector<int>tmp(ADFPR[i].totalLen);
		ADFEx[i] = tmp;
	}
}