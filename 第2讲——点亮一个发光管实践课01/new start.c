/***************************************
*GB2312
*作者：创客海
*内容：点亮一个发光管理论课
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <reg51.H>//用reg51.h代替

//sbit led7 = P1^7;//位声明了P1.7引脚为led7

void main()//主函数，程序的入口
{
    P1 = 0x7f;//将发光管LED7点亮
    //单片机执行了上面这个语句在以后要通过死循环的方式停在某个地方
    //否则后面没指令了，单片机会把后面的内容继续当作指令执行，是不可控的
    while(1);//死循环执行空操作，执行完了以后为了避免
}