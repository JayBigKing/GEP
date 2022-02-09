from  gepChromosome import ChromosomeRule
class testRF:
    def __init__(self):
        self.__ADFPR = []
    def test1(self):
        for i in range(0,5):
            tmpPR = ChromosomeRule.ProgramRule()
            tmpPR.h = i+10
            tmpPR.u = i
            tmpPR.l = ChromosomeRule.getExpressionL(tmpPR.h,tmpPR.u)
            tmpPR.totalLen = tmpPR.h + tmpPR.l
            self.__ADFPR.append(tmpPR)

        for i in range(0,5):
            print(self.__ADFPR[i])

def main():
    t1 = testRF()
    t1.test1()

main()