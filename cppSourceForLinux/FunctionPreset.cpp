//
// Created by JAY on 2022/2/9.
//

#include"FunctionPreset.h"
#include <math.h>
#include <algorithm>
const double theMaxReal = numeric_limits<double>::max() - 1;
const double dangerousVal = theMaxReal * 1e-10;
unordered_map<WhichFunction, pair<int, string>>functionArgMap{
        { W_add ,pair<int,string>{2,"add"} },{ W_minus , pair<int,string>{2,"miuns"} },
        { W_times , pair<int,string>{2,"times"} },{ W_divide,pair<int,string>{2,"divide"} },
        { W_sin,pair<int,string>{1,"sin"} },{ W_cos,pair<int,string>{1,"cos"} },
        { W_tan,pair<int,string>{1,"tan"} },{ W_asin,pair<int,string>{1,"asin"} },
        { W_acos,pair<int,string>{1,"acose"} },{ W_atan,pair<int,string>{1,"atan"} },
        { W_atan2,pair<int,string>{2,"atan2"} },{ W_pow,pair<int,string>{2,"pow"} },
        { W_square,pair<int,string>{1,"square"} },{ W_cube ,pair<int,string>{1,"cube"} },
        { W_sqrt,pair<int,string>{1,"sqrt"} },{ W_log2,pair<int,string>{1,"log2"} },
        { W_log10,pair<int,string>{1,"log10"} },{ W_max,pair<int,string>{2,"max"} },
        { W_min,pair<int,string>{2,"min"} },{ W_ex,pair<int,string>{1,"exp"} }
};


vector<WhichFunction>functionNumVec{ W_add, W_minus ,W_times,W_divide,W_sin,W_cos,W_tan,W_asin,W_acos,
                                     W_atan,W_atan2,W_pow,W_square,W_cube,W_sqrt,W_log2,W_log10,W_max,W_min,W_ex };

bool FunctionPresetSelfCheck() {
    return true;
}
bool checkFunctionArgsLen(WhichFunction whichFunction, int len) {
    if (functionArgMap[whichFunction].first == len)
        return true;
    else
        return false;
}
double functionPresetHandler(const double *args, WhichFunction whichFunction) {
    try {
        double outVal;
        switch (whichFunction)
        {
            case W_add:
                return args[0] + args[1];
            case W_minus:
                return args[0] - args[1];
            case W_times:
                return args[0] * args[1];
            case W_divide:
                if (args[1] < 1e-5)
                    return theMaxReal;
                else{
                    outVal = args[0] / args[1];
                    if(isfinite(outVal))
                        return theMaxReal;
                    else
                        return outVal;
                }

            case W_sin:
                return sin(args[0]);
            case W_cos:
                return cos(args[0]);
            case W_tan:
                outVal = tan(args[0]);
                if(isinf(outVal) || outVal >= dangerousVal)
                    return theMaxReal;
                else
                    return outVal;
            case W_asin:
                if (args[0] > 1 || args[0] < -1)
                    return theMaxReal;
                return asin(args[0]);
            case W_acos:
                if (args[0] > 1 || args[0] < -1)
                    return theMaxReal;
                return acos(args[0]);
            case  W_atan:
                return atan(args[0]);
            case W_atan2:
                if (args[1] < 1e-5)
                    return theMaxReal;
                else{
                    outVal = atan2(args[0], args[1]);
                    if(isinf(outVal))
                        return theMaxReal;
                    else
                        return outVal;
                }
            case W_pow:
                return pow(args[0], args[1]);
            case W_square:
                return args[0] * args[0];
            case W_cube:
                return args[0] * args[0] * args[0];
            case W_sqrt:
                return sqrt(args[0]);
            case W_log2:
                outVal = log(args[0]);
                if(isnan(outVal))
                    return theMaxReal;
                else
                    return outVal;
            case W_log10:
                outVal = log10(args[0]);
                if(isnan(outVal))
                    return theMaxReal;
                else
                    return outVal;
            case W_max:
                return max(args[0], args[1]);
            case W_min:
                return min(args[0], args[1]);
            case W_ex:
                outVal = exp(args[0]);
                if(isinf(outVal) || outVal >= dangerousVal)
                    return theMaxReal;
                else
                    return outVal;
            default:
                throw "error : no such function which is preseted!";
        }
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
}
double functionPresetHandler(const vector<double> &args, WhichFunction whichFunction){
    try {
        double outVal;
        switch (whichFunction)
        {
            case W_add:
                return args[0] + args[1];
            case W_minus:
                return args[0] - args[1];
            case W_times:
                return args[0] * args[1];
            case W_divide:
                if (args[1] < 1e-5)
                    return theMaxReal;
                else{
                    outVal = args[0] / args[1];
                    if(isfinite(outVal))
                        return theMaxReal;
                    else
                        return outVal;
                }

            case W_sin:
                return sin(args[0]);
            case W_cos:
                return cos(args[0]);
            case W_tan:
                outVal = tan(args[0]);
                if(isinf(outVal) || outVal >= dangerousVal)
                    return theMaxReal;
                else
                    return outVal;
            case W_asin:
                if (args[0] > 1 || args[0] < -1)
                    return theMaxReal;
                return asin(args[0]);
            case W_acos:
                if (args[0] > 1 || args[0] < -1)
                    return theMaxReal;
                return acos(args[0]);
            case  W_atan:
                return atan(args[0]);
            case W_atan2:
                if (args[1] < 1e-5)
                    return theMaxReal;
                else{
                    outVal = atan2(args[0], args[1]);
                    if(isinf(outVal))
                        return theMaxReal;
                    else
                        return outVal;
                }
            case W_pow:
                return pow(args[0], args[1]);
            case W_square:
                return args[0] * args[0];
            case W_cube:
                return args[0] * args[0] * args[0];
            case W_sqrt:
                return sqrt(args[0]);
            case W_log2:
                outVal = log(args[0]);
                if(isnan(outVal))
                    return theMaxReal;
                else
                    return outVal;
            case W_log10:
                outVal = log10(args[0]);
                if(isnan(outVal))
                    return theMaxReal;
                else
                    return outVal;
            case W_max:
                return max(args[0], args[1]);
            case W_min:
                return min(args[0], args[1]);
            case W_ex:
                outVal = exp(args[0]);
                if(isinf(outVal) || outVal >= dangerousVal)
                    return theMaxReal;
                else
                    return outVal;
            default:
                throw "error : no such function which is preseted!";
        }
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }




}

double functionPresetHandler(const double *args, const int len, WhichFunction whichFunction) {
    try {
        if (!checkFunctionArgsLen(whichFunction, len))
            throw "error : the length of this function is not equal to the len which is input arg";
        else
            return functionPresetHandler(args, whichFunction);
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
}

string getFunctionName(WhichFunction whichFunction) {
    return functionArgMap[whichFunction].second;
}

int getFunctionArgLen(WhichFunction whichFunction) {
    return functionArgMap[whichFunction].first;
}
const double &getTheMaxReal() {
    return theMaxReal;
}