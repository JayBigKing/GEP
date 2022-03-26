from enum import Enum
from gepSymbol.functionPreset import FunctionPreset
class SymbolType(Enum):
    FUNCTION = 1,
    SUB_FUNCTION = 2
    TERMINAL = 3
    ARGUMENT = 4

class FunctionType(Enum):
    PRESET = 1,
    USER = 2

class Symbol:
    def __init__(self,symbolType0,symbolName0,num0 = 0):
        self.__symbolType = symbolType0
        self.__symbolName = symbolName0
        self.__num = num0
    def getSymbolType(self):
        return self.__symbolType
    def getSymbolName(self):
        return self.__symbolName
    def getNum(self):
        return self.__num
    def setNum(self,x):
        self.__num = x

class FunctionSymbol(Symbol):
    def __init__(self,symbolName,num,numOfInputArgs,functionHandler = None,wf = None):
        super().__init__(SymbolType.FUNCTION,symbolName,num)
        self.__numOfInputArgs = numOfInputArgs

        self.__functionHandler = functionHandler
        self.__whichFunction = wf

        try:
            if (self.__functionHandler is not None and self.__whichFunction is not None)\
                    or (self.__functionHandler is  None and self.__whichFunction is  None):
                raise ValueError("functionHandler and whichFunction can only exist one")
        except ValueError as e:
            print(repr(e))
            exit(-1)

    def getNumOfInputArgs(self):
        return self.__numOfInputArgs

    def getFunctionHandler(self):
        return self.__functionHandler

    def getWhichFunction(self):
        return self.__whichFunction

    def callFunction(self,args):
        if self.__whichFunction is None:
            return self.__functionHandler(args)
        else:
            return FunctionPreset.functionPresetHandler(args,self.__whichFunction)

class SubFunctionSymbol(Symbol):
    def __init__(self,symbolName,num,numOfInputArgs, ADFIndex):
        super().__init__(SymbolType.SUB_FUNCTION,symbolName,num)
        self.__numOfInputArgs = numOfInputArgs
        self.__ADFIndex = ADFIndex

    def getNumOfInputArgs(self):
        return self.__numOfInputArgs

    def getADFIndex(self):
        return self.__ADFIndex


class TerminalSymbol(Symbol):
    def __init__(self,symbolName,num,val,isValConstant = False):
        super().__init__(SymbolType.TERMINAL,symbolName,num)
        self.__value = val
        self.__isValConstant = isValConstant
    def setValue(self,x):
        self.__value = x
    def getValue(self):
        return self.__value
    def getIfValConstant(self):
        return self.__isValConstant

class InputArgSymbol(Symbol):
    def __init__(self,symbolName,num):
        super().__init__(SymbolType.ARGUMENT,symbolName,num)
        self.__value = 0

    def setValue(self, x):
        self.__value = x

    def getValue(self):
        return self.__value