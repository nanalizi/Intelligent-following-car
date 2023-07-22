//#include "uart.h"
//#include "oled.h"
//#include "stdio.h"
//#include "string.h"

//void USART1_Init(void)
//{
//	  //USART1_TX:PA 9   
//	  //USART1_RX:PA10
//		GPIO_InitTypeDef GPIO_InitStructure;     //串口端口配置结构体变量
//		USART_InitTypeDef USART_InitStructure;   //串口参数配置结构体变量
//		NVIC_InitTypeDef NVIC_InitStructure;     //串口中断配置结构体变量

//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开PA端口时钟

//    //USART1_TX   PA9
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          		 //PA9
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //设定IO口的输出速度为50MHz
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //复用推挽输出
//    GPIO_Init(GPIOA, &GPIO_InitStructure);             	 	 //初始化PA9
//    //USART1_RX	  PA10
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //PA10
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //初始化PA10 

//    //USART1 NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;  //抢占优先级0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		    //子优先级2
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	                          //根据指定的参数初始化VIC寄存器

//    //USART 初始化设置
//		USART_InitStructure.USART_BaudRate = 115200;                  //串口波特率为115200
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //字长为8位数据格式
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;        //一个停止位
//		USART_InitStructure.USART_Parity = USART_Parity_No;           //无奇偶校验位
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件数据流控制
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //收发模式
//    USART_Init(USART1, &USART_InitStructure);                     //初始化串口1

//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能中断
//    USART_Cmd(USART1, ENABLE);                     //使能串口1

//  	//如下语句解决第1个字节无法正确发送出去的问题
//	  USART_ClearFlag(USART1, USART_FLAG_TC);        //清串口1发送标志
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
