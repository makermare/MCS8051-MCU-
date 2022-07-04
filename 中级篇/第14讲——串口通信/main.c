/***************************************
*GB2312
*作者：创客海
*内容：串行中断程序
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/
#include <STC89C5xRC.H>

/*******************************************************************************
* 串口中断入口
* 函数功能		   : 收到数据后，再发出去,点亮对应指示灯
*******************************************************************************/
void XQD() interrupt 4
{
    unsigned char ReceiveData;

    if (RI)               //RI=1，判断是否接收完成
    {
        RI = 0;             //软件清零接收中断标志位RI
        ReceiveData = SBUF; //串口接收到的数据 ReceiveData，读取SBUF寄存器
        SBUF=ReceiveData;   //将接收到的数据放入到发送SBUF寄存器
    }

    if (TI)               //TI=1，判断是否发送完成
    {
        TI = 0;             //清零发送中断标志位TI
    }
}
/*******************************************************************************
* 主函数	  : 设置串口
* 函数功能  : 初始化串口后，单片机接收到数据，就转发回计算机
* 波特率    ：9600
*******************************************************************************/
void main()
{
    TMOD=0X20;			//0010 0000，设置定时器1，工作方式2，8位自动装填方式,不能位寻址
    TH1 = 0xfd;
    TL1 = 0xfd;			//设置比特率9600
    TR1=1;					//定时器1开始计数，定时器1仅用于计数，不产生中断，自动装填初值
    //PCON=0X80;		//设置波特率加倍，波特率加倍在PCON寄存器的第7位，PCON不能位寻址

    //SM0 = 0;	SM1 = 1;//串口工作方式1,8位UART波特率可变
    SCON=0X50;			//0101 0000，设置串口为工作方式1，8bit数据，可变波特率，允许接收，查阅SCON寄存器设置
    ES=1;						//打开串口中断
    EA=1;						//打开总中断

    while(1);//主程序进入死循环
}

/****************************************************************
 * 实验板：  创客海51单片机实验板，以STC89C52单片机为核心，适用于51系列单片机
 * 源代码：  源码经过精心调试，逐行注释，倾心录制高品质视频教程，制作PPT文档教程
 * 温馨提示：需要开源例程源码，请到创客海技术论坛学习、讨论、下载！
 * 淘宝店铺：创客海社区一号店/二号店，希望您支持，感谢您的惠顾！
 * 程序目的：学习串口应用
 * 函数功能: 串行中断程序
*******************************************************************************/