/***************************************
*GB2312
*作者：创客海
*内容：点阵屏动态显示A
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
//#include <INTRINS.H>

sbit LCD_EN = P2 ^ 5;     // 位声明了LCD1602、12864的液晶屏使能端
sbit DS1302_RST = P2 ^ 4; // 位声明了DS1302的温湿度传感器使能端
sbit DUAN = P2 ^ 0;       // 位声明了数码管字段码的锁存器使能端
sbit WEI = P2 ^ 1;        // 位声明了数码管位置码的锁存器使能端
sbit CS88 = P2 ^ 2;       // 位声明了点阵屏行列的列锁存器使能端

/*******************************************************************************
 * 延时子函数 : Delaynms
 * 函数功能	 : 延时nms
 *******************************************************************************/
void Delay1ms(unsigned int Xms) //@11.0592MHz
{
    while (Xms--)
    {
        unsigned char i, j;
        ;
        i = 2;
        j = 199;
        do
        {
            while (--j)
                ;
        }
        while (--i);
    }
}
/*******************************************************************************
* 点阵屏子程序  : XDisplay
* 函数功能	    : 列数据DisData形参，第几列Sit形参
*                 把每一列要显示的数据，装在数组里，整幅画面共有8列，就是8个数据
				  从左边第一列开始显示，向右扫描
*******************************************************************************/
void XDisplay(unsigned char DisData, Sit)
{
    P0 = 0xff; //送显示位置，列码Sit，让数据显示在第几列
    CS88 = 1;
    CS88 = 0; //锁住位码到UB（74HC573）内

    P0 = DisData; //送其中1列要显示的数据,
    DUAN = 1;
    DUAN = 0; //锁住数据到UA（74HC573）内

    P0 = ~(0x80 >> Sit); //送显示位置，列码Sit，让数据显示在第几列
    CS88 = 1;
    CS88 = 0; //锁住位码到UB（74HC573）内
}

//在某一区域内显示亮点，用于判断方向
void main()
{
    unsigned char Num[] = {0x00, 0x3E, 0x48, 0x88, 0x48, 0x3E, 0x00, 0x00}; //显示“A”，要8个数据，按列取模；1为亮点，0为暗
	//00000000      00111111    01001000     10001000     01001000    00111111   00000000   00000000
	//左边不显示区  A字左竖杠   A字连接点  A字上点和中横  A字连接点   A字右竖杠  右边不显示区
    unsigned char i;
    LCD_EN = 0;           //如果开发板上有液晶屏，则关闭，避免实验板受到影响
    DS1302_RST = 0;       //关闭开发板上的温湿度传感器，避免实验板受到影响
    DUAN = 0;             //锁住数码管字段码的锁存器使能端
    WEI = 0;              //锁住数码管位置码的锁存器使能端
    CS88 = 0;             //锁住点阵屏行列的列锁存器使能端

    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            XDisplay(Num[i], i); //显示“A”的第一列数据取出来
            Delay1ms(0);		 //延时0毫秒后，去显示下一列，不停的扫描
        }
    }
}