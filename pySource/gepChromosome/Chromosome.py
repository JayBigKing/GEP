from gepChromosome import ChromosomeRule
import numpy as np
class Chromosome:
    def __init__(self,chromosomeRule = None):
        self.mainProgramEx = []
        self.ADFEx = []
        if chromosomeRule is not None:
            self.init(chromosomeRule)

    def init(self,chromosomeRule):
        self.mainProgramEx = np.zeros((chromosomeRule.getMainPR().totalLen),dtype=np.uint32)
        for i in range(0,len(chromosomeRule.getADFPR())):
            self.ADFEx.append(np.zeros(chromosomeRule.getADFPR()[i].totalLen,dtype=np.uint32))

