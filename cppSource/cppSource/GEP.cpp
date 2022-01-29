#include "GEP.h"
#include "initHelp.h"
GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum,
	double similarValue) :
	ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
	realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch) ,ifUseSuspendNum(ifUseSuspendNum),similarValue(similarValue),generator(time(NULL)),
	minDistance(numeric_limits<double>::max()){

	//初始化symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec,inputADFHs);
}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, WhichFunction* presetFunctions,
	int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue 
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals), 
realTermSet(TAPairNum),ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
minDistance(numeric_limits<double>::max()) {

	//初始化symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);

}

GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue 
) :
	ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
	realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
	minDistance(numeric_limits<double>::max()) {

	//初始化symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);
}


GEP::GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, int* presetFunctions,
	int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum , double similarValue 
) : ADFH(numOfADFs), mainProgramH(mainPH), chromosomesNum(chroNum), chromosomes(chroNum), termAnsPairNum(TAPairNum), numOfValInTerm(numOfTerminals),
realTermSet(TAPairNum), ansSet(TAPairNum), epoch(0), needEpoch(needEpoch), ifUseSuspendNum(ifUseSuspendNum), similarValue(similarValue), generator(time(NULL)),
minDistance(numeric_limits<double>::max()) {

	//初始化symbolSet
	SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
	initHelp(realTermVec, ansVec, inputADFHs);

}

void GEP::initHelp(double *realTermVec, double *ansVec , int* inputADFHs) {
	//初始化ADFH
	for (int i = 0; i < ADFH.size(); ++i)
		ADFH[i] = inputADFHs[i];


	//初始化ChromosomeRule
	cr.init(mainProgramH, ADFH, symbolSet);

	//初始化各Chromosome
	for (int i = 0; i < chromosomesNum; ++i)
		chromosomes[i].init(cr);

//	bestChromosome.init(cr);

	//初始化realTermSet 和 ansSet
	for (int i = 0, j = 0; i < termAnsPairNum; ++i) {
		vector<double>tmp(numOfValInTerm);
		for (int k = 0; k < numOfValInTerm; ++k, ++j)
			tmp[k] = realTermVec[j];
		realTermSet[i] = tmp;
		ansSet[i] = ansVec[i];
	}

	

	initCouldChooseSet();
	initChromosomeSymbolCount2();
}




void GEP::initChromosomeSymbolCount() {
	int theExLen = 0;
	int theExH = 0;
	int theExU = 0;
	int theExL = 0;
	vector<Symbol> &functionSet = cr.getSymbolSet().getFunctionSet();
	vector<Symbol> &subFunctionSet = cr.getSymbolSet().getSubFunctionSet();
	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	vector<Symbol> &inputArgSet = cr.getSymbolSet().getInputArgSet();
	unordered_map<int, int> tmpMap;

	//首先是mainProgram
	
	//前面H位
	theExLen = cr.getMainPR().totalLen;
	theExH = cr.getMainPR().h;
	theExL = cr.getMainPR().l;

	for (int i = 0; i < functionSet.size(); ++i)
		tmpMap[functionSet[i].getNum()] = 0;

	for (int i = 0; i < subFunctionSet.size(); ++i)
		tmpMap[subFunctionSet[i].getNum()] = 0;

	for (int i = 0; i < terminalSet.size(); ++i)
		tmpMap[terminalSet[i].getNum()] = 0;



	for (int i = 0; i < theExH; ++i) 
		mainProgramSymbolCount.push_back(tmpMap);


	//后面L位

	tmpMap.clear();
	for (int i = 0; i < terminalSet.size(); ++i)
		tmpMap[terminalSet[i].getNum()] = 0;

	for (int i = 0; i < theExL; ++i)
		mainProgramSymbolCount.push_back(tmpMap);



	//然后是ADF
	int numOfADF = cr.getADFPR().size();
	initVectorHelp(ADFSymbolCount, numOfADF);

	for (int i = 0; i < numOfADF; ++i) {
		theExLen = cr.getADFPR(i).totalLen;
		theExH = cr.getADFPR(i).h;
		theExL = cr.getADFPR(i).l;
		theExU = cr.getADFPR(i).u;

		tmpMap.clear();
		for (int j = 0; j < functionSet.size(); ++j)
			tmpMap[functionSet[j].getNum()] = 0;

		for (int j = 0; j < theExU; ++j)
			tmpMap[inputArgSet[j].getNum()] = 0;

		for (int j = 0; j < theExH; ++j)
			ADFSymbolCount[i].push_back(tmpMap);


		tmpMap.clear();
		for (int j = 0; j < theExU; ++j)
			tmpMap[inputArgSet[j].getNum()] = 0;

		for (int j = 0; j < theExL; ++j)
			ADFSymbolCount[i].push_back(tmpMap);


	}




}

void GEP::initChromosomeSymbolCount2() {
	int theExH = 0;
	int theExU = 0;
	int theExL = 0;
	unordered_map<int, int> tmpMap;
	try {
		if (!couldChooseSetOfMainProgramFirst.size())
			throw "error : CouldChooseSet is not ininted!";
	}
	catch (const char *e) {
		printf("%s\r\n", e);
		exit(-1);
	}


	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	//首先是mainProgram

	//前面H位
	theExH = cr.getMainPR().h;
	theExL = cr.getMainPR().l;

	for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i)
		tmpMap[couldChooseSetOfMainProgramFirst[i]] = 0;



	//将map存入vec
	for (int i = 0; i < theExH; ++i)
		mainProgramSymbolCount.push_back(tmpMap);


	//后面L位

	tmpMap.clear();
	for (int i = 0; i < terminalSet.size(); ++i)
		tmpMap[terminalSet[i].getNum()] = 0;

	//将map存入vec
	for (int i = 0; i < theExL; ++i)
		mainProgramSymbolCount.push_back(tmpMap);

	//然后是ADF
	int numOfADF = cr.getADFPR().size();
	initVectorHelp(ADFSymbolCount, numOfADF);

	for (int i = 0; i < numOfADF; ++i) {
		theExH = cr.getADFPR(i).h;
		theExL = cr.getADFPR(i).l;

		tmpMap.clear();

		for (int j = 0; j < couldChooseSetOfADFFirst[i].size(); ++j)
			tmpMap[couldChooseSetOfADFFirst[i][j]] = 0;

		for (int j = 0; j < theExH; ++j)
			ADFSymbolCount[i].push_back(tmpMap);


		tmpMap.clear();
		for (int j = 0; j < couldChooseSetOfADFSecond[i].size(); ++j)
			tmpMap[couldChooseSetOfADFSecond[i][j]] = 0;

		for (int j = 0; j < theExL; ++j)
			ADFSymbolCount[i].push_back(tmpMap);


	}

}


//初始化可选集合
void GEP::initCouldChooseSet() {
	vector<Symbol> &functionSet = cr.getSymbolSet().getFunctionSet();
	vector<Symbol> &subFunctionSet = cr.getSymbolSet().getSubFunctionSet();
	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	vector<Symbol> &inputArgSet = cr.getSymbolSet().getInputArgSet();
	int numOfADF = cr.getADFPR().size();
	//首先是mainProgram
	for (int i = 0; i < functionSet.size(); ++i)
		couldChooseSetOfMainProgramFirst.push_back(functionSet[i].getNum());

	for (int i = 0; i < subFunctionSet.size(); ++i)
		couldChooseSetOfMainProgramFirst.push_back(subFunctionSet[i].getNum());

	for (int i = 0; i < terminalSet.size(); ++i)
		couldChooseSetOfMainProgramFirst.push_back(terminalSet[i].getNum());

	//然后是每一个ADF
	initVectorHelp(couldChooseSetOfADFFirst, numOfADF);
	initVectorHelp(couldChooseSetOfADFSecond, numOfADF);

	for (int i = 0; i < numOfADF; ++i) {
		int theExU = cr.getADFPR(i).u;
		for (int j = 0; j < functionSet.size(); ++j)
			couldChooseSetOfADFFirst[i].push_back(functionSet[j].getNum());

		for (int j = 0; j < theExU; ++j) {
			couldChooseSetOfADFFirst[i].push_back(inputArgSet[j].getNum());
			couldChooseSetOfADFSecond[i].push_back(inputArgSet[j].getNum());
		}

	}

}



int GEP::getRandSymbolNum(ChromosomePos cp, int ADFIndex) {
	using Range = std::uniform_int_distribution<>::param_type;
	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	uniform_int_distribution<int>distribution;
	switch (cp)
	{
	case MAIN_PROGRAM_FIRST:
		distribution.param(Range{ 0, (int)couldChooseSetOfMainProgramFirst.size() - 1 });
		return couldChooseSetOfMainProgramFirst[distribution(generator)];
	case MAIN_PROGRAM_SECOND:
		distribution.param(Range{ 0, (int)terminalSet.size() - 1 });
		return terminalSet[distribution(generator)].getNum();
	case ADF_FIRST:
		distribution.param(Range{ 0, (int)couldChooseSetOfADFFirst[ADFIndex].size() - 1 });
		return couldChooseSetOfADFFirst[ADFIndex][distribution(generator)];
	case ADF_SECOND:
		distribution.param(Range{ 0, (int)couldChooseSetOfADFSecond[ADFIndex].size() - 1 });
		return couldChooseSetOfADFSecond[ADFIndex][distribution(generator)];
	default:
		break;
	}


}

bool GEP::shouldContiue() {
	if (epoch < needEpoch) {
		epoch++;
		return true;
	}
	else {
		epoch++;
		return false;
	}
}
void GEP::recordBestChromosome(const int &chroIndex, const double & nowMinDistance) {
	if (nowMinDistance < minDistance) {
		minDistance = nowMinDistance;
		bestChromosomeAndIndex.first = chromosomes[chroIndex];
		bestChromosomeAndIndex.second = chroIndex;
	}


}



/*
void GEP::initRand() {
	using Range = std::uniform_int_distribution<>::param_type;
	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	int numOfADF = cr.getADFPR().size();
	MPFirstDistribution.param(Range{ 0, (int)couldChooseSetOfMainProgramFirst.size() - 1 });
	MPSecondDistribution.param(Range{ 0, (int)terminalSet.size() - 1 });
	initVectorHelp(ADFFirstDistribution, numOfADF);
	initVectorHelp(ADFSecondDistribution, numOfADF);
	for (int i = 0; i < numOfADF; ++i) {
		ADFFirstDistribution[i].param(Range{ 0, (int)couldChooseSetOfADFFirst[i].size() - 1 });
		ADFSecondDistribution[i].param(Range{ 0,(int)couldChooseSetOfADFSecond[i].size() - 1 });
	}

}

int GEP::getRandSymbolNum(ChromosomePos cp , int ADFIndex) {
	vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
	switch (cp)
	{
	case MAIN_PROGRAM_FIRST:
		return couldChooseSetOfMainProgramFirst[MPFirstDistribution(generator)];
	case MAIN_PROGRAM_SECOND:

		return terminalSet[MPSecondDistribution(generator)].getNum();
	case ADF_FIRST:
		return couldChooseSetOfADFFirst[ADFIndex][ADFFirstDistribution[ADFIndex](generator)];
	case ADF_SECOND:
		return couldChooseSetOfADFSecond[ADFIndex][ADFSecondDistribution[ADFIndex](generator)];
	default:
		break;
	}


}
*/