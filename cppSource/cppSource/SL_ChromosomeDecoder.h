#pragma once
#include "ChromosomeDecoder.h"
class SL_ChromosomeDecoder : public ChromosomeDecoder
{
public:
	SL_ChromosomeDecoder(){}
	~SL_ChromosomeDecoder(){}

private:
	double mainProgramDecode();
	double ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal);

};
