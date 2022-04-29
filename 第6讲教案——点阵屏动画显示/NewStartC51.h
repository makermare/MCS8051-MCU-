#ifndef NEWSTARTC51_H
#define NEWSTARTC51_H
#include <reg52.h>

//主板函数
extern void newstart_init();

sbit DUAN = P2 ^ 0;
sbit WEI = P2 ^ 1;
sbit CS88 = P2 ^ 2;
sbit LCD_EN = P2 ^ 5; // LCD1602、12864

sbit DS1302_RST = P2 ^ 4; // DS1302
sbit JDQ = P3 ^ 6;
sbit BEEP = P2 ^ 3;

#endif
