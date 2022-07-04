/***************************************
*GB2312
*作者：创客海
*内容：独立按键作为电子琴
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit K1 = P3^0;//位声明了P3.0引脚为按键K1
sbit K2 = P3^1;//位声明了P3.1引脚为按键K2
sbit K3 = P3^2;//位声明了P3.2引脚为按键K3
sbit K4 = P3^3;//位声明了P3.3引脚为按键K4
sbit K5 = P3^4;//位声明了P3.4引脚为按键K5
sbit K6 = P3^5;//位声明了P3.5引脚为按键K6
sbit K7 = P3^6;//位声明了P3.6引脚为按键K7
sbit K8 = P3^7;//位声明了P3.7引脚为按键K8

sbit FM = P2^3;
sbit JDQ = P3^7;

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

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

    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while (1)
    {
        if (K1 == 0)
        {
            i = 50;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1911us();
                FM = 0; //低电平发声音
                Delay1911us();
            }
        }
        else if (K2 == 0)
        {
            i = 54;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1702us();
                FM = 0; //低电平发声音
                Delay1702us();
            }
        }
        else if (K3 == 0)
        {
            i = 59;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1516us();
                FM = 0; //低电平发声音
                Delay1516us();
            }
        }
        else if (K4 == 0)
        {
            i = 66;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1431us();
                FM = 0; //低电平发声音
                Delay1431us();
            }
        }
        else if (K5 == 0)
        {
            i = 74;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1275us();
                FM = 0; //低电平发声音
                Delay1275us();
            }
        }
        else if (K6 == 0)
        {
            i = 83;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1136us();
                FM = 0; //低电平发声音
                Delay1136us();
            }
        }
        else if (K7 == 0)
        {
            i = 83;
            while (i--)
            {
                FM = 1; //高电平不发声音
                Delay1012us();
                FM = 0; //低电平发声音
                Delay1012us();
            }
        }
    }
}

/*------------------------------------------------
 精确延时函数
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
