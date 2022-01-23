#include <iostream>
#include<boost/smart_ptr.hpp>
#include "Symbol.h"
#include "ChromosomeRule.h"
#include "Chromosome.h"
#include "ChromosomeDecoder.h"
using namespace std;
double addHandler(double *args, int len) {
	return args[0] + args[1];
}
double  minusHandler(double *args, int len) {
	return args[0] - args[1];
}
double timesHandler(double *args, int len) {
	return args[0] * args[1];
}

void test1() {
	SymbolSet symbolSet;
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;
	symbolSet.pushFunctionSymbol("add", 2, addHandler);
	symbolSet.pushFunctionSymbol("add0", 2, addHandler);
	symbolSet.pushTerminalSymbol("v0", 10);
	symbolSet.pushSubFunctionSymbol("minus", 2, 1);
	symbolSet.pushInputArgSymbol("a");
	vector<Symbol> functionSet = symbolSet.getFunctionSet();
	vector<Symbol> subFuncSet = symbolSet.getSubFunctionSet();
	vector<Symbol> terminal = symbolSet.getTerminalSet();
	vector<Symbol> symbolSet2 = symbolSet.getInputArgSet();
	unordered_map<string, SymbolMapInfo> symbolMap = symbolSet.getSymbolMap();
	Symbol fs = symbolSet.getSymbol("add");
	Symbol ts = symbolSet.getSymbol("v0");
	printf("%f\r\n", functionSet[0].callFunctionHandler(args.get(), 2));
	printf("%f\r\n", subFuncSet[0].callFunctionHandler(args.get(), 2));
	printf("%f\r\n", terminal[0].getVal());
	cout << symbolSet2[0].getSymbolName() << endl;

	printf("%f\r\n", functionSet[symbolMap["add"].index].callFunctionHandler(args.get(), 2));
	printf("%f\r\n", fs.callFunctionHandler(args.get(), 2));
	printf("%f\r\n", ts.getVal());
	//printf("%s\r\n", symbolSet2[0].getSymbolName());


	//printf("%f\r\n", symbolSet.getSymbolMap["add"].callFunctionHandler(args.get(), 2));

	//printf("%f\r\n", symbolSet.getSymbolMap["minus"].callFunctionHandler(args.get(), 2));
}
void test2() {
	SymbolSet symbolSet;
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;
	symbolSet.pushFunctionSymbol("add", 2, minusHandler);
	symbolSet.pushFunctionSymbol("add0", 2, addHandler);
	symbolSet.pushTerminalSymbol("v0", 10);
	symbolSet.pushSubFunctionSymbol("G", 2, 1);
	symbolSet.pushInputArgSymbol("a");
	vector<Symbol> functionSet = symbolSet.getFunctionSet();
	vector<Symbol> subFuncSet = symbolSet.getSubFunctionSet();
	vector<Symbol> terminal = symbolSet.getTerminalSet();
	vector<Symbol> symbolSet2 = symbolSet.getInputArgSet();


	int mainProgramH = 10; 
	vector<int>ADFH;
	ADFH.push_back(10);
	ADFH.push_back(8);

	ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
	printf("%d\r\n", cr.getADFPR(0).l);
}
void test3() {
	SymbolSet symbolSet;
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;


	symbolSet.pushFunctionSymbol("add", 2, addHandler);	//0
	symbolSet.pushFunctionSymbol("times", 2, timesHandler); //1
	symbolSet.pushTerminalSymbol("a", 10);	//2
	symbolSet.pushTerminalSymbol("b", 10);	//3
	symbolSet.pushSubFunctionSymbol("G", 2, 0);	//4
	symbolSet.pushInputArgSymbol("x");		//5
	symbolSet.pushInputArgSymbol("y");		//6

	int mainProgramH = 10;
	vector<int>ADFH;
	ADFH.push_back(1);
	ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
	Chromosome chromosome(cr);
	ChromosomeDecoder cd;
	vector<double>input(2);


	chromosome.mainProgramEx[0] = 4;
	chromosome.mainProgramEx[1] = 1;
	chromosome.mainProgramEx[2] = 2;
	chromosome.mainProgramEx[3] = 2;
	chromosome.mainProgramEx[4] = 2;
	chromosome.mainProgramEx[5] = 3;
	chromosome.mainProgramEx[6] = 2;

	chromosome.ADFEx[0][0] = 0;
	chromosome.ADFEx[0][1] = 5;
	chromosome.ADFEx[0][2] = 6;


	input[0] = 1;
	input[1] = 2;

	printf("%f\r\n", cd.decode(input, chromosome, cr));




}


int main() {
	test3();



	return 0;
}