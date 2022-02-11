//
// Created by JAY on 2022/2/9.
//

#include"SymbolSetGenerator.h"
#include<unordered_set>
//#include<set>
SymbolSet* SymbolSetGenerator::makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants,
                                             WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    SymbolSet *symbolSet = new SymbolSet();
    makeSymbolSetHelp1(*symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    return symbolSet;
}

SymbolSet* SymbolSetGenerator::makeSymbolSet(int numOfTerminals, double *constants, int numOfConstants,
                                             int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    SymbolSet *symbolSet = new SymbolSet();
    makeSymbolSetHelp1(*symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    return symbolSet;

}

SymbolSet* SymbolSetGenerator::makeSymbolSet(int numOfTerminals,
                                             WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    SymbolSet *symbolSet = new SymbolSet();
    makeSymbolSetHelp2(*symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    return symbolSet;
}
SymbolSet* SymbolSetGenerator::makeSymbolSet(int numOfTerminals,
                                             int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    SymbolSet *symbolSet = new SymbolSet();
    makeSymbolSetHelp2(*symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
    return symbolSet;
}



void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                                      WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    makeSymbolSetHelp1(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
}
void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                                      int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    makeSymbolSetHelp1(symbolSet, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
}

void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
                                      WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    makeSymbolSetHelp2(symbolSet, numOfTerminals, presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
}
void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, int numOfTerminals,
                                      int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    makeSymbolSetHelp2(symbolSet, numOfTerminals,  presetFunctions, numOfPresetFunctions, argsLenOfADFs, numOfADFs);
}


void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet,const int &numOfTerminals,const vector<double>&constants,
                                      const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs) {
    makeSymbolSetHelp3(symbolSet,numOfTerminals,constants,presetFunctions,argsLenOfADFs);
}
void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, const int &numOfTerminals,const vector<double>&constants,
                                      const vector<int> &presetFunctions, const vector<int> &argsLenOfADFs) {
    vector<WhichFunction>tmpWFVec;
    for(int i = 0 ; i < presetFunctions.size();++i)
        tmpWFVec.push_back((WhichFunction)presetFunctions[i]);
    makeSymbolSetHelp3(symbolSet,numOfTerminals,constants,tmpWFVec,argsLenOfADFs);

}

void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet,const int &numOfTerminals,
                                      const vector<WhichFunction> &presetFunctions, const vector<int> &argsLenOfADFs ) {
    vector<double>tmpConstance;
    makeSymbolSetHelp3(symbolSet,numOfTerminals,tmpConstance,presetFunctions,argsLenOfADFs);
}
void SymbolSetGenerator::setSymbolSet(SymbolSet &symbolSet, const int &numOfTerminals,
                                      const vector<int> &presetFunctions, const vector<int> &argsLenOfADFs) {
    vector<WhichFunction>tmpWFVec;
    vector<double>tmpConstance;
    for(int i = 0 ; i < presetFunctions.size();++i)
        tmpWFVec.push_back((WhichFunction)presetFunctions[i]);
    makeSymbolSetHelp3(symbolSet,numOfTerminals,tmpConstance,tmpWFVec,argsLenOfADFs);
}

void SymbolSetGenerator::makeSymbolSetHelp1(SymbolSet &symbolSet,int numOfTerminals, double *constants, int numOfConstants,
                                            int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    pushTerminals(symbolSet, numOfTerminals);
    pushConstans(symbolSet, constants, numOfConstants);
    pushPresetFunctions(symbolSet, (WhichFunction *)presetFunctions, numOfPresetFunctions);
    pushADFandInputArgs(symbolSet, argsLenOfADFs, numOfADFs);

}

void SymbolSetGenerator::makeSymbolSetHelp1(SymbolSet &symbolSet, int numOfTerminals, double *constants, int numOfConstants,
                                            WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    pushTerminals(symbolSet, numOfTerminals);
    pushConstans(symbolSet, constants, numOfConstants);
    pushPresetFunctions(symbolSet, presetFunctions, numOfPresetFunctions);
    pushADFandInputArgs(symbolSet, argsLenOfADFs, numOfADFs);

}

void SymbolSetGenerator::makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
                                            int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    pushTerminals(symbolSet, numOfTerminals);
    pushPresetFunctions(symbolSet, (WhichFunction *)presetFunctions, numOfPresetFunctions);
    pushADFandInputArgs(symbolSet, argsLenOfADFs, numOfADFs);

}

void SymbolSetGenerator::makeSymbolSetHelp2(SymbolSet &symbolSet, int numOfTerminals,
                                            WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs) {
    pushTerminals(symbolSet, numOfTerminals);
    pushPresetFunctions(symbolSet, presetFunctions, numOfPresetFunctions);
    pushADFandInputArgs(symbolSet, argsLenOfADFs, numOfADFs);

}



void SymbolSetGenerator::makeSymbolSetHelp3(SymbolSet &symbolSet,const int &numOfTerminals,const vector<double>&constants,
                                            const vector<WhichFunction> &presetFunctions,const vector<int> &argsLenOfADFs) {
    pushTerminals(symbolSet, numOfTerminals);
    pushConstans(symbolSet,constants);
    pushPresetFunctions(symbolSet, presetFunctions);
    pushADFandInputArgs(symbolSet, argsLenOfADFs);

}

void SymbolSetGenerator::pushTerminals(SymbolSet &symbolSet, int numOfTerminals) {
    int digitPtr = 0;
    char alphaStr[2] = { 0,0 };
    char *alphaPtr = alphaStr;
    *alphaPtr = startAlpha;
    for (int i = 0; i < numOfTerminals; ++i) {
        string theTermName(alphaStr);
        theTermName += to_string(digitPtr);

        symbolSet.pushTerminalSymbol(theTermName, 0);

        if (++(*alphaPtr) > endAlpha) {
            *alphaPtr = startAlpha;
            ++digitPtr;
        }

    }

}

void SymbolSetGenerator::pushConstans(SymbolSet &symbolSet, double *constants, int numOfConstants) {
    int digitPtr = 0;
    char alphaStr[] = {'C', 0,0 };
    char *alphaPtr = &alphaStr[1];
    *alphaPtr = startAlpha;
    for (int i = 0; i < numOfConstants; ++i) {
        string theTermName(alphaStr);
        theTermName += to_string(digitPtr);

        symbolSet.pushTerminalSymbol(theTermName, constants[i],true);

        if (++(*alphaPtr) > endAlpha) {
            *alphaPtr = startAlpha;
            ++digitPtr;
        }

    }
}

void SymbolSetGenerator::pushConstans(SymbolSet &symbolSet, const vector<double> &constants) {
    if(!constants.size())
        return;
    else{
        int digitPtr = 0;
        int numOfConstants = constants.size();
        char alphaStr[] = {'C', 0,0 };
        char *alphaPtr = &alphaStr[1];
        *alphaPtr = startAlpha;
        for (int i = 0; i < numOfConstants; ++i) {
            string theTermName(alphaStr);
            theTermName += to_string(digitPtr);

            symbolSet.pushTerminalSymbol(theTermName, constants[i],true);

            if (++(*alphaPtr) > endAlpha) {
                *alphaPtr = startAlpha;
                ++digitPtr;
            }

        }
    }
}

void SymbolSetGenerator::pushPresetFunctions(SymbolSet &symbolSet, WhichFunction* presetFunctions, int numOfPresetFunctions) {
    unordered_set<WhichFunction>funcTypeSet;
    for (int i = 0; i < numOfPresetFunctions; ++i) {
        if (funcTypeSet.count(presetFunctions[i]))
            continue;
        symbolSet.pushFunctionSymbol(presetFunctions[i]);
        funcTypeSet.insert(presetFunctions[i]);
    }

}
void SymbolSetGenerator::pushPresetFunctions(SymbolSet &symbolSet, const vector<WhichFunction> &presetFunctions) {
    unordered_set<WhichFunction>funcTypeSet;
    int numOfPresetFunctions = presetFunctions.size();
    for (int i = 0; i < numOfPresetFunctions; ++i) {
        if (funcTypeSet.count(presetFunctions[i]))
            continue;
        symbolSet.pushFunctionSymbol(presetFunctions[i]);
        funcTypeSet.insert(presetFunctions[i]);
    }
}
void SymbolSetGenerator::pushADFandInputArgs(SymbolSet &symbolSet, int *argsLenOfADFs, int numOfADFs) {
    int maxLen = 0;
    int ADFIndexCount = 0;
    int digitPtr1 = 0 , digitPtr2 = 0;
    char alphaStr1[] = { 'A', 0,0 }, alphaStr2[] = { 'I', 0,0 };
    char *alphaPtr1 = &alphaStr1[1];

    char *alphaPtr2 = &alphaStr2[1];

    *alphaPtr1 = *alphaPtr2 = startAlpha;

    for (int i = 0; i < numOfADFs; ++i) {
        if (argsLenOfADFs[i] > maxLen)
            maxLen = argsLenOfADFs[i];


        string theTermName(alphaStr1);
        theTermName += to_string(digitPtr1);

        symbolSet.pushSubFunctionSymbol(theTermName, argsLenOfADFs[i], ADFIndexCount++);

        if (++(*alphaPtr1) > endAlpha) {
            *alphaPtr1 = startAlpha;
            ++digitPtr1;
        }

    }


    for (int i = 0; i < maxLen; ++i) {
        string theTermName(alphaStr2);
        theTermName += to_string(digitPtr2);

        symbolSet.pushInputArgSymbol(theTermName);

        if (++(*alphaPtr2) > endAlpha) {
            *alphaPtr2 = startAlpha;
            ++digitPtr2;
        }

    }
}
void SymbolSetGenerator::pushADFandInputArgs(SymbolSet &symbolSet, const vector<int> &argsLenOfADFs) {
    int maxLen = 0;
    int numOfADFs = argsLenOfADFs.size();
    int ADFIndexCount = 0;
    int digitPtr1 = 0 , digitPtr2 = 0;
    char alphaStr1[] = { 'A', 0,0 }, alphaStr2[] = { 'I', 0,0 };
    char *alphaPtr1 = &alphaStr1[1];

    char *alphaPtr2 = &alphaStr2[1];

    *alphaPtr1 = *alphaPtr2 = startAlpha;

    for (int i = 0; i < numOfADFs; ++i) {
        if (argsLenOfADFs[i] > maxLen)
            maxLen = argsLenOfADFs[i];


        string theTermName(alphaStr1);
        theTermName += to_string(digitPtr1);

        symbolSet.pushSubFunctionSymbol(theTermName, argsLenOfADFs[i], ADFIndexCount++);

        if (++(*alphaPtr1) > endAlpha) {
            *alphaPtr1 = startAlpha;
            ++digitPtr1;
        }

    }


    for (int i = 0; i < maxLen; ++i) {
        string theTermName(alphaStr2);
        theTermName += to_string(digitPtr2);

        symbolSet.pushInputArgSymbol(theTermName);

        if (++(*alphaPtr2) > endAlpha) {
            *alphaPtr2 = startAlpha;
            ++digitPtr2;
        }

    }
}