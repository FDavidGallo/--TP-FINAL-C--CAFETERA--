#include "MCP3421.h"
#include "FuncionesEeprom.h"
/*
 * TWI_MCP3421.c
 *  Author: ???????
 *  Edit by: Fabricio David Gallo
 */ 

/*
  Atenci�n: todo est� en ruso y carece de sentido interpretarlo (aunque est� interesante), lo que tenes que saber
  son las funciones principales:
  
 ->TWI_ini(); //INCIALIZA EL TWI (TIENE UNA CONFIGURACI�N ESPECIAL, NO HAY QUE TOCAR)
 ->MCP3421_config(); //configura el sensor MCP3421
 ->int resultado = ((int)a1 << 10) | ((int)a2 << 2) | ((int)a3 >> 6); //ESTO ACOMODA BIEN EL RESULTADO
  
  Al final el resultado est�, bueno, en resultado, como entero, de all� que:
  0 -> inicio de escala
  2047-> Fondo de escala
*/
#define F_CPU 1000000 //??????? ??????????? RC-??????????
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define TamagnoBidon 160   // TIPO V
long int a1,a2,a3;
char sign;//???? ??????????? ???????? ??????????
float a;//?????????? ??? ?????????????? ? ??????
char str[12];//?????? ??? ?????? ?????????? ?? ???????

//????????????? TWI
void TWI_ini(void)
{
	//??????? ???????? ???????? ??????
	TWBR=0x05;//???????? ??? ???????? ???????? ??????: 5
	//???? TWPS1 ? TWPS0 ???????? TWSR ?? ????????? ????? ????
	//f_scl=f_cpu/(16+2*5*4^0)=1000000/26=38,471 ???
}

//???????? ??????? ?????
void TWI_Start(void)
{
	//?????????? ?????? TWI: TWEN=1
	//????????? ???? ????????? "Start": TWSTA=1
	//????????? ???? ?????????? TWI: TWINT=1
	TWCR=(1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while(~TWCR&(1<<TWINT));//????????? ?????????? ????????
}

//???????? ?????
void TWI_Sendbyte(unsigned char byte)
{
	TWDR=byte;//???????? ???? ? ??????? ??????
	//?????????? ?????? TWI
	//????????? ???? ?????????? TWI
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(~TWCR&(1<<TWINT));//????????? ?????????? ????????
}

//????? ??????
void TWI_Receivebytes()
{
   //...............................18 ???..................................
   //????? ??????? ????? ?????? 
   TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//?????????? "ACK": TWEA=1
   while(~TWCR&(1<<TWINT));//????????? ?????????? ????????
   a1=TWDR;//?????????? ??????? ???? ?? MCP3421 ? ?????????? a1=TWDR;
   //????? ??????? ????? ??????
   TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//?????????? "ACK": TWEA=1
   while(~TWCR&(1<<TWINT));//????????? ?????????? ????????
   a2=TWDR;//?????????? ??????? ???? ?? MCP3421 ? ?????????? a1=TWDR;
   //????? ???????? ????? ??????
   TWCR=(1<<TWINT)|(1<<TWEN);//?????????? "NACK": TWEA ?? ?????????
   while(~TWCR&(1<<TWINT));//????????? ?????????? ????????
   a3=TWDR;//?????????? ??????? ???? ?? MCP3421 ? ?????????? a2
  
 

}

//???????? ??????? ????
void TWI_Stop(void)
{
	//?????????? ?????? TWI: TWEN=1
	//????????? ???? ????????? "Stop": TWSTO=1
	//????????? ???? ?????????? TWI: TWINT=1
	TWCR=(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);
}

//????????? MCP3421
void MCP3421_config(void)
{
	TWI_Start();
	TWI_Sendbyte(0b11010000);//?????????? ????? MCP3421: 1101000 + 0 ??????
	TWI_Sendbyte(0b00011100);//?????????? ??????. ????: 00011100
	TWI_Stop();
}

//????????? ?????? ?? MCP3421

int MCP3421_read(void)
{
	TWI_ini(); //INCIALIZA EL TWI (TIENE UNA CONFIGURACI�N ESPECIAL, NO HAY QUE TOCAR)
	MCP3421_config(); //configura el sensor MCP3421
	TWI_Start();
	TWI_Sendbyte(0b11010001);//?????????? ????? MCP3421: 1101000 + 1 ??????
    TWI_Receivebytes();//??????? ????? ? ??????????? ?????????
	int Resultado = (((int)a1 << 10) | ((int)a2 << 2) | ((int)a3 >> 6))-2;
    TWI_Stop();
	return Resultado; 
}
int PesarAgua(void){
int valorLeido = MCP3421_read();
char Buffer[3];
EPROM_Read_String(TamagnoBidon,Buffer,2);
int Tbidon=(atoi(Buffer)*10); // Recuperamos el tama�o del bid�n en  Decalitros de la memoria Eeprom
int Peso = ((((float)valorLeido + 2)*1000) / 2047 )* Tbidon; //esto da en cm3 o ml, (Tbidon = 10 l o 20 l).
return Peso;}
//???????? ?????????