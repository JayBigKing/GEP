//
// Created by JAY on 2022/2/9.
//

#ifndef CPPSOURCEFORLINUX_INITHELP_H
#define CPPSOURCEFORLINUX_INITHELP_H
#include<vector>
using namespace std;
template<class elemType>
void initVectorHelp(vector<elemType> &vec, int size){
    vector<elemType> tmpVec(size);
    vec = tmpVec;
}

#endif //CPPSOURCEFORLINUX_INITHELP_H
