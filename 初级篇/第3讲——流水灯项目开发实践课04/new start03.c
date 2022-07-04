/***************************************
*GB2312
*���ߣ����ͺ�
*���ݣ���ˮ����Ŀ���ۿ�-������ˮ��
*ʵ��壺�����51��Ƭ��ʵ���
*��Ƭ���ͺţ�STC89C52RC
***************************************/

#include <STC89C5xRC.H>//������ͷ�ļ������û�п���reg51.h����
#include <INTRINS.H>//ѭ������ѭ�����Ʊ���ĺ���

sbit led0 = P1^0;//λ������P1.0����Ϊled0
sbit led1 = P1^1;//λ������P1.1����Ϊled1
sbit led2 = P1^2;//λ������P1.2����Ϊled2
sbit led3 = P1^3;//λ������P1.3����Ϊled3
sbit led4 = P1^4;//λ������P1.4����Ϊled4
sbit led5 = P1^5;//λ������P1.5����Ϊled5
sbit led6 = P1^6;//λ������P1.6����Ϊled6
sbit led7 = P1^7;//λ������P1.7����Ϊled7

/*
//ѭ�����������ˮ��
void main()//����������������
{
    while(1)
    {
        unsigned int i;
        led0 = 0;
        i = 50000;
        while(i--);
        led0 = 1;
        i = 50000;
        while(i--);

        led1 = 0;//led1��������
        i = 50000;
        while(i--);//led1�Ƴ�����50000�ε�ָ������
        led1 = 1;
        i = 50000;
        while(i--);

        led2 = 0;
        i = 50000;
        while(i--);
        led2 = 1;
        i = 50000;
        while(i--);

        led3 = 0;
        i = 50000;
        while(i--);
        led3 = 1;
        i = 50000;
        while(i--);

        led4 = 0;
        i = 50000;
        while(i--);
        led4 = 1;
        i = 50000;
        while(i--);

        led5 = 0;
        i = 50000;
        while(i--);
        led5 = 1;
        i = 50000;
        while(i--);

        led6 = 0;
        i = 50000;
        while(i--);
        led6 = 1;
        i = 50000;
        while(i--);

        led7 = 0;
        i = 50000;
        while(i--);
        led7 = 1;
        i = 50000;
        while(i--);
    }
}
*/
/*
//C���������Ƶķ�ʽ
void main()//����������������
{
    unsigned int i,j;//����main�����ڵľֲ�����i��j

    while(1)
    {
        P1 = 0xfe;//1111 1110

        j = 8;//��j��ֵΪ����8
        while(j--)
        {
            i = 20000;//��i��ֵΪ����20000
            while(i--);//ִ��i�οղ���
            //1111 1110
            //1111 1101
            //1111 1011
            P1 = P1<<1;//1111 1100�������ơ����
            P1 = P1 | 0x01;//1111 1111������λ����䡯��P1�����λ��Ϊ1
            //			if(P1 == 0xff)
            //				break;
        }
    }
}
*/
/*
//C������ѭ�����Ƶķ�ʽ
void main()//����������������
{
    unsigned int i;
    P1 = 0x55;//0101 0101
    while(1)
    {
        i = 50000;
        while(i--);
        P1 = _crol_(P1,1);//ѭ�����ơ����
    }
}
*/

//����������ˮ�Ƶ�һ��ʵ��
void main()//����������������
{
    unsigned int i,j;//����main�����ڵľֲ�����i��j
    unsigned char a;//����main�����ڵľֲ�����a

    a = 0xfe;//����a��ֵΪ1111 1110

    while(1)//��ѭ�������ѭ��
    {
        /*
        //�������������
        //i = 50000;
        //while(i--);
        */
        i=500;//��i��ֵΪ����500
        //ִ��i���в�ѭ��
        while(i--)//499-0
        {
            P1 = a;//��P1��ֵΪ����a��ֵ������ĳ�������
            j = 99 - (i/5);//�����в��ѭ����i�ݼ���j������j�ķ�Χ��0-99����
            while(j--);//ִ��j���в�ѭ��

            P1 = 0xff;//��P1��ֵΪ0xff��ֵ��Ϩ�����з����
            j = i/5;//�����ڲ��ѭ����99-0�ݼ�
            while(j--);//ִ��j���в�ѭ��
        }
        /*
        //��������㡢�в㡢�ڲ�ѭ����
        //���ѭ�����Ƶ����ĸ�����ܣ�
        //�в�ѭ���ǿ��Ƶ���ĳ������ܵ�ʱ����
        //�ڲ�ѭ���ǿ��Ʒ���ܵ�����
        */
        i=500;
        while(i--)//499-0
        {
            P1 = 0xff;
            j = 99 - (i/5);//�����ڲ��ѭ������,0-99����
            while(j--);

            P1 = a;
            j = i/5;//�����ڲ��ѭ����99-0�ݼ�
            while(j--);
        }

        a = _crol_(a,1);//�����ѭ����a����ѭ�����ƣ�ͨ���������ڲ㽫a��ֵP1�������Ƶ����ĸ������
    }
}

/*
//ͨ����ʱ������ʵ�鲻ͬ���ȵ���ˮ�ƣ�Ҳ����ÿ����ˮ�Ƶ����Ȳ�����ͬ
//���´���Ϊ�����������ֺŽ�β�������Ǻ�������
//20uS��ʱ����
void delay20us();
//100uS��ʱ����
void delay100us();
//200uS��ʱ����
void delay200us();
//500uS��ʱ����
void delay500us();
//1mS��ʱ����
void delay1ms();
//2mS��ʱ����
void delay2ms();
//5mS��ʱ����
void delay5ms();
//10mS��ʱ����
void delay10ms();
//��ͬ���ȵ���ˮ��ʵ��
void main()//����������������
{
	unsigned char LEDS[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
	unsigned int i;

	while (1)
	{
		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[0];
			delay20us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[1];
			delay100us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[2];
			delay200us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[3];
			delay500us();
			P1 = 0xff;
			delay10ms();
		}

		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[4];
			delay1ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 100; i > 0; i--)
		{
			P1 = LEDS[5];
			delay2ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 75; i > 0; i--)
		{
			P1 = LEDS[6];
			delay5ms();
			P1 = 0xff;
			delay10ms();
		}
		for (i = 50; i > 0; i--)
		{
			P1 = LEDS[7];
			delay10ms();
			P1 = 0xff;
			delay10ms();
		}
	}
}
//20uS��ʱ����
void delay20us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 6;
	while (--i)
		;
}

//100uS��ʱ����
void delay100us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i)
		;
}

//200uS��ʱ����
void delay200us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 89;
	while (--i)
		;
}

//500uS��ʱ����
void delay500us() //@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i)
		;
}

//1mS��ʱ����
void delay1ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j)
			;
	} while (--i);
}

//2mS��ʱ����
void delay2ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j)
			;
	} while (--i);
}

//5mS��ʱ����
void delay5ms() //@11.0592MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j)
			;
	} while (--i);
}

//10mS��ʱ����
void delay10ms() //@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j)
			;
	} while (--i);
}
*/
