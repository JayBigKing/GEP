#pragma once
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
//const double theMaxReal;
enum WhichFunction
{
	W_add = 0,
	W_minus,
	W_times,
	W_divide,
	W_sin,
	W_cos,
	W_tan,
	W_asin,
	W_acos,
	W_atan,
	W_atan2,
	W_pow,
	W_square,
	W_cube,
	W_sqrt,
	W_log2,
	W_log10,
	W_max,
	W_min,
	W_ex
};




bool FunctionPresetSelfCheck();
bool checkFunctionArgsLen(WhichFunction whichFunction, int len);
double functionPresetHandler(const double *args, WhichFunction whichFunction);
double functionPresetHandler(const double *args, const int len, WhichFunction whichFunction);

string getFunctionName(WhichFunction whichFunction);
int getFunctionArgLen(WhichFunction whichFunction);

const double &getTheMaxReal();
