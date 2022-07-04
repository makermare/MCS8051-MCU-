/***************************************
*GB2312
*作者：创客海
*内容：数码管静态显示动态显示理论课-数码管动态显示1、3、1、4、5、2、0、.
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
//#include <INTRINS.H>

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

void main()
{

    //在main变量局部定义了char数据类型的数组DUAN_table，存储在code区
    char code duan_table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x80};
    //这个数组是共阴数码管的段码0     1     2     3     4     5     6     7     8     9     .

    //在main变量局部定义了char数据类型的数组WEI_table，存储在code区
    char code wei_table[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
    //这个数组和数码管位码，  左1   左2   左3   左4   左5   左6   左7   左8

    unsigned char index_table[]= {1,3,1,4,5,2,0,10};

    char i;

    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while(1)
    {
        P0 = duan_table[index_table[i]];
        DUAN = 1;
        DUAN = 0;

        P0 = wei_table[i];
        WEI = 1;
        WEI = 0;

        P0 = 0xff;
        WEI = 1;
        WEI = 0;

        i++;
        if(i>=8) i = 0;
    }
}