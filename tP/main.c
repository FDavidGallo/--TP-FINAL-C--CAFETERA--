// Inclusión de Librerias
#include "Librerias/mcp9800.h"
#include "Librerias/MCP3421.h"
#include "Librerias/pcf857.h"
#include <avr/io.h>
#include "Librerias/LCD_I2C.h"
#include "Librerias/i2c.h"
#include "Librerias/UART.h"
#include "Librerias/pines.h"
//
#define cpu_1600000
#define PCA8575_ADDRESS 0x20
// Definición de pines para los sensores
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421
#include <util/delay.h>
#include <avr/interrupt.h>
#include  <avr/eeprom.h>
// Configuración de la UART (para AVR)
#define BAUD_RATE 9600
//#define F_CPU 16000000UL
// Definición de variables para los sensores
int Temp1=0;
int resultado=12;
long int a1,a2,a3;
char sign;//???? ??????????? ???????? ??????????
float a;//?????????? ??? ?????????????? ? ??????
char str[12];//?????? ??? ?????? ?????????? ?? ???????
int p=0;
 uint8_t SensorTaza = 0; // Estado del sensor de la taza (0 o 1)
 uint8_t SensorPuerta = 0; // Estado del sensor de la puerta (0 o 1)

unsigned char valor;
#include <avr/eeprom.h>
// Dirección en la EEPROM donde se almacenará el carácter
#define EEPROM_ADDR 0 
int main(void)
{
	
	  

	

}

