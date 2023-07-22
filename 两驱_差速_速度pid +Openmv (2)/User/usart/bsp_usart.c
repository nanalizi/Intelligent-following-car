#include "bsp_usart.h"
#include "oled.h"
#include "stdio.h"
#include "string.h"
#include "usart3.h"	
 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	  //USART1_TX:PA 9   
	  //USART1_RX:PA10
		GPIO_InitTypeDef GPIO_InitStructure;     //���ڶ˿����ýṹ�����
		USART_InitTypeDef USART_InitStructure;   //���ڲ������ýṹ�����
		NVIC_InitTypeDef NVIC_InitStructure;     //�����ж����ýṹ�����

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��PA�˿�ʱ��

    //USART1_TX   PA9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          		 //PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //�趨IO�ڵ�����ٶ�Ϊ50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);             	 	 //��ʼ��PA9
    //USART1_RX	  PA10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //��ʼ��PA10 

    //USART1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		    //�����ȼ�2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    //USART ��ʼ������
		USART_InitStructure.USART_BaudRate = 115200;                  //���ڲ�����Ϊ115200
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;        //һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;           //����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure);                     //��ʼ������1

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ���ж�
    USART_Cmd(USART1, ENABLE);                     //ʹ�ܴ���1

  	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
	  USART_ClearFlag(USART1, USART_FLAG_TC);        //�崮��1���ͱ�־
}

/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}







static int fllag1=0,x=0;
int xw=0;
int flag=0;
	
//USART1 ȫ���жϷ�����
void USART1_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		static u8 RxCounter1=0;
		static int RxBuffer1[10]={0};
		static u8 RxState = 0;	
		static u8 RxFlag1 = 0;


		if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	   //�����ж�  
		{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //����жϱ�־
				com_data = USART_ReceiveData(USART1);
			
				if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						RxState=3;
						RxFlag1=1;
						fllag1=RxBuffer1[RxCounter1-3];
						x=RxBuffer1[RxCounter1-2];
					}
				}
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);//�ر�DTSABLE�ж�
									if(RxFlag1)
									{
										OLEDClear();
										sprintf((char *)string,"flag:%d",fllag1);
										OLEDShowString(2,2,string,4);
										flag = fllag1;
										sprintf((char *)string,"xw:%d",x);
										OLEDShowString(2,4,string,4);
										xw = x;
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}

		}
		
}
