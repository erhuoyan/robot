#include <stm32f10x_lib.h>
#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：舵机驱动程序
Author：pinggai    Version:1.0     Data:2015/05/26
Description: 舵机驱动程序 
             驱动端口TIM4_CH3（PB8）、TIM4_CH4(PB9)
**********************************************************/	

//接地：棕色 或 黑色
//电源：红色
//信号：橙色 或 白色
//舵机控制信号端口定义


void TIM4_PWM_Init(u16 arr,u16 psc);
void SERVO1(u8 degree);
void SERVO2(u8 degree);
#endif








