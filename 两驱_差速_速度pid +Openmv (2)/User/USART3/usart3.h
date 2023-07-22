#ifndef __USART3_H
#define __USART3_H

#include "sys.h" 

extern u8 flag3;
void HMISendb(u8 k)	;
void HMISends(char *buf1);

void uart3_init(u32 bound);
void USART3_IRQHandler(void);     	//串口1中断服务程序
#endif
