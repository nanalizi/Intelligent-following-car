//#include "uart.h"
//#include "oled.h"
//#include "stdio.h"
//#include "string.h"

//void USART1_Init(void)
//{
//	  //USART1_TX:PA 9   
//	  //USART1_RX:PA10
//		GPIO_InitTypeDef GPIO_InitStructure;     //���ڶ˿����ýṹ�����
//		USART_InitTypeDef USART_InitStructure;   //���ڲ������ýṹ�����
//		NVIC_InitTypeDef NVIC_InitStructure;     //�����ж����ýṹ�����

//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��PA�˿�ʱ��

//    //USART1_TX   PA9
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          		 //PA9
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //�趨IO�ڵ�����ٶ�Ϊ50MHz
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //�����������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);             	 	 //��ʼ��PA9
//    //USART1_RX	  PA10
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //PA10
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //��ʼ��PA10 

//    //USART1 NVIC ����
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;  //��ռ���ȼ�0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		    //�����ȼ�2
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //IRQͨ��ʹ��
//		NVIC_Init(&NVIC_InitStructure);	                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���

//    //USART ��ʼ������
//		USART_InitStructure.USART_BaudRate = 115200;                  //���ڲ�����Ϊ115200
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;        //һ��ֹͣλ
//		USART_InitStructure.USART_Parity = USART_Parity_No;           //����żУ��λ
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������������
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //�շ�ģʽ
//    USART_Init(USART1, &USART_InitStructure);                     //��ʼ������1

//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ���ж�
//    USART_Cmd(USART1, ENABLE);                     //ʹ�ܴ���1

//  	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
//	  USART_ClearFlag(USART1, USART_FLAG_TC);        //�崮��1���ͱ�־
//}


//void clear_RxBuffer(u8 *buffer)
//{
//	u8 i;
//	for(i = 0; i < 10; i ++)
//	{
//		buffer[i] = '\0';
//	}
//}
//static int flag1=0,x=0;
//static float xw=0;

//void USART1_IRQHandler(void) 
//{
//	char a;
//	uint8_t com_data; 
//	static uint8_t RxCounter1=0;
//    static uint8_t RxBuffer1[10]={0};
// 
//	if( USART_GetITStatus(USART1 ,USART_IT_RXNE) != RESET)
//	{
//		USART_ClearITPendingBit(USART1 ,USART_IT_RXNE);
//		com_data = USART_ReceiveData(USART1);
//		if(com_data == ']')
//		{
//			if(RxBuffer1[0] == '[')
//			{
//				sscanf((const char*)RxBuffer1, "%c%d,%d", &a, &flag1, &x);
//				printf("rheta:%d,  rho:%d\n", flag1, x);
//				xw = ((float)x/1000);

//				sprintf((char *)string,"flag1:%d",flag1);
//				OLEDShowString(16,16,string,16);
//				sprintf((char *)string,"xw:%.3f",xw);
//				OLEDShowString(16,32,string,16);
//				clear_RxBuffer(RxBuffer1);
//			}
//			RxCounter1 = 0;
//		}
//		else
//		{
//			RxBuffer1[RxCounter1 ++] = com_data;
//		}
//		if(RxCounter1 > 10)
//		{
//			RxCounter1 = 0;
//			clear_RxBuffer(RxBuffer1);
//		}
//	}
//}
