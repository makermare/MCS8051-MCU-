/***************************************
*GB2312
*作者：创客海
*内容：点阵屏动态显示人字
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

//0xDF,0xEF,0xF7,0xFB,0xF5,0xEF,0xDF,0xFF[纵向取模+字节倒序]UC
//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00【纵向取模】UA
/*
//显示一个人字，注意方向
void main()
{
    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while(1)
    {
        P0 = 0x80;//0x80,0x40,0x20,0x10,0x08,0x04,0x02;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;//0xdf,0xef,0xf7,oxfb,0xf5,0xef,oxdf;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;//点亮第一个发光管

        P0 = 0x40;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;//点亮第二个发光管

        P0 = 0x20;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf7;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x10;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfb;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf5;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x04;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x02;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;
    }
}
*/
/*
//显示一个人字，注意方向
void main()
{
    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while(1)
    {
        P0 = 0x04;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0x7f;//0x7f,0xbf,oxdf,oxef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xbf;//0x7f,0xbf,oxdf,oxef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x10;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x20;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x50;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf7;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfb;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x04;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfd;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

    }
}
*/
//显示一个人字的动画
void main()
{
    unsigned char code xqd[]= {0x04,0x08,0x10,0x20,0x50,0x08,0x04,0X00};
    unsigned char i = 0;
    unsigned char a = 0x7f;
    unsigned int j = 0;

    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端


    while(1)
    {
        P0 = xqd[i];//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = a;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        a = _cror_(a,1);

        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        i++;
        if(i>=8)i=0;
        j++;
        if(j>2000)
        {
            a = _cror_(a,1);
            j = 0;
        }
    }
}

