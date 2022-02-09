#pragma once
#include "ChromosomeDecoder.h"
#include <stack>
class SL_ChromosomeDecoder : public ChromosomeDecoder
{
public:
	SL_ChromosomeDecoder(){}
	~SL_ChromosomeDecoder(){}
	void setChromosome(Chromosome &chromosome);
private:
	void clearGlobalData();
	void recordMainProgramStackAndVec(vector<bool> &needADF);
	void recordADFStackAndVec(const vector<bool> &needADF);
	double mainProgramDecode();
	double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal);



	double mainProgramDecodeOrigin();
	double ADFProgramDecodeOrigin(Symbol &subFunctionSym, double* inputArgsVal);


	stack<DecodeElement> mainOpStack;
	vector<stack<DecodeElement>>ADFOpStacks;

	vector<DecodeElement> mainOcVector;			//oc means operate code
	vector<vector<DecodeElement>>ADFOcVector;



};
