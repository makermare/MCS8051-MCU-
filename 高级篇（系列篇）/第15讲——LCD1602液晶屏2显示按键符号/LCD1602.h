#ifndef __LCD1602_H__
#define __LCD1602_H__

void InitLcd1602();              //1602初始化
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char Ch);//显示一个字符
void Lcd_ShowStr(unsigned char x,unsigned char y,unsigned char *str); //显示字符串
void LCD_ShowNum(unsigned char x,unsigned char y,unsigned int Number,unsigned char Length);  //显示10进制数字
void LCD_ShowHexNum(unsigned char x,unsigned char y,unsigned int Number,unsigned char Length); //显示16进制数

#endif
