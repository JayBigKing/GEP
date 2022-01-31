#include "SL_GEP.h"
#include "GA_HelpFunc.h"
#include <limits>
SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue),totalWeight(0.0),chromosomeWeight(chroNum) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
	cdPtr->setChromosomeRule(cr);

	UChromosome.init(cr);

	initRandGenerator();
	getTotalExpressionLen();
}

SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
	cdPtr->setChromosomeRule(cr);
	UChromosome.init(cr);

	initRandGenerator();
	getTotalExpressionLen();
}



SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
	cdPtr->setChromosomeRule(cr);
	UChromosome.init(cr);

	initRandGenerator();
	getTotalExpressionLen();
}


SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
	cdPtr->setChromosomeRule(cr);
	UChromosome.init(cr);

	initRandGenerator();
	getTotalExpressionLen();
}



void SL_GEP::initRandGenerator() {
	uniform_int_distribution<uint64_t>initDistribution(0, numeric_limits<uint64_t>::max());
	FGenerator.seed(initDistribution(generator));
	BetaGenerator.seed(initDistribution(generator));
	SelectGenerator.seed(initDistribution(generator));
	YGenerator.seed(initDistribution(generator));
	GambleGenerator.seed(initDistribution(generator));
	CRGenerator.seed(initDistribution(generator));
	KGenerator.seed(initDistribution(generator));
	ACSGenerator.seed(initDistribution(generator));

}

double SL_GEP::test1() {
	chromosomes[0].mainProgramEx[0] = 4;
	chromosomes[0].mainProgramEx[1] = 2;
	chromosomes[0].mainProgramEx[2] = 3;
	chromosomes[0].mainProgramEx[3] = 0;
	chromosomes[0].mainProgramEx[4] = 0;
	chromosomes[0].mainProgramEx[5] = 1;
	chromosomes[0].mainProgramEx[6] = 0;

	chromosomes[0].ADFEx[0][0] = 2;
	chromosomes[0].ADFEx[0][1] = 5;
	chromosomes[0].ADFEx[0][2] = 6;

	return cdPtr.get()->decode(realTermSet[0], chromosomes[0], cr);
}

pair<Chromosome, ChromosomeRule> SL_GEP::train() {
	pair<Chromosome, ChromosomeRule> outPair;
	initChromosomes();
	for (; shouldContiue();) {
		inheritanceProcess();
	}
	outPair.first = bestChromosomeAndIndex.first;
	outPair.second = cr;

	return outPair;
}

//初始化染色体群
//******************************************
void SL_GEP::initChromosomes() {
	int theMExH = cr.getMainPR().h;
	int theMExL = cr.getMainPR().l;
	int theAExH = 0;
	int theAExL = 0;
	int numOfADF = cr.getADFPR().size();
	double nowDis = 0.0;
	for (int i = 0; i < chromosomesNum; ++i) {
		//先mainProgram
		int k = 0;
		for (int j = 0; j < theMExH; ++j, ++k)
			chromosomes[i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
		for(int j = 0 ; j < theMExL ; ++j ,++k)
			chromosomes[i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


		//后ADFs
		for (int t = 0; t < numOfADF; ++t) {
			k = 0;
			theAExH = cr.getADFPR(t).h;
			theAExL = cr.getADFPR(t).l;
			for (int j = 0; j < theAExH; ++j, ++k)
				chromosomes[i].ADFEx[t][k] = getRandSymbolNum(ADF_FIRST,t);

			for (int j = 0; j < theAExL; ++j, ++k)
				chromosomes[i].ADFEx[t][k] = getRandSymbolNum(ADF_SECOND,t);

		}

		nowDis = calculateDistance(chromosomes[i]);
		setChromosomeWeight(i, nowDis);
		recordBestChromosome(i,nowDis);

		//recordOneSymbolCount(i);
	}
	recordAllCount();



}
//******************************************

//变异
//******************************************
double SL_GEP::getPsi(const int &a,const int &b) {
	return (a != b) ? 1 : 0;
}

double SL_GEP::getPhi(const int &bestSymbolNum, const int &chroIndexSymbolNum, const int &r1SymbolNum, const int &r2SymbolNum,
	const double &F, const double &beta) {
	return 1 - (1 - F * getPsi(bestSymbolNum, chroIndexSymbolNum)) * (1 - beta * getPsi(r1SymbolNum, r2SymbolNum));
}

void SL_GEP::mainProgramFragmentMutation(const int &chroIndex, const int &FragmentIndex, const int &r1, const int &r2,
	const double &F, const double &beta, const double  &yRandVal) {
	double Phi = getPhi(chromosomes[chroIndex].mainProgramEx[FragmentIndex], chromosomes[bestChromosomeAndIndex.second].mainProgramEx[FragmentIndex],
		chromosomes[r1].mainProgramEx[FragmentIndex], chromosomes[r2].mainProgramEx[FragmentIndex], F, beta);
	if (yRandVal <= Phi)
		mainProgramGetNewFragment(chroIndex, FragmentIndex);
	else
		UChromosome.mainProgramEx[FragmentIndex] = chromosomes[chroIndex].mainProgramEx[FragmentIndex];
}
void SL_GEP::ADFFragmentMutation(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const int &r1,
	const int &r2, const double &F, const double &beta,const double  &yRandVal) {
	double Phi = getPhi(chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex], chromosomes[bestChromosomeAndIndex.second].mainProgramEx[FragmentIndex],
		chromosomes[r1].mainProgramEx[FragmentIndex], chromosomes[r2].mainProgramEx[FragmentIndex], F, beta);
	if (yRandVal <= Phi)
		ADFGetNewFragmentMutation(chroIndex,ADFIndex,FragmentIndex);
	else 
		UChromosome.ADFEx[ADFIndex][FragmentIndex] = chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex];
	
}

void SL_GEP::mainProgramGetNewFragment(const int &chroIndex , const int &FragmentIndex) {
	int theMExH = cr.getMainPR().h;
	double probabilityDenominator = 0.0;
	double probabilityCount = 0.0;
	uniform_real_distribution<double> distribution(0.0, 1.0);
	if (FragmentIndex < theMExH) {
		vector<double>symbolProbability(couldChooseSetOfMainProgramFirst.size());
		for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i) {
			symbolProbability[i] = (double)this->mainProgramSymbolCount[FragmentIndex][couldChooseSetOfMainProgramFirst[i]];			//只是暂存，后面会分布在0-1
			probabilityDenominator += symbolProbability[i];						
		}

		//UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
		//return;
//		if (probabilityDenominator == 0.0) {
		if (distribution(YGenerator) > 0.9) {
			UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
		}
		else {
			for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i)
				symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


			UChromosome.mainProgramEx[FragmentIndex] = couldChooseSetOfMainProgramFirst[getTheGambleIndex(distribution(GambleGenerator), symbolProbability)];
			//if (this->mainProgramSymbolCount[FragmentIndex][UChromosome.mainProgramEx[FragmentIndex]] == 0)
			//	printf("!!!!!\r\n");
		}

	}
	else {
		vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
		vector<double>symbolProbability(terminalSet.size());
		for (int i = 0 ; i < terminalSet.size(); ++i) {
			symbolProbability[i] = this->mainProgramSymbolCount[FragmentIndex][terminalSet[i].getNum()];			//只是暂存，后面会分布在0-1
			probabilityDenominator += symbolProbability[i];
		}

		//UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_SECOND);
		//return;
//		if (probabilityDenominator == 0.0) {
		if (distribution(YGenerator) > 0.9){
			UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


		}
		else {
			for (int i = 0; i < terminalSet.size(); ++i)
				symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


			UChromosome.mainProgramEx[FragmentIndex] = terminalSet[getTheGambleIndex(distribution(GambleGenerator), symbolProbability)].getNum();
			//if (this->mainProgramSymbolCount[FragmentIndex][UChromosome.mainProgramEx[FragmentIndex]] == 0)
			//	printf("!!!!!\r\n");
		}



	}



}
void SL_GEP::ADFGetNewFragmentMutation(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, bool authorType ) {
	if (authorType) {
		int theAExH = cr.getADFPR(ADFIndex).h;
		if (FragmentIndex < theAExH)
			UChromosome.ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_FIRST, ADFIndex);
		else
			UChromosome.ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_SECOND, ADFIndex);
	}

}


void SL_GEP::individualMutation(const int &chroIndex, const int &r1, const int &r2, const double &F, const double &beta){
	//main program
	int mainProgramExLen = chromosomes[chroIndex].mainProgramEx.size();
	
	int numOfADFs = chromosomes[chroIndex].ADFEx.size();

	uniform_real_distribution<double> distribution(0.0, 1.0);

	for (int i = 0; i < mainProgramExLen; ++i)
		mainProgramFragmentMutation(chroIndex, i, r1, r2, F, beta,distribution(YGenerator));

	for (int i = 0; i < numOfADFs; ++i) {
		int thisADFLen = chromosomes[chroIndex].ADFEx[i].size();
		for (int j = 0; j < thisADFLen; ++j) {
			ADFFragmentMutation(chroIndex, i, j, r1, r2, F, beta, distribution(YGenerator));
		}
	}
}
/*
void SL_GEP::mutation() {
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> indexDistribution(0, chromosomesNum - 1);
	for (int i = 0; i < chromosomesNum; ++i) {
		double F = distribution(FGenerator);
		double beta = distribution(BetaGenerator);
		int r1 = indexDistribution(SelectGenerator),
			r2 = indexDistribution(SelectGenerator);

		individualMutation(i, r1, r2, F, beta);
		

	}

}
*/
//*********************************************************


//交叉
//********************************************************
/*
void SL_GEP::crossover() {
	//mainProgram
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> selectKDistribution;

	for (int i = 0; i < chromosomesNum; ++i) {


	}
}
*/


int SL_GEP::getTotalExpressionLen() {
	try {
		if (!cr.getSymbolSet().getSymbolMap().size())
			throw "error: cr is not init!";
		totalExpressionLen = cr.getMainPR().totalLen;
		for (int i = 0; i < cr.getADFPR().size(); ++i)
			totalExpressionLen += cr.getADFPR(i).totalLen;

		return totalExpressionLen;

	}
	catch (const char *e) {
		printf("%s\r\n", e);
		exit(-1);
	}

}
// 5  4  4
   
int SL_GEP::getTotalExpressionIndex(int inThisExIndex, int ADFIndex ) {
	if (ADFIndex == -1)
		return inThisExIndex;
	else {
		int theIndex = cr.getMainPR().totalLen;
		for (int i = 0; i < ADFIndex - 1; ++i)
			theIndex += cr.getADFPR(i).totalLen;
		return theIndex + inThisExIndex;
	}

}

void SL_GEP::individualCrossover(const int &chroIndex,const double &CR) {
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> indexDistribution(0, totalExpressionLen - 1);
	int mainProgramExLen = chromosomes[chroIndex].mainProgramEx.size();

	int numOfADFs = chromosomes[chroIndex].ADFEx.size();
	//main program first
	for (int i = 0; i < mainProgramExLen; ++i) 
		mainProgramFragmentCrossover(chroIndex, i, CR, indexDistribution(KGenerator),distribution(YGenerator),indexDistribution(YGenerator));


	//ADFs second
	for (int i = 0; i < numOfADFs; ++i) {
		int thisADFLen = chromosomes[chroIndex].ADFEx[i].size();
		for (int j = 0; j < thisADFLen; ++j)
			ADFFragmentCrossover(chroIndex, i, j, CR, indexDistribution(KGenerator), distribution(YGenerator), indexDistribution(YGenerator));
	}



}
void SL_GEP::mainProgramFragmentCrossover(const int &chroIndex, const int &FragmentIndex, const double &CR, const int &K	
	,const double &randVal, const int &theJVal) {
	if (!(randVal < CR || getTotalExpressionIndex(FragmentIndex) == K))
		UChromosome.mainProgramEx[FragmentIndex] = chromosomes[chroIndex].mainProgramEx[FragmentIndex];
}
void SL_GEP::ADFFragmentCrossover(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const double &CR, const int &K
	, const double &randVal, const int &theJVal) {
	if (!(randVal < CR || getTotalExpressionIndex(FragmentIndex, ADFIndex) == K))
		UChromosome.ADFEx[ADFIndex][FragmentIndex] = chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex];
}
//********************************************************



//自然选择
//********************************************************
void SL_GEP::individualSelection(const int &chroIndex){
	double xDistance = 0.0, uDistance = 0.0;
	double nowMinDistance = 0.0;
	//cdPtr->setChromosome(chromosomes[chroIndex]);
	xDistance = calculateDistance(chromosomes[chroIndex]);
	uDistance = calculateDistance(UChromosome);
	if (uDistance < xDistance) {
		chromosomes[chroIndex] = UChromosome;
		nowMinDistance = uDistance;
	}
	else
		nowMinDistance = xDistance;

	recordBestChromosome(chroIndex, nowMinDistance);
	setChromosomeWeight(chroIndex, nowMinDistance);

}
void SL_GEP::individualSelection(const int &chroIndex, const double &randVal) {
	double xDistance = 0.0, uDistance = 0.0;
	double nowMinDistance = 0.0;
	//cdPtr->setChromosome(chromosomes[chroIndex]);
	xDistance = calculateDistance(chromosomes[chroIndex]);
	uDistance = calculateDistance(UChromosome);
	if (uDistance < xDistance) {
		chromosomes[chroIndex] = UChromosome;
		nowMinDistance = uDistance;
	}
	else
		nowMinDistance = xDistance;

	recordBestChromosome(chroIndex, nowMinDistance);
	setChromosomeWeight(chroIndex, nowMinDistance);

	setOneSymbolCountByRandVal(chroIndex, randVal);


}

double SL_GEP::calculateDistance(const 	Chromosome &c){
	return EuclideanDis(c);

}
double SL_GEP::EuclideanDis(const Chromosome &c){
	double count = 0.0;
	cdPtr->setChromosome(const_cast<Chromosome&>(c));
	for (int i = 0; i < termAnsPairNum; ++i) 
		count += pow((cdPtr->decode(realTermSet[i]) - ansSet[i]), 2);
	return  sqrt(count);

}
//********************************************************


//交叉与遗传合并
//********************************************************
void SL_GEP::inheritanceProcess() {
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> indexDistribution(0, chromosomesNum - 1);
	for (int i = 0; i < chromosomesNum; ++i) {
		double F = distribution(FGenerator);
		double beta = distribution(BetaGenerator);
		int r1 = indexDistribution(SelectGenerator),
			r2 = indexDistribution(SelectGenerator);
		double CR = distribution(CRGenerator);
		double ACSRandVal = distribution(ACSGenerator);

		individualMutation(i, r1, r2, F, beta);			//遗传

		individualCrossover(i,CR);						//交叉

		individualSelection(i, ACSRandVal);							//自然选择

		//recordOneSymbolCount(i);


	}
	recordAllCount();

	printf("%d:%f\r\n",epoch, minDistance);		//602  (>2200)

}
//********************************************************


//记录一条染色体的每个片段所用的symbol
//********************************************************
void SL_GEP::recordOneSymbolCount(const int &chroIndex, const double &score) {
	
	int mainPSize = chromosomes[chroIndex].mainProgramEx.size();
	int numOfADF = chromosomes[chroIndex].ADFEx.size();
	for (int i = 0; i < mainPSize; ++i) {
		recordSymbolCount(chromosomes[chroIndex].mainProgramEx[i], i,score);
	}

	for (int i = 0; i < numOfADF; ++i) {
		int ADFLen = chromosomes[chroIndex].ADFEx[i].size();
		for (int j = 0; j < ADFLen; ++j) {
			recordSymbolCount(chromosomes[chroIndex].ADFEx[i][j], j, score, i);
		}
	}
}
void SL_GEP::setOneSymbolCountByRandVal(const int &chroIndex, const double &randVal) {
	int mainPSize = chromosomes[chroIndex].mainProgramEx.size();
	int numOfADF = chromosomes[chroIndex].ADFEx.size();
	for (int i = 0; i < mainPSize; ++i) {
		setSymbolCountByRandVal(chromosomes[chroIndex].mainProgramEx[i], i, randVal);
	}

	for (int i = 0; i < numOfADF; ++i) {
		int ADFLen = chromosomes[chroIndex].ADFEx[i].size();
		for (int j = 0; j < ADFLen; ++j) {
			setSymbolCountByRandVal(chromosomes[chroIndex].ADFEx[i][j], j, randVal, i);
		}
	}


}


void SL_GEP::recordAllCount() {
	if (totalWeight) {
		int theBestIndex = 0;
		long double adjustTotalWeight = 0.0;
		double lastBestWeightScore = -1;
		for (int i = 0; i < chromosomesNum; ++i) {
			double inputWeightScore = (chromosomeWeight[i] == 0.0 ? maxWeightScore : (totalWeight / chromosomeWeight[i]) / chromosomesNum );
			adjustTotalWeight += inputWeightScore;
			chromosomeWeight[i] = inputWeightScore;
			if (inputWeightScore > lastBestWeightScore) {
				lastBestWeightScore = inputWeightScore;
				theBestIndex = i;
			}
			//recordOneSymbolCount(i, inputWeightScore);
			if (inputWeightScore > maxWeightScore)
				maxWeightScore = inputWeightScore;
		}

		for (int i = 0; i < chromosomesNum;++i)
			recordOneSymbolCount(i, chromosomeWeight[i] / adjustTotalWeight);


		//recordOneSymbolCount(theBestIndex, lastBestWeightScore / adjustTotalWeight);
	}
	else {
		int meanVal = 1 / chromosomesNum;
		for (int i = 0; i < chromosomesNum; ++i) {
			recordOneSymbolCount(i, chromosomesNum);
		}
	}

	totalWeight = 0;


}

void SL_GEP::setChromosomeWeight(const int & chroIndex, const double& distance) {
	chromosomeWeight[chroIndex] = distance;
	totalWeight += distance;

}