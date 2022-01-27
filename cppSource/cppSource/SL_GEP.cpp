#include "SL_GEP.h"
SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
}

SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
}



SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue ) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
}


SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
	int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	bool ifUseSuspendNum , double similarValue) :
	GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
		argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue) {
	cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
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