﻿/*
 * TWI_MCP3421.c
 *  Author: Дмитрий
 */ 
#define F_CPU 1000000 //частота внутреннего RC-генератора
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd1604_Wire4.h"
long int a1,a2,a3;
char sign;//Знак измеренного значения напряжения
float a;//переменная для преобразования в массив
char str[12];//Массив для вывода результата на дисплей

//Инициализация TWI
void TWI_ini(void)
{
	//Зададим скорость передачи данных
	TWBR=0x05;//Делитель для скорости передачи данных: 5
	//Биты TWPS1 и TWPS0 регистра TWSR по умолчанию равны нулю
	//f_scl=f_cpu/(16+2*5*4^0)=1000000/26=38,471 кГц
}

//Отправка команды старт
void TWI_Start(void)
{
	//Разрешение работы TWI: TWEN=1
	//Установим флаг состояния "Start": TWSTA=1
	//Установим флаг прерывания TWI: TWINT=1
	TWCR=(1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while(~TWCR&(1<<TWINT));//Подождать завершения операции
}

//Отправка байта
void TWI_Sendbyte(unsigned char byte)
{
	TWDR=byte;//Записать байт в регистр данных
	//Разрешение работы TWI
	//Установим флаг прерывания TWI
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(~TWCR&(1<<TWINT));//Подождать завершения операции
}

//Прием байтов
void TWI_Receivebytes()
{
   //...............................18 бит..................................
   //Прием первого байта данных 
   TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//Отправляем "ACK": TWEA=1
   while(~TWCR&(1<<TWINT));//Подождать завершения операции
   a1=TWDR;//Записываем старший байт из MCP3421 в переменную a1=TWDR;
   //Прием второго байта данных
   TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//Отправляем "ACK": TWEA=1
   while(~TWCR&(1<<TWINT));//Подождать завершения операции
   a2=TWDR;//Записываем старший байт из MCP3421 в переменную a1=TWDR;
   //Прием третьего байта данных
   TWCR=(1<<TWINT)|(1<<TWEN);//Отправляем "NACK": TWEA не выставлен
   while(~TWCR&(1<<TWINT));//Подождать завершения операции
   a3=TWDR;//Записываем младший байт из MCP3421 в переменную a2
}

//Отправка команды стоп
void TWI_Stop(void)
{
	//Разрешение работы TWI: TWEN=1
	//Установим флаг состояния "Stop": TWSTO=1
	//Установим флаг прерывания TWI: TWINT=1
	TWCR=(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);
}

//Настройка MCP3421
void MCP3421_config(void)
{
	TWI_Start();
	TWI_Sendbyte(0b11010000);//Отправляем адрес MCP3421: 1101000 + 0 запись
	TWI_Sendbyte(0b00011100);//Отправляем конфиг. байт: 00011100
	TWI_Stop();
}

//Получение данных от MCP3421
void MCP3421_read(void)
{
	TWI_Start();
	TWI_Sendbyte(0b11010001);//Отправляем адрес MCP3421: 1101000 + 1 чтение
    TWI_Receivebytes();//Принять байты с результатом измерения
	TWI_Stop();
}

//Основная программа
int main(void)
{
	TWI_ini();//Инициализация TWI
	LCD_ini();//Инициализация дисплея
	setpos(0,0);//Установка курсора в позицию 0,0
	str_lcd("Control: Atmega32");//Отправка строки на дисплей
	setpos(0,1);//Установка курсора в позицию 0,1
	str_lcd("ADC: 18-bit MCP3421");//Отправка строки на дисплей
	setpos(0,2);//Установка курсора в позицию 0,3
	str_lcd("Cod=");//Отправка строки на дисплей
	setpos(0,3);//Установка курсора в позицию 0,3
	str_lcd("U=");//Отправка строки на дисплей
	MCP3421_config();//Настройка MCP3421
	_delay_ms(100);//Задержка перед первым измерением
	//
	while (1)
	{
		MCP3421_config();//Настройка MCP3421
		_delay_ms(1);
		MCP3421_read();//Получение данных от MCP3421
		//.............Объединение байтов....................
		if(~a1&(1<<1))sign=0;
		else sign=1;
		a1=a1&0x01;//Сотрем старшие 7 бит
		a1=a1<<16;//Сдвинуть на 16 позиций влево
		a2=a2<<8;//Сдвинуть на 8 позиций влево
		a1|=a1+a2+a3;//Сложить байты MCP3421
		a=a1;//Записать результат в переменную типа float для преобразования в массив
		//............Вывод на дисплей........................
		setpos(4,2);//Установка курсора в позицию 2,2
		sprintf(str,"%.0f",a);
		str_lcd(str);//Вывести массив с результатом на дисплей
		str_lcd("     ");
		setpos(2,3);//Установка курсора в позицию 2,2
		if(sign==0)sprintf(str,"%.5f",a*0.000015625);//0.000015625=2.048/131072   18-bit
		else 
		{
			str_lcd("-");//Отправка строки на дисплей
			sprintf(str,"%.5f",2.048-a*0.000015625);
		}
		str_lcd(str);//Вывести массив с результатом на дисплей
		str_lcd(" Volt    ");//Отправка строки на дисплей
		//........Задержка на проведение измерения........................
		_delay_ms(300);
	}
}