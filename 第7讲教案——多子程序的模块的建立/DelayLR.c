#include <STC89C5xRC.H>

/*******************************************************************************
* 子函数     : Delay1ms
* 函数功能     : 延时函数，延时1ms
*******************************************************************************/
void Delay1ms(unsigned int ms)      //@11.0592MHz
{
    while(ms--)
    {
        unsigned char i, j;
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
* 子函数     : ledLR()
* 函数功能     : for循环左移语句，移动LED流水灯
*******************************************************************************/
void ledLR()
{
    unsigned char i;   //定义变量的位置不能放错误。
    for(i=0; i<8; i++)   //加分号的错误
    {
        P1=~(0x01<<i);     //左移0X01移动位数
        Delay1ms(100);         //延时100ms
    }
}

/*******************************************************************************
* 子函数     : ledRR()
* 函数功能     : for循环右移语句，移动LED流水灯
*******************************************************************************/
void ledRR()
{
    unsigned char n;   //定义变量的位置不能放错误。
    for(n=0; n<8; n++) //加分号的错误
    {
        P1=~(0x80>>n);  //右移0X80，移动位数
        Delay1ms(100); //延时100ms
    }
}

