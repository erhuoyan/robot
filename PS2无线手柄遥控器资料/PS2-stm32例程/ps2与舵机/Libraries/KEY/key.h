#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
/*********************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File��KEY��������
Author��pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 KEY��������
**********************************************************/	 

//�����˿ڳ�ʼ��
#define KEY PAin(5)   //PA5

	 
void KEY_Init(void); //IO��ʼ��
u8 KEY_Scan(void);   //����ɨ�躯��					    
#endif
