#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "led.h"	
#include "pstwo.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
湖南智宇科教设备有限公司
www.hnzhiyu.cn
File：ps2遥控小车
Author：zhulin    Version:1.0     Data:2017/05/30
Description: ps2遥控小车，推动左边摇杆，前后移动，控制小车前进后退的速度
             推动右侧摇杆，左右移动，控制小车转弯的半径，小车转弯控制更
			 加灵活。
**********************************************************/	 	 	  
int main(void)
{								  
	s16 speed,speed1,speed2; 
	s16 swerve;           //转弯量	  
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口1初始化 
	TIM3_PWM_Init(900,0); //arr设定计数器自动重装值   
                                     //psc预分频器不分频,psc=0
	LED_Init();
	PS2_Init();
	M_Init();	   //电机旋转方向控制信号端口初始化	
	while(1)
	{
		if( !PS2_RedLight()) //判断手柄是否为红灯模式，是，指示灯LED点亮
		{
			delay_ms(50);	 //延时很重要不可去
			LED = 0;
			PS2_DataKey();	 //手柄按键捕获处理
			speed = PS2_AnologData(PSS_LY)-127;	   
			swerve = (PS2_AnologData(PSS_RX)-128)*2.3*((float)abs(speed)/128); //	speed取绝对值，	算数运算，得到转弯量。
			speed = -(PS2_AnologData(PSS_LY)-127)*7;	   //正：前进；  负：后退
			if(speed > 0) //向前
			{
				if(swerve < 0)//左转弯
				{
					speed1 = speed + swerve;
					speed2 = speed;
					
				}
				else          //右转弯
				{
					speed1 = speed; 
					speed2 = speed - swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else if(speed < 0)//向后
			{
				if(swerve < 0)//左转弯
				{
					speed1 = speed - swerve;
					speed2 = speed;
					Motor_Speed_Control(speed1, speed2);
				}
				else//右转弯
				{
					speed1 = speed; 
					speed2 = speed + swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else  Motor_Speed_Control(0, 0); //停止
		}
		else	//判断手柄不是红灯模式，指示灯LED熄灭
		{
			LED = 1;
			Motor_Speed_Control(0, 0);
			delay_ms(50);
		}

	}	 
}

























