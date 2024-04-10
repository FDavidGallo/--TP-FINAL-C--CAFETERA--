/*
 * LCD1604_Wire4.h
 *
 * Created: 21.06.2017 16:04:49
 *  Author: nigmatullin
 */ 

#ifndef LCD1602WIRE4_H_
#define LCD1602WIRE4_H_

//Прототипы функций
void sendbyte(unsigned char byte, unsigned char RS);
void LCD_ini(void);
void setpos(unsigned char X, unsigned char Y);
void str_lcd(char str1[]);
void move_right(void);
void move_left(void);
void clear_display(void);

#endif /* LCD1602WIRE4_H_ */