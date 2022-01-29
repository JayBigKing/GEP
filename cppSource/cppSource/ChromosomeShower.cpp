#include "ChromosomeShower.h"
void ChromosomeShower::simpleShow(const Chromosome &c) {
	goodSeeOneLineCount = 0;
	int numOfADFs = cr.getADFPR().size();
	printf("\r\n-------------------------------MAIN-------------------------------\r\n");
	for (int i = 0; i < c.mainProgramEx.size(); ++i) {
		printfOneSymbol(cr.getSymbolSet().getSymbol(c.mainProgramEx[i]).getSymbolName());
	}
	printf("\r\n-------------------------------MAIN-------------------------------\r\n");
	for (int i = 0; i < numOfADFs; ++i) {
		goodSeeOneLineCount = 0;
		int ADFLen = c.ADFEx[i].size();
		printf("-------------------------------ADF%d-------------------------------\r\n",i);
		for (int j = 0; j < ADFLen; ++j) {
			printfOneSymbol(cr.getSymbolSet().getSymbol(c.ADFEx[i][j]).getSymbolName());
		}
		printf("\r\n-------------------------------ADF%d-------------------------------\r\n", i);
	}
}

void ChromosomeShower::printfOneSymbol(const string &s) {
	printf("%s", s.c_str());
	for (int i = 0; i < spaceTimes; ++i)
		printf(" ");

	if (++goodSeeOneLineCount == goodSeeOneLineNum) {
		printf("\r\n");
		goodSeeOneLineCount = 0;
	}
}