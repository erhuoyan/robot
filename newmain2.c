#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char


//����ʹ�ܶ�   
sbit ENB=P0^0;
sbit ENA=P0^1;

//����ѭ��ģ��
sbit lled=P1^3;
sbit mled=P1^2;
sbit rled=P1^1;

//��������ģ��
sbit right2=P2^3;
sbit right1=P2^2;
sbit left2=P2^1;
sbit left1=P2^0;

uchar count=0;
uchar num=0;
uchar max=0;

void delay(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
	{
		for(j=110;j>0;j--);
	}
}


void  gostraight()		//ֱ�� ������ǰת
{
	left1=0;
	left2=1;
	right1=0;
	right2=1;
}
void tleft1()		//��ת  ���ֲ�ת ����ǰת
{
	left1=0;
	left2=0;
	right1=0;
	right2=1;
}
void tright1()		//��ת ���ֲ�ת ����ǰת
{
	left1=0;
	left2=1;
	right1=0;
	right2=0;
}
/*void tleft2()		//ԭ����ת  ���ֺ�ת ����ǰת
{
	left1=1;
	left2=0;
	right1=0;
	right2=1;
}
void tright2()		//ԭ����ת ����ǰת ���ֺ�ת
{
	left1=0;
	left2=1;
	right1=1;
	right2=0;
}*/
void stop()		//ֹͣ
{
	left1=0;
	left2=0;
	right1=0;
	right2=0;
}

void xunji()
{	

	if((lled==1)&& (mled==0) && (rled==1))		//�м��⵽����  ǰ��
	{
		gostraight();
	}
	if((lled==0) &&(mled==1) && (rled==1))		//����⵽����  ��ת
	{
		tleft1();
	}
	if((lled==1) && (mled==1) && (rled==0))		//�Ҳ��⵽����  ��ת
	{
		tright1();
	}
	if((lled==0) && (mled==0) && (rled==0))		//ȫ����⵽����  ǰ��
	{	
		if(max==2)
		{
			gostraight();
			delay(250);
			tright1();
			delay(800);
			max=0;
		}
		else 
		{
			max++;
			gostraight();
			delay(50);
		}
	}
	if((lled==1)&&(mled==1)&&(rled==1))
	{
		gostraight();
	}
	
	
}

void main()
{	
	ENA=1;
	ENB=1;
	max=0;
	while(1)
	{	
		xunji();
	}
}

