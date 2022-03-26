import numpy as np
class TestFunctionDataSetGenerator:
    def __init__(self):
        pass

    def __fitFunctionVec(self,args,inputFunction = None):
        if inputFunction is not None:
            return inputFunction(args)
        else:
            return args[0] * args[0]


    def fitFunctionOutVec(self,terminalDim,dataSetNum,inputFunction = None):
        realTermVec = np.zeros((dataSetNum,terminalDim))
        ansVec = np.zeros(dataSetNum)
        k = 1.0
        for i in range(0,dataSetNum):
            for j in range(0,terminalDim):
                realTermVec[i,j] = k
                k += 1.0

        for i in range(0,dataSetNum):
            ansVec[i] = self.__fitFunctionVec(realTermVec[i],inputFunction)

        return realTermVec,ansVec