#ifndef _DelayLR_H_             //���û���� DelayLR_H
#define _DelayLR_H_             //�Ͷ��� DelayLR_H

sbit K1 = P3^0;//λ������P3.0����Ϊ����K1
sbit K2 = P3^1;//λ������P3.1����Ϊ����K2
sbit K3 = P3^2;//λ������P3.2����Ϊ����K3
sbit K4 = P3^3;//λ������P3.3����Ϊ����K4
sbit K5 = P3^4;//λ������P3.4����Ϊ����K5
sbit K6 = P3^5;//λ������P3.5����Ϊ����K6
sbit K7 = P3^6;//λ������P3.6����Ϊ����K7
sbit K8 = P3^7;//λ������P3.7����Ϊ����K8

void Delay1ms(unsigned int ms); //��������ĺ���
void ledLR();                   //��������ĺ���
void ledRR();                   //��������ĺ���

#endif                          //��������
