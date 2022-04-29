/***************************************
*GB2312
*作者：创客海
*内容：蜂鸣器项目理论课-蜂鸣器发出精准音阶do、re、mi
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>//引用了头文件，如果没有可用reg51.h代替
#include <INTRINS.H>//循环左移循环右移必须的函数

sbit FM = P2 ^ 3;//位声明了P2.3引脚为蜂鸣器

/*------------------------------------------------
 延时函数，精确延时，用STCisp生成的精准延时
------------------------------------------------*/
void Delay1911us() //@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 4;
    j = 105;
    do
    {
        while (--j);
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
        while (--j);
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
        while (--j);
    }
    while (--i);
}

void main()
{
    int i = 50000;
    while (1)
    {
        i = 500;
        while (i--)//执行500次发出音阶do
        {
            FM = 1; //高电平不发声音
            Delay1911us();
            FM = 0; //低电平发声音
            Delay1911us();
        }
        i = 540;
        while (i--)//执行540次发出音阶re
        {
            FM = 1; //高电平不发声音
            Delay1702us();
            FM = 0; //低电平发声音
            Delay1702us();
        }
        i = 590;
        while (i--)//执行540次发出音阶mi
        {
            FM = 1; //高电平不发声音
            Delay1516us();
            FM = 0; //低电平发声音
            Delay1516us();
        }
    }
}