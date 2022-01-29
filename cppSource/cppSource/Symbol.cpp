#include "Symbol.h"
//Symbol's function

Symbol::Symbol(int num, SymbolType symbolType, string symbolName) : num(num),symbolType(symbolType), symbolName(symbolName) {}
Symbol::Symbol(SymbolType symbolType, string symbolName) : Symbol(0,symbolType,symbolName){}

Symbol::Symbol(int num, string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen)) :
	num(num), symbolType(FUNCTION), symbolName(symbolName), numOfInputArg(numOfInputArg), functionHandler(functionHandler) , functionType(USER){}
Symbol::Symbol(string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen)):
	Symbol(0, symbolName, numOfInputArg,functionHandler){}

Symbol::Symbol(int num, WhichFunction wf):
	num(num), symbolType(FUNCTION), symbolName(getFunctionName(wf)), numOfInputArg(getFunctionArgLen(wf)), functionType(PRESET),whichFunction(wf){}
Symbol::Symbol( WhichFunction wf):
	Symbol(0,wf){}


Symbol::Symbol(int num, string symbolName, double val,bool ifConstant):
	num(num),symbolType(TERMINAL),symbolName(symbolName),value(val),ifValueConstant(ifConstant){}
Symbol::Symbol(string symbolName, double val, bool ifConstant):
	Symbol(0,symbolName,val,ifConstant){}

Symbol::Symbol(int num, string symbolName, int numOfInputArg, int ADFIndex):
num(num), symbolType(SUB_FUNCTION), symbolName(symbolName), numOfInputArg(numOfInputArg), ADFIndex(ADFIndex) {}
Symbol::Symbol(string symbolName, int numOfInputArg, int ADFIndex):
	Symbol(0,symbolName,ADFIndex){}




double Symbol::callFunctionHandler(double *args, int argLen) {
	try{
		if(symbolType != FUNCTION )
			throw "it`s no function ";
		if (functionType == PRESET)
			return functionPresetHandler(args, whichFunction);
		else
			return functionHandler(args, argLen);

	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}

}
double Symbol::callFunctionHandler(double *args) {
	return callFunctionHandler(args, this->numOfInputArg);
}
int Symbol::getNumOfInputArg() {
	try {
		if (symbolType != FUNCTION && symbolType != SUB_FUNCTION)
			throw "it`s no function or sub function";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return numOfInputArg;
}
double Symbol::getVal() {
	try {
		if (symbolType != TERMINAL && symbolType != ARGUMENT)
			throw "it`s no terminal or input argument!";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return value;
}
int Symbol::getADFIndex() {
	try {
		if (symbolType != SUB_FUNCTION)
			throw "it`s no sub function";
	}
	catch (const char* &e) {
		printf("%s\r\n", e);
		exit(-1);
	}
	return ADFIndex;
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
bool SymbolSet::pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen)) {
	Symbol fs(symbolNum, symbolName , numOfInputArg, functionHandler);
	SymbolMapInfo smi;

	functionSet.push_back(fs);
	smi.set(FUNCTION, functionSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);

	symbolNum++;
	return true;
}
bool SymbolSet::pushFunctionSymbol( WhichFunction wf) {
	Symbol fs(symbolNum, wf);
	SymbolMapInfo smi;

	functionSet.push_back(fs);
	smi.set(FUNCTION, functionSet.size() - 1);
	symbolMap[fs.getSymbolName()] = smi;
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

bool SymbolSet::pushTerminalSymbol(string symbolName, double val, bool ifConstant) {
	Symbol terminal(symbolNum,symbolName, val, ifConstant);
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

SymbolSet& SymbolSet::operator = (const SymbolSet &ss) {
	/*	int symbolNum = 0;
	vector<Symbol> functionSet;
	vector<Symbol> subFunctionSet;
	vector<Symbol> terminalSet;
	vector<Symbol> inputArgSet;
	unordered_map<string, SymbolMapInfo> symbolMap;
	vector<SymbolMapInfo> symbolVec;*/
	this->symbolNum = ss.symbolNum;
	this->functionSet = ss.functionSet;
	this->subFunctionSet = ss.subFunctionSet;
	this->terminalSet = ss.terminalSet;
	this->inputArgSet = ss.inputArgSet;
	this->symbolMap = ss.symbolMap;
	this->symbolVec = ss.symbolVec;
	return *this;
}