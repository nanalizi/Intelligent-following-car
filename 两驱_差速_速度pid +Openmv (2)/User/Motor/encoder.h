#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys.h"
	
#define ENCODER_TIM_PSC  0          /*计数器分频*/
#define ENCODER_TIM_PERIOD  65536   /*计数器最大值*/
#define CNT_INIT 0                  /*计数器初值*/
#define SPEED_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define SPEED_TIM_PSC              (72-1)


//#define ENCODER_RESOLUTION 11    /*编码器一圈的物理脉冲数*/
//#define ENCODER_MULTIPLE 4       /*编码器倍频，通过定时器的编码器模式设置*/
//#define MOTOR_REDUCTION_RATIO 34 /*电机的减速比*/
///*电机转一圈总的脉冲数(定时器能读到的脉冲数) = 编码器物理脉冲数*编码器倍频*电机减速比 */
///* 11*4*34= 1496*/
//#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO ) 



void Encoder_Init_TIM2(u16 arr,u16 psc);
int Read_Encoder_TIM2(void);
void Encoder_Init_TIM4(u16 arr,u16 psc);
int Read_Encoder_TIM4(void);

#endif
