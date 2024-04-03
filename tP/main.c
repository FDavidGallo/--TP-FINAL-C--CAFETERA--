
#include <avr/io.h>
#define cpu_1600000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD_I2C.h"
#include "i2c.h"
#include "UART.h"

// Configuración de la UART (para AVR)
#define BAUD_RATE 9600
//#define F_CPU 16000000UL






int main(void)
{
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
   	// Eco del usuario
   while (1) {
	   char buffer[10]; // Espacio para la cadena de caracteres
	   sprintf(buffer, "%d", p); // Convierte el entero a una cadena
	   escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	   _delay_ms(5475);
	   limpiar_LCD();
	   escribirEnLCD(" Hola yo");
	   p++; // Incrementa el valor de p
	  uart_send_string(" Hola mundo");
   }

	

}

