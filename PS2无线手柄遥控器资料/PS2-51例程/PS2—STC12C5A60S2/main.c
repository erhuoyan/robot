#include <STC12C5A.H>  
#include <stdio.h>
#include <absacc.h>
#include <intrins.h>
/*********************************************************
Copyright (C), 2015-2025, ZYRobot.
��������ƽ��豸���޹�˾
www.hnzhiyu.cn
File��ps2���Գ���
Author��zhulin    Version:1.0     Data:2017/05/30

**********************************************************/	 

#define  Fosc  22118400     //����Ƶ��

#define uchar unsigned char
#define uint unsigned int

sbit  Speaker=P1^1;
sbit  Led=P1^0;

sbit  DATA=P3^4;	//�ֱ��ӿ�
sbit  CMND=P3^5;
sbit  ATT=P3^6;
sbit  CLK=P3^7;

/********�ֱ��������*********/
uchar code scan[9]={0x01,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uchar  out[9];  
/********************************************************************
* ���� : void delayms(uint xms)
* ���� : ��ʱ
* ���� : ��
* ��� : ��
***********************************************************************/
void delayms(uint xms)
 {
   uint i,j;
   for(i=xms;i>0;i--)
      for(j=1700;j>0;j--);
 }
/********************************************************************
* ���� : void uart_init()
* ���� : ��������
* ���� : ��
* ��� : ��
***********************************************************************/
void uart_init()
{
	SCON=0x50;//8λ���ͣ�����żУ��λ
	BRT=0xfa;//BRT=256-Fosc/32/9600/12;
	AUXR=0x91;//ѡ�񲢴򿪶���������
    EA=1; // �����жϿ���
    ES=1; // �򿪴����жϿ��� 
}
/********************************************************************
* ���� : uart_sendata(uchar n)
* ���� : �����ֽ�
* ���� : ��
* ��� : ��
***********************************************************************/
void uart_sendata(uchar n)
{	
    ES=0;
	TI=0;
    SBUF = n;
	while(!TI);                   //���������ϣ�Ӳ������λTI
	TI=0;
	ES=1;				
}

void delay(uint n)  //delay(x)=(2.5+x)us; 
{
	uint i;
	for(i=0;i<n;i++) _nop_();       
//		_nop_();//ÿ��_nop_();���0.1΢��	
}
void psin(uchar command)//�ֱ������ӳ���
{
    uchar i;
    for(i=0;i<=7;i++)     //��λ����     
    {
	 if(command&0x01)	 //��if��5�������ʱ1us
        CMND=1;
     else
        CMND=0;
     command=command>>1;
	 	_nop_();	
		_nop_();
     CLK=0;
     delay(10); 
     CLK=1;
	 delay(3);
    }
	CMND=1;
}
uchar scanout(uchar command)//�ֱ������ӳ���
{
    uchar i,j=1;
	uchar res=0; 
    for(i=0;i<=7;i++)     //��λ����     
    {
	 if(command&0x01)
        CMND=1;
     else
        CMND=0;
     command=command>>1;
	 	_nop_();	
		_nop_();
     CLK=0;
     delay(10);
	 if(DATA) res=res+j;
     j=j<<1; 
	 CLK=1;
	 delay(3);		 
    }
    CMND=1;
    return res;	
}
 void Read_PS2(void)//�ֱ���ȡ����
{
	 uchar i;
     ATT=0;
	 for(i=0;i<9;i++)	//ɨ�谴��
        {
         out[i]=scanout(scan[i]);	
		 } 
     ATT=1;	    	 
   	 for(i=0;i<9;i++)
        {
		 uart_sendata(0x30);
		 uart_sendata(0x78);
		 if(out[i]/16<10) uart_sendata(out[i]/16+0x30);
		 else uart_sendata(out[i]/16+0x37);
		 if(out[i]%16<10) uart_sendata(out[i]%16+0x30);
		 else uart_sendata(out[i]%16+0x37);
         uart_sendata(' ');
		 uart_sendata(' ');
		}
	uart_sendata(0x0d);
    uart_sendata(0x0a);		  
} 	 	 	 	 	 
void main()
{ 
	delayms(500);

    Speaker=0;
    Led=1;

	P4SW=0x70;	 //P4����������
	uart_init();

while(1)
	 {

	 Read_PS2(); 
	 delayms(500);
	}

} 

/*****************************PS2ң����˵��
out[3]==0xEF//��4����������
out[3]==0xBF//��4����������
out[3]==0x7F//��4����������
out[3]==0xDF//��4����������

out[4]==0xEF//��4����������
out[4]==0xBF//��4����������
out[4]==0x7F//��4����������
out[4]==0xDF//��4����������

out[4]==0xFB//��1,2��������1
out[4]==0xFE//��1,2��������2
out[4]==0xF7//��1,2��������1
out[4]==0xFD//��1,2��������2

������MODE���ֱ�MODE LED������ʱ
out[7] 00����80����FF ��ҡ�˴�����
out[8] 00����7F����FF ��ҡ�˴��ϵ���
out[5] 00����80����FF ��ҡ�˴�����
out[6] 00����7F����FF ��ҡ�˴��ϵ���
���ֱ�MODE LED�Ʋ���ʱ���ֱ�����ͬ�������İ���
*******************************/