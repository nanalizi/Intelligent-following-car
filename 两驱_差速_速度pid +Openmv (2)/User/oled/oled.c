#include "oled.h"
#include "oledfont.h"
#include "stdlib.h"

void IICStart(void)
{
  OLED_SCL_HIGH() ;
  OLED_SDA_HIGH();
  OLED_SDA_LOW();
  OLED_SCL_LOW();
}
 
void IICStop(void)
{
  OLED_SCL_HIGH() ;
  OLED_SDA_LOW();
  OLED_SDA_HIGH();
 
}
 
void I2CWaitAck(void)
{
  OLED_SCL_HIGH() ;
  OLED_SCL_LOW();
}
 
void I2CWriteByte(uint8_t byte)
{
  uint8_t i;
  uint8_t m, data;
 
  data = byte;
  OLED_SCL_LOW();
  for(i = 0; i < 8; i++)
  {
    m = data;
    m = m & 0x80;
    if(m == 0x80)
    {
      OLED_SDA_HIGH();
    }
    else
    {
      OLED_SDA_LOW();
    }
    data = data << 1;
    OLED_SCL_HIGH();
    OLED_SCL_LOW();
  }
}
 
void I2CWriteCmd(uint8_t cmd)
{
  IICStart();
  I2CWriteByte(0x78);      //Slave address,SA0=0
  I2CWaitAck();
  I2CWriteByte(0x00);      //write command
  I2CWaitAck();
  I2CWriteByte(cmd);
  I2CWaitAck();
  IICStop();
}
 
void I2CWriteData(uint8_t data)
{
  IICStart();
  I2CWriteByte(0x78);      //D/C#=0; R/W#=0
  I2CWaitAck();
  I2CWriteByte(0x40);      //write data
  I2CWaitAck();
  I2CWriteByte(data);
  I2CWaitAck();
  IICStop();
}
 
void OLEDWriteByte(uint8_t dat, uint8_t cmd)
{
  if(cmd)
  {
    I2CWriteData(dat);
  }
  else
  {
    I2CWriteCmd(dat);
  }
}
 
//��������
 
void OLEDSetPos(uint8_t x, uint8_t y)
{
  OLEDWriteByte(0xb0 + y, OLED_CMD);
  OLEDWriteByte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
  OLEDWriteByte((x & 0x0f), OLED_CMD);
}
//����OLED��ʾ
void OLEDDisplayOn(void)
{
  OLEDWriteByte(0X8D, OLED_CMD); //SET DCDC����
  OLEDWriteByte(0X14, OLED_CMD); //DCDC ON
  OLEDWriteByte(0XAF, OLED_CMD); //DISPLAY ON
}
//�ر�OLED��ʾ
void OLEDDisplayOff(void)
{
  OLEDWriteByte(0X8D, OLED_CMD); //SET DCDC����
  OLEDWriteByte(0X10, OLED_CMD); //DCDC OFF
  OLEDWriteByte(0XAE, OLED_CMD); //DISPLAY OFF
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLEDClear(void)
{
  uint8_t i, n;
 
  for(i = 0; i < 8; i++)
  {
    OLEDWriteByte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
    OLEDWriteByte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
    OLEDWriteByte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
    for(n = 0; n < 128; n++)
    {
      OLEDWriteByte(0, OLED_DATA);
    }
  } //������ʾ
}
void OLED_On(void)
{
  uint8_t i, n;
 
  for(i = 0; i < 8; i++)
  {
    OLEDWriteByte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
    OLEDWriteByte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
    OLEDWriteByte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
    for(n = 0; n < 128; n++)
    {
      OLEDWriteByte(1, OLED_DATA);
    }
  } //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLEDShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{
  uint8_t c = 0, i = 0;
  c = chr - ' '; //�õ�ƫ�ƺ��ֵ
  if(x > Max_Column - 1)
  {
    x = 0;
    y = y + 2;
  }
  if(Char_Size == 16)
  {
    OLEDSetPos(x, y);
    for(i = 0; i < 8; i++)
    {
      OLEDWriteByte(F8X16[c * 16 + i], OLED_DATA);
    }
    OLEDSetPos(x, y + 1);
    for(i = 0; i < 8; i++)
    {
      OLEDWriteByte(F8X16[c * 16 + i + 8], OLED_DATA);
    }
  }
  else
  {
    OLEDSetPos(x, y);
    for(i = 0; i < 6; i++)
    {
      OLEDWriteByte(F6x8[c][i], OLED_DATA);
    }
 
  }
}
 
//m^n����
uint32_t oled_pow(uint8_t m, uint8_t n)
{
  uint32_t result = 1;
  while(n--)
  {
    result *= m;
  }
  return result;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ 0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLEDShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size2)
{
  uint8_t t, temp;
  uint8_t enshow = 0;
 
  for(t = 0; t < len; t++)
  {
    temp = (num / oled_pow(10, len - t - 1)) % 10;
    if(enshow == 0 && t < (len - 1))
    {
      if(temp == 0)
      {
        OLEDShowChar(x + (size2 / 2)*t, y, ' ', size2);
        continue;
      }
      else
      {
        enshow = 1;
      }
 
    }
    OLEDShowChar(x + (size2 / 2)*t, y, temp + '0', size2);
  }
}
//��ʾһ���ַ��Ŵ�
void OLEDShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size)
{
  uint8_t j = 0;
 
  while (chr[j] != '\0')
  {
    OLEDShowChar(x, y, chr[j], Char_Size);
    x += 8;
    if(x > 120)
    {
      x = 0;
      y += 2;
    }
    j++;
  }
}
//��ʾ����
void OLEDShowCHinese(uint8_t x, uint8_t y, uint8_t no)
{
  uint8_t t;
  OLEDSetPos(x, y);
  for(t = 0; t < 16; t++)
  {
    OLEDWriteByte(chinese[2 * no][t], OLED_DATA);
  }
  OLEDSetPos(x, y + 1);
  for(t = 0; t < 16; t++)
  {
    OLEDWriteByte(chinese[2 * no + 1][t], OLED_DATA);
  }
}
 
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLEDDrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[])
{
  uint32_t j = 0;
  uint8_t x, y;
 
  if(y1 % 8 == 0)
  {
    y = y1 / 8;
  }
  else
  {
    y = y1 / 8 + 1;
  }
  for(y = y0; y < y1; y++)
  {
    OLEDSetPos(x0, y);
    for(x = x0; x < x1; x++)
    {
      OLEDWriteByte(BMP[j++], OLED_DATA);
    }
  }
}
 
static void oled_delay(uint32_t ms)
{
  while(--ms);
}
 
void OLEDInit(void)
{
  OLED_CfgGpio();
  OLED_SCL_HIGH();
  OLED_SDA_HIGH();
 
  OLED_RES_LOW();
  oled_delay(20);
  OLED_RES_HIGH();
  oled_delay(50);
 
  OLEDWriteByte(0xAE, OLED_CMD); //--display off
  OLEDWriteByte(0x00, OLED_CMD); //---set low column address
  OLEDWriteByte(0x10, OLED_CMD); //---set high column address
  OLEDWriteByte(0x40, OLED_CMD); //--set start line address
  OLEDWriteByte(0xB0, OLED_CMD); //--set page address
  OLEDWriteByte(0x81, OLED_CMD); // contract control
  OLEDWriteByte(0xFF, OLED_CMD); //--128
  OLEDWriteByte(0xA1, OLED_CMD); //set segment remap
  OLEDWriteByte(0xA6, OLED_CMD); //--normal / reverse
  OLEDWriteByte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
  OLEDWriteByte(0x3F, OLED_CMD); //--1/32 duty
  OLEDWriteByte(0xC8, OLED_CMD); //Com scan direction
  OLEDWriteByte(0xD3, OLED_CMD); //-set display offset
  OLEDWriteByte(0x00, OLED_CMD); //
 
  OLEDWriteByte(0xD5, OLED_CMD); //set osc division
  OLEDWriteByte(0x80, OLED_CMD); //
 
  OLEDWriteByte(0xD8, OLED_CMD); //set area color mode off
  OLEDWriteByte(0x05, OLED_CMD); //
 
  OLEDWriteByte(0xD9, OLED_CMD); //Set Pre-Charge Period
  OLEDWriteByte(0xF1, OLED_CMD); //
 
  OLEDWriteByte(0xDA, OLED_CMD); //set com pin configuartion
  OLEDWriteByte(0x12, OLED_CMD); //
 
  OLEDWriteByte(0xDB, OLED_CMD); //set Vcomh
  OLEDWriteByte(0x30, OLED_CMD); //
 
  OLEDWriteByte(0x8D, OLED_CMD); //set charge pump enable
  OLEDWriteByte(0x14, OLED_CMD); //
 
  OLEDWriteByte(0xAF, OLED_CMD); //--turn on oled panel
}

void OLED_CfgGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(OLED_RCC_PORT, ENABLE);	/* ��GPIOʱ�� */

	GPIO_InitStructure.GPIO_Pin = OLED_SDA_PIN | OLED_SCL_PIN | OLED_RES_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  	/* ��©��� */
	GPIO_Init(OLED_RES_PORT, &GPIO_InitStructure);

}
//=====================================================================================
//
// OLEDInit();      //��ʼ��OLED
//  OLEDClear();
//  OLEDShowCHinese(10, 0, 0);
//  OLEDShowCHinese(28, 0, 1);
//  OLEDShowCHinese(46, 0, 2);
//  OLEDShowCHinese(64, 0, 3);
//  OLEDShowCHinese(82, 0, 4);
//  OLEDShowCHinese(100, 0, 5);
//  OLEDShowString(6, 3, "CAN ID:0x", 16);
//  OLEDShowString(78, 3, bbb, 16);
//  OLEDShowString(62, 6, ccc, 16);
//=====================================================================================

//void delay_init()	 
//{

//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
//	u32 reload;
//#endif
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
//	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8  
//	 
//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
//	reload=SystemCoreClock/8000000;		//ÿ���ӵļ������� ��λΪK	   
//	reload*=1000000/OS_TICKS_PER_SEC;//����OS_TICKS_PER_SEC�趨���ʱ��
//							//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
//	fac_ms=1000/OS_TICKS_PER_SEC;//����ucos������ʱ�����ٵ�λ	   
//	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
//	SysTick->LOAD=reload; 	//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
//#else
//	fac_ms=(u16)fac_us*1000;//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
//#endif
//}		


//void delay_ms(u16 nms)
//{	 		  	  
//	u32 temp;		   
//	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;           //��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
//	do
//	{
//		temp=SysTick->CTRL;
//	}
//	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
//	SysTick->VAL =0X00;       //��ռ�����	  	    
//} 
void delay(uint16_t x)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
	*/
	for (i = 0; i < x; i++);
}

