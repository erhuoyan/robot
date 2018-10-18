#include <stm32f10x_lib.h>
#include "key.h"
#include "delay.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File��KEY��������
Author��pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 KEY��������
**********************************************************/		  
								    
//������ʼ������
//PA5 ���ó�����
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;      //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFF0FFFFF;  //PA5���ó�����	  
	GPIOA->CRL|=0X00800000;   	   
	GPIOA->ODR|=1<<5;	     //PA5����,
	
} 
//����������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY����
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־	
	if(key_up&&KEY==0)
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY==0)
		{
			return 1;
		}
	}
	else if(KEY==1)key_up=1; 	    
	return 0;// �ް�������
}




















