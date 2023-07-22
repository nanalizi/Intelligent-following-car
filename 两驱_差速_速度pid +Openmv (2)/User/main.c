#include "stm32f10x.h" 
#include "stdio.h"
#include "sys.h"
#include "oled.h"
#include "bsp_led.h"
#include "pwm.h" 
#include "motor.h"
#include "encoder.h"
#include "bsp_usart.h"
#include "pid_usart.h"
#include "bsp_pid.h"  
#include "timer.h"
#include "usart3.h"	  
#include "usart2.h"
u8 string[10] = {0};	

int main(void)
{
	LED_Init();
	uart2_init(115200);
	USART_Config();
	uart3_init(115200);
	
	Motor_Init();

	GENERAL_TIM_NVIC_Config();//�ж����ȼ�
	GENERAL_TIM_Init();//pwm
	Encoder_Init_TIM2(65535,0);     //��ʱ��2������ģʽ��ʼ��
	Encoder_Init_TIM4(65535,0);     //��ʱ��4������ģʽ��ʼ�� 
	TIM1_Getsample_Int(499,719);		//5ms����ʱ�жϣ����ڼ�ʱ��������ͽ���PID�㷨
	OLEDInit();
	OLEDClear();
	

  while(1)
  {   	
//		if(flag==0)	stop();
//		else
//			xunji();
	TIM3->CCR3 = 1500;
	TIM3->CCR4 = 1500;
		
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_SetBits(GPIOB,GPIO_Pin_15);

	}
}
/*********************************************END OF FILE**********************/
