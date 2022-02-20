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
    static SL_GEP loadSL_GEP(const string &loadFileName="",const int &chroNum = -1,const int &TAPairNum = -1,const int &needEpoch = -1,const bool &useTheCount = true,
                           const uint8_t& whichRenewSymbolCountWay = -1);

    static void loadDataSet();
    static void loadSL_GEPAndDataSet();

private:
    static const int startYearInSLDat;
    static const int startMonInSLDat;
    static const string defaultSL_GEPNameHeadStr;
    static string getFileNameByDateTime(string nameHeadStr, bool useRelativePath = true);


};


#endif //CPPSOURCEFORLINUX_SL_GEP_DATAPROCESSOR_H
