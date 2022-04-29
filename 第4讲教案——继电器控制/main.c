/****************************************************************
 * 实验板：  创客海51单片机实验板，以STC89C52单片机为核心，适用于51系列单片机
 * 源代码：  源码经过精心调试，逐行注释，倾心录制高品质视频教程，制作PPT文档教程
 * 温馨提示：需要开源例程源码，请到创客海技术论坛学习、讨论、下载！
 * 淘宝店铺：创客海社区一号店/二号店，希望您支持，感谢您的惠顾！
 * 程序目的：按键K3控制继电器吸合
 * 函数功能: 继电器控制主程序,按动K3，继电器吸合5次
*******************************************************************************/
#include <STC89C5xRC.H>
sbit Relay=P3^6;        //定义继电器IO口，原理图在P3.6
/*******************************************************************************
* 延时函数   : Delay1ms
* 函数功能	 : 延时1ms
*******************************************************************************/
void Delay1ms(unsigned int ms)		//@11.0592MHz
{
    while(ms--)
    {
        unsigned char i=2, j=199;
        do
        {
            while (--j);
        }
        while (--i);
    }
}
/*******************************************************************************
* 主函数    : main
* 函数功能	: 继电器控制主程序,按下K3继电器吸合
*******************************************************************************/
void main()
{
    unsigned char i;
    while(1)            //主循环
    {
        if(P32==0)		    //判断K3是否按下，P32=0时K3被按下，不能加;号
        {
            Delay1ms(20);   //消抖，等按键进入稳态
            while(P32==0);  //等待按键释放
            Delay1ms(20);	  //等进入稳态

            for(i=0; i<5; i++)
            {
                Relay=0;        //位控制，Relay=0，继电器吸合
                Delay1ms(500);  //延时500ms
                Relay=1;        //位方式，Relay=1，继电器断开
                Delay1ms(500);  //延时500ms
            }
        }
    }
}

