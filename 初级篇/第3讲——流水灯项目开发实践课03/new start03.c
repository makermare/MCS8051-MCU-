/***************************************
*GB2312
*作者：创客海
*内容：流水灯项目理论课-流水灯
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>//引用了头文件，如果没有可用reg51.h代替
#include <INTRINS.H>//循环左移循环右移必须的函数


/*
sbit led0 = P1^0;//位声明了P1.0引脚为led0
sbit led1 = P1^1;//位声明了P1.1引脚为led1
sbit led2 = P1^2;//位声明了P1.2引脚为led2
sbit led3 = P1^3;//位声明了P1.3引脚为led3
sbit led4 = P1^4;//位声明了P1.4引脚为led4
sbit led5 = P1^5;//位声明了P1.5引脚为led5
sbit led6 = P1^6;//位声明了P1.6引脚为led6
sbit led7 = P1^7;//位声明了P1.7引脚为led7
//循环逐个点亮流水灯
void main()//主函数，程序的入口
{
    while(1)
    {
        unsigned int i;
        led0 = 0;
        i = 50000;
        while(i--);
        led0 = 1;
        i = 50000;
        while(i--);

        led1 = 0;//led1灯是亮的
        i = 50000;
        while(i--);//led1灯持续亮50000次单指令周期
        led1 = 1;
        i = 50000;
        while(i--);

        led2 = 0;
        i = 50000;
        while(i--);
        led2 = 1;
        i = 50000;
        while(i--);

        led3 = 0;
        i = 50000;
        while(i--);
        led3 = 1;
        i = 50000;
        while(i--);

        led4 = 0;
        i = 50000;
        while(i--);
        led4 = 1;
        i = 50000;
        while(i--);

        led5 = 0;
        i = 50000;
        while(i--);
        led5 = 1;
        i = 50000;
        while(i--);

        led6 = 0;
        i = 50000;
        while(i--);
        led6 = 1;
        i = 50000;
        while(i--);

        led7 = 0;
        i = 50000;
        while(i--);
        led7 = 1;
        i = 50000;
        while(i--);
    }
}
*/

/*
//C语言中左移的方式
void main()//主函数，程序的入口
{
    unsigned int i,j;//定义main函数内的局部变量i、j

    while(1)
    {
        P1 = 0xfe;//1111 1110

        j = 8;//将j赋值为整数8
        while(j--)
        {
            i = 20000;//将i赋值为整数20000
            while(i--);//执行i次空操作
            //1111 1110
            //1111 1101
            //1111 1011
            P1 = P1<<1;//1111 1100，‘左移’语句
            P1 = P1 | 0x01;//1111 1101，‘按位或语句’将P1的最低位置为1
            //			if(P1 == 0xff)
            //				break;
        }
    }
}
*/

//C语言中循环左移的方式
void main()//主函数，程序的入口
{
    unsigned int i;
    P1 = 0x55;//0101 0101
    while(1)
    {
        i = 50000;
        while(i--);
        P1 = _crol_(P1,1);//循环左移’语句
    }
}
