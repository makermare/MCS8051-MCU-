#ifndef __LCD1602_H__
#define __LCD1602_H__

void InitLcd1602();              //1602��ʼ��
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char Ch);//��ʾһ���ַ�
void Lcd_ShowStr(unsigned char x,unsigned char y,unsigned char *str); //��ʾ�ַ���
void LCD_ShowNum(unsigned char x,unsigned char y,unsigned int Number,unsigned char Length);  //��ʾ10��������
void LCD_ShowHexNum(unsigned char x,unsigned char y,unsigned int Number,unsigned char Length); //��ʾ16������

#endif
