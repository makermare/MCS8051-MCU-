/***************************************
*GB2312
*���ߣ����ͺ�
*���ݣ����󰴼���������ܾ�̬��ʾ-����ɨ�跨
*ʵ��壺�����51��Ƭ��ʵ���
*��Ƭ���ͺţ�STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

#define uchar unsigned char
#define uint  unsigned int

sbit LCD_EN = P2 ^ 5;     // λ������LCD1602��12864��Һ����ʹ�ܶ�
sbit DS1302_RST = P2 ^ 4; // λ������DS1302����ʪ�ȴ�����ʹ�ܶ�
sbit DUAN = P2 ^ 0;       // λ������������ֶ����������ʹ�ܶ�
sbit WEI = P2 ^ 1;        // λ�����������λ�����������ʹ�ܶ�
sbit CS88 = P2 ^ 2;       // λ�����˵��������е���������ʹ�ܶ�

uchar key = 16;//ȫ�ֱ�������Ű����ļ���

//��λ��������ܶ�ѡ��
unsigned char code table[]=
{
// 0      1     2     3
    0x3f, 0x06, 0x5b, 0x4f,
// 4      5     6     7
    0x66, 0x6d, 0x7d, 0x07,
// 8      9     A     B
    0x7f, 0x6f, 0x77, 0x7c,
// C      D     E     F     Ϩ��
    0x39, 0x5e, 0x79, 0x71, 0x00
};

void delayms(uint xms)
{
    unsigned char i, j;

    while (xms--)
    {
        _nop_();
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

void matrixkeyscan()
{
    uchar temp;

    P3 = 0xfe; //���͵�1��
    temp = P3; //��ȡ��
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 0;
                break;
            case 0xd0: // 11011110
                key = 1;
                break;
            case 0xb0:
                key = 2;
                break;
            case 0x70:
                key = 3;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xfd; //���͵�2��
    temp = P3; //��ȡ��
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 4;
                break;
            case 0xd0: // 11011110
                key = 5;
                break;
            case 0xb0:
                key = 6;
                break;
            case 0x70:
                key = 7;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xfb; //���͵�3��
    temp = P3; //��ȡ��
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 8;
                break;
            case 0xd0: // 11011110
                key = 9;
                break;
            case 0xb0:
                key = 10;
                break;
            case 0x70:
                key = 11;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
    P3 = 0xf7; //���͵�4��
    temp = P3; //��ȡ��
    if ((temp & 0xf0) != 0xf0)
    {
        delayms(50);
        if ((temp & 0xf0) != 0xf0)
        {
            switch (temp & 0xf0)
            {
            case 0xe0: // 11101110
                key = 12;
                break;
            case 0xd0: // 11011110
                key = 13;
                break;
            case 0xb0:
                key = 14;
                break;
            case 0x70:
                key = 15;
                break;
            }
            delayms(5);
            while ((temp & 0xf0) != 0xf0)
            {
                temp = P3;
            }
        }
    }
}

void main()
{
    LCD_EN = 0;           //�������������Һ��������رգ�����ʵ����ܵ�Ӱ��
    DS1302_RST = 0;       //�رտ������ϵ���ʪ�ȴ�����������ʵ����ܵ�Ӱ��
    DUAN = 0;             //��ס������ֶ����������ʹ�ܶ�
    WEI = 0;              //��ס�����λ�����������ʹ�ܶ�
    CS88 = 0;             //��ס���������е���������ʹ�ܶ�

    P0  = 0x00;
    WEI = 1;
    WEI = 0;

    while(1)
    {
        matrixkeyscan();  //��ͣ���ü���ɨ�����
        P0 = table[key];  //���Ͷ�ѡֵ��������ʾ
        DUAN = 1;
        DUAN = 0;
    }
}