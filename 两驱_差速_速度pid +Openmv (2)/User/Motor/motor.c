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
	SetPoint2 = 0; //设定目标 Desired Value 
  SetPoint4 = 0; //设定目标 Desired Value 
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
}
void straight(int32_t path_lenght)//直走
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}


void Right(void)  //右转90
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void Left(void)		//左转90
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
}

void back(void)//掉头
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_SetBits(GPIOB,GPIO_Pin_15);

}

void xunji(void){
//	SetPoint2 = 90; //设定目标 Desired Value 
//  SetPoint4 = 90; //设定目标 Desired Value 

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);			//左轮
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//右轮
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

