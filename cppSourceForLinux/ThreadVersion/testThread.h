//
// Created by JAY on 2022/2/12.
//

#ifndef CPPSOURCEFORLINUX_TESTTHREAD_H
#define CPPSOURCEFORLINUX_TESTTHREAD_H

#include <vector>
#include <thread>
using namespace std;
void testThread1();
void testThread1Help(const vector<int>& vec,vector<int>&res,int index);

void testThread2(int num);
void testThread2Help0(const vector<int>& vec,int &res);
void testThread2Help0_1(const vector<int>& vec,vector<int>&res,int index,int &detachNum);
void testThread2Help1(int num);
void testThread2Help2(int num);
#endif //CPPSOURCEFORLINUX_TESTTHREAD_H
