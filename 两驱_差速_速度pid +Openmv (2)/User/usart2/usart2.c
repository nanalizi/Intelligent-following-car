#include "sys.h"
#include "usart2.h"	  
#include "oled.h"
 

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ

u16 USART2_RX_STA=0;       //����״̬���	  
int data3[4];	
void uart2_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}

void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	  u8 com_data; 
		u8 i,ttt=0;
		u32 np;
		u32 tempor_data;
		static u8 RxCounter2=0;
		static u16 RxBuffer2[12]={0};
		static u8 RxState2 = 0;	
		static u8 RxFlag2 = 0;

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	   //�����ж�  
		{
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //����жϱ�־
				com_data = USART_ReceiveData(USART2);
			
				if(RxState2==0&&com_data==0x2C)  //0x2c֡ͷ
				{
					RxState2=1;
					RxBuffer2[RxCounter2++]=com_data;
				}
		
				else if(RxState2==1&&com_data==0x12)  //0x12֡ͷ
				{
					RxState2=2;
					RxBuffer2[RxCounter2++]=com_data;
				}
		
				else if(RxState2==2)
				{
					RxBuffer2[RxCounter2++]=com_data;

					if(RxCounter2>=12||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						RxState2=3;
						RxFlag2=1;
					}
				}
		
				else if(RxState2==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer2[RxCounter2-1] == 0x5B)
						{
									USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//�ر�DTSABLE�ж�
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
						else   //���մ���
						{
									RxState2 = 0;
									RxCounter2=0;
									for(i=0;i<10;i++)
									{
											RxBuffer2[i]=0x00;      //�����������������
									}
						}
				} 
				else   //�����쳣
				{
						RxState2 = 0;
						RxCounter2=0;
						for(i=0;i<10;i++)
						{
								RxBuffer2[i]=0x00;      //�����������������
						}
				}

		}

} 


