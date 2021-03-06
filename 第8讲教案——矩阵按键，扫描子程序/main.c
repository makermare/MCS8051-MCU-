/****************************************************************
 * 实验板：  创客海51单片机实验板，以STC89C52单片机为核心，适用于51系列单片机
 * 源代码：  源码经过精心调试，逐行注释，倾心录制高品质视频教程，制作PPT文档教程
 * 温馨提示：需要开源例程源码，请到创客海技术论坛学习、讨论、下载！
 * 淘宝店铺：创客海社区一号店/二号店，希望您支持，感谢您的惠顾！
 * 程序目的：学习矩阵键盘应用
 * 函数功能: 扫描矩阵键盘程序，测试键值,按SW0键流水灯右移，按SW4键流水灯左移
*******************************************************************************/
#include <STC89C5xRC.H>

/*******************************************************************************
* 子函数     : Delay1ms
* 函数功能     : 延时函数，延时1ms
*******************************************************************************/
void Delay1ms(unsigned int ms)      //@11.0592MHz
{
    while(ms--)   //括弧内的MS--,等效与ms=ms-1，先判断后减1
    {
        unsigned char i=2, j=199;
        ;       //这里加的1个分号，是空操作
        do
        {
            while (--j);
        }
        while (--i);
    }
}
/*******************************************************************************
* 子函数     : ledLR
* 函数功能     : 左移流水灯子程序,for循环
*******************************************************************************/
void ledLR ()
{
    unsigned char n,M;  //定义变量的位置不能放错误。
    for(n=0; n<8; n++)  //加分号的错误
    {
        M=0x01;           //左移0X01
        P1=~(M<<n);       //移动位数
        Delay1ms(100);    //循环100ms
    }
}
/*******************************************************************************
* 子函数     : ledRR
* 函数功能     : 右移动流水灯子程序,for循环
*******************************************************************************/
void ledRR ()
{
    unsigned char n,M;   //定义变量的位置不能放错误。
    for(n=0; n<8; n++)   //加分号的错误
    {
        M=0x80;          //右移0X80
        P1=~(M>>n);      //移动位数
        Delay1ms(100);     //循环100ms
    }
}
/*******************************************************************************
* 矩阵键盘函数 : 返回一个char类型的键值 KeyNum
* 函数功能       : 参数KeyNum是测得键值
*******************************************************************************/
unsigned char keyboard ()
{
    unsigned char KeyNum=0;

    P3=0xFF;    //P3口复位
    P34=0;      //1110 1111，判断第1列是否有按下
    if(P30==0)
    {
        Delay1ms(50);    //判断第1行
        if(P30==0)
        {
            while(P30==0);
            KeyNum=1;
        }
    }
    if(P31==0)
    {
        Delay1ms(50);    //判断第2行
        if(P30==0)
        {
            while(P31==0);
            KeyNum=2;
        }
    }
    if(P32==0)
    {
        Delay1ms(50);    //判断第3行
        if(P32==0)
        {
            while(P32==0);
            KeyNum=3;
        }
    }
    if(P33==0)
    {
        Delay1ms(50);    //判断第4行
        if(P33==0)
        {
            while(P33==0);
            KeyNum=4;
        }
    }

    P3=0xFF;    //P3口复位
    P35=0;      //1101 1111，判断第2列是否有按下
    if(P30==0)
    {
        Delay1ms(50);    //判断第1行
        if(P30==0)
        {
            while(P30==0);
            KeyNum=5;
        }
    }
    if(P31==0)
    {
        Delay1ms(50);    //判断第2行
        if(P31==0)
        {
            while(P31==0);
            KeyNum=6;
        }
    }
    if(P32==0)
    {
        Delay1ms(50);    //判断第3行
        if(P32==0)
        {
            while(P32==0);
            KeyNum=7;
        }
    }
    if(P33==0)
    {
        Delay1ms(50);    //判断第4行
        if(P33==0)
        {
            while(P33==0);
            KeyNum=8;
        }
    }

    P3=0xFF;    //P3口复位
    P36=0;      //1011 1111，判断第3列是否有按下
    if(P30==0)
    {
        Delay1ms(50);    //判断第1行
        if(P30==0)
        {
            while(P30==0);
            KeyNum=9;
        }
    }
    if(P31==0)
    {
        Delay1ms(50);    //判断第2行
        if(P31==0)
        {
            while(P31==0);
            KeyNum=10;
        }
    }
    if(P32==0)
    {
        Delay1ms(50);    //判断第3行
        if(P32==0)
        {
            while(P32==0);
            KeyNum=11;
        }
    }
    if(P33==0)
    {
        Delay1ms(50);    //判断第4行
        if(P33==0)
        {
            while(P33==0);
            KeyNum=12;
        }
    }

    P3=0xFF;    //P3口复位
    P37=0;      //0111 1111，判断第4列是否有按下
    if(P30==0)
    {
        Delay1ms(50);    //判断第1行
        if(P30==0)
        {
            while(P30==0);
            KeyNum=13;
        }
    }
    if(P31==0)
    {
        Delay1ms(50);    //判断第2行
        if(P31==0)
        {
            while(P31==0);
            KeyNum=14;
        }
    }
    if(P32==0)
    {
        Delay1ms(50);    //判断第3行
        if(P32==0)
        {
            while(P32==0);
            KeyNum=15;
        }
    }
    if(P33==0)
    {
        Delay1ms(50);    //判断第4行
        if(P33==0)
        {
            while(P33==0);
            KeyNum=16;
        }
    }

    return KeyNum;        //返回键值
}
/*******************************************************************************
* 主函数    : main
* 函数功能    : 调用矩阵键盘，判断键值
*             if语句后面只有一条语句，可以省略{}
*******************************************************************************/
void main()
{
    while(1)        //主循环
    {
        unsigned char KeyNum;
        KeyNum=keyboard ();  //调用子程序，得到键值

        if(KeyNum==1)   //如果KeyNum=1，SW0键按下
            ledLR ();     //LED流水灯左移

        if(KeyNum==5)   //如果KeyNum=5，SW4键按下
            ledRR ();            //LED流水灯左移
    }
}
