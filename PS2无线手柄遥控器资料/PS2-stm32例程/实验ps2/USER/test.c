#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "pstwo.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
湖南智宇科教设备有限公司
www.hnzhiyu.cn
File：ps2应用程序
Author：zhulin    Version:1.0     Data:2017/05/06
Description: ps2应用程序
**********************************************************/	 	 	  
int main(void)
{								  
	u8 key;	  
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口1初始化 
	PS2_Init();
	while(1)
	{
	
		key=PS2_DataKey();
		if(key!=0)                   //有按键按下
    	{
			printf("  \r\n   %d  is  pressed  \r\n",key);
    	}
		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
       delay_ms(50);
	}	 
}

























