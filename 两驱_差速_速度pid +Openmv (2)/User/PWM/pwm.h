#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H

#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3
//��ʱ��3 PWM�����CH1->PA6 CH2->PA7 CH3->PB0 CH4->PB1��**TIM_SetComparex(TIMx,xxx);//ռ�ձȺ���

#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            7199
#define            GENERAL_TIM_Prescaler         0
//// TIM3 ����Ƚ�ͨ��1
//#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
//#define            GENERAL_TIM_CH1_PORT          GPIOA
//#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

//// TIM3 ����Ƚ�ͨ��2
//#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
//#define            GENERAL_TIM_CH2_PORT          GPIOA
//#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7

// TIM3 ����Ƚ�ͨ��3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH3_PORT          GPIOB
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 ����Ƚ�ͨ��4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH4_PORT          GPIOB
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_1

//ռ�ձ�����
//extern uint16_t CCR3_Val;
//extern uint16_t CCR4_Val;
#define	 CCR3_Val     TIM3->CCR3
#define	 CCR4_Val     TIM3->CCR4

/**************************��������********************************/


void GENERAL_TIM_Init(void);

#endif	/* __BSP_GENERALTIME_H */


