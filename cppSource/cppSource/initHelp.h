#pragma once
#include<vector>
using namespace std;
template<class elemType>
void initVectorHelp(vector<elemType> &vec, int size){
	vector<elemType> tmpVec(size);
	vec = tmpVec;
}