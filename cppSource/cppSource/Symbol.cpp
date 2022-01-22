#include "Symbol.h"
//Symbol's function
Symbol::Symbol(SymbolType symbolType, string symbolName):symbolType(symbolType),symbolName(symbolName){}

//FunctionSymbol's functions
FunctionSymbol::FunctionSymbol(SymbolType symbolType, string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)):
	Symbol(symbolType,symbolName),numOfInputArg(numOfInputArg),functionHandler(functionHandler){}

double FunctionSymbol::callFunctionHandler(double *args, int argLen) {
	return functionHandler(args, argLen);
}

//TerminalSymbol's function
TerminalSymbol::TerminalSymbol(string symbolName, double val):
	Symbol(TERMINAL,symbolName),value(val){}

//SymbolSet's function
bool SymbolSet::pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) {
	FunctionSymbol fs(FUNCTION, symbolName , numOfInputArg, functionHandler);
	functionSet.push_back(fs);
	return true;
}
bool SymbolSet::pushFunctionSymbol(FunctionSymbol functionSymbol) {
	if (functionSymbol.getSymbolType() != FUNCTION)
		return false;
	functionSet.push_back(functionSymbol);
	return true;
}


bool SymbolSet::pushSubFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen)) {
	FunctionSymbol fs(SUB_FUNCTION, symbolName, numOfInputArg, functionHandler);
	subFunctionSet.push_back(fs);
	return true;
}
bool SymbolSet::pushSubFunctionSymbol(FunctionSymbol functionSymbol) {
	if (functionSymbol.getSymbolType() != SUB_FUNCTION)
		return false;
	subFunctionSet.push_back(functionSymbol);
	return true;
}

bool SymbolSet::pushTerminalSymbol(string symbolName, double val) {
	TerminalSymbol terminal(symbolName, val);
	terminalSet.push_back(terminal);
	return true;

}
bool SymbolSet::pushTerminalSymbol(TerminalSymbol terminal) {
	terminalSet.push_back(terminal);
	return true;
}

bool SymbolSet::pushInputArgSymbol(string symbolName) {
	Symbol inputArgSymbol(ARGUMENT, symbolName);
	inputArgSet.push_back(inputArgSymbol);
	return true;
}
bool SymbolSet::pushInputArgSymbol(Symbol inputArg) {
	inputArgSet.push_back(inputArg);
	return true;
}