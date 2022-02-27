//
// Created by JAY on 2022/2/9.
//

#include "SL_GEP.h"
#include "GA_HelpFunc.h"
#include <limits>

SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
               WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
               bool ifUseSuspendNum , double similarValue ) :
        GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
            argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue),totalWeight(0.0),chromosomeWeight(chroNum) {
//    cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
//    cdPtr->setChromosomeRule(cr);
//
//    UChromosome.init(cr);
//
//    initRandGenerator();
//    getTotalExpressionLen();
    constructorInitHelp();
}

SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
               WhichFunction* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
               bool ifUseSuspendNum , double similarValue ) :
        GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
            argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
//    cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
//    cdPtr->setChromosomeRule(cr);
//    UChromosome.init(cr);
//
//    initRandGenerator();
//    getTotalExpressionLen();
    constructorInitHelp();
}



SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals, double *constants, int numOfConstants,
               int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
               bool ifUseSuspendNum , double similarValue ) :
        GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, constants, numOfConstants, presetFunctions, numOfPresetFunctions,
            argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
//    cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
//    cdPtr->setChromosomeRule(cr);
//    UChromosome.init(cr);
//
//    initRandGenerator();
//    getTotalExpressionLen();
    constructorInitHelp();
}


SL_GEP::SL_GEP(int chroNum, double *realTermVec, double *ansVec, int TAPairNum, int needEpoch, int numOfTerminals,
               int* presetFunctions, int numOfPresetFunctions, int *argsLenOfADFs, int numOfADFs, int mainPH, int* inputADFHs,
               bool ifUseSuspendNum , double similarValue) :
        GEP(chroNum, realTermVec, ansVec, TAPairNum, needEpoch, numOfTerminals, presetFunctions, numOfPresetFunctions,
            argsLenOfADFs, numOfADFs, mainPH, inputADFHs, ifUseSuspendNum, similarValue), totalWeight(0.0), chromosomeWeight(chroNum) {
    constructorInitHelp();
}

SL_GEP::SL_GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
       const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
       const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
       const bool &ifUseSuspendNum ,const double &similarValue
):GEP(chroNum,realTermVec,ansVec,needEpoch,numOfTerminals,constants,presetFunctions,
      argsLenOfADFs,mainPH,inputADFHs,ifUseSuspendNum,similarValue), totalWeight(0.0), chromosomeWeight(chroNum)
{
    constructorInitHelp();
}

SL_GEP::SL_GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
       const int &needEpoch, const int &numOfTerminals,
       const vector<WhichFunction>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
       const bool &ifUseSuspendNum ,const double &similarValue
):GEP(chroNum,realTermVec,ansVec,needEpoch,numOfTerminals,presetFunctions,
      argsLenOfADFs,mainPH,inputADFHs,ifUseSuspendNum,similarValue), totalWeight(0.0), chromosomeWeight(chroNum)
{
    constructorInitHelp();
}

SL_GEP::SL_GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
       const int &needEpoch, const int &numOfTerminals, const vector<double>&constants,
       const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
       const bool &ifUseSuspendNum ,const double &similarValue
):GEP(chroNum,realTermVec,ansVec,needEpoch,numOfTerminals,constants,presetFunctions,
      argsLenOfADFs,mainPH,inputADFHs,ifUseSuspendNum,similarValue), totalWeight(0.0), chromosomeWeight(chroNum)
{
    constructorInitHelp();
}

SL_GEP::SL_GEP(const int &chroNum,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,
       const int &needEpoch, const int &numOfTerminals,
       const vector<int>&presetFunctions, const vector<int>&argsLenOfADFs,const int &mainPH, const vector<int>&inputADFHs,
       const bool &ifUseSuspendNum ,const double &similarValue
):GEP(chroNum,realTermVec,ansVec,needEpoch,numOfTerminals,presetFunctions,
      argsLenOfADFs,mainPH,inputADFHs,ifUseSuspendNum,similarValue), totalWeight(0.0), chromosomeWeight(chroNum)
{
    constructorInitHelp();
}
/**
  * @brief  类的初始化相关，帮助构造函数的一部分初始化内容
  *
  * @param  threadNum0:多少个线程
  *
  * @note   构造函数会调用，后面单独的init()函数也会调用
  *
  * @retval None
  */
void SL_GEP::constructorInitHelp() {
    cdPtr = boost::make_shared<SL_ChromosomeDecoder>();
    cdPtr->setChromosomeRule(cr);
    UChromosome.init(cr);

    initRandGenerator();
    getTotalExpressionLen();
}

void SL_GEP::initRandGenerator() {
    uniform_int_distribution<uint64_t>initDistribution(0, numeric_limits<uint64_t>::max());
    FGenerator.seed(initDistribution(generator));
    BetaGenerator.seed(initDistribution(generator));
    SelectGenerator.seed(initDistribution(generator));
    YGenerator.seed(initDistribution(generator));
    GambleGenerator.seed(initDistribution(generator));
    CRGenerator.seed(initDistribution(generator));
    KGenerator.seed(initDistribution(generator));
    ACSGenerator.seed(initDistribution(generator));

}

double SL_GEP::test1() {
    chromosomes[0].mainProgramEx[0] = 4;
    chromosomes[0].mainProgramEx[1] = 2;
    chromosomes[0].mainProgramEx[2] = 3;
    chromosomes[0].mainProgramEx[3] = 0;
    chromosomes[0].mainProgramEx[4] = 0;
    chromosomes[0].mainProgramEx[5] = 1;
    chromosomes[0].mainProgramEx[6] = 0;

    chromosomes[0].ADFEx[0][0] = 2;
    chromosomes[0].ADFEx[0][1] = 5;
    chromosomes[0].ADFEx[0][2] = 6;

    return cdPtr.get()->decode(realTermSet[0], chromosomes[0], cr);
}

void SL_GEP::reInit() {
    return;
    generator.seed(time(NULL));
    initRandGenerator();
    minDistance = numeric_limits<double>::max();
    epoch = 0;
    resetSymbolCount();
}
/**
  * @brief  输出一些GEP的参数信息
  *
  * @param
  *
  * @note   父类已经输出了一些信息，子类做一些补充
  *
  * @retval None
  */
void SL_GEP::printOutArgumentDetail() {
    GEP::printOutArgumentDetail();
    try{
        switch (whichRenewSymbolCountWay) {
            case ANY_ONE_EQUAL_WAY:
                printf("any one equal way\r\n");
                break;
            case LOW_ONE_FIRST:
                printf("low one first way\r\n");
                break;
            case BEST_ONE_ONLY:
                printf("best one only way\r\n");
                break;
            case ANY_ONE_COUNT_BY_WEIGHT:
                printf("any one count by weight way\r\n");
                break;
            default:
                throw "error : unknown way!";
        }
    }catch(const char * &e){
        printf("%s\r\n",e);
        exit(-1);
    }
}
/**
  * @brief  用ANY_ONE_EQUAL_WAY等方式的时候，值可能会一直很大，需要选择合适时机，对所有count进行一个reduce操作，即全部乘上相同的系数
  *
  * @param
  *
  * @note
  *
  * @retval None
  */
void SL_GEP::reduceAllCount() {
    static int reduceCount = 0;
    static int theReduceOccasion = needEpoch * 0.2;
    if(reduceCount++ >= theReduceOccasion){
        reduceCount = 0;
        chromosomeSymbolCountReduce(0.4);
    }
}
pair<Chromosome, ChromosomeRule> SL_GEP::train() {
    pair<Chromosome, ChromosomeRule> outPair;
    printOutArgumentDetail();
    initChromosomes();
    for (; shouldContiue();) {
        if(whichRenewSymbolCountWay == ANY_ONE_EQUAL_WAY)
            reduceAllCount();
        inheritanceProcess();
        printf("%d:%f\r\n", epoch, minDistance);		//602  (>2200)
    }
    outPair.first = bestChromosomeAndIndex.first;
    outPair.second = cr;

    return outPair;
}
/**
  * @brief  用训练中得到的最优染色体进行预测
  *
  * @param  terminal:输入参数
  *
  * @note   先train再predict
  *
  * @retval 预测值
  */
double SL_GEP::predict(vector<double> &terminal) {
    try{
        if (epoch < needEpoch)
            throw "please train first, you are not train enough!";
        else{
            cdPtr->setChromosome(bestChromosomeAndIndex.first);
            return cdPtr->decode(terminal);
        }
    }catch (const char * &e){
        printf("%s\r\n",e);
    }
}
/**
  * @brief  计算训练中得到的最优染色体在测试集中的欧式距离，即最优染色体在测试集中的表现
  *
  * @param  realTermVec:测试集的参数
  * @param  ansVec:测试集的label
  *
  * @note
  *
  * @retval 最优染色体在测试集的距离
  */
double SL_GEP::testDataRunPerformance(const vector<vector<double>> &realTermVec, const vector<double> &ansVec) {
    try{
        if (epoch < needEpoch)
            throw "please train first, you are not train enough!";
        else{
            return calculateDistance(bestChromosomeAndIndex.first);
        }
    }catch (const char * &e){
        printf("%s\r\n",e);
    }

}

//初始化染色体群
//******************************************
void SL_GEP::initChromosomes() {
    int theMExH = cr.getMainPR().h;
    int theMExL = cr.getMainPR().l;
    int theAExH = 0;
    int theAExL = 0;
    int numOfADF = cr.getADFPR().size();
    double nowDis = 0.0;
    for (int i = 0; i < chromosomesNum; ++i) {
        //先mainProgram
        int k = 0;
        for (int j = 0; j < theMExH; ++j, ++k)
            chromosomes[i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
        for(int j = 0 ; j < theMExL ; ++j ,++k)
            chromosomes[i].mainProgramEx[k] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


        //后ADFs
        for (int t = 0; t < numOfADF; ++t) {
            k = 0;
            theAExH = cr.getADFPR(t).h;
            theAExL = cr.getADFPR(t).l;
            for (int j = 0; j < theAExH; ++j, ++k)
                chromosomes[i].ADFEx[t][k] = getRandSymbolNum(ADF_FIRST,t);

            for (int j = 0; j < theAExL; ++j, ++k)
                chromosomes[i].ADFEx[t][k] = getRandSymbolNum(ADF_SECOND,t);

        }

        nowDis = calculateDistance(chromosomes[i]);
        if(whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
            setChromosomeWeight(i, nowDis);


        recordBestChromosome(i,nowDis);

        if(whichRenewSymbolCountWay == ANY_ONE_EQUAL_WAY)
            recordOneSymbolCount(i,theMinSymbolCount);
    }

    if(whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
        recordAllCount();




}
//******************************************

//变异
//******************************************
double SL_GEP::getPsi(const int &a,const int &b) {
    return (a != b) ? 1 : 0;
}

double SL_GEP::getPhi(const int &bestSymbolNum, const int &chroIndexSymbolNum, const int &r1SymbolNum, const int &r2SymbolNum,
                      const double &F, const double &beta) {
    return 1 - (1 - F * getPsi(bestSymbolNum, chroIndexSymbolNum)) * (1 - beta * getPsi(r1SymbolNum, r2SymbolNum));
}

void SL_GEP::mainProgramFragmentMutation(const int &chroIndex, const int &FragmentIndex, const int &r1, const int &r2,
                                         const double &F, const double &beta, const double  &yRandVal) {
    double Phi = getPhi(chromosomes[chroIndex].mainProgramEx[FragmentIndex], chromosomes[bestChromosomeAndIndex.second].mainProgramEx[FragmentIndex],
                        chromosomes[r1].mainProgramEx[FragmentIndex], chromosomes[r2].mainProgramEx[FragmentIndex], F, beta);
    if (yRandVal <= Phi)
        mainProgramGetNewFragment(chroIndex, FragmentIndex);
    else
        UChromosome.mainProgramEx[FragmentIndex] = chromosomes[chroIndex].mainProgramEx[FragmentIndex];
}
void SL_GEP::ADFFragmentMutation(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const int &r1,
                                 const int &r2, const double &F, const double &beta,const double  &yRandVal) {
    double Phi = getPhi(chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex], chromosomes[bestChromosomeAndIndex.second].mainProgramEx[FragmentIndex],
                        chromosomes[r1].mainProgramEx[FragmentIndex], chromosomes[r2].mainProgramEx[FragmentIndex], F, beta);
    if (yRandVal <= Phi)
        ADFGetNewFragmentMutation(chroIndex,ADFIndex,FragmentIndex);
    else
        UChromosome.ADFEx[ADFIndex][FragmentIndex] = chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex];

}

void SL_GEP::mainProgramGetNewFragment(const int &chroIndex , const int &FragmentIndex) {
    int theMExH = cr.getMainPR().h;
    double probabilityDenominator = 0.0;
    double probabilityCount = 0.0;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    if (FragmentIndex < theMExH) {
        vector<double>symbolProbability(couldChooseSetOfMainProgramFirst.size());
        for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i) {
            symbolProbability[i] = (double)this->mainProgramSymbolCount[FragmentIndex][couldChooseSetOfMainProgramFirst[i]];			//只是暂存，后面会分布在0-1
            probabilityDenominator += symbolProbability[i];
        }

        //UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
        //return;
//		if (probabilityDenominator == 0.0) {
        if (distribution(YGenerator) > 0.9) {
            UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_FIRST);
        }
        else {
            for (int i = 0; i < couldChooseSetOfMainProgramFirst.size(); ++i)
                symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


            UChromosome.mainProgramEx[FragmentIndex] = couldChooseSetOfMainProgramFirst[getTheGambleIndex(distribution(GambleGenerator), symbolProbability)];
            //if (this->mainProgramSymbolCount[FragmentIndex][UChromosome.mainProgramEx[FragmentIndex]] == 0)
            //	printf("!!!!!\r\n");
        }

    }
    else {
        vector<Symbol> &terminalSet = cr.getSymbolSet().getTerminalSet();
        vector<double>symbolProbability(terminalSet.size());
        for (int i = 0 ; i < terminalSet.size(); ++i) {
            symbolProbability[i] = this->mainProgramSymbolCount[FragmentIndex][terminalSet[i].getNum()];			//只是暂存，后面会分布在0-1
            probabilityDenominator += symbolProbability[i];
        }

        //UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_SECOND);
        //return;
//		if (probabilityDenominator == 0.0) {
        if (distribution(YGenerator) > 0.9){
            UChromosome.mainProgramEx[FragmentIndex] = getRandSymbolNum(MAIN_PROGRAM_SECOND);


        }
        else {
            for (int i = 0; i < terminalSet.size(); ++i)
                symbolProbability[i] = (probabilityCount += (symbolProbability[i] / probabilityDenominator));


            UChromosome.mainProgramEx[FragmentIndex] = terminalSet[getTheGambleIndex(distribution(GambleGenerator), symbolProbability)].getNum();
            //if (this->mainProgramSymbolCount[FragmentIndex][UChromosome.mainProgramEx[FragmentIndex]] == 0)
            //	printf("!!!!!\r\n");
        }



    }



}
void SL_GEP::ADFGetNewFragmentMutation(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, bool authorType ) {
    if (authorType) {
        int theAExH = cr.getADFPR(ADFIndex).h;
        if (FragmentIndex < theAExH)
            UChromosome.ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_FIRST, ADFIndex);
        else
            UChromosome.ADFEx[ADFIndex][FragmentIndex] = getRandSymbolNum(ADF_SECOND, ADFIndex);
    }

}


void SL_GEP::individualMutation(const int &chroIndex, const int &r1, const int &r2, const double &F, const double &beta){
    //main program
    int mainProgramExLen = chromosomes[chroIndex].mainProgramEx.size();

    int numOfADFs = chromosomes[chroIndex].ADFEx.size();

    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < mainProgramExLen; ++i)
        mainProgramFragmentMutation(chroIndex, i, r1, r2, F, beta,distribution(YGenerator));

    for (int i = 0; i < numOfADFs; ++i) {
        int thisADFLen = chromosomes[chroIndex].ADFEx[i].size();
        for (int j = 0; j < thisADFLen; ++j) {
            ADFFragmentMutation(chroIndex, i, j, r1, r2, F, beta, distribution(YGenerator));
        }
    }
}
/*
void SL_GEP::mutation() {
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> indexDistribution(0, chromosomesNum - 1);
	for (int i = 0; i < chromosomesNum; ++i) {
		double F = distribution(FGenerator);
		double beta = distribution(BetaGenerator);
		int r1 = indexDistribution(SelectGenerator),
			r2 = indexDistribution(SelectGenerator);

		individualMutation(i, r1, r2, F, beta);


	}

}
*/
//*********************************************************


//交叉
//********************************************************
/*
void SL_GEP::crossover() {
	//mainProgram
	uniform_real_distribution<double> distribution(0.0, 1.0);
	uniform_int_distribution<int> selectKDistribution;

	for (int i = 0; i < chromosomesNum; ++i) {


	}
}
*/

/**
  * @brief  交叉相关，初始化的时候获得染色体总长度(即点位数)
  *
  * @param  None
  *
  * @note   因为在交叉的时候需要随机选择某个点位
  *
  * @retval None
  */
int SL_GEP::getTotalExpressionLen() {
    try {
        if (!cr.getSymbolSet().getSymbolMap().size())
            throw "error: cr is not init!";
        totalExpressionLen = cr.getMainPR().totalLen;
        for (int i = 0; i < cr.getADFPR().size(); ++i)
            totalExpressionLen += cr.getADFPR(i).totalLen;

        return totalExpressionLen;

    }
    catch (const char *e) {
        printf("%s\r\n", e);
        exit(-1);
    }

}
// 5  4  4
/**
  * @brief  交叉相关，因为染色体被分成mainProgram部分和多个ADF部分，但是有时需要得到染色体总体上的某个点位
  *         所以需要根据mainProgram的某个点位或者某个ADF的某个点位转换到其在染色体上的总体上的某个点位
  *
  * @param  inThisExIndex:总体点位
  * @param  ADFIndex:第几个ADF(若是在mainProgram的点位，不需要输入)
  *
  * @note   若是在mainProgram的点位，不需要输入第二个参数
  *
  * @retval None
  */
int SL_GEP::getTotalExpressionIndex(int inThisExIndex, int ADFIndex ) {
    if (ADFIndex == -1)
        return inThisExIndex;
    else {
        int theIndex = cr.getMainPR().totalLen;
        for (int i = 0; i < ADFIndex - 1; ++i)
            theIndex += cr.getADFPR(i).totalLen;
        return theIndex + inThisExIndex;
    }

}

void SL_GEP::individualCrossover(const int &chroIndex,const double &CR) {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    uniform_int_distribution<int> indexDistribution(0, totalExpressionLen - 1);
    int mainProgramExLen = chromosomes[chroIndex].mainProgramEx.size();

    int numOfADFs = chromosomes[chroIndex].ADFEx.size();
    //main program first
    for (int i = 0; i < mainProgramExLen; ++i)
        mainProgramFragmentCrossover(chroIndex, i, CR, indexDistribution(KGenerator),distribution(YGenerator),indexDistribution(YGenerator));


    //ADFs second
    for (int i = 0; i < numOfADFs; ++i) {
        int thisADFLen = chromosomes[chroIndex].ADFEx[i].size();
        for (int j = 0; j < thisADFLen; ++j)
            ADFFragmentCrossover(chroIndex, i, j, CR, indexDistribution(KGenerator), distribution(YGenerator), indexDistribution(YGenerator));
    }



}
void SL_GEP::mainProgramFragmentCrossover(const int &chroIndex, const int &FragmentIndex, const double &CR, const int &K
        ,const double &randVal, const int &theJVal) {
    if (!(randVal < CR || getTotalExpressionIndex(FragmentIndex) == K))
        UChromosome.mainProgramEx[FragmentIndex] = chromosomes[chroIndex].mainProgramEx[FragmentIndex];
}
void SL_GEP::ADFFragmentCrossover(const int &chroIndex, const int &ADFIndex, const int &FragmentIndex, const double &CR, const int &K
        , const double &randVal, const int &theJVal) {
    if (!(randVal < CR || getTotalExpressionIndex(FragmentIndex, ADFIndex) == K))
        UChromosome.ADFEx[ADFIndex][FragmentIndex] = chromosomes[chroIndex].ADFEx[ADFIndex][FragmentIndex];
}
//********************************************************



//自然选择
//********************************************************
void SL_GEP::individualSelection(const int &chroIndex){
    double xDistance = 0.0, uDistance = 0.0;
    double nowMinDistance = 0.0;
    //cdPtr->setChromosome(chromosomes[chroIndex]);
    xDistance = calculateDistance(chromosomes[chroIndex]);
    uDistance = calculateDistance(UChromosome);
    if (uDistance < xDistance) {
        chromosomes[chroIndex] = UChromosome;
        nowMinDistance = uDistance;
    }
    else
        nowMinDistance = xDistance;

    recordBestChromosome(chroIndex, nowMinDistance);
    //setChromosomeWeight(chroIndex, nowMinDistance);

}
void SL_GEP::individualSelection(const int &chroIndex, const double &randVal) {
    double xDistance = 0.0, uDistance = 0.0;
    double nowMinDistance = 0.0;
    //cdPtr->setChromosome(chromosomes[chroIndex]);
    xDistance = calculateDistance(chromosomes[chroIndex]);
    uDistance = calculateDistance(UChromosome);
    if (uDistance < xDistance) {
        chromosomes[chroIndex] = UChromosome;
        nowMinDistance = uDistance;
    }
    else
        nowMinDistance = xDistance;

    recordBestChromosome(chroIndex, nowMinDistance);
    setChromosomeWeight(chroIndex, nowMinDistance);

    setOneSymbolCountByRandVal(chroIndex, randVal);				//片段的信息素衰减


}

double SL_GEP::calculateDistance(const 	Chromosome &c){
    return EuclideanDis(c);

}
double SL_GEP::EuclideanDis(const Chromosome &c){
    double count = 0.0;
    double decodeVal;
    cdPtr->setChromosome(const_cast<Chromosome&>(c));
    for (int i = 0; i < termAnsPairNum; ++i) {
        decodeVal = (cdPtr->decode(realTermSet[i]));
        if (decodeVal >= getTheMaxReal())
            return maxDistanceByNow;
        count += pow((decodeVal - ansSet[i]), 2);
    }
    count = sqrt(adjustValue(count));
    if (count > maxDistanceByNow)
        maxDistanceByNow = count;

    return  count;

}
//********************************************************


//交叉与遗传合并
//********************************************************
void SL_GEP::inheritanceProcess() {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    uniform_int_distribution<int> indexDistribution(0, chromosomesNum - 1);
    for (int i = 0; i < chromosomesNum; ++i) {
        double F = distribution(FGenerator);
        double beta = distribution(BetaGenerator);
        int r1 = indexDistribution(SelectGenerator),
                r2 = indexDistribution(SelectGenerator);
        double CR = distribution(CRGenerator);
        double ACSRandVal = distribution(ACSGenerator);

        individualMutation(i, r1, r2, F, beta);			//遗传

        individualCrossover(i,CR);						//交叉

        if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
            individualSelection(i, ACSRandVal);							//自然选择
        else if (whichRenewSymbolCountWay == ANY_ONE_EQUAL_WAY) {
            individualSelection(i);
            recordOneSymbolCount(i,theMinSymbolCount);
        }





        //recordOneSymbolCount(i);


    }
    if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT || whichRenewSymbolCountWay == BEST_ONE_ONLY || whichRenewSymbolCountWay == LOW_ONE_FIRST)
        recordAllCount();



}
//********************************************************


//记录一条染色体的每个片段所用的symbol
//********************************************************
void SL_GEP::recordOneSymbolCount(const int &chroIndex, const double &score) {

    int mainPSize = chromosomes[chroIndex].mainProgramEx.size();
    int numOfADF = chromosomes[chroIndex].ADFEx.size();
    for (int i = 0; i < mainPSize; ++i) {
        recordSymbolCount(chromosomes[chroIndex].mainProgramEx[i], i,score);
    }

    for (int i = 0; i < numOfADF; ++i) {
        int ADFLen = chromosomes[chroIndex].ADFEx[i].size();
        for (int j = 0; j < ADFLen; ++j) {
            recordSymbolCount(chromosomes[chroIndex].ADFEx[i][j], j, score, i);
        }
    }
}
void SL_GEP::setOneSymbolCountByRandVal(const int &chroIndex, const double &randVal) {
    int mainPSize = chromosomes[chroIndex].mainProgramEx.size();
    int numOfADF = chromosomes[chroIndex].ADFEx.size();
    for (int i = 0; i < mainPSize; ++i) {
        setSymbolCountByRandVal(chromosomes[chroIndex].mainProgramEx[i], i, randVal);
    }

    for (int i = 0; i < numOfADF; ++i) {
        int ADFLen = chromosomes[chroIndex].ADFEx[i].size();
        for (int j = 0; j < ADFLen; ++j) {
            setSymbolCountByRandVal(chromosomes[chroIndex].ADFEx[i][j], j, randVal, i);
        }
    }


}


void SL_GEP::recordAllCount() {
    if (totalWeight > 1e-8) {
        if (whichRenewSymbolCountWay == LOW_ONE_FIRST) {
            for (int i = 0; i < chromosomesNum; ++i)
                recordOneSymbolCount(i, chromosomeWeight[i] / totalWeight);

        }
        else {
            int theBestIndex = 0;
            long double adjustTotalWeight = 0.0;
            double lastBestWeightScore = -1;
            for (int i = 0; i < chromosomesNum; ++i) {
                double inputWeightScore = (chromosomeWeight[i] == 0.0 ? maxWeightScore : (totalWeight / chromosomeWeight[i]) / chromosomesNum);
                adjustTotalWeight += inputWeightScore;
                if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT)
                    chromosomeWeight[i] = inputWeightScore;

                if (whichRenewSymbolCountWay == BEST_ONE_ONLY) {
                    if (inputWeightScore > lastBestWeightScore) {
                        lastBestWeightScore = inputWeightScore;
                        theBestIndex = i;
                    }
                }




                //recordOneSymbolCount(i, inputWeightScore);
                if (inputWeightScore > maxWeightScore)
                    maxWeightScore = inputWeightScore;
            }
            if (whichRenewSymbolCountWay == ANY_ONE_COUNT_BY_WEIGHT) {
                for (int i = 0; i < chromosomesNum; ++i)
                    recordOneSymbolCount(i, chromosomeWeight[i] / adjustTotalWeight);
            }
            else if (whichRenewSymbolCountWay == BEST_ONE_ONLY) {
                recordOneSymbolCount(theBestIndex, lastBestWeightScore / adjustTotalWeight);
            }

        }



    }
    else {
        int meanVal = 1 / chromosomesNum;
        for (int i = 0; i < chromosomesNum; ++i) {
            recordOneSymbolCount(i, chromosomesNum);
        }
    }

    totalWeight = 0;


}

void SL_GEP::setChromosomeWeight(const int & chroIndex, const double& distance) {
    chromosomeWeight[chroIndex] = distance;
    totalWeight += distance;
    adjustTotalWeight();
}

double SL_GEP::adjustValue(const double &x) {
    if(isinf(x))
        return getTheMaxReal();
}

void SL_GEP::adjustTotalWeight() {
    if(isinf(totalWeight))
        totalWeight = getTheMaxReal();
}
