/***************************************
*GB2312
*作者：创客海
*内容：点阵屏动态显示爱心
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

#define uchar unsigned char
#define uint unsigned int

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

unsigned char const heart_duan[] = {0x00, 0x6C, 0x92, 0x82, 0x44, 0x28, 0x10, 0x00}; //心的形状段
unsigned char const heart_wei[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};	 //分别对应相应的行列

/*******************************************************************************
 * 延时子函数 : Delaynms
 * 函数功能	 : 延时nms
 *******************************************************************************/
/*
void delayms(uint xms)
{
    unsigned char i, j;

    while (xms--)
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j)
                ;
        }
        while (--i);
    }
}
*/
void main()
{
    char i;

    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while (1)
    {
        P0 = 0xff; //取段码
        CS88 = 1;
        CS88 = 0;

        P0 = heart_duan[7 - i]; //取显示数据
        DUAN = 1;
        DUAN = 0;

        P0 = heart_wei[i]; //取段码
        CS88 = 1;
        CS88 = 0;

        // delayms(1); //扫描间隙延时
        i++;
        if (8 == i)
            i = 0;
    }
}

