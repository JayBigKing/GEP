from gepChromosome import Chromosome
from gepChromosome import ChromosomeRule
from dataStructure import Stack,MyQueue
from gepSymbol import SymbolSet
from gepSymbol import Symbol
from gepSymbol.functionPreset import FunctionPreset
from baseDataReference import IntReference
import queue
import copy
import numpy as np

class ChromosomeDecoder:
    class DecodeElement:
        def __init__(self):
            self.symbolSetIndex = 0
            self.symbolType = None
            self.chroIndex = 0
            self.pointIndex = 0
            self.opNum = 0

    def __init__(self):
        self.__cr:ChromosomeRule.ChromosomeRule
        self.__symbolSet:SymbolSet.SymbolSet
        self.__chromosome:Chromosome.Chromosome
        self.__realTerminals = []

        self.__mainOpStack = Stack.Stack()
        self.__ADFOpStacks = []
        self.__mainOcVector = []
        self.__ADFOcVector = []

    def setChromosomeRule(self,cr:ChromosomeRule.ChromosomeRule):
        self.__cr = copy.deepcopy(cr)
        self.__symbolSet = cr.getSymbolSet()

    def setChromosome(self,chromosome:Chromosome.Chromosome):
        self.__chromosome = copy.deepcopy(chromosome)
        self.__clearGlobalData()
        needADF = [False]*len(self.__chromosome.ADFEx)
        self.__recordMainProgramStackAndVec(needADF)
        self.__recordADFStackAndVec(needADF)

    def __clearGlobalData(self):
        self.__mainOpStack.clear()
        self.__ADFOpStacks = []
        self.__mainOcVector = []
        self.__ADFOcVector = []

    def __makeDecodeElement(self,index:int,chroIndex:int,globalPointIndex:IntReference.IntReference):
        tmpSym = self.__symbolSet.getSymbolByIndex(index)
        tmpDe = ChromosomeDecoder.DecodeElement()
        tmpDe.symbolSetIndex = index
        tmpDe.chroIndex = chroIndex
        tmpDe.symbolType = tmpSym.getSymbolType()

        if tmpDe.symbolType == Symbol.SymbolType.FUNCTION or \
            tmpDe.symbolType == Symbol.SymbolType.SUB_FUNCTION:
            tmpDe.pointIndex = globalPointIndex.x + 1
            tmpDe.opNum = tmpSym.getNumOfInputArgs()
            globalPointIndex.x = tmpDe.pointIndex + tmpDe.opNum - 1
        else:
            tmpDe.pointIndex = tmpDe.opNum = -1
            globalPointIndex.x += 1

        return tmpDe

    def decode(self,realTerm,chromosome = None,cr = None):
        self.__decodeIn(realTerm,chromosome,cr)
        return self.__decodeOut()

    def __decodeIn(self,realTerm,chromosome = None,cr = None):
        if self.__cr is None or self.__symbolSet is None:
            try:
                if cr is None:
                    raise ValueError("Symbol set or Symobol set`s rule is not init!")
                else:
                    self.setChromosomeRule(cr)
            except ValueError as e:
                print(repr(e))
                exit(-1)

        if self.__chromosome is None:
            try:
                if chromosome is None:
                    raise ValueError("chromosome is not init!")
                else:
                    self.setChromosome(chromosome)
            except ValueError as e:
                print(repr(e))
                exit(-1)

        if cr is not None:
            self.setChromosomeRule(cr)

        if chromosome is not None:
            self.setChromosome(chromosome)

        self.__realTerminals =  realTerm

    def __decodeOut(self):
        self.__setSymbolSetTerminals()
        return self.__mainProgramDecoder()

    def __setSymbolSetTerminals(self):
        terms = self.__symbolSet.getTerminalSet()
        try:
            if len(terms) != len(self.__realTerminals):
                raise ValueError("长度不一样")
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            # for item in self.__realTerminals:
            #     terms.setNum(item)
            for i in range(0,len(terms)):
                terms[i].setValue(self.__realTerminals[i])


    def __recordMainProgramStackAndVec(self,needADF):
        readQue = MyQueue.MyQueue()
        tmpDe = ChromosomeDecoder.DecodeElement()
        lastDe = ChromosomeDecoder.DecodeElement()
        queuePtr:int = 0
        globalPointIndex = IntReference.IntReference(0)
        try:
            if len(self.__chromosome.mainProgramEx) == 0:
                raise NameError("chromosome 的 mainProgramEx 不能为空")
        except NameError as e:
            print(repr(e))
            exit(-1)
        else:
            tmpDe = self.__makeDecodeElement(self.__chromosome.mainProgramEx[queuePtr],
                                             queuePtr,
                                             globalPointIndex)

        try:
            if tmpDe.symbolType == Symbol.SymbolType.TERMINAL:
                self.__mainOcVector.append(tmpDe)
                return
            elif tmpDe.symbolType == Symbol.SymbolType.ARGUMENT:
                raise ValueError("invaild chromosome!")
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            readQue.push(tmpDe)
            queuePtr += 1

        while readQue.empty() is False:
            lastDe = readQue.front()
            readQue.pop()
            if lastDe.symbolType == Symbol.SymbolType.TERMINAL:
                self.__mainOcVector.append(lastDe)
            else:
                opNum = lastDe.opNum
                for i in range(0,opNum):
                    tmpDe = self.__makeDecodeElement(self.__chromosome.mainProgramEx[queuePtr],
                                                     queuePtr,
                                                     globalPointIndex)
                    readQue.push(tmpDe)
                    queuePtr += 1

                if lastDe.symbolType == Symbol.SymbolType.SUB_FUNCTION:
                    needADF[self.__symbolSet.getSymbolByIndex(lastDe.symbolSetIndex).getADFIndex()] = True
                self.__mainOpStack.push(lastDe)



    def __recordADFStackAndVec(self,needADF):
        for i in range(0,len(needADF)):
            if needADF[i] is False:
                self.__ADFOpStacks.append(Stack.Stack())
                self.__ADFOcVector.append([])
            else:
                readQue = MyQueue.MyQueue()
                tmpDe = ChromosomeDecoder.DecodeElement()
                lastDe = ChromosomeDecoder.DecodeElement()
                queuePtr: int = 0
                globalPointIndex = IntReference.IntReference(0)

                ADFEx = self.__chromosome.ADFEx[i]
                self.__ADFOpStacks.append(Stack.Stack())
                self.__ADFOcVector.append([])
                try:
                    if len(ADFEx) == 0:
                        raise NameError("chromosome 的第%u个 ADFEx 不能为空%d"%i)
                except NameError as e:
                    print(repr(e))
                    exit(-1)
                else:
                    tmpDe = self.__makeDecodeElement(ADFEx[queuePtr],
                                                     queuePtr,
                                                     globalPointIndex)

                try:
                    if tmpDe.symbolType == Symbol.SymbolType.ARGUMENT:
                        self.__ADFOcVector[i].append(tmpDe)
                        continue
                    elif tmpDe.symbolType == Symbol.SymbolType.TERMINAL:
                        raise ValueError("invaild chromosome!sub fuction 里面不能有 terminal")
                except ValueError as e:
                    print(repr(e))
                    exit(-1)
                else:
                    readQue.push(tmpDe)
                    queuePtr += 1

                while readQue.empty() is False:
                    lastDe = readQue.front()
                    readQue.pop()
                    if lastDe.symbolType == Symbol.SymbolType.ARGUMENT:
                        self.__ADFOcVector[i].append(lastDe)
                    else:
                        opNum = lastDe.opNum
                        for j in range(0, opNum):
                            tmpDe = self.__makeDecodeElement(ADFEx[queuePtr],
                                                             queuePtr,
                                                             globalPointIndex)
                            readQue.push(tmpDe)
                            queuePtr += 1

                        self.__ADFOpStacks[i].push(lastDe)

    def __mainProgramDecoder(self):
        outputVec = np.zeros(self.__cr.getMainPR().totalLen)
        opStack = copy.deepcopy(self.__mainOpStack)
        ocVector = self.__mainOcVector
        # tmpDe = ChromosomeDecoder.DecodeElement()
        # lastDe = ChromosomeDecoder.DecodeElement()
        args = np.zeros(self.__cr.getMainU())
        nowDecodeVal = 0.0

        for i in range(0,len(ocVector)):
            outputVec[ocVector[i].chroIndex] = self.__symbolSet.\
                                                getSymbolByIndex(ocVector[i].symbolSetIndex).getValue()

        while opStack.empty() == False:
            tmpDe = opStack.top()
            opStack.pop()
            tmpSym = self.__symbolSet.getSymbolByIndex(tmpDe.symbolSetIndex)
            # opLastIndex = np.add(tmpDe.pointIndex,np.subtract(tmpDe.opNum,1))            #不是有多个参数吗，先指到最后一个参数
                                                                                         #tmpDe.pointIndex + tmpDe.opNum - 1
            j = 0
            for i in range(tmpDe.pointIndex,tmpDe.pointIndex + tmpDe.opNum):
                args[j] = outputVec[i]
                j += 1

            if tmpDe.symbolType == Symbol.SymbolType.FUNCTION:
                nowDecodeVal = tmpSym.callFunction(args)
                if FunctionPreset.ifValDangerous(nowDecodeVal):
                    return FunctionPreset.getTheDangerousReal()
                outputVec[tmpDe.chroIndex] = nowDecodeVal
            elif tmpDe.symbolType == Symbol.SymbolType.SUB_FUNCTION:
                nowDecodeVal = self.__ADFProgramDecoder(tmpSym,args)
                if FunctionPreset.ifValDangerous(nowDecodeVal):
                    return FunctionPreset.getTheDangerousReal()
                outputVec[tmpDe.chroIndex] = nowDecodeVal

        return outputVec[0]


    def __setSymbolSetInputArgs(self,num,args):
        inputArgs = self.__symbolSet.getInputArgSet()
        try:
            if len(inputArgs) < num:
                raise ValueError("error!num is longer than the size of inputArgs set!")
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            for i in range(0,len(args)):
                inputArgs[i].setValue(args[i])


    def __ADFProgramDecoder(self,subFunctionSym : Symbol.SubFunctionSymbol, inputArgsVal):
        theADFIndex = subFunctionSym.getADFIndex()
        outputVec = np.zeros(self.__cr.getADFPR()[theADFIndex].totalLen)
        opStack = copy.deepcopy(self.__ADFOpStacks[theADFIndex])
        ocVector = self.__ADFOcVector[theADFIndex]
        args = np.zeros(self.__cr.getADFU())
        nowDecodeVal = 0.0

        self.__setSymbolSetInputArgs(subFunctionSym.getNumOfInputArgs(),inputArgsVal)

        for i in range(0,len(ocVector)):
            outputVec[ocVector[i].chroIndex] = self.__symbolSet.\
                                                getSymbolByIndex(ocVector[i].symbolSetIndex).getValue()

        # tmpDe = opStack.top()
        # if tmpDe.symbolType == Symbol.SymbolType.ARGUMENT:
        #     return outputVec[0]


        while opStack.empty() is False:
            tmpDe = opStack.top()
            opStack.pop()
            tmpSym = self.__symbolSet.getSymbolByIndex(tmpDe.symbolSetIndex)

            j = 0
            for i in range(tmpDe.pointIndex,tmpDe.pointIndex + tmpDe.opNum):
                args[j] = outputVec[i]
                j += 1

            if tmpDe.symbolType == Symbol.SymbolType.FUNCTION:
                nowDecodeVal = tmpSym.callFunction(args)
                if FunctionPreset.ifValDangerous(nowDecodeVal):
                    return FunctionPreset.getTheDangerousReal()
                outputVec[tmpDe.chroIndex] = nowDecodeVal

        return outputVec[0]





