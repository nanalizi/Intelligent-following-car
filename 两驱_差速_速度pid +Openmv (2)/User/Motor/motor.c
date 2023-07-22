#include "motor.h"
#include "bsp_pid.h"
#include "encoder.h"
#include "oled.h"



void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}



void stop(void){
	SetPoint2 = 0; //�趨Ŀ�� Desired Value 
  SetPoint4 = 0; //�趨Ŀ�� Desired Value 
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
}
void straight(int32_t path_lenght)//ֱ��
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}


void Right(void)  //��ת90
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void Left(void)		//��ת90
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
}

void back(void)//��ͷ
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_SetBits(GPIOB,GPIO_Pin_15);

}

void xunji(void){
//	SetPoint2 = 90; //�趨Ŀ�� Desired Value 
//  SetPoint4 = 90; //�趨Ŀ�� Desired Value 

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//����
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//����
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

