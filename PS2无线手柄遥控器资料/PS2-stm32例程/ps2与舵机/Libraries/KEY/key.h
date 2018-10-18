#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
/*********************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File：KEY驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 KEY驱动代码
**********************************************************/	 

//按键端口初始化
#define KEY PAin(5)   //PA5

	 
void KEY_Init(void); //IO初始化
u8 KEY_Scan(void);   //按键扫描函数					    
#endif
