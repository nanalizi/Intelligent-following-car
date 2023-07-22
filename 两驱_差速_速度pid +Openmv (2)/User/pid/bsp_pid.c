#include "bsp_pid.h"
#include "timer.h"
#include "oled.h"
#include "stdio.h"
int SetPoint2; //�趨Ŀ�� Desired Value 
int SetPoint4; //�趨Ŀ�� Desired Value 

int balance(float now_Value,float SetPoint,float Balance_KP,float Balance_KD,float Balance_KI)
{                         
   float Bias;                       //���ƫ��
	 static float Last_Bias,D_Bias,I_Bias;    //PID��ر���
	 int balance;                      //PWM����ֵ 
	 Bias =SetPoint - now_Value;
	 I_Bias += Bias;
	 if(I_Bias>2000)
	 I_Bias=2000;
	 D_Bias=Bias-Last_Bias;            //���ƫ���΢�� ����΢�ֿ���
	 balance = Balance_KP*Bias + D_Bias*Balance_KD + I_Bias*Balance_KI;   //===������ǿ��Ƶĵ��PWM  PD����

   Last_Bias=Bias;                   //������һ�ε�ƫ��
	 return balance;		
}


/*-----------------------------------------------------------------------
//4.����ƽ���˲������ֳƻ���ƽ���˲�����(���ã�����)
//������������ȡN������ֵ����һ�����У����еĳ��ȹ̶�ΪN
//         ÿ�β�����һ�������ݷ����β,���ӵ�ԭ�����׵�һ������(�Ƚ��ȳ�ԭ��)
//         �Ѷ����е�N�����ݽ�������ƽ������,�Ϳɻ���µ��˲����
//         Nֵ��ѡȡ��������N=12��ѹ����N=4��Һ�棬N=4~12���¶ȣ�N=1~4
//�ŵ㣺�������Ը��������õ��������ã�ƽ���ȸߣ������ڸ�Ƶ�񵴵�ϵͳ
//ȱ�㣺�����ȵͣ���żȻ���ֵ������Ը��ŵ��������ýϲ������������Ž����صĳ���
//        �Ƚ��˷�RAM���Ľ���������ȥ�Ĳ��Ƕ��׵�ֵ��������һ�εõ���ƽ��ֵ��
*/   
