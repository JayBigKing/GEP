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

	//����vector����Ҫ�Ƿ���C++ʹ��
	double decode(vector<double>& realTerm, Chromosome &chromosome1, ChromosomeRule &cr1);
	double decode(vector<double>& realTerm);

	//���µ�decode()�����ã���װ�������������
	void decodeHelpIn(Chromosome &chromosome1, ChromosomeRule &cr1);
	double decodeHelpOut();

	//��������ָ�룬��Ҫ�Ƿ������
	double decode(double* realTerm, Chromosome &chromosome1, ChromosomeRule &cr1);
	double decode(double* realTerm);

	virtual void setChromosome(Chromosome &chromosome) { this->chromosome = chromosome; }
	void setChromosomeRule(ChromosomeRule &cr) { this->cr = cr;	symbolSet = cr.getSymbolSet();}

protected:
	vector<double> realTerminals;
	Chromosome chromosome;
	ChromosomeRule cr;
	SymbolSet symbolSet;

	virtual double mainProgramDecode() = 0;
	virtual double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal) = 0;
	DecodeElement makeDecodElement(int index, int chroIndex , int &globalPointIndex);
	void setSymbolSetTerminals();
	void setSymbolSetInputArgs(int num, double* args);
	void setRealTerm(double* realTerm);


};

