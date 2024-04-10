#include "MCP3421.h"
#include <avr/io.h>
#define cpu_1600000
// Definici�n de pines para los sensores
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421
#include <util/delay.h>
#include <avr/interrupt.h>
#include  <avr/eeprom.h>
#include "LCD_I2C.h"
#include "i2c.h"
#include "UART.h"
#include "pines.h"
// Configuraci�n de la UART (para AVR)
#define BAUD_RATE 9600
//#define F_CPU 16000000UL
// Definici�n de variables para los sensores

 uint8_t SensorTaza = 0; // Estado del sensor de la taza (0 o 1)
 uint8_t SensorPuerta = 0; // Estado del sensor de la puerta (0 o 1)

unsigned char valor;
#include <avr/eeprom.h>
// Direcci�n en la EEPROM donde se almacenar� el car�cter
#define EEPROM_ADDR 0




int main(void)
{
	ConfigurarPinesSensores();
	int p=0;
	uart_init();
	uart_send_string("	Hola mundo");
	Carpy();
	//uart_send_newline();
	//uart_send_string("1- Editar valores ");
	//uart_send_newline();
	//uart_send_string("2- Ver estadisticas");
	//uart_send_newline();
	//uart_send_string("3-Datos del proyecto");
	uart_send_newline();
	//echo_serial();
    i2c_init();
    i2c_start();
    i2c_write(0x40);
    lcd_init();
    escribirEnLCD(" Hola Mundo");
   _delay_ms(1000);
    limpiar_LCD();
   escribirEnLCD(" Hola yo");
     limpiar_LCD();
	   char charToStore = 'A';

	   // Escribir el car�cter en la EEPROM
	   eeprom_write_byte((uint8_t*)EEPROM_ADDR, charToStore);

	   // Leer el car�cter desde la EEPROM
	   char readChar = eeprom_read_byte((uint8_t*)EEPROM_ADDR);

	   // Convertir el car�cter le�do en una cadena de caracteres
	   char VALOR[2]; // Espacio para el car�cter y el terminador nulo
	   sprintf(VALOR, "%c", readChar);

	   // Tu c�digo adicional aqu� (si es necesario)

	   // Enviar la cadena de caracteres a trav�s de UART
	   uart_send_string(VALOR);

   while (1) {
	   char buffer[10]; // Espacio para la cadena de caracteres
	   sprintf(buffer, "%d", p); // Convierte el entero a una cadena
	   escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	   _delay_ms(5475);
	   limpiar_LCD();
	   escribirEnLCD(" Hola yo");
	   p++; // Incrementa el valor de p
	   escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	   _delay_ms(5475);
	   limpiar_LCD();
	  uart_send_string(" Hola mundo");
	  SensorTaza = (PIND & (1 << PD3)) ? 1 : 0;
	  SensorPuerta = (PIND & (1 << PD4)) ? 1 : 0;
	  sprintf(buffer, "%d", SensorTaza); // Convierte el entero a una cadena
	   escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	   escribirEnLCD(" >>");
	     sprintf(buffer, "%d", SensorPuerta); // Convierte el entero a una cadena
	     escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	   _delay_ms(5475);
	   limpiar_LCD();
	   uart_send_string(VALOR);
	  _delay_ms(5475);
	  
   }

	

}

