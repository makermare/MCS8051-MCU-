/***************************************
*GB2312
*作者：创客海
*内容：定时器控制数码管动态显示秒表
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P1 ^ 2; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

//在main变量局部定义了char数据类型的数组DUAN_table，存储在code区
char code duan_table[] =
{
//0     1    2     3
    0x3f, 0x06, 0x5b, 0x4f,
//4     5    6     7
    0x66, 0x6d, 0x7d, 0x07,
//8     9    .
    0x7f, 0x6f, 0x80
};

//在main变量局部定义了char数据类型的数组WEI_table，存储在code区
char code wei_table[] =
{
//左1  左2   左3   左4  左5   左6   左7   左8
    0xfe, 0xfd, 0xfb, 0xf7,0xef, 0xdf, 0xbf, 0x7f
};

unsigned int a = 0;//全局变量，存放数码管的显示值
unsigned char ru = 0;//全局变量，存放定时器的中断次数值，每50毫秒中断1次，20次就是1秒

void main()
{
    char i=0;             //用于数码管显示的变量

    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI  = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    TMOD = 0x01;  //设置定时器模式1，16位定时/计数器
    TL0 = 0x00;		//设置定时初始值
    TH0 = 0x4C;		//设置定时初始值
    ET0 = 1;      //定时器0中断开启
    EA  = 1;      //全局中断开
    TR0 = 1;		  //定时器0开始计时

    while(1)     //主程序进入死循环，刷新数码管的显示
    {
        if(i == 7)   //秒表个位
        {
            P0 = duan_table[a%10];
        }
        else if(i == 6)     //秒表十位
        {
            P0 = duan_table[(a/10)%10];
        }
        else if(i == 5)     //秒表百位
        {
            P0 = duan_table[(a/100)%10];
        }
        else
        {
            P0 = duan_table[0];
        }
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

void T0_Delay03(void) interrupt 1
{
    TR0=0;	//停止定时器T0计数
    TL0 = 0x00;		//设置定时初始值
    TH0 = 0x4C;		//设置定时初始值
    TR0=1;	//定时器T0计数
    ru++;//第1次中断ru为1；第20次中断ru为20后执行a增1，ru并清零；第21次中断ru仍然为1
    if(ru==20)   //产生了20次中断后执行
    {
        ru=0;//ru清零
        a = a + 1;//a增1，a++或者a+=1是等效的
    }
}
