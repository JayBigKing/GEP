#include <iostream>
#include<boost/smart_ptr.hpp>
#include "Symbol.h"
#include "ChromosomeRule.h"
#include "Chromosome.h"
#include "ChromosomeDecoder.h"
#include "SL_ChromosomeDecoder.h"
#include "SymbolSetGenerator.h"
#include "initHelp.h"
#include "SL_GEP.h"
using namespace std;
double addHandler(const double *args, const int len) {
	return args[0] + args[1];
}
double  minusHandler(const double *args, const int len) {
	return args[0] - args[1];
}
double timesHandler(const double *args, const int len) {
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
	SL_ChromosomeDecoder cd;
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


void test4() {
	SymbolSet symbolSet;
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;


	symbolSet.pushFunctionSymbol(W_add);	//0
	symbolSet.pushFunctionSymbol(W_times); //1
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
	SL_ChromosomeDecoder cd;
	vector<double>input(2);


	chromosome.mainProgramEx[0] = 4;
	chromosome.mainProgramEx[1] = 1;
	chromosome.mainProgramEx[2] = 0;
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

void test5() {
	//(int numOfTerminals, 
	//	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

	//a  0
	//b  1
	//add 2
	//times 3
	//G 4
	//x  5
	//y  6
	int numOfTerminals = 2;
	int numOfPresetFunctions = 2;
	int numOfADFs = 1;

	int mainProgramH = 10;

	boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
	boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;

	presetFunctions[0] = 0;
	presetFunctions[1] = 2;

	argsLenOfADFs[0] = 2;

	SymbolSetGenerator sg;
	boost::shared_array<SymbolSet> symbolSetSA(sg.makeSymbolSet(numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs));
	SymbolSet *symbolSet = symbolSetSA.get();



	vector<int>ADFH;
	ADFH.push_back(1);
	ChromosomeRule cr(mainProgramH, ADFH, *symbolSet);
	Chromosome chromosome(cr);
	SL_ChromosomeDecoder cd;
//	vector<double>input(2);
	boost::shared_array<double> input(new double[2]);


	chromosome.mainProgramEx[0] = 4;
	chromosome.mainProgramEx[1] = 3;
	chromosome.mainProgramEx[2] = 2;
	chromosome.mainProgramEx[3] = 0;
	chromosome.mainProgramEx[4] = 0;
	chromosome.mainProgramEx[5] = 1;
	chromosome.mainProgramEx[6] = 0;

	chromosome.ADFEx[0][0] = 2;
	chromosome.ADFEx[0][1] = 5;
	chromosome.ADFEx[0][2] = 6;


	input[0] = 1;
	input[1] = 2;

	printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

}

void test6() {
	//(int numOfTerminals, 
	//	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

	//a  0
	//b  1
	//add 2
	//times 3
	//G 4
	//x  5
	//y  6
	int numOfTerminals = 2;
	int numOfPresetFunctions = 2;
	int numOfADFs = 1;

	int mainProgramH = 10;

	boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
	boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
	boost::shared_array<double> args(new double[2]);
	args[0] = 1;
	args[1] = 2;

	presetFunctions[0] = 0;
	presetFunctions[1] = 2;

	argsLenOfADFs[0] = 2;

	SymbolSetGenerator sg;
	SymbolSet symbolSet;
	sg.setSymbolSet(symbolSet, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs);
	//SymbolSetGenerator::setSymbolSet(symbolSet, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs);
	//boost::shared_array<SymbolSet> symbolSetSA(sg.makeSymbolSet(numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(), numOfADFs));
	//SymbolSet *symbolSet = symbolSetSA.get();



	vector<int>ADFH;
	ADFH.push_back(1);
	ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
	Chromosome chromosome(cr);
	SL_ChromosomeDecoder cd;
	//	vector<double>input(2);
	boost::shared_array<double> input(new double[2]);


	chromosome.mainProgramEx[0] = 4;
	chromosome.mainProgramEx[1] = 3;
	chromosome.mainProgramEx[2] = 2;
	chromosome.mainProgramEx[3] = 0;
	chromosome.mainProgramEx[4] = 0;
	chromosome.mainProgramEx[5] = 1;
	chromosome.mainProgramEx[6] = 0;

	chromosome.ADFEx[0][0] = 2;
	chromosome.ADFEx[0][1] = 5;
	chromosome.ADFEx[0][2] = 6;


	input[0] = 1;
	input[1] = 2;

	printf("%f\r\n", cd.decode(input.get(), chromosome, cr));

}

void test7() {
	vector<double> tmp(10);
	initVectorHelp(tmp, 20);
	printf("%d\r\n", tmp.size());
}


void test8() {
	//(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
	//	WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
	//	bool ifUseSuspendNum = true, double similarValue = 1e-6)
	//a  0
	//b  1
	//add 2
	//times 3
	//G 4
	//x  5
	//y  6
	int chroNum = 1;
	int numOfTerminals = 2;
	int numOfPresetFunctions = 2;
	int numOfADFs = 1;

	int mainProgramH = 10;

	int TAPairNum = 1;
	int needEpoch = 1000;

	boost::shared_array<int> presetFunctions(new int[numOfPresetFunctions]);
	boost::shared_array<int> argsLenOfADFs(new int[numOfADFs]);
	boost::shared_array<double> realTermVec(new double[2]);
	boost::shared_array<double> ansVec(new double[2]);
	realTermVec[0] = 1;
	realTermVec[1] = 2;
	ansVec[0] = 0;
	ansVec[1] = 0;



	presetFunctions[0] = 0;
	presetFunctions[1] = 2;

	argsLenOfADFs[0] = 2;


	boost::shared_array<int> ADFH(new int[1]);
	ADFH[0] = 1;


	SL_GEP slgep(chroNum, realTermVec.get(), ansVec.get(), TAPairNum, needEpoch, numOfTerminals, presetFunctions.get(), numOfPresetFunctions, argsLenOfADFs.get(),
		numOfADFs, mainProgramH, ADFH.get());


	printf("%f\r\n", slgep.test1());
}


int main() {
	test8();


	return 0;
}


//
//void test3() {
//	SymbolSet symbolSet;
//	boost::shared_array<double> args(new double[2]);
//	args[0] = 1;
//	args[1] = 2;
//
//
//	symbolSet.pushFunctionSymbol("add", 2, addHandler);	//0
//	symbolSet.pushFunctionSymbol("times", 2, timesHandler); //1
//	symbolSet.pushTerminalSymbol("a", 10);	//2
//	symbolSet.pushTerminalSymbol("b", 10);	//3
//	symbolSet.pushSubFunctionSymbol("G", 2, 0);	//4
//	symbolSet.pushInputArgSymbol("x");		//5
//	symbolSet.pushInputArgSymbol("y");		//6
//
//	int mainProgramH = 10;
//	vector<int>ADFH;
//	ADFH.push_back(1);
//	ChromosomeRule cr(mainProgramH, ADFH, symbolSet);
//	Chromosome chromosome(cr);
//	ChromosomeDecoder cd;
//	vector<double>input(2);
//
//
//	chromosome.mainProgramEx[0] = 4;
//	chromosome.mainProgramEx[1] = 1;
//	chromosome.mainProgramEx[2] = 2;
//	chromosome.mainProgramEx[3] = 2;
//	chromosome.mainProgramEx[4] = 2;
//	chromosome.mainProgramEx[5] = 3;
//	chromosome.mainProgramEx[6] = 2;
//
//	chromosome.ADFEx[0][0] = 0;
//	chromosome.ADFEx[0][1] = 5;
//	chromosome.ADFEx[0][2] = 6;
//
//
//	input[0] = 1;
//	input[1] = 2;
//
//	printf("%f\r\n", cd.decode(input, chromosome, cr));
//
//
//
//
//}