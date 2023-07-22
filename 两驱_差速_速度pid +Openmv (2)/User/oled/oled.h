#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"
#include <inttypes.h>
#define OLED_RCC_PORT      	 RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define OLED_SCL_PORT        GPIOA
#define OLED_SCL_PIN         GPIO_Pin_5
#define OLED_SCL_LOW()       GPIO_ResetBits(OLED_SCL_PORT, OLED_SCL_PIN) // SCL
#define OLED_SCL_HIGH()      GPIO_SetBits(OLED_SCL_PORT, OLED_SCL_PIN)
 
#define OLED_SDA_PORT        GPIOA
#define OLED_SDA_PIN         GPIO_Pin_7
#define OLED_SDA_LOW()       GPIO_ResetBits(OLED_SDA_PORT, OLED_SDA_PIN) // SDA
#define OLED_SDA_HIGH()      GPIO_SetBits(OLED_SDA_PORT, OLED_SDA_PIN)
 
#define OLED_RES_PORT        GPIOA
#define OLED_RES_PIN         GPIO_Pin_15
#define OLED_RES_LOW()       GPIO_ResetBits(OLED_RES_PORT, OLED_RES_PIN) // RES
#define OLED_RES_HIGH()      GPIO_SetBits(OLED_RES_PORT, OLED_RES_PIN)
 
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

extern uint8_t string[10];
 
void IICStart(void);
void IICStop(void);
void I2CWriteCmd(uint8_t cmd);
void I2CWriteData(uint8_t data);
void I2CWriteByte(uint8_t byte);
void I2CWaitAck(void);
 
//OLED控制用函数
void OLEDWriteByte(uint8_t dat,uint8_t cmd);  
void OLEDDisplayOn(void);
void OLEDDisplayOff(void);	   							   		    
void OLEDInit(void);
void OLEDClear(void);
void OLEDDrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLEDFill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLEDShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLEDShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLEDShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);	 
void OLEDSetPos(uint8_t x, uint8_t y);
void OLEDShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLEDDrawBMP(uint8_t x0, uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);
void OLED_CfgGpio(void);
void delay(uint16_t x);
#endif  

