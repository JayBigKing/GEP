#include "Symbol.h"
//Symbol's function
Symbol::Symbol(SymbolType symbolType, string symbolName):symbolType(symbolType),symbolName(symbolName){}
Symbol::Symbol(int num, SymbolType symbolType, string symbolName) : num(num),symbolType(symbolType), symbolName(symbolName) {}


//FunctionSymbol's functions
FunctionSymbol::FunctionSymbol(SymbolType symbolType, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
	Symbol(symbolType,symbolName),numOfInputArg(numOfInputArg),functionHandler(functionHandler){}
FunctionSymbol::FunctionSymbol(int num, SymbolType symbolType, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
	Symbol(num,symbolType, symbolName), numOfInputArg(numOfInputArg), functionHandler(functionHandler) {}
double FunctionSymbol::callFunctionHandler(double *args, int argLen) {
	return functionHandler(args, argLen);
}

//TerminalSymbol's function
TerminalSymbol::TerminalSymbol(string symbolName, double val):
	Symbol(TERMINAL,symbolName),value(val){}
TerminalSymbol::TerminalSymbol(int num, string symbolName, double val):
	Symbol(num, TERMINAL, symbolName), value(val) {}

//SymbolSet's function
bool SymbolSet::pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) {
	FunctionSymbol fs(symbolNum,FUNCTION, symbolName , numOfInputArg, functionHandler);
	SymbolMapInfo smi;

	functionSet.push_back(fs);
	smi.set(FUNCTION, functionSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);

	symbolNum++;
	return true;
}
bool SymbolSet::pushFunctionSymbol(FunctionSymbol functionSymbol) {
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


bool SymbolSet::pushSubFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) {
	FunctionSymbol sfs(symbolNum,SUB_FUNCTION, symbolName, numOfInputArg, functionHandler);
	SymbolMapInfo smi;

	subFunctionSet.push_back(sfs);
	smi.set(SUB_FUNCTION, subFunctionSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;
}
bool SymbolSet::pushSubFunctionSymbol(FunctionSymbol subFunctionSymbol) {
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
	TerminalSymbol terminal(symbolNum,symbolName, val);
	SymbolMapInfo smi;

	terminalSet.push_back(terminal);
	smi.set(TERMINAL, terminalSet.size() - 1);
	symbolMap[symbolName] = smi;
	symbolVec.push_back(smi);
	symbolNum++;
	return true;

}
bool SymbolSet::pushTerminalSymbol(TerminalSymbol terminal) {
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