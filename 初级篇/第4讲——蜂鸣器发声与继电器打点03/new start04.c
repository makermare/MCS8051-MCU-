/***************************************
*GB2312
*作者：创客海
*内容：蜂鸣器项目理论课-单片机音乐-孤勇者-录课前编写
*实验板：新起点51单片机实验板
*单片机型号：STC89C52RC
***************************************/

#include <STC89C5xRC.H>
#include <INTRINS.H>
sbit FM = P2^3;
sbit JDQ = P3^6;//继电器新版本的硬件从P3.7改动到了P3.6

#define B6N 19
#define B7N 21
#define B1H 23
#define B2H 24
#define B3H 26
#define B4H 28
#define B5H 29
#define B6H 31

unsigned int code music_table[] = {130,139,147,156,165,175,185,196,208,220,233,247,//0-11
                                   262,277,294,311,329,349,370,392,415,440,466,494,//12-23
                                   523,554,587,622,659,698,740,784,830,880,932,988,0
                                  };//24-35
//C  D-  D   E-  E   F   G-  G   A-   A  B-  B
//unsigned int music[] = {12,14,16,17,19,21,23,0};

unsigned int code music2[] = {B6N,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //爱  你  孤  身  走 暗  巷
                              B1H,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //爱 你  不  跪  的  模  样
                              B1H,B2H,B3H,B2H,B3H,B2H,B3H,36,
                              //爱 你  对  峙  过  绝  望
                              B3H,B2H,B3H,36,B5H,B5H,B3H,36,36,
                              //不 肯  哭      一      场
                              B6N,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //爱 你  破  烂  的 衣  裳
                              B1H,B7N,B1H,B2H,B7N,B1H,B1H,36,
                              //却 敢  赌  命  运 的  枪
                              B1H,B2H,B3H,B2H,B3H,B2H,B3H,36,
                              //爱 你  和  我  那  么  像
                              B3H,B2H,B3H,36,B5H,B5H,B3H,36,36,
                              //缺 口  都     一      样
                              B5H,B3H,B3H,36,36,B5H,B3H,36,36,
                              //去 吗            配  吗
                              B5H,B3H,B5H,B6H,B3H,B5H,36,
                              //这 褴  褛  的  披  风
                              B5H,B3H,B5H,B3H, 36,
                              //战  马  斩 啊
                              B5H,B3H,B5H,B6H,B3H,B5H,36,
                              //以  最  卑  微  的  梦
                              B5H,B5H,B3H,B2H,B2H,B2H,B1H,B3H,B3H,B2H,B2H,B2H,B1H,B1H,B6N,36,36,
                              //掷 那  黑      夜  中  的  呜          咽  与  怒  吼
                              B5H,B5H,B3H,B2H,B2H,B2H,B1H,B3H,B3H,B2H,B2H,B2H,B1H,B1H,B6N,36,36,
                              //谁 说  站      在  光  里  的              才  算  英  雄
                              0,
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
    unsigned int i,j,index;
    index=0;
    while(1)
    {
        j = music_table[music2[index]];
        if(j)
        {
            i = j*3/5;
            JDQ =!JDQ;
            while(i--)
            {
                FM = !FM;//1.08us
                Delay50uss(10000/j);
                //延时
            }
        }
        else
        {
            j = 640;
            i = j*3/5;
            JDQ =!JDQ;
            while(i--)
            {
                Delay50uss(10000/j);
                //延时
            }
        }
        index++;
        if(music2[index]==0)
            index = 0;
    }
}