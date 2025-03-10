//
// Created by JAY on 2022/2/11.
//

#include "SL_ChromosomeDecoder_Thread.h"
#include <queue>
#include <vector>


void SL_ChromosomeDecoder_Thread::clearGlobalData() {
    //清主函数的操作符栈和操作数向量
    stack<DecodeElement>tmpEmptyStack;
    mainOpStack = tmpEmptyStack;
    mainOcVector.clear();

    //清ADF的操作符栈和操作数向量
    for (int i = 0; i < ADFOpStacks.size(); ++i)
        ADFOpStacks[i] = tmpEmptyStack;

    ADFOpStacks.clear();

    for (int i = 0; i < ADFOcVector.size(); ++i)
        ADFOcVector[i].clear();

    ADFOcVector.clear();

}


void  SL_ChromosomeDecoder_Thread::recordADFStackAndVec(const vector<bool> &needADF) {
    stack<DecodeElement>tmpEmptyStack;
    vector<DecodeElement>tmpEmptyVector;
    for (int i = 0; i < needADF.size(); ++i) {
        if (!needADF[i]) {
            ADFOpStacks.push_back(tmpEmptyStack);
            ADFOcVector.push_back(tmpEmptyVector);
        }
        else {
            queue<DecodeElement> readQue;
            DecodeElement tmpDe;
            DecodeElement lastDe;
            int queuePtr = 0;
            int globalPointIndex = 0;

            vector<int>ADFEx = chromosome.ADFEx[i];
            ADFOpStacks.push_back(tmpEmptyStack);
            ADFOcVector.push_back(tmpEmptyVector);

            try {
                if (!ADFEx.size())
                    throw  "invailed chromosome";
            }
            catch (const char* &e) {
                printf("%s\r\n", e);
                exit(-1);
            }

            tmpDe = makeDecodElement(ADFEx[queuePtr], queuePtr, globalPointIndex);

            try {
                if (tmpDe.symbolType == ARGUMENT) {
                    ADFOcVector[i].push_back(tmpDe);
                    continue;
                }
                else if (tmpDe.symbolType == TERMINAL)
                    throw  "invailed chromosome";
            }
            catch (const char* &e) {
                printf("%s\r\n", e);
                exit(-1);
            }

            readQue.push(tmpDe);
            ++queuePtr;


            while (!readQue.empty())
            {
                lastDe = readQue.front();
                readQue.pop();
                if (lastDe.symbolType == ARGUMENT) {
                    ADFOcVector[i].push_back(lastDe);
                }
                else {
                    int opNum = lastDe.opNum;
                    for (int i = 0; i < opNum; i++) {
                        tmpDe = makeDecodElement(ADFEx[queuePtr], queuePtr, globalPointIndex);
                        readQue.push(tmpDe);
                        ++queuePtr;
                    }
                    ADFOpStacks[i].push(lastDe);
                }
            }


        }

    }



}


void SL_ChromosomeDecoder_Thread::recordMainProgramStackAndVec(vector<bool> &needADF) {
    queue<DecodeElement> readQue;
    DecodeElement tmpDe;
    DecodeElement lastDe;
    int queuePtr = 0;
    int globalPointIndex = 0;


    try {
        if (!chromosome.mainProgramEx.size())
            throw  "invailed chromosome";
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
    tmpDe = makeDecodElement(chromosome.mainProgramEx[queuePtr], queuePtr, globalPointIndex);

    try {
        if (tmpDe.symbolType == TERMINAL) {
            mainOcVector.push_back(tmpDe);
            return;
        }
        else if (tmpDe.symbolType == ARGUMENT)
            throw  "invailed chromosome";
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }

    readQue.push(tmpDe);
    ++queuePtr;

    while (!readQue.empty())
    {
        lastDe = readQue.front();
        readQue.pop();
        if (lastDe.symbolType == TERMINAL) {
            mainOcVector.push_back(lastDe);
        }
        else {
            int opNum = lastDe.opNum;
            for (int i = 0; i < opNum; i++) {
                tmpDe = makeDecodElement(chromosome.mainProgramEx[queuePtr], queuePtr, globalPointIndex);
                readQue.push(tmpDe);
                ++queuePtr;
            }
            if (lastDe.symbolType == SUB_FUNCTION)
                needADF[symbolSet.getSymbol(lastDe.symbolSetIndex).getADFIndex()] = true;		//只记录mian program 包含的ADF
            mainOpStack.push(lastDe);
        }
    }

}

void SL_ChromosomeDecoder_Thread::setChromosome(Chromosome &chromosome) {
    this->chromosome = chromosome;
    try {
        if (!cr.getSymbolSet().getTerminalSet().size())
            throw "ChromosomeRule did not initial!";
    }
    catch (const char * &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
    clearGlobalData();
    vector<bool> needADF(this->chromosome.ADFEx.size());			//main program未必包含所有的ADF，只记录mian program 包含的ADF，节约空间
    for (int i = 0; i < needADF.size(); ++i)
        needADF[i] = false;
    recordMainProgramStackAndVec(needADF);
    recordADFStackAndVec(needADF);

}

double SL_ChromosomeDecoder_Thread::mainProgramDecode() {
    vector<double>outputVec(cr.getMainPR().totalLen);
    stack<DecodeElement> opStack = mainOpStack;
    DecodeElement tmpDe;
    DecodeElement lastDe;
    vector<double>args(cr.getMainU());
    double nowDecodeVal = 0.0;
    for(int i = 0 ; i < mainOcVector.size() ; ++i)
        outputVec[mainOcVector[i].chroIndex] = symbolSet.getSymbol(mainOcVector[i].symbolSetIndex).getVal();


    while (!opStack.empty()) {
        tmpDe = opStack.top();
        Symbol tmpSym = symbolSet.getSymbol(tmpDe.symbolSetIndex);
        int opLastIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
        opStack.pop();

        for (int i = tmpDe.pointIndex, j = 0; i < tmpDe.pointIndex + tmpDe.opNum; ++i, ++j) {
            args[j] = outputVec[i];
        }

        if (tmpDe.symbolType == FUNCTION) {
            nowDecodeVal = tmpSym.callFunctionHandler(args);
            if (nowDecodeVal >= getTheMaxReal())
                return nowDecodeVal;
            outputVec[tmpDe.chroIndex] = nowDecodeVal;
        }
        else if (tmpDe.symbolType == SUB_FUNCTION) {
            nowDecodeVal = ADFProgramDecode(tmpSym, args);
            if (nowDecodeVal >= getTheMaxReal())
                return nowDecodeVal;
            outputVec[tmpDe.chroIndex] = nowDecodeVal;
        }

//        if (tmpDe.symbolType == FUNCTION)
//            outputVec[tmpDe.chroIndex] = tmpSym.callFunctionHandler(args.get());
//        else if (tmpDe.symbolType == SUB_FUNCTION)
//            outputVec[tmpDe.chroIndex] = ADFProgramDecode(tmpSym, args.get());
    }

    return outputVec[0];
}

void SL_ChromosomeDecoder_Thread::setSymbolSetInputArgs(int num, vector<double> args) {
    vector<Symbol>& inputArgs = symbolSet.getInputArgSet();
    try {
        if (inputArgs.size() < num)
            throw  "error!num is longer than the size of inputArgs set!";
    }
    catch (const char* &e) {
        printf("%s\r\n", e);
        exit(-1);
    }
    for (int i = 0; i < inputArgs.size(); ++i) {
        inputArgs[i].setVal(args[i]);
    }
}


//ADF,即 sub-function
double SL_ChromosomeDecoder_Thread::ADFProgramDecode(Symbol &subFunctionSym, vector<double> inputArgsVal){
    int theADFIndex = subFunctionSym.getADFIndex();
    vector<double>outputVec(cr.getADFPR(theADFIndex).totalLen);
    stack<DecodeElement> opStack = ADFOpStacks[theADFIndex];
    DecodeElement tmpDe;
    vector<double>args(cr.getADFU());
    double nowDecodeVal = 0.0;

    setSymbolSetInputArgs(subFunctionSym.getNumOfInputArg(), inputArgsVal);
    for (int i = 0; i < ADFOcVector[theADFIndex].size(); ++i)
        outputVec[ADFOcVector[theADFIndex][i].chroIndex] = symbolSet.getSymbol(ADFOcVector[theADFIndex][i].symbolSetIndex).getVal();



    while (!opStack.empty()) {
        tmpDe = opStack.top();
        Symbol tmpSym = symbolSet.getSymbol(tmpDe.symbolSetIndex);
        int opLastIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
        opStack.pop();

        for (int i = tmpDe.pointIndex, j = 0; i < tmpDe.pointIndex + tmpDe.opNum; ++i, ++j) {
            args[j] = outputVec[i];
        }
        if (tmpDe.symbolType == FUNCTION) {
            nowDecodeVal = tmpSym.callFunctionHandler(args);
            if (nowDecodeVal >= getTheMaxReal())
                return nowDecodeVal;
            outputVec[tmpDe.chroIndex] = nowDecodeVal;
        }

    }

    return outputVec[0];
}



//ADF,即 sub-function
double SL_ChromosomeDecoder_Thread::ADFProgramDecode(Symbol &subFunctionSym, double* inputArgsVal) {
    return 0;
//    int theADFIndex = subFunctionSym.getADFIndex();
//    vector<double>outputVec(cr.getADFPR(theADFIndex).totalLen);
//    stack<DecodeElement> opStack = ADFOpStacks[theADFIndex];
//    DecodeElement tmpDe;
//    vector<double>args(cr.getU());
//    double nowDecodeVal = 0.0;
//
//    setSymbolSetInputArgs(subFunctionSym.getNumOfInputArg(), inputArgsVal);
//    for (int i = 0; i < ADFOcVector[theADFIndex].size(); ++i)
//        outputVec[ADFOcVector[theADFIndex][i].chroIndex] = symbolSet.getSymbol(ADFOcVector[theADFIndex][i].symbolSetIndex).getVal();
//
//
//
//    while (!opStack.empty()) {
//        tmpDe = opStack.top();
//        Symbol tmpSym = symbolSet.getSymbol(tmpDe.symbolSetIndex);
//        int opLastIndex = tmpDe.pointIndex + tmpDe.opNum - 1;
//        opStack.pop();
//
//        for (int i = tmpDe.pointIndex, j = 0; i < tmpDe.pointIndex + tmpDe.opNum; ++i, ++j) {
//            args[j] = outputVec[i];
//        }
//        if (tmpDe.symbolType == FUNCTION) {
//            nowDecodeVal = tmpSym.callFunctionHandler(args);
//            if (nowDecodeVal >= getTheMaxReal())
//                return nowDecodeVal;
//            outputVec[tmpDe.chroIndex] = nowDecodeVal;
//        }
//
////        if (tmpDe.symbolType == FUNCTION)
////            outputVec[tmpDe.chroIndex] = tmpSym.callFunctionHandler(args.get());
//    }
//
//    return outputVec[0];
}