#pragma once
#include"GEP.h"
#include "SL_ChromosomeDecoder.h"
#include "SL_GEPTester.h"
#define ANY_ONE_EQUAL_WAY 0
#define LOW_ONE_FIRST 1
#define BEST_ONE_ONLY 2
#define ANY_ONE_COUNT_BY_WEIGHT 3
//#define WHICH_RENEW_SYMBOL_COUNT_WAY ANY_ONE_EQUAL_WAY
class SL_GEP : public GEP
{
public:
	SL_GEP(){}
	SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
		bool ifUseSuspendNum = true, double similarValue = 1e-6);

	SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, 
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
		bool ifUseSuspendNum = true, double similarValue = 1e-6);

	SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
		bool ifUseSuspendNum = true, double similarValue = 1e-6);

	SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
		bool ifUseSuspendNum = true, double similarValue = 1e-6);

	double test1();

	pair<Chromosome, ChromosomeRule> train();

	void reInit();

	~SL_GEP(){}

	friend class SL_GEPTester;

private:
	uint8_t whichRenewSymbolCountWay = ANY_ONE_COUNT_BY_WEIGHT;

	default_random_engine FGenerator;
	default_random_engine BetaGenerator;
	default_random_engine SelectGenerator;
	default_random_engine YGenerator;
	default_random_engine GambleGenerator;
	default_random_engine CRGenerator;
	default_random_engine KGenerator;
	default_random_engine ACSGenerator;


	//vector<Chromosome> UChromosomes;
	Chromosome UChromosome;

	int totalExpressionLen;


	long double totalWeight;
	vector<double>chromosomeWeight;
	double maxWeightScore = 0;
	double maxDistanceByNow = 20000.0;

	void initRandGenerator();




	void initChromosomes();					//��ʼ��Ⱦɫ��

	void mutation() {}						//����
	double getPsi(const int &a, const int &b);
	double getPhi(const int &bestSymbolNum, const int &chroIndexSymbolNum, const int &r1SymbolNum, const int &r2SymbolNum,
		const double &F, const double &beta);
	void individualMutation(const int &chroIndex, const int &r1, const int &r2, const double &F, const double &beta);
	void mainProgramFragmentMutation(const int &chroIndex, const int &FragmentIndex, const int &r1, const int &r2, 
		const double &F, const double &beta , const double  &yRandVal);
	void ADFFragmentMutation(const int &chroIndex, const int &ADFIndex , const int &FragmentIndex, const int &r1, 
		const int &r2, const double &F, const double &beta, const double  &yRandVal);
	void mainProgramGetNewFragment(const int &chroIndex, const int &FragmentIndex );
	void ADFGetNewFragmentMutation(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex,bool authorType = true);



	void crossover() {}						//����
	void individualCrossover(const int &chroIndex , const double &CR);
	void mainProgramFragmentCrossover(const int &chroIndex, const int &FragmentIndex, const double &CR, const int &K , 
		const double &randVal , const int &theJVal);
	void ADFFragmentCrossover(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const double &CR, const int &K, 
		const double &randVal, const int &theJVal);
	int getTotalExpressionLen();
	int getTotalExpressionIndex(int inThisExIndex, int ADFIndex = -1);


	void selection() {}						//��Ȼѡ��
	void individualSelection(const int &chroIndex);
	void individualSelection(const int &chroIndex,const double &randVal);
	double calculateDistance(const 	Chromosome &c);
	double EuclideanDis(const Chromosome &c);
	//ManhattanDis ChebyshevDis

	void inheritanceProcess();				//�Ŵ����̣��Ż����̵߳ĳ��򣬽�ͻ�䣬���棬��Ȼ��ת����һ��

	void recordOneSymbolCount(const int &chroIndex, const double &score = 1);
	//void setOneSymbolCount(const int &chroIndex, const double &score );
	void setOneSymbolCountByRandVal(const int &chroIndex, const double &randVal);

	void recordAllCount();

	void setChromosomeWeight(const int & chroIndex, const double& distance);
	void adjustTotalWeight();
};

