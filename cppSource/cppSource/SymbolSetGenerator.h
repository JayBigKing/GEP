#pragma once
#include "Symbol.h"
//Éú³ÉSymbolSet
class SymbolSetGenerator
{
public:
	SymbolSetGenerator(){}
	~SymbolSetGenerator(){}
	static SymbolSet* makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants, 
		WhichFunction* presetFunctions, int numOfPresetFunctions,int *argsLenOfADFs, int numOfADFs);
	static SymbolSet* makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);


	static SymbolSet* makeSymbolSet(int numOfTerminals,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
	static SymbolSet* makeSymbolSet(int numOfTerminals,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

	static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
	static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);


	static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
	static void setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
private:
	static const int startAlpha = 'a', endAlpha = 'z';
	static void pushTerminals(SymbolSet &symbolSet,int numOfTerminals);
	static void pushConstans(SymbolSet &symbolSet, double *constants,int numOfConstants);
	static void pushPresetFunctions(SymbolSet &symbolSet, WhichFunction* presetFunctions, int numOfPresetFunctions);
	static void pushADFandInputArgs(SymbolSet &symbolSet, int *argsLenOfADFs, int numOfADFs);
	static void makeSymbolSetHelp1(SymbolSet &symbolSet,int numOfTerminals, double *constants, int numOfConstants,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
	static void makeSymbolSetHelp1(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);

	static void makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
		int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);
	static void makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
		WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs);


};















//
//double addHandler(const double *args, const int len) {
//	return args[0] + args[1];
//}
//double  minusHandler(const double *args, const int len) {
//	return args[0] - args[1];
//}
//double timesHandler(const  double *args, const int len) {
//	return args[0] * args[1];
//}
//double divideHandler(const double *args, const  int len) {
//	try {
//		if (!args[1])
//			throw "error : divide zero!!";
//		return args[0] / args[1];
//	}
//	catch (const char *e) {
//		printf("%d\r\n", e);
//	}
//}
//double sinHandler(const double *args, const  int len) {
//	return sin(args[0]);
//}
//double cosHandler(const double *args, const  int len) {
//	return cos(args[0]);
//}
//double tanHandler(const double *args, const  int len) {
//	return tan(args[0]);
//}
//double asinHandler(const double *args, const  int len) {
//	return asin(args[0]);
//}
//double acosHandler(const double *args, const  int len) {
//	return acos(args[0]);
//}
//double atanHandler(const double *args, const  int len) {
//	return atan2(args[0],args[1]);
//}
//double powHandler(const double *args, const  int len) {
//	return pow(args[0], args[1]);
//}
//double squareHandler(const double *args, const  int len) {
//	return pow(args[0], 2);
//}
//double sqrtHandler(const double *args) {
//	return sqrt(args[0]);
//}
//double log2Handler(const double *args) {
//	return log(args[0]);
//}
//double log10Handler(const double *args) {
//	return log2(args[0]);
//}
//double maxHandler(const double *args) {
//	return max(args[0], args[1]);
//}
//double minHandler(const double *args) {
//	return min(args[0], args[1]);
//}