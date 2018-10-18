#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "led.h"	
#include "pstwo.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
��������ƽ��豸���޹�˾
www.hnzhiyu.cn
File��ps2ң��С��
Author��zhulin    Version:1.0     Data:2017/05/30
Description: ps2ң��С�����ƶ����ҡ�ˣ�ǰ���ƶ�������С��ǰ�����˵��ٶ�
             �ƶ��Ҳ�ҡ�ˣ������ƶ�������С��ת��İ뾶��С��ת����Ƹ�
			 ����
**********************************************************/	 	 	  
int main(void)
{								  
	s16 speed,speed1,speed2; 
	s16 swerve;           //ת����	  
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //����1��ʼ�� 
	TIM3_PWM_Init(900,0); //arr�趨�������Զ���װֵ   
                                     //pscԤ��Ƶ������Ƶ,psc=0
	LED_Init();
	PS2_Init();
	M_Init();	   //�����ת��������źŶ˿ڳ�ʼ��	
	while(1)
	{
		if( !PS2_RedLight()) //�ж��ֱ��Ƿ�Ϊ���ģʽ���ǣ�ָʾ��LED����
		{
			delay_ms(50);	 //��ʱ����Ҫ����ȥ
			LED = 0;
			PS2_DataKey();	 //�ֱ�����������
			speed = PS2_AnologData(PSS_LY)-127;	   
			swerve = (PS2_AnologData(PSS_RX)-128)*2.3*((float)abs(speed)/128); //	speedȡ����ֵ��	�������㣬�õ�ת������
			speed = -(PS2_AnologData(PSS_LY)-127)*7;	   //����ǰ����  ��������
			if(speed > 0) //��ǰ
			{
				if(swerve < 0)//��ת��
				{
					speed1 = speed + swerve;
					speed2 = speed;
					
				}
				else          //��ת��
				{
					speed1 = speed; 
					speed2 = speed - swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else if(speed < 0)//���
			{
				if(swerve < 0)//��ת��
				{
					speed1 = speed - swerve;
					speed2 = speed;
					Motor_Speed_Control(speed1, speed2);
				}
				else//��ת��
				{
					speed1 = speed; 
					speed2 = speed + swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else  Motor_Speed_Control(0, 0); //ֹͣ
		}
		else	//�ж��ֱ����Ǻ��ģʽ��ָʾ��LEDϨ��
		{
			LED = 1;
			Motor_Speed_Control(0, 0);
			delay_ms(50);
		}

	}	 
}

























