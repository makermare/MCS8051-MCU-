/****************************************************************
 * 实验板：  创客海51单片机实验板，以STC89C52单片机为核心，适用于51系列单片机
 * 源代码：  源码经过精心调试，逐行注释，倾心录制高品质视频教程，制作PPT文档教程
 * 温馨提示：需要开源例程源码，请到创客海技术论坛学习、讨论、下载！
 * 淘宝店铺：创客海社区一号店/二号店，希望您支持，感谢您的惠顾！
 * 程序目的：学习lcd显示应用,学习数组，
 * 函数功能: LCD驱动程序
*******************************************************************************/
#include <STC89C5xRC.H>
#include "LCD1602.h"

sbit Key_Data = P3 ^ 4;
sbit Key_CLK = P3 ^ 3;

unsigned int interrupt_dog = 0;
unsigned char IntTimes = 0;                   //中断次数计数
unsigned char KeyValue = 0;                   //键值
unsigned char DisplayNumbers = 0;             //显示用指针
unsigned char Key_UP = 0, Shift = 0;          //Key_UP是键松开标识，Shift是Shift键按下标识
unsigned char KeyValueBuffer;                 //按键的键值缓存
unsigned char LcdShowLines0[32];              //用于液晶屏显示的数组
unsigned char Position;                       //数组下标变量
unsigned char IsFinishedInput;                //是否有字符被收到的标识
unsigned char DisplayBit;                     //是否液晶屏显示的标识
unsigned char code WL[]="Please press key";   //初始化显示字段

unsigned char code UnShifted[58][2] =
{
    0x1C, 'a', 0x32, 'b', 0x21, 'c', 0x23, 'd', 0x24, 'e', 0x2B, 'f', 0x34, 'g',
    0x33, 'h', 0x43, 'i', 0x3B, 'j', 0x42, 'k', 0x4B, 'l', 0x3A, 'm', 0x31, 'n',
    0x44, 'o', 0x4D, 'p', 0x15, 'q', 0x2D, 'r', 0x1B, 's', 0x2C, 't', 0x3C, 'u',
    0x2A, 'v', 0x1D, 'w', 0x22, 'x', 0x35, 'y', 0x1A, 'z', 0x45, '0', 0x16, '1',
    0x1E, '2', 0x26, '3', 0x25, '4', 0x2E, '5', 0x36, '6', 0x3D, '7', 0x3E, '8',
    0x46, '9', 0x70, '0', 0x69, '1', 0x72, '2', 0x7A, '3', 0x6B, '4', 0x73, '5',
    0x74, '6', 0x6C, '7', 0x75, '8', 0x7D, '9', 0x4E, '-', 0x55, '=', 0x5D, ' ',
    0x29, ' ', 0x54, '[', 0x5B, ']', 0x4C, ';', 0x52, ' ', 0x41, ',', 0x49, '.',
    0x4A, '/', 0x71, '.',
};
unsigned char code Shifted[59][2] =
{
    0x1C, 'A', 0x32, 'B', 0x21, 'C', 0x23, 'D', 0x24, 'E', 0x2B, 'F', 0x34, 'G',
    0x33, 'H', 0x43, 'I', 0x3B, 'J', 0x42, 'K', 0x4B, 'L', 0x3A, 'M', 0x31, 'N',
    0x44, 'O', 0x4D, 'P', 0x15, 'Q', 0x2D, 'R', 0x1B, 'S', 0x2C, 'T', 0x3C, 'U',
    0x2A, 'V', 0x1D, 'W', 0x22, 'X', 0x35, 'Y', 0x1A, 'Z', 0x45, ')', 0x16, '!',
    0x1E, '@', 0x26, '#', 0x25, '$', 0x2E, '%', 0x36, '^', 0x3D, '&', 0x3E, '*',
    0x46, '(', 0x4e, '_', 0x4E, '_', 0x55, '+', 0x5D, '|', 0x29, ' ', 0x29, ' ',
    0x29, ' ', 0x4C, ':', 0x29, ' ', 0x41, '<', 0x49, '>', 0x4A, '?', 0x71, '.',
    0x70, '0', 0x69, '1', 0x72, '2', 0x7A, '3', 0x6B, '4', 0x73, '5', 0x74, '6',
    0x6C, '7', 0x75, '8', 0x7D, '9',
};

/*******************************************************************************
* 函数   : 键处理函数
* 函数功能 :shift的通码+G的通码+shift的断码+G的断码，
* 如SHIFT+G为12H 34H F0H 34H F0H 12H?
*******************************************************************************/
unsigned char Decode(unsigned char ScanCode)
{
    unsigned char TempCyc;
    unsigned char KeyChar = 0;
    if (!Key_UP)       //当键盘松开时
    {
        switch (ScanCode)
        {
        case 0xF0:     // 当收到0xF0，Key_UP置1表示断码开始
            Key_UP = 1;
            break;

        case 0x12:     // 左 SHIFT
            Shift = 1;
            break;

        case 0x59:     // 右 SHIFT
            Shift = 1;
            break;
        case 0x66:     // backspace
            if (Position > 0)
            {
                Position--;
                LcdShowLines0[Position] = 0x20;
                DisplayBit = 1;
            }
            break;
        default:
            if (DisplayNumbers > 15)
                DisplayNumbers = 0;
            if (!Shift) //如果SHIFT没按下
            {
                for (TempCyc = 0; (UnShifted[TempCyc][0] != ScanCode) && (TempCyc < 59); TempCyc++)
                    ;   //查表显示
                if (UnShifted[TempCyc][0] == ScanCode)
                {
                    KeyChar = UnShifted[TempCyc][1];
                    DisplayBit = 1;
                    LcdShowLines0[Position] = KeyChar;
                    if (++Position > 31)
                    {
                        for (Position = 0; Position < 32; Position++)
                            LcdShowLines0[Position] = 0x20;
                        Position = 0;
                    }
                }
                DisplayNumbers++;
            }
            else      //按下SHIFT
            {
                for (TempCyc = 0; (Shifted[TempCyc][0] != ScanCode) && (TempCyc < 59); TempCyc++)
                    ; //查表显示
                if (Shifted[TempCyc][0] == ScanCode)
                {
                    KeyChar = Shifted[TempCyc][1];
                    DisplayBit = 1;
                    LcdShowLines0[Position] = KeyChar;
                    if (++Position > 31)
                    {
                        for (Position = 0; Position < 32; Position++)
                            LcdShowLines0[Position] = 0x20;
                        Position = 0;
                    }
                }
                DisplayNumbers++;
            }
            break;
        }
    }
    else
    {
        Key_UP = 0;
        switch (ScanCode) //当键松开时不处理判码，如G 34H F0H 34H 那么第二个34H不会被处理
        {
        case 0x12:        // 左 SHIFT
            Shift = 0;
            break;
        case 0x59:        // 右 SHIFT
            Shift = 0;
            break;
        }
    }
    return KeyChar;
}
/*******************************************************************************
* 函数   : 键扫描函数
* 函数功能 :将键盘的键值解码到ASCII码
*******************************************************************************/
void scakey()
{
    if (IsFinishedInput)
    {
        Decode(KeyValueBuffer);
        IsFinishedInput = 0;
        EX1 = 0;
    }
    else
        EX1 = 1; //开中断
}

/*******************************************************************************
* 主函数   : main
* 函数功能 : 显示键盘的键值数据在1602液晶屏上
*******************************************************************************/
void main()
{
    InitLcd1602();                                 //初始化1602液晶屏
    Lcd_ShowStr(0,0,WL);                           //显示一串字符 第0行，第0列开始显示
    LCD_ShowChar(1,15,'Z');                        //显示一个字符，例如A 在第1行，第2列开始显示
    LCD_ShowNum(1,2,1234,4);                       //显示十进制数，例如987，在第1行，第4列开始显示，长度4
    LCD_ShowHexNum(1,13,0xFE,2);                   //显示一组16进制数，例如0x8C，在第1行，第10列开始显示，长度2

    EX1 = 1;                                       //开启外部中断1，通过外部中断1接收键盘的时钟信号
    EA = 1;                                        //开启总中断开关

    for (Position = 0; Position < 32; Position++)  //初始化用于在液晶屏上显示的数组
        LcdShowLines0[Position] = 0x20;            //全部显示空格
    Position = 0;                                  //数组下标变量清零

    while (1)                                      //主函数死循环
    {
        scakey();                                  //扫描键值
        if (DisplayBit)                            //如果有要显示的内容
        {
            DisplayBit = 0;                        //清除标志位
            Lcd_ShowStr(0,0,LcdShowLines0);        //显示一串字符 第0行，第0列开始显示
        }
        interrupt_dog++;                           //软看门狗变量自加
        if(!interrupt_dog)                         //软看门狗变量溢出时值为零
        {
            IntTimes = 0;                          //如果数据接收有错误直接清零
            IsFinishedInput = 0;        
            KeyValueBuffer = 0;
            KeyValue = 0;
            InitLcd1602();                         //初始化Lcd1602液晶屏
            Lcd_ShowStr(0,0,LcdShowLines0);        //显示一串字符 第0行，第0列开始显示
            interrupt_dog = 0;                     //软看门狗变量清零
        }
    }
}

/*******************************************************************************
* 外部中断函数   : init1
* 函数功能 : 接收并处理键盘的键值
*******************************************************************************/
void init1() interrupt 2 using 0
{
    interrupt_dog = 0;
    if ((IntTimes > 0) && (IntTimes < 9))         //当中断1次后开始存储数据
    {
        KeyValue = KeyValue >> 1;                 //因键盘数据是先收到高位，结合上一句所以右移一位
        if (Key_Data)                             //判断接收的数据高低位
            KeyValue = KeyValue | 0x80;           //当键盘数据线为1时为1到最高位
    }
    IntTimes++;
    while (!Key_CLK)                              //等待PS/2的CLK上升沿数据
        ;
    if (IntTimes > 10)                            //当中断11次后表示一帧数据收完
    {
        IntTimes = 0;                             //清变量准备下一次接收
        IsFinishedInput = 1;                      //标识有字符输入完了
        KeyValueBuffer = KeyValue;                //存储键值
        KeyValue = 0;                             //清零键值
    }
}