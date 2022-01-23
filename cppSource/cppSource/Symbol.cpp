#include "Symbol.h"
//Symbol's function

Symbol::Symbol(int num, SymbolType symbolType, string symbolName) : num(num),symbolType(symbolType), symbolName(symbolName) {}
Symbol::Symbol(SymbolType symbolType, string symbolName) : Symbol(0,symbolType,symbolName){}

Symbol::Symbol(int num, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) :
	num(num), symbolType(FUNCTION), symbolName(symbolName), numOfInputArg(numOfInputArg), functionHandler(functionHandler) {}
Symbol::Symbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
	Symbol(0, symbolName, numOfInputArg,functionHandler){}

Symbol::Symbol(int num, string symbolName, double val):
	num(num),symbolType(TERMINAL),symbolName(symbolName),value(val){}
Symbol::Symbol(string symbolName, double val):
	Symbol(0,symbolName,val){}

Symbol::Symbol(int num, string symbolName, int numOfInputArg, int ADFIndex):
num(num), symbolType(SUB_FUNCTION), symbolName(symbolName), ADFIndex(ADFIndex) {}
Symbol::Symbol(string symbolName, int numOfInputArg, int ADFIndex):
	Symbol(0,symbolName,ADFIndex){}


double Symbol::callFunctionHandler(double *args, int argLen) {
	try{
		if(symbolType != FUNCTION )
		throw "it`s no function ";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return functionHandler(args, argLen);
}
double Symbol::callFunctionHandler(double *args) {
	return callFunctionHandler(args, this->numOfInputArg);
}
int Symbol::getNumOfInputArg() {
	try {
		if (symbolType != FUNCTION )
			throw "it`s no function ";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return numOfInputArg;
}
double Symbol::getVal() {
	try {
		if (symbolType != TERMINAL)
			throw "it`s no terminal";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return value;
}

////FunctionSymbol's functions
//FunctionSymbol::FunctionSymbol(SymbolType symbolType, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
//	Symbol(symbolType,symbolName),numOfInputArg(numOfInputArg),functionHandler(functionHandler){}
//FunctionSymbol::FunctionSymbol(int num, SymbolType symbolType, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
//	Symbol(num,symbolType, symbolName), numOfInputArg(numOfInputArg), functionHandler(functionHandler) {}
//double FunctionSymbol::callFunctionHandler(double *args, int argLen) {
//	return functionHandler(args, argLen);
//}
//
////TerminalSymbol's function
//TerminalSymbol::TerminalSymbol(string symbolName, double val):
//	Symbol(TERMINAL,symbolName),value(val){}
//TerminalSymbol::TerminalSymbol(int num, string symbolName, double val):
//	Symbol(num, TERMINAL, symbolName), value(val) {}

//SymbolSet's function
bool SymbolSet::pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) {
	Symbol fs(symbolNum, symbolName , numOfInputArg, functionHandler);
	SymbolMapInfo smi;

	functionSet.push_back(fs);
	smi.set(FUNCTION, functionSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);

	symbolNum++;
	return true;
}
bool SymbolSet::pushFunctionSymbol(Symbol functionSymbol) {
	if (functionSymbol.getSymbolType() != FUNCTION)
		return false;
	SymbolMapInfo smi;
	functionSymbol.setNum(symbolNum);
	functionSet.push_back(functionSymbol);
	smi.set(FUNCTION, functionSet.size() - 1);
	symbolMap[functionSymbol.getSymbolName()] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}


bool SymbolSet::pushSubFunctionSymbol(string symbolName, int numOfInputArg, int ADFIndex) {
	Symbol sfs(symbolNum,symbolName, numOfInputArg, ADFIndex);
	SymbolMapInfo smi;

	subFunctionSet.push_back(sfs);
	smi.set(SUB_FUNCTION, subFunctionSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}
bool SymbolSet::pushSubFunctionSymbol(Symbol subFunctionSymbol) {
	if (subFunctionSymbol.getSymbolType() != SUB_FUNCTION)
		return false;
	SymbolMapInfo smi;

	subFunctionSymbol.setNum(symbolNum);
	subFunctionSet.push_back(subFunctionSymbol);

	smi.set(SUB_FUNCTION, subFunctionSet.size() - 1);
	symbolMap[subFunctionSymbol.getSymbolName()] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}

bool SymbolSet::pushTerminalSymbol(string symbolName, double val) {
	Symbol terminal(symbolNum,symbolName, val);
	SymbolMapInfo smi;

	terminalSet.push_back(terminal);
	smi.set(TERMINAL, terminalSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;

}
bool SymbolSet::pushTerminalSymbol(Symbol terminal) {
	SymbolMapInfo smi;

	terminal.setNum(symbolNum);
	terminalSet.push_back(terminal);

	smi.set(TERMINAL, terminalSet.size() - 1);
	symbolMap[terminal.getSymbolName()] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}

bool SymbolSet::pushInputArgSymbol(string symbolName) {
	Symbol inputArgSymbol(symbolNum,ARGUMENT, symbolName);
	SymbolMapInfo smi;

	inputArgSet.push_back(inputArgSymbol);

	smi.set(ARGUMENT, inputArgSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}
bool SymbolSet::pushInputArgSymbol(Symbol inputArg) {
	SymbolMapInfo smi;

	inputArg.setNum(symbolNum);
	inputArgSet.push_back(inputArg);

	smi.set(ARGUMENT, inputArgSet.size() - 1);
	symbolMap[inputArg.getSymbolName()] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}

Symbol& SymbolSet::getSymbolHelp(SymbolMapInfo smi) {
	switch (smi.symbolType)
	{
	case FUNCTION:
		return functionSet[smi.index];
		break;

	case SUB_FUNCTION:
		return subFunctionSet[smi.index];
		break;
	case TERMINAL:
		return terminalSet[smi.index];
		break;
	case ARGUMENT:
		return inputArgSet[smi.index];
		break;
	default:
		break;
	}

}
Symbol& SymbolSet::getSymbol(string str) {
	SymbolMapInfo smi = symbolMap[str];
	return getSymbolHelp(smi);
}
Symbol& SymbolSet::getSymbol(int index) {
	SymbolMapInfo smi = symbolVec[index];
	return getSymbolHelp(smi);
}