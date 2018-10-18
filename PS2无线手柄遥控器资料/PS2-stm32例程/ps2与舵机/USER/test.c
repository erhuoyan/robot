#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "led.h"	
#include "pstwo.h"
#include "servo.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
湖南智宇科教设备有限公司
www.hnzhiyu.cn
File：PS2控制舵机
Author：zhulin    Version:1.0     Data:2017/05/06
Description: PS2控制舵机
**********************************************************/	 	 	  
int main(void)
{								  
//	u8 key;
	u8 angle;  
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口1初始化 
	LED_Init();
	PS2_Init();

	TIM4_PWM_Init(20000,71); //TIM4初始化，产生50HZ PWM
	while(1)
	{
		PS2_ClearData();   //清除缓存
		PS2_ReadData();	   //读数据
		angle = (PS2_AnologData(PSS_RX)/5)*3+15;  //只产生15°~165°的运动范围
		SERVO1(angle);
		delay_ms(50);
    }
}

























