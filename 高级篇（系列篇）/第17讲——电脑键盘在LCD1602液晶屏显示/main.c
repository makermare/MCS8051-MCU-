/****************************************************************
 * ʵ��壺  ���ͺ�51��Ƭ��ʵ��壬��STC89C52��Ƭ��Ϊ���ģ�������51ϵ�е�Ƭ��
 * Դ���룺  Դ�뾭�����ĵ��ԣ�����ע�ͣ�����¼�Ƹ�Ʒ����Ƶ�̳̣�����PPT�ĵ��̳�
 * ��ܰ��ʾ����Ҫ��Դ����Դ�룬�뵽���ͺ�������̳ѧϰ�����ۡ����أ�
 * �Ա����̣����ͺ�����һ�ŵ�/���ŵ꣬ϣ����֧�֣���л���Ļݹˣ�
 * ����Ŀ�ģ�ѧϰlcd��ʾӦ��,ѧϰ���飬
 * ��������: LCD��������
*******************************************************************************/
#include <STC89C5xRC.H>
#include "LCD1602.h"

sbit Key_Data = P3 ^ 4;
sbit Key_CLK = P3 ^ 3;

unsigned int interrupt_dog = 0;
unsigned char IntTimes = 0;                   //�жϴ�������
unsigned char KeyValue = 0;                   //��ֵ
unsigned char DisplayNumbers = 0;             //��ʾ��ָ��
unsigned char Key_UP = 0, Shift = 0;          //Key_UP�Ǽ��ɿ���ʶ��Shift��Shift�����±�ʶ
unsigned char KeyValueBuffer;                 //�����ļ�ֵ����
unsigned char LcdShowLines0[32];              //����Һ������ʾ������
unsigned char Position;                       //�����±����
unsigned char IsFinishedInput;                //�Ƿ����ַ����յ��ı�ʶ
unsigned char DisplayBit;                     //�Ƿ�Һ������ʾ�ı�ʶ
unsigned char code WL[]="Please press key";   //��ʼ����ʾ�ֶ�

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
* ����   : ��������
* �������� :shift��ͨ��+G��ͨ��+shift�Ķ���+G�Ķ��룬
* ��SHIFT+GΪ12H 34H F0H 34H F0H 12H?
*******************************************************************************/
unsigned char Decode(unsigned char ScanCode)
{
    unsigned char TempCyc;
    unsigned char KeyChar = 0;
    if (!Key_UP)       //�������ɿ�ʱ
    {
        switch (ScanCode)
        {
        case 0xF0:     // ���յ�0xF0��Key_UP��1��ʾ���뿪ʼ
            Key_UP = 1;
            break;

        case 0x12:     // �� SHIFT
            Shift = 1;
            break;

        case 0x59:     // �� SHIFT
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
            if (!Shift) //���SHIFTû����
            {
                for (TempCyc = 0; (UnShifted[TempCyc][0] != ScanCode) && (TempCyc < 59); TempCyc++)
                    ;   //�����ʾ
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
            else      //����SHIFT
            {
                for (TempCyc = 0; (Shifted[TempCyc][0] != ScanCode) && (TempCyc < 59); TempCyc++)
                    ; //�����ʾ
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
        switch (ScanCode) //�����ɿ�ʱ���������룬��G 34H F0H 34H ��ô�ڶ���34H���ᱻ����
        {
        case 0x12:        // �� SHIFT
            Shift = 0;
            break;
        case 0x59:        // �� SHIFT
            Shift = 0;
            break;
        }
    }
    return KeyChar;
}
/*******************************************************************************
* ����   : ��ɨ�躯��
* �������� :�����̵ļ�ֵ���뵽ASCII��
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
        EX1 = 1; //���ж�
}

/*******************************************************************************
* ������   : main
* �������� : ��ʾ���̵ļ�ֵ������1602Һ������
*******************************************************************************/
void main()
{
    InitLcd1602();                                 //��ʼ��1602Һ����
    Lcd_ShowStr(0,0,WL);                           //��ʾһ���ַ� ��0�У���0�п�ʼ��ʾ
    LCD_ShowChar(1,15,'Z');                        //��ʾһ���ַ�������A �ڵ�1�У���2�п�ʼ��ʾ
    LCD_ShowNum(1,2,1234,4);                       //��ʾʮ������������987���ڵ�1�У���4�п�ʼ��ʾ������4
    LCD_ShowHexNum(1,13,0xFE,2);                   //��ʾһ��16������������0x8C���ڵ�1�У���10�п�ʼ��ʾ������2

    EX1 = 1;                                       //�����ⲿ�ж�1��ͨ���ⲿ�ж�1���ռ��̵�ʱ���ź�
    EA = 1;                                        //�������жϿ���

    for (Position = 0; Position < 32; Position++)  //��ʼ��������Һ��������ʾ������
        LcdShowLines0[Position] = 0x20;            //ȫ����ʾ�ո�
    Position = 0;                                  //�����±��������

    while (1)                                      //��������ѭ��
    {
        scakey();                                  //ɨ���ֵ
        if (DisplayBit)                            //�����Ҫ��ʾ������
        {
            DisplayBit = 0;                        //�����־λ
            Lcd_ShowStr(0,0,LcdShowLines0);        //��ʾһ���ַ� ��0�У���0�п�ʼ��ʾ
        }
        interrupt_dog++;                           //���Ź������Լ�
        if(!interrupt_dog)                         //���Ź��������ʱֵΪ��
        {
            IntTimes = 0;                          //������ݽ����д���ֱ������
            IsFinishedInput = 0;        
            KeyValueBuffer = 0;
            KeyValue = 0;
            InitLcd1602();                         //��ʼ��Lcd1602Һ����
            Lcd_ShowStr(0,0,LcdShowLines0);        //��ʾһ���ַ� ��0�У���0�п�ʼ��ʾ
            interrupt_dog = 0;                     //���Ź���������
        }
    }
}

/*******************************************************************************
* �ⲿ�жϺ���   : init1
* �������� : ���ղ�������̵ļ�ֵ
*******************************************************************************/
void init1() interrupt 2 using 0
{
    interrupt_dog = 0;
    if ((IntTimes > 0) && (IntTimes < 9))         //���ж�1�κ�ʼ�洢����
    {
        KeyValue = KeyValue >> 1;                 //��������������յ���λ�������һ����������һλ
        if (Key_Data)                             //�жϽ��յ����ݸߵ�λ
            KeyValue = KeyValue | 0x80;           //������������Ϊ1ʱΪ1�����λ
    }
    IntTimes++;
    while (!Key_CLK)                              //�ȴ�PS/2��CLK����������
        ;
    if (IntTimes > 10)                            //���ж�11�κ��ʾһ֡��������
    {
        IntTimes = 0;                             //�����׼����һ�ν���
        IsFinishedInput = 1;                      //��ʶ���ַ���������
        KeyValueBuffer = KeyValue;                //�洢��ֵ
        KeyValue = 0;                             //�����ֵ
    }
}