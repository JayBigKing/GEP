#include "ChromosomeRule.h"
int getExpressionL(int h, int u) {
	return h * (u - 1) + 1;
}
ChromosomeRule::ChromosomeRule(int mainProgramH, vector<int>&ADFH, SymbolSet sSet):
	ADFPR(ADFH.size()),u(0),symbolSet(sSet)
{
	u = 0;
	vector<Symbol> *fs = &symbolSet.getFunctionSet();
	vector<Symbol> *sfs = &symbolSet.getSubFunctionSet();
	//first find the u
	for (int i = 0; i < fs->size(); ++i)
		if ((*fs)[i].getNumOfInputArg() > u)
			u = (*fs)[i].getNumOfInputArg();

	for (int i = 0; i < sfs->size(); ++i)
		if ((*sfs)[i].getNumOfInputArg() > u)
			u = (*sfs)[i].getNumOfInputArg();

	//second initial the mainProgram rules
	mainPR.h = mainProgramH;
	mainPR.u = u;
	mainPR.l = getExpressionL(mainPR.h, mainPR.u);
	mainPR.totalLen = mainPR.h + mainPR.l;

	//third initail the ADF rules
	for (int i = 0; i < ADFH.size(); ++i) {
		ProgramRule tmpPR;
		tmpPR.h = ADFH[i];
		tmpPR.u = u;
		tmpPR.l = getExpressionL(tmpPR.h, tmpPR.u);
		tmpPR.totalLen = tmpPR.h + tmpPR.l;
		ADFPR[i] = tmpPR;
	}

}