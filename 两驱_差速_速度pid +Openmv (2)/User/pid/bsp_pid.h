#ifndef  _PID_H
#define  _PID_H
#include "stm32f10x.h"

/***************************PID*************************/
extern int qwer;

// PID�ṹ����

extern int SetPoint2; //�趨Ŀ�� Desired Value 
extern float Balance_KP; //�������� Proportional Const 
extern float Balance_KI; //���ֳ��� Integral Const 
extern float Balance_KD; //΢�ֳ��� Derivative Const 
extern int LastError; //Error[-1] 
extern int PrevError; //Error[-2] 
extern int SumError; //Sums of Errors 

extern int SetPoint2; //�趨Ŀ�� Desired Value 
extern int SetPoint4; //�趨Ŀ�� Desired Value 

extern int balance(float now_Value,float SetPoint,float Balance_KP,float Balance_KD,float Balance_KI);
extern float moveAverageFilter(int i);
extern u16 sum2;
extern u16 sum4;
extern u16 curNum;
extern u16 sum_2;
extern u16 sum_4;

#endif
