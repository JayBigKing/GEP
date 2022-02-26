//
// Created by JAY on 2022/2/20.
//

#ifndef CPPSOURCEFORLINUX_SL_GEP_DATAPROCESSOR_H
#define CPPSOURCEFORLINUX_SL_GEP_DATAPROCESSOR_H
#include "../SL_GEP.h"
#include <string>

using namespace std;
class SL_GEP;
class SL_GEP_dataProcessor {
public:
    static void testSave();
    static void testLoad();

    static void saveSL_GEP(const SL_GEP &slGep,const string &saveFileName="");
    static SL_GEP loadSL_GEP(const string &loadFileName,const vector<vector<double>>&realTermVec, const vector<double>&ansVec,const int &chroNum = -1,
                             const int &needEpoch = -1,const bool &useTheCount = true,const uint8_t& whichRenewSymbolCountWay = -1);

    static void loadDataSet(const string &dataSetFileName,const uint32_t &whichLabel = 0);
    static pair<vector<vector<double>>,vector<double>> loadDataSetOut(const string &dataSetFileName,const uint32_t &whichLabel = 0);
    static SL_GEP loadSL_GEPAndDataSet(const string &loadFileName,const string &dataSetFileName,const uint32_t &whichLabel = 0,const int &chroNum = -1,const int &needEpoch = -1,
                                     const bool &useTheCount = true,const uint8_t& whichRenewSymbolCountWay = -1);

    static void testLoadDataSet();

private:
    static const int startYearInSLDat;
    static const int startMonInSLDat;
    static const string defaultSL_GEPNameHeadStr;

    static const char inTheSecondFlagChar;
    static const char oneReadDoneFlagChar;
    static const char setReadDoneFlagChar;
    static const char mapKeyFlagChar;
    static const char mapValFlagChar;
    static const char inTheLabelDataChar;

    static pair<vector<vector<double>>,vector<double>> theDataSet;
    static string getFileNameByDateTime(string nameHeadStr, bool useRelativePath = true);

    static vector<vector<string>> readCSV(const string &csvFileName);



};


#endif //CPPSOURCEFORLINUX_SL_GEP_DATAPROCESSOR_H
