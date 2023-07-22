#include "sys.h"
#include "usart2.h"	  
#include "oled.h"
 

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目

u16 USART2_RX_STA=0;       //接收状态标记	  
int data3[4];	
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

}

void USART2_IRQHandler(void)                	//串口1中断服务程序
	{
	  u8 com_data; 
		u8 i,ttt=0;
		u32 np;
		u32 tempor_data;
		static u8 RxCounter2=0;
		static u16 RxBuffer2[12]={0};
		static u8 RxState2 = 0;	
		static u8 RxFlag2 = 0;

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	   //接收中断  
		{
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //清除中断标志
				com_data = USART_ReceiveData(USART2);
			
				if(RxState2==0&&com_data==0x2C)  //0x2c帧头
				{
					RxState2=1;
					RxBuffer2[RxCounter2++]=com_data;
				}
		
				else if(RxState2==1&&com_data==0x12)  //0x12帧头
				{
					RxState2=2;
					RxBuffer2[RxCounter2++]=com_data;
				}
		
				else if(RxState2==2)
				{
					RxBuffer2[RxCounter2++]=com_data;

					if(RxCounter2>=12||com_data == 0x5B)       //RxBuffer1接受满了,接收数据结束
					{
						RxState2=3;
						RxFlag2=1;
					}
				}
		
				else if(RxState2==3)		//检测是否接受到结束标志
				{
						if(RxBuffer2[RxCounter2-1] == 0x5B)
						{
									USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
									if(RxFlag2)
									{
										tempor_data = 0;
										tempor_data = RxBuffer2[3];
										tempor_data <<= 8;
										tempor_data |= RxBuffer2[2];
										
										if(tempor_data != 0)
										{
											data3[0] = tempor_data;
										}
										tempor_data = 0;
										
										tempor_data = RxBuffer2[5];
										tempor_data <<= 8;
										tempor_data |= RxBuffer2[4];
										
										if(tempor_data != 0)
										{
											data3[1] = tempor_data;
										}
										tempor_data = 0;
										
										tempor_data = RxBuffer2[7];
										tempor_data <<= 8;
										tempor_data |= RxBuffer2[6];
										
										if(tempor_data != 0)
										{
											data3[2] = tempor_data;
										}
										else
										{
											 ttt = 1;
										}
										tempor_data = 0;
										
										tempor_data = RxBuffer2[9];
										tempor_data <<= 8;
										tempor_data |= RxBuffer2[8];
										
										if(tempor_data != 0)
										{
											data3[3] = tempor_data;
										}
										
										if( ttt )
										{
											np = data3[1]; 
											data3[1] = data3[0];
											data3[2] = np;
											data3[0] = 0;
											data3[3] = 0;
										}
										
										sprintf((char *)string,"0:%d",data3[0]);
										OLEDShowString(2,1,string,4);
										sprintf((char *)string,"1:%d",data3[1]);
										OLEDShowString(2,2,string,4);
										sprintf((char *)string,"2:%d",data3[2]);
										OLEDShowString(2,3,string,4);
										sprintf((char *)string,"3:%d",data3[3]);
										OLEDShowString(2,4,string,4);
									}
									RxFlag2 = 0;
									RxCounter2 = 0;
									RxState2 = 0;
									USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
						}
						else   //接收错误
						{
									RxState2 = 0;
									RxCounter2=0;
									for(i=0;i<10;i++)
									{
											RxBuffer2[i]=0x00;      //将存放数据数组清零
									}
						}
				} 
				else   //接收异常
				{
						RxState2 = 0;
						RxCounter2=0;
						for(i=0;i<10;i++)
						{
								RxBuffer2[i]=0x00;      //将存放数据数组清零
						}
				}

		}

} 


