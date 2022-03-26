from gepSymbol import Symbol
import copy
class SymbolMapInfo:
    def __init__(self):
        self.symbolType = Symbol.SymbolType
        self.index = 0
        self.isConstant = False
    def setIt(self,st,index0,isConstant = False):
        self.symbolType = st
        self.index = index0
        self.isConstant = isConstant


class SymbolSet:
    def __init__(self):
        self.__symbolNum = 0
        self.__functionSet = []
        self.__subFunctionSet = []
        self.__terminalSet = []
        self.__constantSet = []
        self.__inputArgsSet = []
        self.__symbolMap = dict()
        self.__symbolVec = []

    def __appendSymbolVecAndMap(self,symbolType,symbolName,isConstant = False):
        smi = SymbolMapInfo()
        try:
            if symbolType == Symbol.SymbolType.FUNCTION:
                smi.setIt(symbolType,(len(self.__functionSet) - 1))
            elif symbolType == Symbol.SymbolType.SUB_FUNCTION:
                smi.setIt(symbolType,(len(self.__subFunctionSet) - 1))
            elif symbolType == Symbol.SymbolType.TERMINAL:
                smi.setIt(symbolType,(len(self.__terminalSet) - 1),isConstant)
            elif symbolType == Symbol.SymbolType.ARGUMENT:
                smi.setIt(symbolType,(len(self.__inputArgsSet) - 1))
            else:
                raise ValueError("error symbolType!")
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            self.__symbolMap[symbolName] = smi
            self.__symbolVec.append(smi)
            self.__symbolNum += 1


    def pushFunctionSymbol(self,symbolName,numOfInputArgs,functionHandler = None,wf = None):
        try:
            if (functionHandler is None and wf is None) \
                or (functionHandler is not None and wf is not None):
                raise ValueError("functionHandler and whichFunction can only exist one")
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            self.__functionSet.append(Symbol.FunctionSymbol(symbolName,self.__symbolNum,numOfInputArgs,functionHandler,wf))
            self.__appendSymbolVecAndMap(Symbol.SymbolType.FUNCTION,symbolName)


    def pushFunctionSymbolObject(self,functionSymbol):
        functionSymbol.setNum(self.__symbolNum)
        self.__functionSet.append(copy.deepcopy(functionSymbol))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.FUNCTION, functionSymbol.getSymbolName())

    def pushSubFunctionSymbol(self,symbolName,numOfInputArgs, ADFIndex):
        self.__subFunctionSet.append(Symbol.SubFunctionSymbol(symbolName,self.__symbolNum,numOfInputArgs,ADFIndex))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.SUB_FUNCTION,symbolName)

    def pushSubFunctionSymbolObject(self,subFunctionSymbol):
        subFunctionSymbol.setNum(self.__symbolNum)
        self.__subFunctionSet.append(copy.deepcopy(subFunctionSymbol))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.SUB_FUNCTION,subFunctionSymbol.getSymbolName())


    def pushTerminalSymbol(self,symbolName,value):
        self.__terminalSet.append(Symbol.TerminalSymbol(symbolName,self.__symbolNum,value))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.TERMINAL,symbolName)

    def pushTerminalSymbolObject(self,terminalSymbol):
        terminalSymbol.setNum(self.__symbolNum)
        self.__terminalSet.append(copy.deepcopy(terminalSymbol))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.TERMINAL,terminalSymbol.getSymbolName())

    def pushConstantSymbol(self,symbolName,value = 1):
        self.__constantSet.append(Symbol.TerminalSymbol(symbolName,self.__symbolNum,value,True))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.TERMINAL, symbolName,True)

    def pushConstantSymbolObject(self,terminalSymbol):
        terminalSymbol.setNum(self.__symbolNum)
        self.__terminalSet.append(copy.deepcopy(terminalSymbol))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.TERMINAL,terminalSymbol.getSymbolName(),True)

    def pushInputArgSymbol(self,symbolName):
        self.__inputArgsSet.append(Symbol.InputArgSymbol(symbolName,self.__symbolNum))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.ARGUMENT,symbolName)

    def pushInputArgSymbolObject(self,inputArgSymbol):
        inputArgSymbol.setNum(self.__symbolNum)
        self.__inputArgsSet.append(copy.deepcopy(inputArgSymbol))
        self.__appendSymbolVecAndMap(Symbol.SymbolType.ARGUMENT,inputArgSymbol.getSymbolName())

    def getFunctionSet(self):
        return self.__functionSet

    def getSubFunctionSet(self):
        return self.__subFunctionSet

    def getTerminalSet(self):
        return self.__terminalSet

    def getConstantSet(self):
        return self.__constantSet

    def getInputArgSet(self):
        return self.__inputArgsSet

    def getSymbolMap(self):
        return self.__symbolMap

    def getSymbolByIndex(self,index):
        return self.__getSymbolHelp(self.__symbolVec[index])

    def getSymbolByStr(self,str):
        return self.__getSymbolHelp(self.__symbolMap[str])

    def __getSymbolHelp(self,symbolMapInfo):
        try:
            if symbolMapInfo.symbolType == Symbol.SymbolType.FUNCTION:
                return self.__functionSet[symbolMapInfo.index]
            elif symbolMapInfo.symbolType == Symbol.SymbolType.SUB_FUNCTION:
                return self.__subFunctionSet[symbolMapInfo.index]
            elif symbolMapInfo.symbolType == Symbol.SymbolType.TERMINAL:
                if symbolMapInfo.isConstant is False:
                    return self.__terminalSet[symbolMapInfo.index]
                else:
                    return self.__constantSet[symbolMapInfo.index]
            elif symbolMapInfo.symbolType == Symbol.SymbolType.ARGUMENT:
                return self.__inputArgsSet[symbolMapInfo.index]
            else:
                raise ValueError("error:no this symbolType")
        except ValueError as e:
            print(repr(e))
            exit(-1)


