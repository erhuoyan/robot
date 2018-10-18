#include <stm32f10x_lib.h>	   
#include "led.h"

/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
��������ƽ��豸���޹�˾
www.hnzhiyu.cn
File��LED��������
Author��zhulin    Version:1.0     Data:2015/05/06
Description: Balance-STM32 LED��������
**********************************************************/	   

//��ʼ��PD2Ϊ�����.��ʹ�˿�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	 
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2�������
	GPIOD->ODR|=1<<2;      //PD.2����� 
}




