#include "Chromosome.h"
#include "initHelp.h"
Chromosome::Chromosome(ChromosomeRule &cr) :
	mainProgramEx(cr.getMainPR().totalLen), ADFEx(cr.getADFPR().size()) 
{
	initHelp(cr);
}

void Chromosome::init(ChromosomeRule &cr) {
	initVectorHelp(mainProgramEx, cr.getMainPR().totalLen);
	initVectorHelp(ADFEx, cr.getADFPR().size());

	initHelp(cr);
}

void Chromosome::initHelp(ChromosomeRule &cr) {
	//first init ADFPR`s element ex`s lenth
	vector<ProgramRule>& ADFPR = cr.getADFPR();
	for (int i = 0; i < ADFPR.size(); ++i) {
		vector<int>tmp(ADFPR[i].totalLen);
		ADFEx[i] = tmp;
	}
}
Chromosome& Chromosome::operator = (const Chromosome &c) {
	this->mainProgramEx = c.mainProgramEx;
	this->ADFEx = c.ADFEx;
	return *this;
}