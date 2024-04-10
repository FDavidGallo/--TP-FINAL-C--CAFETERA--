/*
 * LCD1604_Wire4.c
 *
 * Created: 21.06.2017 16:00:53
 *  Author: nigmatullin
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD1604_Wire4.h"
//Введем замены #define для выводов управления дисплеем
#define LCD_Port PORTA 
#define LCD_port_out DDRA|=0xF0 //Определим на выход только старший полубайт.
#define E_out DDRA|=(1<<3)
#define E_1 PORTA|=(1<<3)
#define E_0 PORTA&=~(1<<3)
#define RS_out DDRA|=(1<<2)
#define RS_1 PORTA|=(1<<2)
#define RS_0 PORTA&=~(1<<2)

int cod;// Переменная в которую записывается результат преобразования
//Функция отправки полубайтных команд при инициализации
void halfbytecommand(unsigned halfbyte)
{
RS_0;//Установим RS=0 - отправка команды
E_1;//E=1;
_delay_us(50);
LCD_Port&=0x0F;//Обнулим старший байт
LCD_Port|=halfbyte&0xF0;//Запишем только в старший байт
_delay_us(50);
E_0;//E=0;
_delay_us(50);	
}
//Функция отправки байта
void sendbyte(unsigned char byte, unsigned char RS)
{
	if (RS==0)RS_0;//Если RS=0 - отправка команды
	else RS_1;//Если RS=1 - отправка данных
	//Отправим старшую половину байта
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//Обнулим старший байт
	LCD_Port|=byte&0xF0;//Запишем только в старший байт
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
	//Отправим младшую половину байта
	byte=byte<<4;//Сдвинуть на 4 позиции младшую половину байта
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//Обнулим старший байт
	LCD_Port|=byte&0xF0;//Запишем только в старший байт
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
}
//Инициализация дисплея
void LCD_ini(void)
{
	LCD_port_out;//Настроим  порт дисплея на выход
	LCD_Port=0x00;//Обнулим порт дисплея
	RS_out;//Вывод управления RS на выход
	E_out;//Вывод управления E на выход
	//Установка разрядности интерфейса (важен только старший полубайт)
	_delay_ms(30);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00100000);
	_delay_us(41);
	//Настройки дисплея
	sendbyte(0b00101000,0);//Установка 4-битной передачи данных и 1-й табл знакогенер
	_delay_us(1);
	sendbyte(0b00001100,0);//Дисплей включить. курсора нет
	_delay_us(1);
}
//Установка курсора в указанную позицию
void setpos(unsigned char X, unsigned char Y)
{
	char adress;
	if(Y==0)adress=(X)|0b10000000;
	if(Y==1)adress=(0x40+X)|0b10000000;
	if(Y==2)adress=(0x14+X)|0b10000000;
	if(Y==3)adress=(0x54+X)|0b10000000;	
	sendbyte(adress,0);
}
//Вывод строки на дисплей
void str_lcd(char str1[])
{
	wchar_t n;//Символьный тип данных
	for(n=0; str1[n]!='\0';n++)sendbyte(str1[n],1);//Отправлять все символы из
	//массива str1[] по очереди, пока символы в нем не закончатся str1[n]!='\0'
}
//Сдвиг вправо на 1 позицию
void move_right(void)
{
	sendbyte(0b00011100,0);
}
//Сдвиг влево на 1 позицию
void move_left(void)
{
	sendbyte(0b00011000,0);
}
//Очистить дисплей
void clear_display(void)
{
	sendbyte(0b00000001,0);
	_delay_ms(2);//Время необходимое для очистки
}
