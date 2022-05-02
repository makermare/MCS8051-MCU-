#ifndef _DelayLR_H_             //如果没定义 DelayLR_H
#define _DelayLR_H_             //就定义 DelayLR_H

sbit K1 = P3^0;//位声明了P3.0引脚为按键K1
sbit K2 = P3^1;//位声明了P3.1引脚为按键K2
sbit K3 = P3^2;//位声明了P3.2引脚为按键K3
sbit K4 = P3^3;//位声明了P3.3引脚为按键K4
sbit K5 = P3^4;//位声明了P3.4引脚为按键K5
sbit K6 = P3^5;//位声明了P3.5引脚为按键K6
sbit K7 = P3^6;//位声明了P3.6引脚为按键K7
sbit K8 = P3^7;//位声明了P3.7引脚为按键K8

void Delay1ms(unsigned int ms); //声明里面的函数
void ledLR();                   //声明里面的函数
void ledRR();                   //声明里面的函数

#endif                          //结束定义
