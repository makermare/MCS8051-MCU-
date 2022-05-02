/***************************************
*GB2312
*���ߣ����ͺ�
*���ݣ�����������Ϊ������
*ʵ��壺�����51��Ƭ��ʵ���
*��Ƭ���ͺţ�STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit K1 = P3^0;//λ������P3.0����Ϊ����K1
sbit K2 = P3^1;//λ������P3.1����Ϊ����K2
sbit K3 = P3^2;//λ������P3.2����Ϊ����K3
sbit K4 = P3^3;//λ������P3.3����Ϊ����K4
sbit K5 = P3^4;//λ������P3.4����Ϊ����K5
sbit K6 = P3^5;//λ������P3.5����Ϊ����K6
sbit K7 = P3^6;//λ������P3.6����Ϊ����K7
sbit K8 = P3^7;//λ������P3.7����Ϊ����K8

sbit FM = P2^3;
sbit JDQ = P3^7;

sbit LCD_EN = P2 ^ 5;     // λ������LCD1602��12864��Һ����ʹ�ܶ�
sbit DS1302_RST = P2 ^ 4; // λ������DS1302����ʪ�ȴ�����ʹ�ܶ�
sbit DUAN = P2 ^ 0;       // λ������������ֶ����������ʹ�ܶ�
sbit WEI = P2 ^ 1;        // λ�����������λ�����������ʹ�ܶ�
sbit CS88 = P2 ^ 2;       // λ�����˵��������е���������ʹ�ܶ�

void Delay1911us();
void Delay1702us();
void Delay1516us();
void Delay1431us();
void Delay1275us();
void Delay1136us();
void Delay1012us();

void main()
{
    int i = 0;

    LCD_EN = 0;           //�������������Һ��������رգ�����ʵ����ܵ�Ӱ��
    DS1302_RST = 0;       //�رտ������ϵ���ʪ�ȴ�����������ʵ����ܵ�Ӱ��
    DUAN = 0;             //��ס������ֶ����������ʹ�ܶ�
    WEI = 0;              //��ס�����λ�����������ʹ�ܶ�
    CS88 = 0;             //��ס���������е���������ʹ�ܶ�

    while (1)
    {
        if (K1 == 0)
        {
            i = 50;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1911us();
                FM = 0; //�͵�ƽ������
                Delay1911us();
            }
        }
        else if (K2 == 0)
        {
            i = 54;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1702us();
                FM = 0; //�͵�ƽ������
                Delay1702us();
            }
        }
        else if (K3 == 0)
        {
            i = 59;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1516us();
                FM = 0; //�͵�ƽ������
                Delay1516us();
            }
        }
        else if (K4 == 0)
        {
            i = 66;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1431us();
                FM = 0; //�͵�ƽ������
                Delay1431us();
            }
        }
        else if (K5 == 0)
        {
            i = 74;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1275us();
                FM = 0; //�͵�ƽ������
                Delay1275us();
            }
        }
        else if (K6 == 0)
        {
            i = 83;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1136us();
                FM = 0; //�͵�ƽ������
                Delay1136us();
            }
        }
        else if (K7 == 0)
        {
            i = 83;
            while (i--)
            {
                FM = 1; //�ߵ�ƽ��������
                Delay1012us();
                FM = 0; //�͵�ƽ������
                Delay1012us();
            }
        }
    }
}

/*------------------------------------------------
 ��ȷ��ʱ����
------------------------------------------------*/
void Delay1911us() //@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 4;
    j = 105;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1702us() //@11.0592MHz
{
    unsigned char i, j;

    i = 4;
    j = 9;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1516us() //@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 3;
    j = 180;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1431us() //@11.0592MHz
{
    unsigned char i, j;

    i = 3;
    j = 141;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1275us() //@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 3;
    j = 69;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1136us() //@11.0592MHz
{
    unsigned char i, j;

    i = 3;
    j = 5;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
void Delay1012us() //@11.0592MHz
{
    unsigned char i, j;

    i = 2;
    j = 205;
    do
    {
        while (--j)
            ;
    }
    while (--i);
}
