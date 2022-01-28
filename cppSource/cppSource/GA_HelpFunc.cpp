//
// Created by JAY on 2021/11/2.
//

#include "GA_HelpFunc.h"
#include "GA_HelpFunc.h"
//#if CODING_MODE == BINARY_CODING_MODE

int getTheGambleIndexHelp(const double &val, const vector<double> &vec,int low, int high);

int myBinaryPow(int i){
    switch (i) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 8;
        case 4:
            return 16;
        case 5:
            return 32;
        case 6:
            return 64;
        case 7:
            return 128;
        case 8:
            return 256;
        case 9:
            return 512;
        case 10:
            return 1024;
        case 11:
            return 2048;
        case 12:
            return 4096;
        case 13:
            return 8192;
        case 14:
            return 16384;
        case 15:
            return 32768;
        case 16:
            return 65536;
        case 17:
            return 131072;
        case 18:
            return 262144;
        case 19:
            return 524288;
        case 20:
            return 1048576;
        default:return (int) pow(2,i);
    }
}
int getTheBits(double val , int low  , int high ){
    while (low <= high){
        int mid = (high + low) /2;
        if(val > pow(2,mid)){
            low = mid + 1;
        }else if(val < pow(2,mid -1)){
            high = mid - 1;
        }else{
            return mid;
        }
    }
    return 30;
}
//#endif
int getTheBitsHelp(double val ,double *array, int low  , int high );
int getTheBits(double val , double *array , int len){
    if(val < 0 || val > 1)
        return -1;
    else
        return getTheBitsHelp(val,array,1,len - 1);
}
int getTheBitsHelp(double val ,double *array, int low  , int high ){
    while (low <= high){
        int mid = (high + low) / 2;
        if(val > array[mid])
            low = mid + 1;
        else if(val < array[mid - 1])
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}
double LimitHighandLow(double val,double high , double low){
    val = (val > high)?high:val;
    val = (val < low)?low:val;
    return val;
}
//				0.25
//  0  0.1  0.2		0.3   0.4  0.8  1
//		0	 1		 2	  3

int getTheGambleIndexHelp(const double &val, const vector<double> &vec, int low, int high) {
	for (; low < high;) {
		int mid = (low + high) / 2;
		if (val > vec[mid])
			low = mid + 1;
		else if (val < vec[mid - 1])
			high = mid ;
		else
			return mid;
	}
	return -1;
}
int getTheGambleIndex(const double &val, const vector<double> &vec) {
	if (val < 0 || val > 1)
		return -1;
	else if (val < vec[0])
		return 0;
	else if (val > vec[vec.size() - 2])
		return vec.size() - 1;
	else
		return getTheGambleIndexHelp(val,vec, 1, vec.size() - 1);

}