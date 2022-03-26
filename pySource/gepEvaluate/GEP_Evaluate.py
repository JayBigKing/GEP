from gepSymbol import SymbolSet
from gepChromosome import ChromosomeRule,Chromosome,ChromosomeDecoder
import numpy as np
class GEP_Evaluate:
    def __init__(self,cr = None,chromosome = None,sl_gep = None,
                 trainDatasetRealTerms = None,trainDatasetRealLabels = None,
                 testDatasetRealTerms = None,testDatasetRealLabels = None):
        self.init(cr,chromosome,sl_gep,trainDatasetRealTerms,trainDatasetRealLabels,
                  testDatasetRealTerms,testDatasetRealLabels)

    def init(self,cr = None,chromosome = None,sl_gep = None,
                 trainDatasetRealTerms = None,trainDatasetRealLabels = None,
                 testDatasetRealTerms = None,testDatasetRealLabels = None):
        self.__cr : ChromosomeRule.ChromosomeRule = cr
        self.__chrmosome : Chromosome.Chromosome = chromosome
        self.__sl_gep = sl_gep
        self.__trainDatasetRealTerms = trainDatasetRealTerms
        self.__trainDatasetRealLabels = trainDatasetRealLabels
        self.__testDatasetRealTerms = testDatasetRealTerms
        self.__testDatasetRealLabels = testDatasetRealLabels

    def setCR(self,cr):
        self.__cr = cr

    def setChromosome(self,chromosome):
        self.__chrmosome = chromosome

    def setSL_GEP(self,sl_gep):
        self.__sl_gep = sl_gep

    def setTrainDataset(self,trainDatasetRealTerms = None,trainDatasetRealLabels = None):
        self.__trainDatasetRealTerms = trainDatasetRealTerms
        self.__trainDatasetRealLabels = trainDatasetRealLabels

    def setTestDataset(self,testDatasetRealTerms = None,testDatasetRealLabels = None):
        self.__testDatasetRealTerms = testDatasetRealTerms
        self.__testDatasetRealLabels = testDatasetRealLabels

    def __makeChromosomeDecoder(self,chromosome = None):
        try:
            if self.__cr is None or (self.__chrmosome is None and chromosome is None):
                raise ValueError("decode的cr或chromosome不能为None")
            cd = ChromosomeDecoder.ChromosomeDecoder()
            cd.setChromosomeRule(self.__cr)
            if chromosome is None:
                cd.setChromosome(self.__chrmosome)
            else:
                cd.setChromosome(chromosome)
            return cd
        except ValueError as e:
            print(repr(e))
            exit(-1)

    def evaluateTrainDataSetDistance(self,distanceHandler = None):
        try:
            if self.__trainDatasetRealTerms is None or self.__trainDatasetRealLabels is None:
                raise ValueError("训练数据集不能不输入！")
            cd = self.__makeChromosomeDecoder()
            if distanceHandler is None:
                disVal = 0.0
                for i in range(0,len(self.__trainDatasetRealLabels)):
                    predictValue = cd.decode(self.__trainDatasetRealTerms[i])
                    disVal += np.power((predictValue - self.__trainDatasetRealLabels[i]),2)
                return np.sqrt(disVal)
            else:
                return distanceHandler(cd,self.__trainDatasetRealTerms,self.__trainDatasetRealLabels)
        except ValueError as e:
            print(repr(e))
            exit(-1)

    def evaluateTrainDataSetAcc(self,correctRate = 0.1):
        try:
            if self.__trainDatasetRealTerms is None or self.__trainDatasetRealLabels is None:
                raise ValueError("训练数据集不能不输入！")
            cd = self.__makeChromosomeDecoder()
            datasetNum = len(self.__trainDatasetRealLabels)
            correctCount = 0
            for i in range(0, datasetNum):
                predictValue = cd.decode(self.__trainDatasetRealTerms[i])
                tmpDis = np.abs(predictValue - self.__trainDatasetRealLabels[i])
                if np.abs(predictValue - self.__trainDatasetRealLabels[i]) <= correctRate:
                    correctCount += 1

            return float(correctCount) / float(datasetNum)
        except ValueError as e:
            print(repr(e))
            exit(-1)

    def evaluateTestDataSetDistance(self,distanceHandler = None):
        try:
            if self.__testDatasetRealTerms is None or self.__testDatasetRealLabels is None:
                raise ValueError("测试数据集不能不输入！")
            cd = self.__makeChromosomeDecoder()
            if distanceHandler is None:
                disVal = 0.0
                for i in range(0,len(self.__testDatasetRealLabels)):
                    predictValue = cd.decode(self.__testDatasetRealTerms[i])
                    disVal += np.power((predictValue - self.__testDatasetRealLabels[i]),2)
                return np.sqrt(disVal)
            else:
                return distanceHandler(cd,self.__testDatasetRealTerms,self.__testDatasetRealLabels)
        except ValueError as e:
            print(repr(e))
            exit(-1)
    def evaluateTestDataSetAcc(self,correctRate = 0.1):
        try:
            if self.__testDatasetRealTerms is None or self.__testDatasetRealLabels is None:
                raise ValueError("测试数据集不能不输入！")
            cd = self.__makeChromosomeDecoder()
            datasetNum = len(self.__testDatasetRealLabels)
            correctCount = 0
            for i in range(0, datasetNum):
                predictValue = cd.decode(self.__testDatasetRealTerms[i])
                if np.abs(predictValue - self.__testDatasetRealLabels[i]) <= correctRate:
                    correctCount += 1

            return float(correctCount) / float(datasetNum)
        except ValueError as e:
            print(repr(e))
            exit(-1)


    def __packDecodeData(self,nowX,nowY,nowSpeed,nowDirection,desX,desY,
                            leftSectorDisFromPerson = 6,centerSectorDisFromPerson = 6,rightSectorDisFromPerson = 6,
                           leftSectorDisFromOb = 6,centerSectorDisFromOb = 6,rightSectorDisFromOb = 6):
        decodeData = np.zeros(12)
        decodeData[0] = nowX
        decodeData[1] = nowY
        decodeData[2] = nowSpeed
        decodeData[3] = nowDirection
        decodeData[4] = desX
        decodeData[5] = desY
        decodeData[6] = leftSectorDisFromPerson
        decodeData[7] = centerSectorDisFromPerson
        decodeData[8] = rightSectorDisFromPerson
        decodeData[9] = leftSectorDisFromOb
        decodeData[10] = centerSectorDisFromOb
        decodeData[11] = rightSectorDisFromOb

        return decodeData

    def __getSpeed(self,nowX,nowY,lastX,lastY):
        h = (nowY - lastY)  # 高
        bottom = (nowX - lastX)  # 底边
        hypo = np.sqrt(h * h + bottom * bottom)  # 斜边
        return hypo

    def __getAngle(self,nowX,nowY,lastX,lastY):
        if nowX == lastX:
            return np.radians(90)
        else:
            return np.arctan2((nowY-lastY),(nowX-lastY))
    def __getSpeedAndAngle(self,nowX,nowY,lastX,lastY):
        return self.__getSpeed(nowX,nowY,lastX,lastY),self.__getAngle(nowX,nowY,lastX,lastY)


    def generateTrajectory(self,chromosome1,chromosome2,desX,desY,howManytrajectroyTimes = 10,
                           originX = 0,originY = 0,originSpeed = 0,orginDirection = 0,
                           leftSectorDisFromPerson = 6,centerSectorDisFromPerson = 6,rightSectorDisFromPerson = 6,
                           leftSectorDisFromOb = 6,centerSectorDisFromOb = 6,rightSectorDisFromOb = 6):
        '''
        0-1 当前位置
        2   当前速度绝对值
        3   当前速度方向
        4-5 目的坐标
        6   离左边扇叶最近的人的距离
        7   离中间扇叶最近的人的距离
        8   离右边扇叶最近的人的距离
        9   离左边扇叶最近的障碍物的距离
        10  离中间扇叶最近的障碍物的距离
        11  离右边扇叶最近的障碍物的距离
        :param chromosome1:
        :param chromosome2:
        :return:
        '''
        xPredictor = self.__makeChromosomeDecoder(chromosome1)
        yPredictor = self.__makeChromosomeDecoder(chromosome2)
        nowX = originX
        nowY = originY
        nowSpeed = originSpeed
        nowDirection = orginDirection

        lastX = nowX
        lastY = nowY

        res = np.zeros((howManytrajectroyTimes + 1,2))
        res[0] = [nowX,nowY]

        k_for_y = 6
        for i in range(0,howManytrajectroyTimes):
            decodeData = self.__packDecodeData(nowX,nowY,nowSpeed,nowDirection,desX,desY,
                                leftSectorDisFromPerson,centerSectorDisFromPerson,rightSectorDisFromPerson,
                                leftSectorDisFromOb,centerSectorDisFromOb,rightSectorDisFromOb)
            nowX -= (xPredictor.decode(decodeData) - nowX)
            nowY -= k_for_y * (yPredictor.decode(decodeData) - nowY)
            nowSpeed,nowDirection = self.__getSpeedAndAngle(nowX,nowY,lastX,lastY)
            lastX = nowX
            lastY = nowY

            res[i+1] = [nowX, nowY]


        return res


