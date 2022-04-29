/****************************************************************
 * 实验板：  创客海51单片机实验板，以STC89C52单片机为核心，适用于51系列单片机
 * 源代码：  源码经过精心调试，逐行注释，倾心录制高品质视频教程，制作PPT文档教程
 * 温馨提示：需要开源例程源码，请到创客海技术论坛学习、讨论、下载！
 * 淘宝店铺：创客海社区一号店/二号店，希望您支持，感谢您的惠顾！
 * 程序目的：学习主函数的创建方法
 * 函数功能: 创建流水灯方法
*******************************************************************************/
#include <STC89C5xRC.H>

/*******************************************************************************
* 延时子函数 : Delay1ms
* 函数功能	 : 延时1ms
*******************************************************************************/
void Delay1ms(unsigned int Xms)		//@11.0592MHz
{
    unsigned char i, j;
    while(Xms--)
    {
        ;
        i = 2;
        j = 199;
        do
        {
            while (--j);
        }
        while (--i);
    }
}

/*******************************************************************************
* 主函数    : main
* 函数功能  : 左移循环显示
*******************************************************************************/
void main()
{
    while(1)
    {
        unsigned char idata n,M;
        for(n=0; n<8; n++)       //注意：这里不加分号，因后面有{}，for循环语句还没写完，
        {
            //如果加了分号，编译也不提示错误，就是不执行{}内的循环体了
            M=0X01;                //左移初值0X01,
            P1=~(M<<n);            //左移n位，再每一位取反
            Delay1ms(200);			   //延时200ms
        }		                     //执行完，参数n+1，判断n<8否成立，成立,再执行一遍循环体，不成立，结束循环
    }
}