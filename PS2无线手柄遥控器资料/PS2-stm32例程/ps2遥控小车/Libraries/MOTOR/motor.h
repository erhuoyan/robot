#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
/***********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：TB6612驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 TB6612FNG驱动代码
             
			 PC0~3接AIN1,AIN2,BIN1,BIN2;方向控制端口
			 PA6接PWMA;右电机（J1）速度控制 
			 PA7接PWMB;左电机（J2）速度控制
             
			 371电机与电机驱动TB6612FNG连接方式			
	         右电机（J1）：黄色连AO1;橙色连接AO2
             左电机（J2）：黄色连BO1;橙色连接BO2
	         
			 向前：从右侧看，两电机顺时针方向转动
	         向后：从右侧看，两电机逆时针方向转动	  
***********************************************************/

#define M1_1 PCout(0)
#define M1_2 PCout(1)
#define M2_1 PCout(2)
#define M2_2 PCout(3)


void M_Init(void);	   //电机旋转方向控制信号端口初始化
void TIM3_PWM_Init(u16 arr,u16 psc); //arr设定计数器自动重装值   
                                     //psc预分频器不分频,psc=0
void Motor_Speed_Control(s16 motor1, s16 motor2);  //左右电机方向与速度控制	
#endif






