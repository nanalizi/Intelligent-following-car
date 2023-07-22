#include "bsp_pid.h"
#include "timer.h"
#include "oled.h"
#include "stdio.h"
int SetPoint2; //设定目标 Desired Value 
int SetPoint4; //设定目标 Desired Value 

int balance(float now_Value,float SetPoint,float Balance_KP,float Balance_KD,float Balance_KI)
{                         
   float Bias;                       //倾角偏差
	 static float Last_Bias,D_Bias,I_Bias;    //PID相关变量
	 int balance;                      //PWM返回值 
	 Bias =SetPoint - now_Value;
	 I_Bias += Bias;
	 if(I_Bias>2000)
	 I_Bias=2000;
	 D_Bias=Bias-Last_Bias;            //求出偏差的微分 进行微分控制
	 balance = Balance_KP*Bias + D_Bias*Balance_KD + I_Bias*Balance_KI;   //===计算倾角控制的电机PWM  PD控制

   Last_Bias=Bias;                   //保持上一次的偏差
	 return balance;		
}


/*-----------------------------------------------------------------------
//4.递推平均滤波法（又称滑动平均滤波法）(能用！！！)
//方法：把连续取N个采样值看成一个队列，队列的长度固定为N
//         每次采样到一个新数据放入队尾,并扔掉原来队首的一次数据(先进先出原则)
//         把队列中的N个数据进行算术平均运算,就可获得新的滤波结果
//         N值的选取：流量，N=12；压力：N=4；液面，N=4~12；温度，N=1~4
//优点：对周期性干扰有良好的抑制作用，平滑度高；试用于高频振荡的系统
//缺点：灵敏度低；对偶然出现的脉冲性干扰的抑制作用较差，不适于脉冲干扰较严重的场合
//        比较浪费RAM（改进方法，减去的不是队首的值，而是上一次得到的平均值）
*/   
