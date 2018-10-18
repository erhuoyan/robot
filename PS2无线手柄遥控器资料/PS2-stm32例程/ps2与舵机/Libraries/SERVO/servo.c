#include <stm32f10x_lib.h>
#include "servo.h"
#include "delay.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
www.hnzhiyu.cn
File：舵机驱动程序
Author：zhulin    Version:1.0     Data:2015/05/26
Description: 舵机驱动程序
             驱动端口TIM4_CH3（PB8）、TIM4_CH4(PB9)
**********************************************************/

//定时器TIM4，PWM控制初始化,CH3（PB8）、CH4(PB9)。
//arr：自动重装值
//psc：时钟预分频数
//设置TIM4_PWM_Init(20000,71); 
//设定自动装载值为20000，分频71+1。PWM频率=1000000/20000=50hz
void TIM4_PWM_Init(u16 arr,u16 psc) //arr设定计数器自动重装值   
                                    //psc预分频器不分频,psc=0
{
	RCC->APB1ENR|=1<<2;       //TIM4时钟使能    
	  	
	GPIOB->CRH&=0XFFFFFF00;//PA8,9输出
	GPIOB->CRH|=0X000000BB;//复用功能输出 	  
	GPIOB->ODR|=3<<8;//PA8.9上拉	

	TIM4->ARR=arr;//设定计数器自动重装值 
	TIM4->PSC=psc;//预分频器不分频
	
	TIM4->CCMR2|=6<<4;  //CH3 PWM1模式	高电平有效	 
	TIM4->CCMR2|=1<<3; //CH3预装载使能
	TIM4->CCMR2|=6<<12;  //CH4 PWM1模式		 
	TIM4->CCMR2|=1<<11; //CH4预装载使能	   

	TIM4->CCER|=1<<8;   //OC1 输出使能
	TIM4->CCER|=1<<12;   //OC2 输出使能	   

	TIM4->CR1=0x0080;   //ARPE使能 
	TIM4->CR1|=0x01;    //使能定时器3 
}

//舵机1驱动函数，控制端口TIM4_CH3（PB8）
void SERVO1(u8 degree)
{
	u16 k;
	k = 500 + degree * 11;
	TIM4->CCR3 = k;
}
//舵机2驱动函数，控制端口TIM4_CH4(PB9)
void SERVO2(u8 degree)
{
	u16 k;
	k = 500 + degree * 11;
	TIM4->CCR4 = k;
}












