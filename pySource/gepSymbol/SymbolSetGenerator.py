from gepSymbol import Symbol,SymbolSet
from gepSymbol.functionPreset import FunctionPreset
class SymbolSetGenerator:
    def __init__(self):
        self.__startAlpha = ord('a')
        self.__endAlpha = ord('z')
        self.__constantFirstAlpha = 'C'
        self.__ADFFirstAlpha = 'ADF'
        self.__InputArgFirstAlpha = 'I'

    def makeSymbolSet(self,numOfTerminals,
		presetFunctions, argsLenOfADFs,numOfConstant = 0,constants = None):
        """自动化地产生SymbolSet
        :param numOfTerminals:变量数
        :param presetFunctions:预设有函数，只需要传入编号就好了
        :param argsLenOfADFs:包含了两个东西，它的长度说明了有多少个ADF，他的值代表每一个ADF的参数
        :param numOfConstant:常量数，没有的话就填0，或者不填
        :param constants:预设了值的常量
        :return:
        """
        try:
            if numOfConstant < 0:
                raise ValueError("num of terminals can be less than 0!")
            if numOfConstant < 0:
                numOfConstant = 0
        except ValueError as e:
            print(repr(e))
            exit(-1)
        else:
            symbolSet = SymbolSet.SymbolSet()
            self.__pushTerminal(symbolSet,numOfTerminals)
            self.__pushConstants(symbolSet,constants,numOfConstant)
            self.__pushPresetFunctions(symbolSet,presetFunctions)
            self.__pushADFsAndInputArgs(symbolSet,argsLenOfADFs)
            return symbolSet

    def __pushTerminal(self,symbolSet : SymbolSet.SymbolSet,numOfTerminals):
        digitPtr = 0
        alphaPtr = self.__startAlpha

        for i in range(0,numOfTerminals):
            symbolSet.pushTerminalSymbol(chr(alphaPtr)+ str(digitPtr),0)
            alphaPtr += 1
            if(alphaPtr > self.__endAlpha):
                alphaPtr = self.__startAlpha
                digitPtr += 1


    def __pushConstants(self,symbolSet: SymbolSet.SymbolSet,constants,numOfConstant = None):
        digitPtr = 0
        alphaPtr = self.__startAlpha
        if constants is None:
            if numOfConstant is not None:
                for i in range(0,numOfConstant):
                    symbolSet.pushConstantSymbol(self.__constantFirstAlpha+chr(alphaPtr) +str(digitPtr))
                    alphaPtr += 1
                    if (alphaPtr > self.__endAlpha):
                        alphaPtr = self.__startAlpha
                        digitPtr += 1
        else:
            for i in range(0,numOfConstant):
                symbolSet.pushConstantSymbol(self.__constantFirstAlpha+chr(alphaPtr) +str(digitPtr),constants[i])
                alphaPtr += 1
                if (alphaPtr > self.__endAlpha):
                    alphaPtr = self.__startAlpha
                    digitPtr += 1

    def __pushPresetFunctions(self,symbolSet : SymbolSet.SymbolSet,presetFunctions):
        funcTypeSet = set()
        for i in range(0,len(presetFunctions)):
            if presetFunctions[i] in funcTypeSet is True:
                continue
            else:
                try:
                    if isinstance(presetFunctions[i],FunctionPreset.WhichFunction):
                        symbolSet.pushFunctionSymbol(FunctionPreset.functionArgMap[presetFunctions[i]][1],
                                                     FunctionPreset.functionArgMap[presetFunctions[i]][0],
                                                     wf = presetFunctions[i])
                    elif isinstance(presetFunctions[i],int):
                        presetFunctionsVal = FunctionPreset.WhichFunction(presetFunctions[i])
                        symbolSet.pushFunctionSymbol(FunctionPreset.functionArgMap[presetFunctionsVal][1],
                                                     FunctionPreset.functionArgMap[presetFunctionsVal][0],
                                                     wf=presetFunctionsVal)
                    else:
                        raise ValueError("没有这样的 wf")
                except ValueError as e:
                    print(repr(e))
                    exit(-1)





    def __pushADFsAndInputArgs(self,symbolSet : SymbolSet.SymbolSet,argsLenOfADFs):
        maxLen = 0
        ADFIndexCount = 0
        digitPtr1 = digitPtr2 = 0
        alphaPtr1 = alphaPtr2 = self.__startAlpha
        for i in range(0,len(argsLenOfADFs)):
            if argsLenOfADFs[i] > maxLen:
                maxLen = argsLenOfADFs[i]
            symbolSet.pushSubFunctionSymbol(self.__ADFFirstAlpha + chr(alphaPtr1) + str(digitPtr1),
                                            argsLenOfADFs[i],ADFIndexCount)
            ADFIndexCount += 1

            alphaPtr1 += 1
            if (alphaPtr1 > self.__endAlpha):
                alphaPtr1 = self.__startAlpha
                digitPtr1 += 1

        for i in range(0,maxLen):
            symbolSet.pushInputArgSymbol(self.__InputArgFirstAlpha + chr(alphaPtr2) + str(digitPtr2))

            alphaPtr2 += 1
            if (alphaPtr2 > self.__endAlpha):
                alphaPtr2 = self.__startAlpha
                digitPtr2 += 1

