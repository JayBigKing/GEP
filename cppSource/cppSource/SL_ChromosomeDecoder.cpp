#include "SL_ChromosomeDecoder.h"
#include <queue>

#include<boost/smart_ptr.hpp>

void SL_ChromosomeDecoder::clearGlobalData() {
	//清主函数的操作符栈和操作数向量
	stack<DecodeElement>tmpEmptyStack;
	mainOpStack = tmpEmptyStack;
	mainOcVector.clear();

	//清ADF的操作符栈和操作数向量
	for (int i = 0; i < ADFOpStacks.size(); ++i)
		ADFOpStacks[i] = tmpEmptyStack;

	ADFOpStacks.clear();

	for (int i = 0; i < ADFOcVector.size(); ++i)
		ADFOcVector[i].clear();

	ADFOcVector.clear();

}


void  SL_ChromosomeDecoder::recordADFStackAndVec(const vector<bool> &needADF) {
	stack<DecodeElement>tmpEmptyStack;
	vector<DecodeElement>tmpEmptyVector;
	for (int i = 0; i < needADF.size(); ++i) {
		if (!needADF[i]) {
			ADFOpStacks.push_back(tmpEmptyStack);
			ADFOcVector.push_back(tmpEmptyVector);
		}
		else {
			queue<DecodeElement> readQue;
			DecodeElement tmpDe;
			DecodeElement lastDe;
			int queuePtr = 0;
			int globalPointIndex = 0;

			vector<int>ADFEx = chromosome.ADFEx[i];
			ADFOpStacks.push_back(tmpEmptyStack);
			ADFOcVector.push_back(tmpEmptyVector);

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
				if (tmpDe.symbolType == ARGUMENT) {
					ADFOcVector[i].push_back(tmpDe);
					continue;
				}
				else if (tmpDe.symbolType == TERMINAL)
					throw  "invailed chromosome";
			}
			catch (const char* &e) {
				printf("%s\r\n", e);
				exit(-1);
			}

			readQue.push(tmpDe);
			++queuePtr;


			while (!readQue.empty())
			{
				lastDe = readQue.front();
				readQue.pop();
				if (lastDe.symbolType == ARGUMENT) {
					ADFOcVector[i].push_back(lastDe);
				}
				else {
					int opNum = lastDe.opNum;
					for (int i = 0; i < opNum; i++) {
						tmpDe = makeDecodElement(ADFEx[queuePtr], queuePtr, globalPointIndex);
						readQue.push(tmpDe);
						++queuePtr;
					}
					ADFOpStacks[i].push(lastDe);
				}
			}


		}

	}



}


void SL_ChromosomeDecoder::recordMainProgramStackAndVec(vector<bool> &needADF) {
	queue<DecodeElement> readQue;
	DecodeElement tmpDe;
	DecodeElement lastDe;
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
		if (tmpDe.symbolType == TERMINAL) {
			mainOcVector.push_back(tmpDe);
			return;
		}
		else if (tmpDe.symbolType == ARGUMENT)
			throw  "invailed chromosome";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}

	readQue.push(tmpDe);
	++queuePtr;

	while (!readQue.empty())
	{
		lastDe = readQue.front();
		readQue.pop();
		if (lastDe.symbolType == TERMINAL) {
			mainOcVector.push_back(lastDe);
		}
		else {
			int opNum = lastDe.opNum;
			for (int i = 0; i < opNum; i++) {
				tmpDe = makeDecodElement(chromosome.mainProgramEx[queuePtr], queuePtr, globalPointIndex);
				readQue.push(tmpDe);
				++queuePtr;
			}
			if (lastDe.symbolType == SUB_FUNCTION)
				needADF[symbolSet.getSymbol(lastDe.symbolSetIndex).getADFIndex()] = true;		//只记录mian program 包含的ADF
			mainOpStack.push(lastDe);
		}
	}

}

void SL_ChromosomeDecoder::setChromosome(Chromosome &chromosome) {
	this->chromosome = chromosome;
	try {
		if (!cr.getSymbolSet().getTerminalSet().size())
			throw "ChromosomeRule did not initial!";
	}
	catch (const char * &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	clearGlobalData();
	vector<bool> needADF(this->chromosome.ADFEx.size());			//main program未必包含所有的ADF，只记录mian program 包含的ADF，节约空间
	for (int i = 0; i < needADF.size(); ++i)
		needADF[i] = false;
	recordMainProgramStackAndVec(needADF);
	recordADFStackAndVec(needADF);

}

double SL_ChromosomeDecoder::mainProgramDecode() {
	vector<double>outputVec(cr.getMainPR().totalLen);
	stack<DecodeElement> opStack = mainOpStack;
	DecodeElement tmpDe;
	DecodeElement lastDe;
	//	vector<double> optNum(cr.getU());
	boost::shared_array<double> args(new double[cr.getU()]);
	for(int i = 0 ; i < mainOcVector.size() ; ++i)
		outputVec[mainOcVector[i].chroIndex] = symbolSet.getSymbol(mainOcVector[i].symbolSetIndex).getVal();


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
		else if (tmpDe.symbolType == SUB_FUNCTION)
			outputVec[tmpDe.chroIndex] = ADFProgramDecode(tmpSym, args.get());
	}

	return outputVec[0];
}








//ADF,即 sub-function
double SL_ChromosomeDecoder::ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal) {
	int theADFIndex = subFunctionSym.getADFIndex();
	vector<double>outputVec(cr.getADFPR(theADFIndex).totalLen);
	stack<DecodeElement> opStack = ADFOpStacks[theADFIndex];
	DecodeElement tmpDe;
	//	vector<double> optNum(cr.getU());
	boost::shared_array<double> args(new double[cr.getU()]);

	setSymbolSetInputArgs(subFunctionSym.getNumOfInputArg(), inputArgsVal);
	for (int i = 0; i < ADFOcVector[theADFIndex].size(); ++i)
		outputVec[ADFOcVector[theADFIndex][i].chroIndex] = symbolSet.getSymbol(ADFOcVector[theADFIndex][i].symbolSetIndex).getVal();



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















double SL_ChromosomeDecoder::mainProgramDecodeOrigin() {
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

		for (int i = tmpDe.pointIndex, j = 0; i < tmpDe.pointIndex + tmpDe.opNum; ++i, ++j) {
			args[j] = outputVec[i];
		}

		if (tmpDe.symbolType == FUNCTION)
			outputVec[tmpDe.chroIndex] = tmpSym.callFunctionHandler(args.get());
		else if (tmpDe.symbolType == SUB_FUNCTION)
			outputVec[tmpDe.chroIndex] = ADFProgramDecode(tmpSym, args.get());
	}

	return outputVec[0];
}








//ADF,即 sub-function
double SL_ChromosomeDecoder::ADFProgramDecodeOrigin(Symbol &subFunctionSym, double* inputArgsVal) {
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