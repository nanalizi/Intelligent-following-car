#include "timer.h"
#include "encoder.h"
#include "bsp_pid.h"
#include "stm32f10x_it.h"
#include "pid_usart.h"
#include "pwm.h" 
#include "bsp_usart.h"
#include "oled.h"

/*********************************************�����������ȡ��PID����ˢ��ʱ��2***********************************/
void TIM1_Getsample_Int(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 Ϊ50ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ���������
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  TIM_ClearFlag(TIM1,TIM_FLAG_Update);  //����жϱ�־λ
	
	TIM_ITConfig( TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//ʹ�ܶ�ʱ��1���´����ж�
 
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�;//**--**��ͨ��ʱ����=TIMx_IRQn��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure); 
}


//***************TIME1���ж�********************************/

// �ж����ȼ�����
void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = SPEED_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
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
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET) //����ж�
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
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //����жϱ�־λ
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

