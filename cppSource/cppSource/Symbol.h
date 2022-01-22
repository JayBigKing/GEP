#pragma once
#include <string>
#include <vector>
using namespace std;
enum SymbolType
{
	FUNCTION = 1,
	SUB_FUNCTION,
	TERMINAL,
	ARGUMENT
};

class Symbol
{
public:
	Symbol(SymbolType symbolType, string symbolName);
	~Symbol(){}
	SymbolType getSymbolType() { return symbolType; }
	string getSymbolName() { return symbolName; }

protected:
	SymbolType symbolType;
	string symbolName;
};

class FunctionSymbol: public Symbol
{
public:
	FunctionSymbol(SymbolType symbolType,string symbolName,int numOfInputArg , double(*functionHandler)(double *args, int argLen));
	~FunctionSymbol(){}
	double callFunctionHandler(double *args, int argLen);
	int getNumOfInputArg() { return numOfInputArg; }
private:
	int numOfInputArg;
	double(*functionHandler)(double *args, int argLen);
};

class TerminalSymbol : public Symbol
{
public:
	TerminalSymbol(string symbolName , double val);
	~TerminalSymbol(){}
	double getVal() { return value; }
private:
	double value;
};

class SymbolSet
{
public:
	SymbolSet(){}
	~SymbolSet(){}

	bool pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen));
	bool pushFunctionSymbol(FunctionSymbol functionSymbol);

	bool pushSubFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(double *args, int argLen));
	bool pushSubFunctionSymbol(FunctionSymbol subFunctionSymbol);

	bool pushTerminalSymbol(string symbolName, double val);
	bool pushTerminalSymbol(TerminalSymbol terminal);

	bool pushInputArgSymbol(string symbolName);
	bool pushInputArgSymbol(Symbol inputArg);

	vector<FunctionSymbol>& getFunctionSet() { return functionSet; }
	vector<FunctionSymbol>& getSubFunctionSet() { return subFunctionSet; }
	vector<TerminalSymbol>& getTerminalSet() { return terminalSet; }
	vector<Symbol>& getInputArgSet() { return inputArgSet; }
private:
	vector<FunctionSymbol> functionSet;
	vector<FunctionSymbol> subFunctionSet;
	vector<TerminalSymbol> terminalSet;
	vector<Symbol> inputArgSet;
};
