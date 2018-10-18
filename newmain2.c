#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char


//定义使能端   
sbit ENB=P0^0;
sbit ENA=P0^1;

//定义循迹模块
sbit lled=P1^3;
sbit mled=P1^2;
sbit rled=P1^1;

//定义驱动模块
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


void  gostraight()		//直走 左右轮前转
{
	left1=0;
	left2=1;
	right1=0;
	right2=1;
}
void tleft1()		//左转  左轮不转 右轮前转
{
	left1=0;
	left2=0;
	right1=0;
	right2=1;
}
void tright1()		//右转 右轮不转 左轮前转
{
	left1=0;
	left2=1;
	right1=0;
	right2=0;
}
/*void tleft2()		//原地左转  左轮后转 右轮前转
{
	left1=1;
	left2=0;
	right1=0;
	right2=1;
}
void tright2()		//原地右转 左轮前转 右轮后转
{
	left1=0;
	left2=1;
	right1=1;
	right2=0;
}*/
void stop()		//停止
{
	left1=0;
	left2=0;
	right1=0;
	right2=0;
}

void xunji()
{	

	if((lled==1)&& (mled==0) && (rled==1))		//中间检测到白线  前进
	{
		gostraight();
	}
	if((lled==0) &&(mled==1) && (rled==1))		//左侧检测到白线  左转
	{
		tleft1();
	}
	if((lled==1) && (mled==1) && (rled==0))		//右侧检测到白线  右转
	{
		tright1();
	}
	if((lled==0) && (mled==0) && (rled==0))		//全部检测到白线  前进
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

