/***************************************
*GB2312
*���ߣ����ͺ�
*���ݣ���������̬��ʾ����
*ʵ��壺�����51��Ƭ��ʵ���
*��Ƭ���ͺţ�STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit LCD_EN = P2 ^ 5;     // λ������LCD1602��12864��Һ����ʹ�ܶ�
sbit DS1302_RST = P2 ^ 4; // λ������DS1302����ʪ�ȴ�����ʹ�ܶ�
sbit DUAN = P2 ^ 0;       // λ������������ֶ����������ʹ�ܶ�
sbit WEI = P2 ^ 1;        // λ�����������λ�����������ʹ�ܶ�
sbit CS88 = P2 ^ 2;       // λ�����˵��������е���������ʹ�ܶ�

//0xDF,0xEF,0xF7,0xFB,0xF5,0xEF,0xDF,0xFF[����ȡģ+�ֽڵ���]UC
//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00������ȡģ��UA
/*
//��ʾһ�����֣�ע�ⷽ��
void main()
{
    LCD_EN = 0;           //�������������Һ��������رգ�����ʵ����ܵ�Ӱ��
    DS1302_RST = 0;       //�رտ������ϵ���ʪ�ȴ�����������ʵ����ܵ�Ӱ��
    DUAN = 0;             //��ס������ֶ����������ʹ�ܶ�
    WEI = 0;              //��ס�����λ�����������ʹ�ܶ�
    CS88 = 0;             //��ס���������е���������ʹ�ܶ�

    while(1)
    {
        P0 = 0x80;//0x80,0x40,0x20,0x10,0x08,0x04,0x02;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;//0xdf,0xef,0xf7,oxfb,0xf5,0xef,oxdf;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;//������һ�������

        P0 = 0x40;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;//�����ڶ��������

        P0 = 0x20;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf7;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x10;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfb;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf5;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x04;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x02;
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;
    }
}
*/
/*
//��ʾһ�����֣�ע�ⷽ��
void main()
{
    LCD_EN = 0;           //�������������Һ��������رգ�����ʵ����ܵ�Ӱ��
    DS1302_RST = 0;       //�رտ������ϵ���ʪ�ȴ�����������ʵ����ܵ�Ӱ��
    DUAN = 0;             //��ס������ֶ����������ʹ�ܶ�
    WEI = 0;              //��ס�����λ�����������ʹ�ܶ�
    CS88 = 0;             //��ס���������е���������ʹ�ܶ�

    while(1)
    {
        P0 = 0x04;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0x7f;//0x7f,0xbf,oxdf,oxef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xbf;//0x7f,0xbf,oxdf,oxef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x10;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xdf;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x20;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xef;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x50;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xf7;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x08;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfb;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        P0 = 0x04;//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = 0xfd;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

    }
}
*/
//��ʾһ�����ֵĶ���
void main()
{
    unsigned char code xqd[]= {0x04,0x08,0x10,0x20,0x50,0x08,0x04,0X00};
    unsigned char i = 0;
    unsigned char a = 0x7f;
    unsigned int j = 0;

    LCD_EN = 0;           //�������������Һ��������رգ�����ʵ����ܵ�Ӱ��
    DS1302_RST = 0;       //�رտ������ϵ���ʪ�ȴ�����������ʵ����ܵ�Ӱ��
    DUAN = 0;             //��ס������ֶ����������ʹ�ܶ�
    WEI = 0;              //��ס�����λ�����������ʹ�ܶ�
    CS88 = 0;             //��ס���������е���������ʹ�ܶ�


    while(1)
    {
        P0 = xqd[i];//0x04,0x08,0x10,0x20,0x50,0x08,0x04,0x00
        DUAN = 1;
        DUAN = 0;
        P0 = a;//0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xff
        a = _cror_(a,1);

        CS88 = 1;
        CS88 = 0;
        P0 = 0xff;
        CS88 = 1;
        CS88 = 0;

        i++;
        if(i>=8)i=0;
        j++;
        if(j>2000)
        {
            a = _cror_(a,1);
            j = 0;
        }
    }
}

