from gepSymbol import Symbol,SymbolSet
from gepSymbol.functionPreset import FunctionPreset
class SymbolSetGenerator:
    def __init__(self):
        self.__startAlpha = ord('a')
        self.__endAlpha = ord('z')
        self.__constantFirstAlpha = 'C'
        self.__ADFFirstAlpha = 'ADF'
        self.__InputArgFirstAlpha = 'I'

    def makeSymbolSet(self,numOfTerminals, numOfConstant,
		presetFunctions, argsLenOfADFs,constants = None):
        symbolSet = SymbolSet.SymbolSet()
        self.__pushTerminal(symbolSet,numOfTerminals)
        self.__pushConstants(symbolSet,constants,numOfConstant)
        self.__pushPresetFunctions(symbolSet,presetFunctions)
        self.__pushADFsAndInputArgs(symbolSet,argsLenOfADFs)

    def __pushTerminal(self,symbolSet,numOfTerminals):
        digitPtr = 0
        alphaPtr = 0

        for i in range(0,numOfTerminals):
            symbolSet.pushTerminal(chr(alphaPtr + self.__startAlpha)+ str(digitPtr),0)
            alphaPtr += 1
            if(alphaPtr > self.__endAlpha):
                digitPtr = alphaPtr = 0


    def __pushConstants(self,symbolSet,constants,numOfConstant):
        digitPtr = 0
        alphaPtr = 0
        if constants is None:
            for i in range(0,numOfConstant):
                symbolSet.pushConstant(self.__constantFirstAlpha+chr(alphaPtr + self.__startAlpha) +str(digitPtr))
                alphaPtr += 1
                if (alphaPtr > self.__endAlpha):
                    digitPtr = alphaPtr = 0
        else:
            for i in range(0,numOfConstant):
                symbolSet.pushConstant(self.__constantFirstAlpha+chr(alphaPtr + self.__startAlpha) +str(digitPtr),constants[i])
                alphaPtr += 1
                if (alphaPtr > self.__endAlpha):
                    digitPtr = alphaPtr = 0

    def __pushPresetFunctions(self,symbolSet,presetFunctions):
        funcTypeSet = set()
        for i in range(0,len(presetFunctions)):
            if presetFunctions[i] in funcTypeSet is True:
                continue
            else:
                symbolSet.pushFunctionSymbol(FunctionPreset.functionArgMap[presetFunctions[i]][1],
                                             FunctionPreset.functionArgMap[presetFunctions[i]][0],
                                             wf = presetFunctions[i])




    def __pushADFsAndInputArgs(self,symbolSet,argsLenOfADFs):
        maxLen = 0
        ADFIndexCount = 0
        digitPtr1 = digitPtr2 = 0
        alphaPtr1 = alphaPtr2 = 0
        for i in range(0,len(argsLenOfADFs)):
            if argsLenOfADFs[i] > maxLen:
                maxLen = argsLenOfADFs[i]
            symbolSet.pushSubFunctionSymbol(self.__ADFFirstAlpha + chr(alphaPtr1+self.__startAlpha) + str(digitPtr1),
                                            argsLenOfADFs[i],ADFIndexCount)
            ADFIndexCount += 1

            alphaPtr1 += 1
            if (alphaPtr1 > self.__endAlpha):
                digitPtr1 = alphaPtr1 = 0

        for i in range(0,len(maxLen)):
            symbolSet.pushInputArgSymbol(self.__InputArgFirstAlpha + chr(alphaPtr2 + self.__startAlpha) + str(digitPtr2))

            alphaPtr2 += 1
            if (alphaPtr2 > self.__endAlpha):
                digitPtr2 = alphaPtr2 = 0

