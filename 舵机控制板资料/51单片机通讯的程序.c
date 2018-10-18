/*********************************************************************

* ��������STC89C51RC��Ƭ���н��й����ԣ���ȫ����������11.0592M��

*�û����Ը��ݾ���ͬ�����޸ģ������û�������PC��ͨ��PC�Ĵ��ڵ���

* ��������֤�����Ƿ���Ч

* P30: RXD

* P31: TXD

**********************************************************************/

#include <reg52.h>

#ifndef _DG_TYPE_

#define _DG_TYPE_

    typedef unsigned char uchar;

    typedef unsigned int uint;

#endif

#define CMD_LEN 75 // �����

#define CMD_TAG 1 // ��ʾ������

void UartInit();

void UartSendChar(unsigned char ch);

void UartSendStr(uchar *pStr);

void UartCharPro(uchar ch);

void UartCmdPro();

uchar g_ucCmd[CMD_LEN + 1] = {0};

uchar g_ucLen = 0; // �����

uchar g_ucCur = 1; // ���λ��

void main()

{

    UartInit();

    UartSendStr("#1P1500T100\r\n"); // S1�Ŷ����ʱ��100ms���ƶ���PWM1500��λ��

    // UartSendStr("#1GC2\r\n");  // ִ�е�һ�������飬ѭ��ִ��2��

    while(1);

}

/************************************************************

* Name: UartInit

* Func:

* ����ͨ�ų�ʼ��

* Para:

* uchar ch: ���͵��ַ�

* Return: None

***********************************************************/

void UartInit()

{

    SCON = 0x50; // SCON: serail mode 1, 8-bit UART

    TMOD |= 0x20; // TMOD: timer 1, mode 2, 8-bit reload

    PCON |= 0x80; // SMOD="1";

    TH1 = 0xFA; // Baud:9600 fosc="11".0592MHz

    TL1 = 0xFA;

    IE |= 0x90; // ʹ�ܴ����ж�

    TR1 = 1; // ����TIMER1

    EA = 1;

}

/************************************************************

* Name: UartSendChar

* Func:

* �򴮿ڷ���һ���ַ�

* Para:

* uchar ch: ���͵��ַ�

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

* �򴮿ڷ�����0��β���ַ���

* Para:

* uchar *pStr: ���͵��ַ�ָ��

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

* �ַ�������̺����������������ͨ�ַ�������ַ��жϻ��ԡ�

* Para:

* uchar ch: �жϵ��ַ�

* Return: None

***********************************************************/

void UartCharPro(uchar ch)

{

    P0 = ~ch;

    switch(ch) 

        {

            case '\b': // �˸��

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

            case '\r': // �س���

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

        default: // �����ַ�

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