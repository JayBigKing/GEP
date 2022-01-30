from gepSymbol import Symbol,SymbolSet
import numpy as np
class ProgramRule:
    def __init__(self):
        self.h = 0
        self.u = 0
        self.l = 0
        self.totalLen = 0

def getExpressionL(h,u):
    return h  * (u - 1) + 1

class ChromosomeRule:
    def __init__(self,mainProgramH = None, ADFH = None, symbolSet = None):
        self.__mainPR = ProgramRule()
        self.__ADFPR = []
        self.__mainU = 0
        self.__ADFU = 0
        self.__symbolSet = None
        if mainProgramH is None or ADFH is None or symbolSet is None:
            pass
        else:
            self.init(mainProgramH,ADFH,symbolSet)

    def getMainPR(self):
        return self.__mainPR
    def getADFPR(self):
        return self.__ADFPR
    def getMainU(self):
        return self.__mainU
    def getADFU(self):
        return self.__ADFU
    def getSymbolSet(self):
        return self.__symbolSet
    def init(self,mainProgramH , ADFH , symbolSet ):
        self.__mainU = 0
        self.__ADFU = 0
        self.__symbolSet = symbolSet

        fs = symbolSet.getFunctionSet()         #fs namely functionSet
        sfs = symbolSet.getSubFunctionSet()     #sfs namely subFunctionSet

        #first find the u
        #firstly the u of ADFs would be fond out,next the u of main would be found out
        for i in range(0,len(fs)):
            if fs[i].getNumOfInputArgs() > self.__mainU:
                self.__mainU = fs[i].getNumOfInputArgs()

        self.__ADFU = self.__mainU

        for i in range(0,len(sfs)):
            if sfs[i].getNumOfInputArgs() > self.__mainU:
                self.__mainU = sfs[i].getNumOfInputArgs()


        #second initial the mainProgram rules
        self.__mainPR.h = mainProgramH
        self.__mainPR.u = self.__mainU
        self.__mainPR.l = getExpressionL(self.__mainPR.h,self.__mainPR.u)
        self.__mainPR.totalLen = self.__mainPR.h + self.__mainPR.l

        #finally initial the ADF rules
        for i in range(0,len(ADFH)):
            tmpPR = ProgramRule()
            tmpPR.h = ADFH[i]
            tmpPR.u = self.__ADFU
            tmpPR.l = getExpressionL(tmpPR.h,tmpPR.u)
            tmpPR.totalLen = tmpPR.h + tmpPR.l
            self.__ADFPR.append(tmpPR)

