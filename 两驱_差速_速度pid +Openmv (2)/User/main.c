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

	GENERAL_TIM_NVIC_Config();//中断优先级
	GENERAL_TIM_Init();//pwm
	Encoder_Init_TIM2(65535,0);     //定时器2编码器模式初始化
	Encoder_Init_TIM4(65535,0);     //定时器4编码器模式初始化 
	TIM1_Getsample_Int(499,719);		//5ms任务定时中断，用于计时、记脉冲和进行PID算法
	OLEDInit();
	OLEDClear();
	

  while(1)
  {   	
//		if(flag==0)	stop();
//		else
//			xunji();
	TIM3->CCR3 = 1500;
	TIM3->CCR4 = 1500;
		
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_SetBits(GPIOB,GPIO_Pin_15);

	}
}
/*********************************************END OF FILE**********************/
