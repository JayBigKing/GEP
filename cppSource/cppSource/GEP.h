#pragma once
#include "ChromosomeRule.h"
#include "Chromosome.h"
#include "ChromosomeDecoder.h"
#include "SymbolSetGenerator.h"
#include<boost/smart_ptr.hpp>
#include <random>
#include <time.h>

enum ChromosomePos
{
	MAIN_PROGRAM_FIRST = 0,
	MAIN_PROGRAM_SECOND,
	ADF_FIRST,
	ADF_SECOND
};


class GEP
{
public:
	GEP(){}
	GEP(int chroNum,double *realTermVec, double *ansVec,int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, 
		bool ifUseSuspendNum = true,double similarValue = 1e-6
		);

	GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, WhichFunction* presetFunctions, 
		int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,bool ifUseSuspendNum = true, double similarValue = 1e-6
		);


	GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
		bool ifUseSuspendNum = true, double similarValue = 1e-6
	);

	GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, int* presetFunctions,
		int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs, bool ifUseSuspendNum = true, double similarValue = 1e-6
	);


	virtual pair<Chromosome, ChromosomeRule> train() = 0;
	pair<Chromosome, int> getBestChromosomeAndIndex() { return bestChromosomeAndIndex; }
	ChromosomeRule getChromosomeRule() { return cr; }



	~GEP(){}

protected:
	SymbolSet symbolSet;
	vector<int>ADFH;
	int mainProgramH;
	int chromosomesNum;
	int termAnsPairNum;
	int numOfValInTerm;
	ChromosomeRule cr;

	vector<Chromosome> chromosomes;
	pair<Chromosome, int>bestChromosomeAndIndex;


	//��¼mainProgramÿ��λ��ѡ��symbol������
	vector<unordered_map<int, int>>mainProgramSymbolCount;	
	//��¼ADFÿ��λ��ѡ��symbol������
	vector<vector<unordered_map<int, int>>>ADFSymbolCount;

	//MainProgram ǰHλ����ѡ��symbol
	vector<int>couldChooseSetOfMainProgramFirst;
	//MainProgram ��Lλ����ѡ��symbol����TerminalSet����ģ����Բ��õ����г���

	//ADF ǰHλ����ѡ��symbol
	vector<vector<int>>couldChooseSetOfADFFirst;

	//ADF ��Lλ����ѡ��symbol
	vector<vector<int>>couldChooseSetOfADFSecond;


	boost::shared_ptr<ChromosomeDecoder>cdPtr;

	vector<vector<double>>realTermSet;
	vector<double>ansSet;

	int epoch = 0;
	int needEpoch = 0;

	bool ifUseSuspendNum = true;
	int suspendNum = 1000;
	int suspendCount = 0;              //�����ж��Ż��Ƿ�ͣ����
	double similarValue = 1e-6;

	default_random_engine generator;
//	uniform_int_distribution<int>MPFirstDistribution;
//	uniform_int_distribution<int>MPSecondDistribution;
//	vector<uniform_int_distribution<int>>ADFFirstDistribution;
//	vector<uniform_int_distribution<int>>ADFSecondDistribution;

	//��ʼ��GEP
	void initHelp(double *realTermVec, double *ansVec, int* inputADFHs);
	void initChromosomeSymbolCount();
	void initChromosomeSymbolCount2();
	void initCouldChooseSet();
//	void initRand();


	//train��غ���
	//�ж��Ƿ�Ӧ��ֹͣѵ��
	//bool shouldContiue();

	//�Ŵ�����
	virtual void initChromosomes() = 0;					//��ʼ��Ⱦɫ��
	virtual void mutation() = 0;						//����
	virtual void crossover() = 0;						//����
	//virtual void selection() = 0;

	int getRandSymbolNum(ChromosomePos cp ,int ADFIndex = -1);

};
