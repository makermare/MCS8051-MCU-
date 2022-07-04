/***************************************
*GB2312
*作者：创客海
*内容：矩阵按键控制数码管静态显示-交错扫描法
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>

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

void Delay100ms()		//@11.0592MHz 延时100毫秒软件消抖
{
    unsigned char i, j;
    i = 180;
    j = 73;
    do
    {
        while (--j);
    }
    while (--i);
}

void matrixkeyscan()//4*4矩阵按键扫描
{
    P3 = 0xf0;//首先进行列扫描1111 0000
    if(P3 != 0xf0)//判断按键是否被按下
    {
        Delay100ms();//抖动消抖
        if(P3 != 0xf0)//判断按键是否被按下，而不是误触
        {
            switch (P3)//判断哪一列被按下
            {
            case 0xe0:
                key = 0;
                break;//第0列被按下
            case 0xd0:
                key = 1;
                break;//第1列被按下
            case 0xb0:
                key = 2;
                break;//第2列被按下
            case 0x70:
                key = 3;
                break;//第3列被按下
            }

            P3 = 0x0f;//接着进行行扫描 0000 1111
            switch (P3)//判断哪一行被按下
            {
            case 0x0e:
                key = key;
                break;//第0行被按下
            case 0x0d:
                key = key+4;
                break;//第1行被按下
            case 0x0b:
                key = key+8;
                break;//第2行被按下
            case 0x07:
                key = key+12;
                break;//第3行被按下
            }
            while(P3 != 0x0f);//按键松开检测
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