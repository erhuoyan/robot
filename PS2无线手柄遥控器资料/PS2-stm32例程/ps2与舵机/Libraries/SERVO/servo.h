#include <stm32f10x_lib.h>
#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File�������������
Author��pinggai    Version:1.0     Data:2015/05/26
Description: ����������� 
             �����˿�TIM4_CH3��PB8����TIM4_CH4(PB9)
**********************************************************/	

//�ӵأ���ɫ �� ��ɫ
//��Դ����ɫ
//�źţ���ɫ �� ��ɫ
//��������źŶ˿ڶ���


void TIM4_PWM_Init(u16 arr,u16 psc);
void SERVO1(u8 degree);
void SERVO2(u8 degree);
#endif








