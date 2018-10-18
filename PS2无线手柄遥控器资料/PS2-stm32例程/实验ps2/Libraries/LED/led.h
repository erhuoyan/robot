#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：LED驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 LED驱动代码
**********************************************************/	

//LED端口定义

#define LED PDout(2) // PD2	

void LED_Init(void); //端口初始化		 				    
#endif

















