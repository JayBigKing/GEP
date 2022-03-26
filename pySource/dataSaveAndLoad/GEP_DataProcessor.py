import csv
import pandas as pd
from gepSymbol import SymbolSetGenerator
from gepChromosome import ChromosomeRule,Chromosome
class GEP_DataProcessor:
    def __init__(self):
        self.__setReadDoneFlagChar = '*'
        self.__inTheLabelDataChar = 'l'
    def loadCSV(self,loadFileName):
        data = []
        with open(loadFileName) as csvfile:
            csvReader = csv.reader(csvfile)
            for row in csvReader:
                data.append(row)
        for item in data:
            if item[-1] is '':
                item.pop()
        return data

    def __readCSVOneLine(self,data,revObject,ifRevIsArray = True):
        if ifRevIsArray is False:
            revObject.x = int(data[0])
        else:
            for item in data:
                revObject.append(int(item))

    def loadChromosome(self,loadFileName):
        data = self.loadCSV(loadFileName)

        index = int(1)
        numOfTerminal = int(data[index][0])     #读有多少个变量维度
        presetFunctions = []
        argsLenOfADFs = []
        mainProgramH = 10
        ADFHs = []
        mainProgramEx = []
        ADFExs = []

        index += 1
        #读函数
        self.__readCSVOneLine(data[index],presetFunctions)

        index += 1
        #读ADF的参数
        self.__readCSVOneLine(data[index],argsLenOfADFs)

        index += 1
        #读main program的前端长度
        mainProgramH = int(data[index][0])

        index += 1
        #各个ADF 的前端长度
        self.__readCSVOneLine(data[index],ADFHs)

        index += 5          #跳过4个数据
        #读mainProgram
        self.__readCSVOneLine(data[index],mainProgramEx)

        index += 1
        #读各个ADF
        while data[index][0] != self.__setReadDoneFlagChar:
            ADFOneLine = []
            self.__readCSVOneLine(data[index],ADFOneLine)
            ADFExs.append(ADFOneLine)
            index += 1

        sg = SymbolSetGenerator.SymbolSetGenerator()
        symbolSet = sg.makeSymbolSet(numOfTerminal,presetFunctions,argsLenOfADFs)
        cr = ChromosomeRule.ChromosomeRule(mainProgramH,ADFHs,symbolSet)
        chromosome = Chromosome.Chromosome(cr)

        for i in range(0,len(mainProgramEx)):
            chromosome.mainProgramEx[i] = mainProgramEx[i]

        for i in range(0,len(ADFExs)):
            for j in range(0,len(ADFExs[i])):
                chromosome.ADFEx[i][j] = ADFExs[i][j]

        return chromosome,cr


    def loadDataSet(self,loadFileName,whichLabel = 0):
        data = self.loadCSV(loadFileName)
        terms = []
        labels = []
        for item in data:
            tmpTerm = []
            colIndex = 0
            while item[colIndex] != self.__inTheLabelDataChar:
                tmpTerm.append(float(item[colIndex]))
                colIndex += 1

            colIndex = colIndex + int(whichLabel) * 2 + 1

            terms.append(tmpTerm)
            labels.append(float(item[colIndex]))

        return terms,labels

# dp = GEP_DataProcessor()
# dp.loadChromosome("./SL_GEP_WORK2_DIM_1.csv")
# dp.loadDataSet("trainDataSetCSV2.csv",1)