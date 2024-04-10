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
//������ ������ #define ��� ������� ���������� ��������
#define LCD_Port PORTA 
#define LCD_port_out DDRA|=0xF0 //��������� �� ����� ������ ������� ��������.
#define E_out DDRA|=(1<<3)
#define E_1 PORTA|=(1<<3)
#define E_0 PORTA&=~(1<<3)
#define RS_out DDRA|=(1<<2)
#define RS_1 PORTA|=(1<<2)
#define RS_0 PORTA&=~(1<<2)

int cod;// ���������� � ������� ������������ ��������� ��������������
//������� �������� ����������� ������ ��� �������������
void halfbytecommand(unsigned halfbyte)
{
RS_0;//��������� RS=0 - �������� �������
E_1;//E=1;
_delay_us(50);
LCD_Port&=0x0F;//������� ������� ����
LCD_Port|=halfbyte&0xF0;//������� ������ � ������� ����
_delay_us(50);
E_0;//E=0;
_delay_us(50);	
}
//������� �������� �����
void sendbyte(unsigned char byte, unsigned char RS)
{
	if (RS==0)RS_0;//���� RS=0 - �������� �������
	else RS_1;//���� RS=1 - �������� ������
	//�������� ������� �������� �����
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//������� ������� ����
	LCD_Port|=byte&0xF0;//������� ������ � ������� ����
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
	//�������� ������� �������� �����
	byte=byte<<4;//�������� �� 4 ������� ������� �������� �����
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//������� ������� ����
	LCD_Port|=byte&0xF0;//������� ������ � ������� ����
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
}
//������������� �������
void LCD_ini(void)
{
	LCD_port_out;//��������  ���� ������� �� �����
	LCD_Port=0x00;//������� ���� �������
	RS_out;//����� ���������� RS �� �����
	E_out;//����� ���������� E �� �����
	//��������� ����������� ���������� (����� ������ ������� ��������)
	_delay_ms(30);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00100000);
	_delay_us(41);
	//��������� �������
	sendbyte(0b00101000,0);//��������� 4-������ �������� ������ � 1-� ���� ����������
	_delay_us(1);
	sendbyte(0b00001100,0);//������� ��������. ������� ���
	_delay_us(1);
}
//��������� ������� � ��������� �������
void setpos(unsigned char X, unsigned char Y)
{
	char adress;
	if(Y==0)adress=(X)|0b10000000;
	if(Y==1)adress=(0x40+X)|0b10000000;
	if(Y==2)adress=(0x14+X)|0b10000000;
	if(Y==3)adress=(0x54+X)|0b10000000;	
	sendbyte(adress,0);
}
//����� ������ �� �������
void str_lcd(char str1[])
{
	wchar_t n;//���������� ��� ������
	for(n=0; str1[n]!='\0';n++)sendbyte(str1[n],1);//���������� ��� ������� ��
	//������� str1[] �� �������, ���� ������� � ��� �� ���������� str1[n]!='\0'
}
//����� ������ �� 1 �������
void move_right(void)
{
	sendbyte(0b00011100,0);
}
//����� ����� �� 1 �������
void move_left(void)
{
	sendbyte(0b00011000,0);
}
//�������� �������
void clear_display(void)
{
	sendbyte(0b00000001,0);
	_delay_ms(2);//����� ����������� ��� �������
}
