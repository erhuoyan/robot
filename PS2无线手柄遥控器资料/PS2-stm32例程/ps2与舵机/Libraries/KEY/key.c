#include <stm32f10x_lib.h>
#include "key.h"
#include "delay.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：KEY驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 KEY驱动代码
**********************************************************/		  
								    
//按键初始化函数
//PA5 设置成输入
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;      //使能PORTA时钟
	GPIOA->CRL&=0XFF0FFFFF;  //PA5设置成输入	  
	GPIOA->CRL|=0X00800000;   	   
	GPIOA->ODR|=1<<5;	     //PA5上拉,
	
} 
//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY按下
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志	
	if(key_up&&KEY==0)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY==0)
		{
			return 1;
		}
	}
	else if(KEY==1)key_up=1; 	    
	return 0;// 无按键按下
}




















