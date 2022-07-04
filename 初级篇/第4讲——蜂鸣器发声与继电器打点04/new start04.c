/***************************************
*GB2312
*���ߣ����ͺ�
*���ݣ���������Ŀ���ۿ�-��Ƭ������-������-¼��ʱ��д
*ʵ��壺�����51��Ƭ��ʵ���
*��Ƭ���ͺţ�STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>

#define B6N 19
#define B7N 21
#define B1H 23
#define B2H 24
#define B3H 26
#define B4H 28
#define B5H 29
#define B6H 31

sbit FM = P2^3;
sbit JDQ = P3^6;//�̵����°汾��Ӳ����P3.7�Ķ�����P3.6



//unsigned int music_table[] = {262,277,294,311,329,349,370,392,415,440,466,494};

unsigned int code music_table[] = {130,139,147,156,165,175,185,196,208,220,233,247,//0-11
                                   262,277,294,311,329,349,370,392,415,440,466,494,//12-23
                                   523,554,587,622,659,698,740,784,830,880,932,988,0
                                  };//24-35

unsigned char code music[] = {B6N,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //��  ��  ��  ��  �� ��  ��
                              B1H,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //�� ��  ��  ��  ��  ģ  ��
                              B1H,B2H,B3H,B2H,B3H,B2H,B3H,36,
                              //�� ��  ��  ��  ��  ��  ��
                              B3H,B2H,B3H,36,B5H,B5H,B3H,36,36,
                              //�� ��  ��      һ      ��
                              B6N,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //�� ��  ��  ��  �� ��  ��
                              B1H,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //ȴ ��  ��  ��  �� ��  ǹ
                              B1H,B2H,B3H,B2H,B3H,B2H,B3H,36,
                              //�� ��  ��  ��  ��  ô  ��
                              B3H,B2H,B3H,36,B5H,B5H,B3H,36,36,
                              //ȱ ��  ��     һ      ��
                              B5H,B3H,B3H,36,36,B5H,B3H,36,36,
                              //ȥ ��            ��  ��
                              B5H,B3H,B5H,B6H,B3H,B5H,36,
                              //�� ��  ��  ��  ��  ��
                              B5H,B3H,B5H,B3H, 36,
                              //ս  ��  ն ��
                              B5H,B3H,B5H,B6H,B3H,B5H,36,
                              //��  ��  ��  ΢  ��  ��
                              B5H,B5H,B3H,B2H,B2H,B2H,B1H,B3H,B3H,B2H,B2H,B2H,B1H,B1H,B6N,36,36,
                              //�� ��  ��      ҹ  ��  ��  ��          ��  ��  ŭ  ��
                              B5H,B5H,B3H,B2H,B2H,B2H,B1H,B3H,B3H,B2H,B2H,B2H,B1H,B1H,B6N,36,36,
                              //˭ ˵  վ      ��  ��  ��  ��              ��  ��  Ӣ  ��
                             };

void Delay50uss(unsigned char us)
{
    unsigned char i;
    while(us--)
    {
        i = 6;
        while (--i);
    }
}

void main()
{
    unsigned int i,j;
    unsigned int index,endindex;
    index =0;
    endindex = sizeof(music);

    while(1)
    {
        j= music_table[music[index]];
        i =j*3/5;//ȫ����*2��������*1
        while(i--)//��������
        {
            FM = !FM;//1.08us
            Delay50uss(10000/j);
            //50 0000/440 ΢�� ���㹫ʽ��1/262*1000*1000/2 ��
        }
        if(j == 0)//��ֹ
        {
            Delay50uss(10000*3/5);
            JDQ = !JDQ;//����
        }

        index++;
        if(index>=endindex)index = 0;
    }
}