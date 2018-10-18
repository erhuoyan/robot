#include "sys.h"
#include "motor.h"
/***********************************************************
Copyright (C), 2015-2025, ZYRobot.
��������ƽ��豸���޹�˾
www.hnzhiyu.cn
File��TB6612��������
Author��zhulin    Version:1.0     Data:2015/05/06
Description: Balance-STM32 TB6612FNG��������
             
			 PC0~3��AIN1,AIN2,BIN1,BIN2;������ƶ˿�
			 PA6��PWMA;�ҵ����J1���ٶȿ��� 
			 PA7��PWMB;������J2���ٶȿ���
             
			 371�����������TB6612FNG���ӷ�ʽ			
	         �ҵ����J1������ɫ��AO1;��ɫ����AO2
             ������J2������ɫ��BO1;��ɫ����BO2
	         
			 ��ǰ�����Ҳ࿴�������˳ʱ�뷽��ת��  ��ת
	         ��󣺴��Ҳ࿴���������ʱ�뷽��ת��  ��ת  
***********************************************************/



//�����ת��������źŶ˿ڳ�ʼ��
//PC0~3��������������
void M_Init(void)
{
	RCC->APB2ENR|=1<<4;      //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFF0000;
	GPIOC->CRL|=0X00003333;  //PC3~0�������
	GPIOC->ODR|=0XF<<0;	     //PC3~0����ߵ�ƽ
}

//��ʱ��TIM3��PWM���Ƴ�ʼ��,CH1��PA6����CH2(PA7)��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//����TIM3_PWM_Init(900,0); 
//�趨�Զ�װ��ֵΪ900������Ƶ��PWMƵ��=72000/900=80Khz
void TIM3_PWM_Init(u16 arr,u16 psc) //arr�趨�������Զ���װֵ   
                                    //pscԤ��Ƶ������Ƶ,psc=0
{
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    
	  	
	GPIOA->CRL&=0X00FFFFFF;//PA6,7���
	GPIOA->CRL|=0XBB000000;//���ù������ 	  
	GPIOA->ODR|=3<<6;//PA6.7����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1ģʽ	�ߵ�ƽ��Ч	 
	TIM3->CCMR1|=1<<3; //CH1Ԥװ��ʹ��
	TIM3->CCMR1|=6<<12;  //CH2 PWM1ģʽ		 
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   

	TIM3->CCER|=1<<0;   //OC1 ���ʹ��
	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	   

	TIM3->CR1=0x0080;   //ARPEʹ�� 
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
}

//���ҵ���������ٶȿ���
//motor1���ҵ����J1����motor2��������J2��
//С��0ʱ����ǰ������0ʱ�����    
//motor1/2��ȡֵ��Χ��-900~+900����ֵ�Ĵ�С����ռ�ձȵĴ�С
//��motor1ȡֵΪ90����ռ�ձ�Ϊ10%��
void Motor_Speed_Control(s16 motor1, s16 motor2)	 
{
    s16 motor1speed = 0, motor2speed = 0 ;	
    if(motor1>900)  motor1speed = 900;
	    else if (motor1<-900)  motor1speed = -900;
			else  motor1speed = motor1;
	if(motor2>900)  motor2speed = 900;
	    else if (motor2<-900)  motor2speed = -900;
			else  motor2speed = motor2;
	if(motor1speed == 0) //ɲ��
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




