//
// Created by JAY on 2022/2/12.
//

#include "../ThreadVersion/testThread.h"
#include <ctime>
#include "unistd.h"

void testThread1(){
    vector<vector<int>>vecVec;
    vector<int>resVec;
    vector<thread>myThread;

    for(int i = 0 ; i < 30 ; ){
        vector<int>tmpVec;
        for(int j = 0;j < 10; ++i,++j)
            tmpVec.push_back(i+1);

        vecVec.push_back(tmpVec);
        resVec.push_back(0);
    }

    for(int i = 0 ; i < 3 ; ++i)
        myThread.push_back(thread(testThread1Help,std::ref(vecVec[i]),std::ref(resVec),i));
//    thread myThread1(testThread1Help,std::ref(vecVec[0]),std::ref(resVec),0);
//    thread myThread2(testThread1Help,std::ref(vecVec[1]),std::ref(resVec),1);
//    thread myThread3(testThread1Help,std::ref(vecVec[2]),std::ref(resVec),2);
//
//    myThread1.join();
//    myThread2.join();
//    myThread3.join();
    for(int i = 0 ; i < 3 ; ++i)
        myThread[i].join();

    int count = 0;
    for(int i = 0; i < 3;++i)
        count +=  resVec[i];
    printf("%d\r\n",count);
}



void testThread1Help(const vector<int>& vec,vector<int>&res,int index){
    for(int i = 0; i < vec.size(); ++i)
        res[index] += vec[i];
}
mutex mtx;
void testThread2Help0(const vector<int>& vec,int &res){

    for(int i = 0; i < vec.size(); ++i){
        mtx.lock();
        res += vec[i];
        mtx.unlock();
    }

}
void testThread2Help0_1(const vector<int>& vec,vector<int>&res,int index,int &detachNum,mutex &detachNumMutex){
    for(int i = 0; i < vec.size(); ++i)
        res[index] += vec[i];

    detachNumMutex.lock();
    detachNum ++;
    detachNumMutex.unlock();
}
void testThread2(int num){
    clock_t startTime,endTime;
//    printf("%d\r\n",sysconf( _SC_NPROCESSORS_CONF));
    startTime = clock();
    testThread2Help1(num);
    endTime = clock();
    printf("cost:%f\r\n",(double)(endTime - startTime) / CLOCKS_PER_SEC);

    startTime = clock();
    testThread2Help2(num);
    endTime = clock();
    printf("cost:%f\r\n",(double)(endTime - startTime) / CLOCKS_PER_SEC);
}

void testThread2Help1(int num){
    int threadNum = 5;
    int detachNum = 0;
    vector<int>theRawVec;
    vector<vector<int>>vecVec;
    vector<int>resVec;
    vector<thread>myThread;
    const int tenNum = 10;
    int totalNum = num * tenNum;
    int oneThreadNums = totalNum / threadNum;
    int lastThreadNums = totalNum - oneThreadNums * threadNum;
    for(int i = 0 ; i < totalNum ; i++){
        theRawVec.push_back(i+1);
    }
    for(int i = 0 , k = 0; i < threadNum ;++i){
        int nowThreadNum ;
        if(i != threadNum -1)
            nowThreadNum = oneThreadNums;
        else
            nowThreadNum = (lastThreadNums > 0)?lastThreadNums:oneThreadNums;
        vector<int>tmpVec;
        for(int j = 0 ; j < nowThreadNum;j++)
            tmpVec.push_back(theRawVec[k++]);
        vecVec.push_back(tmpVec);
        resVec.push_back(0);
    }
//    int count = 0;
//    for(int i = 0 ; i < threadNum ; ++i)
//        myThread.push_back(thread(testThread2Help0,std::ref(vecVec[i]),std::ref(count)));
//
//    for(int i = 0 ; i < threadNum ; ++i)
//        myThread[i].join();
//
//    printf("%d\r\n",count);

    for(int i = 0 ; i < threadNum ; ++i){
        myThread.push_back(thread(testThread2Help0_1,std::ref(vecVec[i]),std::ref(resVec),i,std::ref(detachNum),std::ref(mtx)));
        myThread[i].detach();
    }


//    for(int i = 0 ; i < threadNum ; ++i)
//        myThread[i].detach();

    for(;detachNum < threadNum;){}

    int count = 0;
    for(int i = 0; i < threadNum;++i)
        count +=  resVec[i];
    printf("%d\r\n",count);
}
void testThread2Help2(int num){
    vector<int>vecVec;
    const int tenNum = 10;
    int totalNum = num * tenNum;
    for(int i = 0 ; i < totalNum ; ++i){
        vecVec.push_back(i+1);
    }


    int count = 0;
    for(int i = 0; i < vecVec.size();++i)
        count +=  vecVec[i];
    printf("%d\r\n",count);
}