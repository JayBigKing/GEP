#include "GEP.h"
GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum,
	double similarValue) :
	ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
	realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch) ,ifUseSuspendNum(ifUseSuspendNum),similarValue(similarValue){

	//��ʼ��symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec,inputADFHs);
}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, WhichFunction* presetFunctions,
	int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue 
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals), 
realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue) {

	//��ʼ��symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);

}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue 
) :
	ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
	realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue) {

	//��ʼ��symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);
}


GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, int* presetFunctions,
	int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue 
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue) {

	//��ʼ��symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);

}

void GEP::initHelp(double *realTermVec, double *ansVec , int* inputADFHs) {
	//��ʼ��ADFH
	for (int i = 0; i < ADFH.size(); ++i)
		ADFH[i] = inputADFHs[i];


	//��ʼ��ChromosomeRule
	cr.init(mainProgramH, ADFH, symbolSet);

	//��ʼ����Chromosome
	for (int i = 0; i < chromosomesNum; ++i)
		chromosomes[i].init(cr);

	//��ʼ��realTermSet �� ansSet
	for (int i = 0, j = 0; i < termAnsPairNum; ++i) {
		vector<double>tmp(numOfValInTerm);
		for (int k = 0; k < numOfValInTerm; ++k, ++j)
			tmp[k] = realTermVec[j];
		realTermSet[i] = tmp;
		ansSet[i] = ansVec[i];
	}
}