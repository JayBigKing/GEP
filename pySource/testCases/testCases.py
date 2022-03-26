from gepSymbol import Symbol,SymbolSet,SymbolSetGenerator
from gepSymbol.functionPreset import FunctionPreset
from gepChromosome import ChromosomeRule,Chromosome,ChromosomeDecoder
from dataSaveAndLoad import GEP_DataProcessor
from gepEvaluate import GEP_Evaluate
import numpy as np
def testSymbolSetGenerator():
    numOfTerminal = 30
    presetFunctions = []
    argsLenOfADFs = []

    for i in range(0,5):
        presetFunctions.append(FunctionPreset.WhichFunction(i))

    argsLenOfADFs.append(2)
    argsLenOfADFs.append(1)
    argsLenOfADFs.append(30)


    sg = SymbolSetGenerator.SymbolSetGenerator()

    symbolSet = sg.makeSymbolSet(numOfTerminal,presetFunctions,argsLenOfADFs)

    print("-------")

def testChmosomeRule():
    numOfTerminal = 5
    presetFunctions = []
    argsLenOfADFs = []
    mainProgramH = 10
    ADFHs = []

    for i in range(0,5):
        presetFunctions.append(FunctionPreset.WhichFunction(i))

    argsLenOfADFs.append(2)
    argsLenOfADFs.append(1)
    argsLenOfADFs.append(3)

    ADFHs.append(5)
    ADFHs.append(10)
    ADFHs.append(4)

    sg = SymbolSetGenerator.SymbolSetGenerator()

    symbolSet = sg.makeSymbolSet(numOfTerminal,presetFunctions,argsLenOfADFs)

    cr = ChromosomeRule.ChromosomeRule(mainProgramH,ADFHs,symbolSet)

    print("-------")


def testChmosome():
    numOfTerminal = 3
    presetFunctions = []
    argsLenOfADFs = []
    mainProgramH = 10
    ADFHs = []

    for i in range(0,5):
        presetFunctions.append(FunctionPreset.WhichFunction(i))

    argsLenOfADFs.append(2)
    argsLenOfADFs.append(1)
    argsLenOfADFs.append(3)

    ADFHs.append(5)
    ADFHs.append(3)
    ADFHs.append(4)

    sg = SymbolSetGenerator.SymbolSetGenerator()

    symbolSet = sg.makeSymbolSet(numOfTerminal,presetFunctions,argsLenOfADFs)

    cr = ChromosomeRule.ChromosomeRule(mainProgramH,ADFHs,symbolSet)

    chromosome = Chromosome.Chromosome(cr)

    return chromosome,cr

def testChromosomeDecoder():
    chromosome,cr = testChmosome()
    args = np.array([10,25,0])
    #add 3,miuns 4,times 5,divide 6,sin 7
    #ADFa0 8,ADFb1 9,ADFc0 10,
    #times a b
    #add sin devide a a b  === sin(a) + (a/b)

    #times A0 add A1 A2 a c a a b c
    #A0 : add i0 i1
    #A1 : times i0 i0
    #A2 : mius add i2 i1 i0

    chromosome.mainProgramEx[0] = 5
    chromosome.mainProgramEx[1] = 8
    chromosome.mainProgramEx[2] = 3
    chromosome.mainProgramEx[3] = 9
    chromosome.mainProgramEx[4] = 10
    chromosome.mainProgramEx[5] = 0
    chromosome.mainProgramEx[6] = 2
    chromosome.mainProgramEx[7] = 0
    chromosome.mainProgramEx[8] = 0
    chromosome.mainProgramEx[9] = 1
    chromosome.mainProgramEx[10] = 2

    chromosome.ADFEx[0][0] = 3
    chromosome.ADFEx[0][1] = 11
    chromosome.ADFEx[0][2] = 12

    chromosome.ADFEx[1][0] = 5
    chromosome.ADFEx[1][1] = 11
    chromosome.ADFEx[1][2] = 11

    chromosome.ADFEx[2][0] = 4
    chromosome.ADFEx[2][1] = 3
    chromosome.ADFEx[2][2] = 13
    chromosome.ADFEx[2][3] = 12
    chromosome.ADFEx[2][4] = 11


    cd = ChromosomeDecoder.ChromosomeDecoder()

    cd.setChromosomeRule(cr)
    cd.setChromosome(chromosome)

    print(cd.decode(args))
    #times A0 add A1 A2 a c a a b c
    #A0 : add i0 i1
    #A1 : times i0 i0
    #A2 : mius add i2 i1 i0
    print((args[0] + args[2]) * ((args[0]*args[0])+((args[1]+args[0]) - args[2])))

def ManhanttanDis(cd,terms,labels):
    try:
        if terms is None or labels is None:
            raise ValueError("训练数据集不能不输入！")
        disVal = 0.0
        for i in range(0,len(labels)):
            predictValue = cd.decode(terms[i])
            disVal += np.abs((predictValue - labels[i]))
        return disVal
    except ValueError as e:
        print(repr(e))
        exit(-1)

def testLoadDatas1():
    dp = GEP_DataProcessor.GEP_DataProcessor()
    chromosome ,cr = dp.loadChromosome("../dataSaveAndLoad/SL_GEP_WORK_ANGLE_DIM_2.csv")
    terms,labels = dp.loadDataSet("../dataSaveAndLoad/trainDataSetCSV3.csv", 0)
    return chromosome,cr,terms,labels
def testEvalute1():
    chromosome,cr,terms,labels =  testLoadDatas1()
    evaluate = GEP_Evaluate.GEP_Evaluate(cr,chromosome,None,terms,labels)
    print(evaluate.evaluateTrainDataSetDistance())

def testAcc1():
    chromosome,cr,terms,labels =  testLoadDatas1()
    evaluate = GEP_Evaluate.GEP_Evaluate(cr,chromosome,None,terms,labels)
    print(evaluate.evaluateTrainDataSetDistance())
    print(evaluate.evaluateTrainDataSetDistance(ManhanttanDis))
    print(evaluate.evaluateTrainDataSetAcc(5))


def testLoadDatas2(whichDim = 0):
    dp = GEP_DataProcessor.GEP_DataProcessor()
    chromosome ,cr = dp.loadChromosome("../dataSaveAndLoad/SL_GEP_WORK2_DIM_%d.csv"%whichDim)
    trainTerms,trainLabels = dp.loadDataSet("../dataSaveAndLoad/trainDataSetCSV2.csv", whichDim)
    testTerms,testLabels = dp.loadDataSet("../dataSaveAndLoad/testDataSetCSV2.csv", whichDim)
    return chromosome,cr,trainTerms,trainLabels,testTerms,testLabels

def testEvaluteAndAcc():
    whichDim = 0
    chromosome, cr, trainTerms, trainLabels, testTerms, testLabels = testLoadDatas2(whichDim)
    evaluate = GEP_Evaluate.GEP_Evaluate(cr,chromosome,None,trainTerms, trainLabels,testTerms,testLabels)
    print("x direction train dataset dis : %f"%evaluate.evaluateTrainDataSetDistance())
    print("x direction train dataset acc : %f"%evaluate.evaluateTrainDataSetAcc())
    print("x direction test dataset dis : %f"%evaluate.evaluateTestDataSetDistance())
    print("x direction test dataset acc : %f"%evaluate.evaluateTestDataSetAcc())
    print("-------------------------------------")
    whichDim = 1
    chromosome, cr, trainTerms, trainLabels, testTerms, testLabels = testLoadDatas2(whichDim)
    evaluate.init(cr,chromosome,None,trainTerms, trainLabels,testTerms,testLabels)
    print("y direction train dataset dis : %f"%evaluate.evaluateTrainDataSetDistance())
    print("y direction train dataset acc : %f"%evaluate.evaluateTrainDataSetAcc())
    print("y direction test dataset dis : %f"%evaluate.evaluateTestDataSetDistance())
    print("y direction test dataset acc : %f"%evaluate.evaluateTestDataSetAcc())


def testPredictTrajectory():
    dp = GEP_DataProcessor.GEP_DataProcessor()
    chromosomeX ,cr = dp.loadChromosome("../dataSaveAndLoad/SL_GEP_WORK2_DIM_0.csv")
    chromosomeY, _ = dp.loadChromosome("../dataSaveAndLoad/SL_GEP_WORK2_DIM_1.csv")
    evaluate = GEP_Evaluate.GEP_Evaluate(cr)
    res = evaluate.generateTrajectory(chromosomeX,chromosomeY,7.59518,1.44582,6,3.52305,5.6807,0.978853,2.25317)
    print(res)

# testSymbolSetGenerator()
# testChmosomeRule()
# testChmosome()
# testChromosomeDecoder()
# testEvalute1()
testAcc1()
# testEvaluteAndAcc()
# testPredictTrajectory()