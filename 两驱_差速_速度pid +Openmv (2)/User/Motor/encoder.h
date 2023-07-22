#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys.h"
	
#define ENCODER_TIM_PSC  0          /*��������Ƶ*/
#define ENCODER_TIM_PERIOD  65536   /*���������ֵ*/
#define CNT_INIT 0                  /*��������ֵ*/
#define SPEED_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define SPEED_TIM_PSC              (72-1)


//#define ENCODER_RESOLUTION 11    /*������һȦ������������*/
//#define ENCODER_MULTIPLE 4       /*��������Ƶ��ͨ����ʱ���ı�����ģʽ����*/
//#define MOTOR_REDUCTION_RATIO 34 /*����ļ��ٱ�*/
///*���תһȦ�ܵ�������(��ʱ���ܶ�����������) = ����������������*��������Ƶ*������ٱ� */
///* 11*4*34= 1496*/
//#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO ) 



void Encoder_Init_TIM2(u16 arr,u16 psc);
int Read_Encoder_TIM2(void);
void Encoder_Init_TIM4(u16 arr,u16 psc);
int Read_Encoder_TIM4(void);

#endif
