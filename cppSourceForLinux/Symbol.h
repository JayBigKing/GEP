//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_SYMBOL_H
#define CPPSOURCEFORLINUX_SYMBOL_H


#include "FunctionPreset.h"

using namespace std;
enum SymbolType
{
    FUNCTION = 1,
    SUB_FUNCTION,
    TERMINAL,
    ARGUMENT
};
enum FunctionType {
    PRESET,
    USER
};


class Symbol
{
public:
    Symbol(){}
    Symbol(SymbolType symbolType, string symbolName);
    Symbol(int num,SymbolType symbolType, string symbolName);

    Symbol(string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen));
    Symbol(int num, string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen));

    Symbol(WhichFunction wf);
    Symbol(int num, WhichFunction wf);


    Symbol(string symbolName , double val,bool ifConstant = false);
    Symbol(int num, string symbolName, double val, bool ifConstant = false);

    Symbol(string symbolName, int numOfInputArg, int ADFIndex);
    Symbol(int num, string symbolName, int numOfInputArg, int ADFIndex);
    ~Symbol(){}
    void setNum(int theNum) { num = theNum; }
    void setVal(double val) { value = val; }

    SymbolType getSymbolType() { return symbolType; }
    string getSymbolName() { return symbolName; }
    int getNum() { return num; }

    double callFunctionHandler(double *args, int argLen);
    double callFunctionHandler(double *args);
    double callFunctionHandler(vector<double>args);
    WhichFunction getWhichFunction();
    int getNumOfInputArg();
    double getVal();
    int getADFIndex();
protected:
    int num;
    SymbolType symbolType;
    string symbolName;
    double value;
    int numOfInputArg;
    double(*functionHandler)(const double *args,const int argLen);
    FunctionType functionType;
    WhichFunction whichFunction;
    bool ifValueConstant;
    int ADFIndex;
};

struct SymbolMapInfo
{
    SymbolType symbolType;
    int index;
    void set(SymbolType st, int index0) {
        symbolType = st;
        index = index0;
    }
};

class SymbolSet
{
public:
    SymbolSet(){}
    ~SymbolSet(){}

    bool pushFunctionSymbol(string symbolName, int numOfInputArg, double(*functionHandler)(const double *args, const int argLen));
    bool pushFunctionSymbol( WhichFunction wf);
    bool pushFunctionSymbol(Symbol functionSymbol);

    bool pushSubFunctionSymbol(string symbolName,int numOfInputArg, int ADFIndex);
    bool pushSubFunctionSymbol(Symbol subFunctionSymbol);

    bool pushTerminalSymbol(string symbolName, double val, bool ifConstant = false);
    bool pushTerminalSymbol(Symbol terminal);

    bool pushInputArgSymbol(string symbolName);
    bool pushInputArgSymbol(Symbol inputArg);

    vector<Symbol>& getFunctionSet() { return functionSet; }
    vector<Symbol>& getSubFunctionSet() { return subFunctionSet; }
    vector<Symbol>& getTerminalSet() { return terminalSet; }
    vector<Symbol>& getInputArgSet() { return inputArgSet; }
    unordered_map<string, SymbolMapInfo>& getSymbolMap() { return symbolMap; }
    Symbol& getSymbol(string str);
    Symbol& getSymbol(int index);
    Symbol& getSymbolHelp(SymbolMapInfo smi);

    SymbolSet& operator = (const SymbolSet &ss);
private:
    int symbolNum = 0;
    vector<Symbol> functionSet;
    vector<Symbol> subFunctionSet;
    vector<Symbol> terminalSet;
    vector<Symbol> inputArgSet;
    unordered_map<string, SymbolMapInfo> symbolMap;
    vector<SymbolMapInfo> symbolVec;
};

#endif //CPPSOURCEFORLINUX_SYMBOL_H
