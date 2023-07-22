#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "sys.h"

// �ж���غ궨��
#define            SPEED_TIM_IT_CCx            TIM_IT_CC1
#define            SPEED_TIM_IRQ               TIM3_IRQn//��ʱ�������ж϶�������������ж��ٸ���ʵ����������������ж�
#define            SPEED_TIM_INT_FUN           TIM3_IRQHandler
#define N 40
	
#define ENCODER_RESOLUTION 260    /*������һȦ������������*/
#define ENCODER_MULTIPLE 4       /*��������Ƶ��ͨ����ʱ��������ģʽ����*/
#define MOTOR_REDUCTION_RATIO 20 /*����ļ��ٱ�*/
/*���תһȦ�ġ��������� */
/* 11*4*34= 1496*/
#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO ) 
#define WheelR 1.70   //���Ӱ뾶 cm
extern	int read2;
extern	int read4;
extern	int now2;
extern	int now4;
extern	int Motor2_journey_cm;
extern	int Motor4_journey_cm;
extern	float journey_cm;


extern void GENERAL_TIM_NVIC_Config(void);
extern void PWM_count(void);

extern float s2;
extern float s4;

extern float  speed2;
extern float  speed4;


extern uint8_t string[10];
extern float  value2_buf[N];
extern float  value4_buf[N];
void TIM1_Getsample_Int(u16 arr,u16 psc);


#endif	








