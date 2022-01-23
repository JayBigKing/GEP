#include"ChromosomeDecoder.h"
#include <queue>
#include <stack>
#include<boost/smart_ptr.hpp>
void ChromosomeDecoder::setSymbolSetTerminals() {
	vector<Symbol>& terms = symbolSet.getTerminalSet();
	try {
		if (terms.size() != terminals.size())
			throw  "terminal size is not equal!";

		for (int i = 0; i < terms.size(); ++i) {
			terms[i].setVal(terminals[i]);
		}
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}

}
double ChromosomeDecoder::decode(vector<double>& term, Chromosome &chromosome1, ChromosomeRule &cr1) {
	chromosome = chromosome1;
	cr = cr1;
	symbolSet = cr.getSymbolSet();
	return decode(term);

}
double ChromosomeDecoder::decode(vector<double>& term) {
	terminals = term;
	setSymbolSetTerminals();
	return mainProgramDecode();
}
DecodeElement ChromosomeDecoder::makeDecodElement(int index, int chroIndex , int &globalPointIndex) {
	Symbol tmpSym = symbolSet.getSymbol(index);
	DecodeElement tmpDe;
	tmpDe.symbolSetIndex = index;
	tmpDe.chroIndex = chroIndex;
	tmpDe.symbolType = tmpSym.getSymbolType();

	if (tmpDe.symbolType == FUNCTION || tmpDe.symbolType == SUB_FUNCTION) {
		tmpDe.pointIndex = globalPointIndex + 1;
		tmpDe.opNum = tmpSym.getNumOfInputArg();
		globalPointIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
	}
	else {
		tmpDe.pointIndex = tmpDe.opNum = -1;
		++globalPointIndex;
	}


	return tmpDe;
}
double ChromosomeDecoder::mainProgramDecode() {
	vector<double>outputVec(cr.getMainPR().totalLen);
	queue<DecodeElement> readQue;
	stack<DecodeElement> opStack;
	DecodeElement tmpDe;
	DecodeElement lastDe;
//	vector<double> optNum(cr.getU());
	boost::shared_array<double> args(new double[cr.getU()]);
	int queuePtr = 0;
	int globalPointIndex = 0;
	try {
		if (!chromosome.mainProgramEx.size())
			throw  "invailed chromosome";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	tmpDe = makeDecodElement(chromosome.mainProgramEx[queuePtr], queuePtr, globalPointIndex);

	try {
		if (tmpDe.symbolType == TERMINAL)
			return symbolSet.getSymbol(tmpDe.symbolSetIndex).getVal();
		else if (tmpDe.symbolType == ARGUMENT)
			throw  "invailed chromosome";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}

	readQue.push(tmpDe);
	++queuePtr;
	//globalPointIndex = tmpDe.pointIndex;

	while (!readQue.empty())
	{
		lastDe = readQue.front();
		readQue.pop();
		if (lastDe.symbolType == TERMINAL) {
			outputVec[lastDe.chroIndex] = symbolSet.getSymbol(lastDe.symbolSetIndex).getVal();
		}
		else {
			int opNum = lastDe.opNum;
			for (int i = 0; i < opNum; i++) {
				tmpDe = makeDecodElement(chromosome.mainProgramEx[queuePtr], queuePtr, globalPointIndex);
				readQue.push(tmpDe);
				++queuePtr;
			}
			opStack.push(lastDe);
		}
		//++queuePtr;
	}


	while (!opStack.empty()) {
		tmpDe = opStack.top();
		Symbol tmpSym = symbolSet.getSymbol(tmpDe.symbolSetIndex);
		int opLastIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
		opStack.pop();

		for (int i = tmpDe.pointIndex ,j = 0; i < tmpDe.pointIndex + tmpDe.opNum ; ++i,++j) {
			args[j] = outputVec[i];
		}
		
		if (tmpDe.symbolType == FUNCTION)
			outputVec[tmpDe.chroIndex] = tmpSym.callFunctionHandler(args.get());
		else if (tmpDe.symbolType == SUB_FUNCTION)
			outputVec[tmpDe.chroIndex] = ADFProgramDecode(tmpSym,args.get());
	}

	return outputVec[0];
}


void ChromosomeDecoder::setSymbolSetInputArgs(int num, double* args) {
	vector<Symbol>& inputArgs = symbolSet.getInputArgSet();
	try {
		if (inputArgs.size() < num)
			throw  "error!num is longer than the size of inputArgs set!";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	for (int i = 0; i < inputArgs.size(); ++i) {
		inputArgs[i].setVal(args[i]);
	}
}
//ADF,�� sub-function
double ChromosomeDecoder::ADFProgramDecode(Symbol &subFunctionSym,  double* inputArgsVal) {
	vector<double>outputVec(cr.getADFPR(subFunctionSym.getADFIndex()).totalLen);
	queue<DecodeElement> readQue;
	stack<DecodeElement> opStack;
	vector<int>& ADFEx = chromosome.ADFEx[subFunctionSym.getADFIndex()];
	DecodeElement tmpDe;
	DecodeElement lastDe;
	//	vector<double> optNum(cr.getU());
	boost::shared_array<double> args(new double[cr.getU()]);
	int queuePtr = 0;
	int globalPointIndex = 0;

	setSymbolSetInputArgs(subFunctionSym.getNumOfInputArg(), inputArgsVal);
	try {
		if (!ADFEx.size())
			throw  "invailed chromosome";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	tmpDe = makeDecodElement(ADFEx[queuePtr], queuePtr, globalPointIndex);

	try {
		if (tmpDe.symbolType == ARGUMENT)
			return symbolSet.getSymbol(tmpDe.symbolSetIndex).getVal();
		else if (tmpDe.symbolType == TERMINAL)
			throw  "invailed sub chromosome";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}

	readQue.push(tmpDe);
	++queuePtr;
	//globalPointIndex = tmpDe.pointIndex;

	while (!readQue.empty())
	{
		lastDe = readQue.front();
		readQue.pop();
		if (lastDe.symbolType == ARGUMENT) {
			outputVec[lastDe.chroIndex] = symbolSet.getSymbol(lastDe.symbolSetIndex).getVal();
		}
		else {
			int opNum = lastDe.opNum;
			for (int i = 0; i < opNum; i++) {
				tmpDe = makeDecodElement(ADFEx[queuePtr], queuePtr, globalPointIndex);
				readQue.push(tmpDe);
				++queuePtr;
			}
			opStack.push(lastDe);
		}
	}


	while (!opStack.empty()) {
		tmpDe = opStack.top();
		Symbol tmpSym = symbolSet.getSymbol(tmpDe.symbolSetIndex);
		int opLastIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
		opStack.pop();

		for (int i = tmpDe.pointIndex, j = 0; i < tmpDe.pointIndex + tmpDe.opNum; ++i, ++j) {
			args[j] = outputVec[i];
		}

		if (tmpDe.symbolType == FUNCTION)
			outputVec[tmpDe.chroIndex] = tmpSym.callFunctionHandler(args.get());
	}

	return outputVec[0];
}