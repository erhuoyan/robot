/*********************************************************************

* 本程序在STC89C51RC单片机中进行过测试，完全正常（晶振11.0592M）

*用户可以根据晶振不同自行修改，建议用户先连接PC，通过PC的串口调试

* 助手来验证程序是否有效

* P30: RXD

* P31: TXD

**********************************************************************/

#include <reg52.h>

#ifndef _DG_TYPE_

#define _DG_TYPE_

    typedef unsigned char uchar;

    typedef unsigned int uint;

#endif

#define CMD_LEN 75 // 命令长度

#define CMD_TAG 1 // 提示符长度

void UartInit();

void UartSendChar(unsigned char ch);

void UartSendStr(uchar *pStr);

void UartCharPro(uchar ch);

void UartCmdPro();

uchar g_ucCmd[CMD_LEN + 1] = {0};

uchar g_ucLen = 0; // 命令长度

uchar g_ucCur = 1; // 光标位置

void main()

{

    UartInit();

    UartSendStr("#1P1500T100\r\n"); // S1号舵机在时间100ms内移动到PWM1500的位置

    // UartSendStr("#1GC2\r\n");  // 执行第一个动作组，循环执行2次

    while(1);

}

/************************************************************

* Name: UartInit

* Func:

* 串行通信初始化

* Para:

* uchar ch: 发送的字符

* Return: None

***********************************************************/

void UartInit()

{

    SCON = 0x50; // SCON: serail mode 1, 8-bit UART

    TMOD |= 0x20; // TMOD: timer 1, mode 2, 8-bit reload

    PCON |= 0x80; // SMOD="1";

    TH1 = 0xFA; // Baud:9600 fosc="11".0592MHz

    TL1 = 0xFA;

    IE |= 0x90; // 使能串行中断

    TR1 = 1; // 启动TIMER1

    EA = 1;

}

/************************************************************

* Name: UartSendChar

* Func:

* 向串口发送一个字符

* Para:

* uchar ch: 发送的字符

* Return: None

***********************************************************/

void UartSendChar(unsigned char ch)

{

    SBUF = ch;

    while(TI==0);

    TI=0;

}

/************************************************************

* Name: UartSendStr

* Func:

* 向串口发送以0结尾的字符串

* Para:

* uchar *pStr: 发送的字符指针

* Return: None

***********************************************************/

void UartSendStr(uchar *pStr)

{

    while(*pStr != 0)

     {

        SBUF = *pStr++;

        while(TI==0);

        TI=0;

        }

}

void UartSrv() interrupt 4

{

unsigned char ch;

ch = SBUF;

if(RI)

    {

        RI = 0;

        //UartSendChar(ch);

        //P0 = ~ch;

        UartCharPro(ch);

    }

}

/************************************************************

* Name: UartCharPro

* Func:

* 字符处理过程函数。根据输入的普通字符或控制字符判断回显。

* Para:

* uchar ch: 判断的字符

* Return: None

***********************************************************/

void UartCharPro(uchar ch)

{

    P0 = ~ch;

    switch(ch) 

        {

            case '\b': // 退格键

            if(g_ucCur > CMD_TAG) {

            UartSendChar('\b');

            UartSendChar(' ');

            UartSendChar('\b');

            if(g_ucLen) {

                                    g_ucLen--;

                                }

            g_ucCur--;

                }

            break;

            case '\r': // 回车键

            UartSendChar('\r');

            UartSendChar('\n');

            g_ucCmd[g_ucLen] = 0;

            UartSendStr(g_ucCmd);

            UartSendChar('\r');

        UartSendChar('\n');

        UartSendChar('>');

        g_ucLen = 0;

        g_ucCur = 1;

        break;

        default: // 其它字符

        UartSendChar(ch);

        g_ucCur++;

        if(g_ucLen < CMD_LEN) {

            g_ucCmd[g_ucLen++] = ch;

            }

        else {

            g_ucCmd[g_ucLen] = 0;

            }

        }

}