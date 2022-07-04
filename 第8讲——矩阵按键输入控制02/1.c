/***************************************
*GB2312
*作者：创客海
*内容：矩阵按键控制数码管静态显示-逐行扫描法
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

#define uchar unsigned char
#define uint  unsigned int

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

uchar key = 16;//全局变量，存放按键的键码

//八位共阴数码管段选表
unsigned char code table[]=
{
// 0      1     2     3
    0x3f, 0x06, 0x5b, 0x4f,
// 4      5     6     7
    0x66, 0x6d, 0x7d, 0x07,
// 8      9     A     B
    0x7f, 0x6f, 0x77, 0x7c,
// C      D     E     F     熄灭
    0x39, 0x5e, 0x79, 0x71, 0x00
};

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

void matrixkeyscan()
{
    uchar temp;

    P3 = 0xfe; //发送第1行
    temp = P3; //读取列
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 0;
                break;
            case 0xd0: // 11011110
                key = 1;
                break;
            case 0xb0:
                key = 2;
                break;
            case 0x70:
                key = 3;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xfd; //发送第2行
    temp = P3; //读取列
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 4;
                break;
            case 0xd0: // 11011110
                key = 5;
                break;
            case 0xb0:
                key = 6;
                break;
            case 0x70:
                key = 7;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xfb; //发送第3行
    temp = P3; //读取列
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 8;
                break;
            case 0xd0: // 11011110
                key = 9;
                break;
            case 0xb0:
                key = 10;
                break;
            case 0x70:
                key = 11;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xf7; //发送第4行
    temp = P3; //读取列
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 12;
                break;
            case 0xd0: // 11011110
                key = 13;
                break;
            case 0xb0:
                key = 14;
                break;
            case 0x70:
                key = 15;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
}

void main()
{
    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    P0  = 0x00;
    WEI = 1;
    WEI = 0;

    while(1)
    {
        matrixkeyscan();  //不停调用键盘扫描程序
        P0 = table[key];  //输送段选值，用于显示
        DUAN = 1;
        DUAN = 0;
    }
}