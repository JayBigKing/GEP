#pragma once
#include "ChromosomeRule.h"
#include "Chromosome.h"
#include "ChromosomeDecoder.h"
#include "SymbolSetGenerator.h"
#include<boost/smart_ptr.hpp>
#include <random>
#include <time.h>
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
	boost::shared_ptr<ChromosomeDecoder>cdPtr;

	vector<vector<double>>realTermSet;
	vector<double>ansSet;

	int epoch = 0;
	int needEpoch = 0;

	bool ifUseSuspendNum = true;
	int suspendNum = 1000;
	int suspendCount = 0;              //用来判断优化是否停滞了
	double similarValue = 1e-6;


	void initHelp(double *realTermVec, double *ansVec, int* inputADFHs);

};
