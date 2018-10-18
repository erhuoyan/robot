#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "pstwo.h"
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
��������ƽ��豸���޹�˾
www.hnzhiyu.cn
File��ps2Ӧ�ó���
Author��zhulin    Version:1.0     Data:2017/05/06
Description: ps2Ӧ�ó���
**********************************************************/	 	 	  
int main(void)
{								  
	u8 key;	  
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //����1��ʼ�� 
	PS2_Init();
	while(1)
	{
	
		key=PS2_DataKey();
		if(key!=0)                   //�а�������
    	{
			printf("  \r\n   %d  is  pressed  \r\n",key);
    	}
		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
       delay_ms(50);
	}	 
}

























