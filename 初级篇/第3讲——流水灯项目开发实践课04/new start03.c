/***************************************
*GB2312
*作者：创客海
*内容：流水灯项目理论课-呼吸流水灯
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>//引用了头文件，如果没有可用reg51.h代替
#include <INTRINS.H>//循环左移循环右移必须的函数

sbit led0 = P1^0;//位声明了P1.0引脚为led0
sbit led1 = P1^1;//位声明了P1.1引脚为led1
sbit led2 = P1^2;//位声明了P1.2引脚为led2
sbit led3 = P1^3;//位声明了P1.3引脚为led3
sbit led4 = P1^4;//位声明了P1.4引脚为led4
sbit led5 = P1^5;//位声明了P1.5引脚为led5
sbit led6 = P1^6;//位声明了P1.6引脚为led6
sbit led7 = P1^7;//位声明了P1.7引脚为led7

/*
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
            P1 = P1 | 0x01;//1111 1111，‘按位或语句’将P1的最低位置为1
            //			if(P1 == 0xff)
            //				break;
        }
    }
}
*/
/*
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
*/

//点亮呼吸流水灯的一个实验
void main()//主函数，程序的入口
{
    unsigned int i,j;//定义main函数内的局部变量i、j
    unsigned char a;//定义main函数内的局部变量a

    a = 0xfe;//变量a赋值为1111 1110

    while(1)//死循环，外层循环
    {
        /*
        //在这里调节亮度
        //i = 50000;
        //while(i--);
        */
        i=500;//将i赋值为整数500
        //执行i次中层循环
        while(i--)//499-0
        {
            P1 = a;//将P1赋值为变量a的值，点亮某个发光管
            j = 99 - (i/5);//随着中层的循环，i递减，j递增，j的范围是0-99递增
            while(j--);//执行j次中层循环

            P1 = 0xff;//将P1赋值为0xff的值，熄灭所有发光管
            j = i/5;//随着内层的循环，99-0递减
            while(j--);//执行j次中层循环
        }
        /*
        //这里有外层、中层、内层循环，
        //外层循环控制点亮哪个发光管，
        //中层循环是控制点亮某个发光管的时长，
        //内层循环是控制发光管的亮度
        */
        i=500;
        while(i--)//499-0
        {
            P1 = 0xff;
            j = 99 - (i/5);//随着内层的循环递增,0-99递增
            while(j--);

            P1 = a;
            j = i/5;//随着内层的循环，99-0递减
            while(j--);
        }

        a = _crol_(a,1);//在外层循环将a变量循环左移，通过传递在内层将a赋值P1，来控制点亮哪个发光管
    }
}

/*
//通过延时函数，实验不同亮度的流水灯，也就是每个流水灯的亮度并不相同
//以下代码为函数声明，分号结尾，后面是函数定义
//20uS延时函数
void delay20us();
//100uS延时函数
void delay100us();
//200uS延时函数
void delay200us();
//500uS延时函数
void delay500us();
//1mS延时函数
void delay1ms();
//2mS延时函数
void delay2ms();
//5mS延时函数
void delay5ms();
//10mS延时函数
void delay10ms();
//不同亮度的流水灯实验
void main()//主函数，程序的入口
{
	unsigned char LEDS[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
	unsigned int i;

	while (1)
	{
		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[0];
			delay20us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[1];
			delay100us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[2];
			delay200us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[3];
			delay500us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[4];
			delay1ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[5];
			delay2ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 75; i > 0; i--)
		{
			P1 = LEDS[6];
			delay5ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 50; i > 0; i--)
		{
			P1 = LEDS[7];
			delay10ms();
			P1 = 0xff;
			delay10ms();
		}
	}
}
//20uS延时函数
void delay20us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 6;
	while (--i)
		;
}

//100uS延时函数
void delay100us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i)
		;
}

//200uS延时函数
void delay200us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 89;
	while (--i)
		;
}

//500uS延时函数
void delay500us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i)
		;
}

//1mS延时函数
void delay1ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j)
			;
	} while (--i);
}

//2mS延时函数
void delay2ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j)
			;
	} while (--i);
}

//5mS延时函数
void delay5ms() //@11.0592MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j)
			;
	} while (--i);
}

//10mS延时函数
void delay10ms() //@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j)
			;
	} while (--i);
}
*/
