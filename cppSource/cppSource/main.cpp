#include <iostream>
#include<boost/smart_ptr.hpp>
#include "Symbol.h"
using namespace std;
double addHandler(double *args, int len) {
	return args[0] + args[1];
}
double  minusHandler(double *args, int len) {
	return args[0] - args[1];
}
int main() {
	SymbolSet symbolSet;
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;
	symbolSet.pushFunctionSymbol("add", 2, addHandler);
	symbolSet.pushFunctionSymbol("add0", 2, addHandler);
	symbolSet.pushTerminalSymbol("v0", 10);
	symbolSet.pushSubFunctionSymbol("minus", 2, minusHandler);
	symbolSet.pushInputArgSymbol("a");
	vector<FunctionSymbol> functionSet = symbolSet.getFunctionSet();
	vector<FunctionSymbol> subFuncSet = symbolSet.getSubFunctionSet();
	vector<TerminalSymbol> terminal = symbolSet.getTerminalSet();
	vector<Symbol> symbolSet2 = symbolSet.getInputArgSet();
	unordered_map<string, SymbolMapInfo> symbolMap = symbolSet.getSymbolMap();
	printf("%f\r\n", functionSet[0].callFunctionHandler(args.get(), 2));
	printf("%f\r\n", subFuncSet[0].callFunctionHandler(args.get(), 2));
	printf("%f\r\n", terminal[0].getVal());
	cout << symbolSet2[0].getSymbolName() << endl;

	printf("%f\r\n", functionSet[symbolMap["add"].index].callFunctionHandler(args.get(), 2));
	//printf("%s\r\n", symbolSet2[0].getSymbolName());


	//printf("%f\r\n", symbolSet.getSymbolMap["add"].callFunctionHandler(args.get(), 2));

	//printf("%f\r\n", symbolSet.getSymbolMap["minus"].callFunctionHandler(args.get(), 2));



	return 0;
}