#pragma once
#include "Chromosome.h"
struct DecodeElement {
	int symbolSetIndex;
	SymbolType symbolType;
	int chroIndex;
	int pointIndex;
	int opNum;
};

class ChromosomeDecoder
{
public:
	ChromosomeDecoder(){}
	~ChromosomeDecoder(){}
	double decode(vector<double>& term, Chromosome &chromosome1, ChromosomeRule &cr1);
	double decode(vector<double>& term);
	void setChromosome(Chromosome &chromosome) { this->chromosome = chromosome; }
	void setChromosomeRule(ChromosomeRule &cr) { this->cr = cr;	symbolSet = cr.getSymbolSet();}

private:
	vector<double> terminals;
	Chromosome chromosome;
	ChromosomeRule cr;
	SymbolSet symbolSet;

	double mainProgramDecode();
	DecodeElement makeDecodElement(int index, int chroIndex , int &globalPointIndex);
	void setSymbolSetTerminals();


};

