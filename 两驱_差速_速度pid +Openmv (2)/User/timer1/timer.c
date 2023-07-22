#include "timer.h"
#include "encoder.h"
#include "bsp_pid.h"
#include "stm32f10x_it.h"
#include "pid_usart.h"
#include "pwm.h" 
#include "bsp_usart.h"
#include "oled.h"

/*********************************************编码器脉冲读取，PID计算刷新时钟2***********************************/
void TIM1_Getsample_Int(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 为50ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数设置
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  TIM_ClearFlag(TIM1,TIM_FLAG_Update);  //清楚中断标志位
	
	TIM_ITConfig( TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//使能定时器1更新触发中断
 
	TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断;//**--**普通定时器（=TIMx_IRQn）
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure); 
}


//***************TIME1的中断********************************/

// 中断优先级配置
void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = SPEED_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int i=0,j=0;
float s2;
float s4;
float  speed2;
float  speed4;
float  value2_buf[N];
float  value4_buf[N];
int read2;
int read4;
float journey_cm;
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET) //溢出中断
	{

//	int now2;
//	int now4;
//	int Motor2_journey_cm;
//	int Motor4_journey_cm;
////			OLEDClear();
//			read2=Read_Encoder_TIM2();
//			read4=Read_Encoder_TIM4();
//			now2 += read2;
//			now4 += read2;//???????
//	
//		Motor2_journey_cm  = ( now2 /TOTAL_RESOLUTION)  * (2*WheelR*3.1416);//???????
//		Motor4_journey_cm	 = ( now4 /TOTAL_RESOLUTION) * (2*WheelR*3.1416);
//	journey_cm = (Motor2_journey_cm + Motor4_journey_cm)/2;
//			sprintf((char*)string,"spd2:%d",read2);
//			OLEDShowString(2,1,string,4);		
//			sprintf((char*)string,"spd2:%d",read4);
//			OLEDShowString(2,2,string,4);		
			CCR3_Val = 2000;
			CCR4_Val = 2000;
//			sprintf((char*)string,"CCR2_Val:%d ",CCR3_Val);
//			OLEDShowString(2,5,string,4);		
//			sprintf((char*)string,"CCR4_Val:%d ",CCR4_Val);
//			OLEDShowString(2,6,string,4);		
			TIM_ClearITPendingBit(TIM2 , TIM_IT_CC1);  
			TIM_ClearITPendingBit(TIM4 , TIM_IT_CC1);  
			TIM_ClearITPendingBit(TIM2 , TIM_IT_CC2);  
			TIM_ClearITPendingBit(TIM4 , TIM_IT_CC2);  

	}	
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除中断标志位
}


//void DEBUG_USART_IRQHandler(void)
//{
//  uint8_t ucTemp;
//	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(DEBUG_USARTx);
//    USART_SendData(DEBUG_USARTx,ucTemp);    
//	}	 
//}

