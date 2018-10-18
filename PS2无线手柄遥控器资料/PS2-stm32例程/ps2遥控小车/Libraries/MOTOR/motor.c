#include "sys.h"
#include "motor.h"
/***********************************************************
Copyright (C), 2015-2025, ZYRobot.
湖南智宇科教设备有限公司
www.hnzhiyu.cn
File：TB6612驱动代码
Author：zhulin    Version:1.0     Data:2015/05/06
Description: Balance-STM32 TB6612FNG驱动代码
             
			 PC0~3接AIN1,AIN2,BIN1,BIN2;方向控制端口
			 PA6接PWMA;右电机（J1）速度控制 
			 PA7接PWMB;左电机（J2）速度控制
             
			 371电机与电机驱动TB6612FNG连接方式			
	         右电机（J1）：黄色连AO1;橙色连接AO2
             左电机（J2）：黄色连BO1;橙色连接BO2
	         
			 向前：从右侧看，两电机顺时针方向转动  正转
	         向后：从右侧看，两电机逆时针方向转动  反转  
***********************************************************/



//电机旋转方向控制信号端口初始化
//PC0~3推挽输出，输出高
void M_Init(void)
{
	RCC->APB2ENR|=1<<4;      //使能PORTC时钟
	GPIOC->CRL&=0XFFFF0000;
	GPIOC->CRL|=0X00003333;  //PC3~0推挽输出
	GPIOC->ODR|=0XF<<0;	     //PC3~0输出高电平
}

//定时器TIM3，PWM控制初始化,CH1（PA6）、CH2(PA7)。
//arr：自动重装值
//psc：时钟预分频数
//设置TIM3_PWM_Init(900,0); 
//设定自动装载值为900，不分频。PWM频率=72000/900=80Khz
void TIM3_PWM_Init(u16 arr,u16 psc) //arr设定计数器自动重装值   
                                    //psc预分频器不分频,psc=0
{
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能    
	  	
	GPIOA->CRL&=0X00FFFFFF;//PA6,7输出
	GPIOA->CRL|=0XBB000000;//复用功能输出 	  
	GPIOA->ODR|=3<<6;//PA6.7上拉	

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1模式	高电平有效	 
	TIM3->CCMR1|=1<<3; //CH1预装载使能
	TIM3->CCMR1|=6<<12;  //CH2 PWM1模式		 
	TIM3->CCMR1|=1<<11; //CH2预装载使能	   

	TIM3->CCER|=1<<0;   //OC1 输出使能
	TIM3->CCER|=1<<4;   //OC2 输出使能	   

	TIM3->CR1=0x0080;   //ARPE使能 
	TIM3->CR1|=0x01;    //使能定时器3 
}

//左右电机方向与速度控制
//motor1：右电机（J1）；motor2：左电机（J2）
//小于0时，向前，大于0时，向后    
//motor1/2的取值范围（-900~+900）；值的大小决定占空比的大小
//例motor1取值为90，则占空比为10%。
void Motor_Speed_Control(s16 motor1, s16 motor2)	 
{
    s16 motor1speed = 0, motor2speed = 0 ;	
    if(motor1>900)  motor1speed = 900;
	    else if (motor1<-900)  motor1speed = -900;
			else  motor1speed = motor1;
	if(motor2>900)  motor2speed = 900;
	    else if (motor2<-900)  motor2speed = -900;
			else  motor2speed = motor2;
	if(motor1speed == 0) //刹车
	{
		M1_1 = 1;
		M1_2 = 1;
		TIM3->CCR1 = 900;
	}
    	else if(motor1speed > 0)
		{
			M1_1 = 0;
			M1_2 = 1;
			TIM3->CCR1 = motor1speed;
		}
			else
			{
				M1_1 = 1;
				M1_2 = 0;
				TIM3->CCR1 = -motor1speed;
			}

	if(motor2speed == 0)
	{
		M2_1 = 1;
		M2_2 = 1;
		TIM3->CCR2 = 900;
	}
		else if(motor2speed > 0)
		{
			M2_1 = 0;
			M2_2 = 1;
			TIM3->CCR2 = motor2speed;
		}
			else
			{
				M2_1 = 1;
				M2_2 = 0;
				TIM3->CCR2 = -motor2speed;
			}
}




