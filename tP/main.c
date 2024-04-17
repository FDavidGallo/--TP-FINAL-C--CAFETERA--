// Inclusi�n de Librerias
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
// Definici�n de pines para los sensores
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421
#include <util/delay.h>
#include <avr/interrupt.h>
#include  <avr/eeprom.h>
// Configuraci�n de la UART (para AVR)
#define BAUD_RATE 9600
//#define F_CPU 16000000UL
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
// Definici�n de variables para los sensores
int Temp1=0;
int resultado=12;
long int a1,a2,a3;
char sign;//???? ??????????? ???????? ??????????
float a;//?????????? ??? ?????????????? ? ??????
char str[12];//?????? ??? ?????? ?????????? ?? ???????
int p=0;
 uint8_t SensorTaza = 0; // Estado del sensor de la taza (0 o 1)
 uint8_t SensorPuerta = 0; // Estado del sensor de la puerta (0 o 1)
<<<<<<< Updated upstream

unsigned char valor;
#include <avr/eeprom.h>
// Direcci�n en la EEPROM donde se almacenar� el car�cter
#define EEPROM_ADDR 0 
int main(void)
{
	
	  
=======
int NivelPolvo1,NivelPolvo2, NivelPolvo3,NivelPolvo4; 
unsigned char valor;
#include <avr/eeprom.h>
// Direcci�n en la EEPROM donde se almacenar� el car�cter
#define EEPROM_ADDR 0 
>>>>>>> Stashed changes




<<<<<<< Updated upstream


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
=======
void MedicionPolvos(void){
	int Auxiliar = 0; // Declara la variable pepe
	char buffer[10]; // Declara la variable buffer
	iniciar_ADC(); // Inicializa el ADC
	leer_ADC(0); // Lee el valor del pin PC0
	NivelPolvo1 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resoluci�n y por 100)
	sprintf(buffer, "%.d", NivelPolvo1); // Convierte el valor  a una cadena y la guarda en buffer
	SiguienteTextoLCD();
	escribirEnLCD(buffer); // Escribe el valor en el LCD, para ver que se hizo algo, despues la comentamos
    leer_ADC(1); // Lee el valor del pin PC0
    NivelPolvo2 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resoluci�n y por 100)
    sprintf(buffer, "%.d", NivelPolvo2); // Convierte el valor  a una cadena y la guarda en buffer
 SiguienteTextoLCD();
    escribirEnLCD(buffer); // Escribe el valor en el LCD, para ver que se hizo algo, despues la comentamos
	 leer_ADC(2); // Lee el valor del pin PC0
	 NivelPolvo3 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resoluci�n y por 100)
	 sprintf(buffer, "%d", NivelPolvo3); // Convierte el valor  a una cadena y la guarda en buffer
	  SiguienteTextoLCD();
	 escribirEnLCD(buffer);
	leer_ADC(3); // Lee el valor del pin PC0
	 NivelPolvo4 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resoluci�n y por 100)
	sprintf(buffer, "%d", NivelPolvo4); // Convierte el valor  a una cadena y la guarda en buffer
	SiguienteTextoLCD();
	 escribirEnLCD(buffer); // Escribe el valor en el LCD, para ver que se hizo algo, despues la comentamos
	SiguienteTextoLCD();
	;
	};
	
	void MedirVariables(void){
		MedicionPolvos();
	}
int main(void)
{
	while(1){
	
		 
	int Temperatura=LeerTemperatura();
	char buffer[22];
	  sprintf(buffer, "%d", Temperatura); // Convierte el entero a una cadena
	  lcd_init();
	  escribirEnLCD("aaaaa");
	  escribirEnLCD(buffer); // Muestra la cadena en la pantalla LCD
	  escribirEnLCD("---");
	  _delay_ms(5000);
	  limpiar_LCD();
	  i2c_stop();
	  
	  int Peso=PesarAgua();
	   // Aseg�rate de tener suficiente espacio en el buffer
	  sprintf(buffer, "%d", Peso); // Convierte el float a una cadena con 4 decimales
	  lcd_init();
	  escribirEnLCD("-");
	  escribirEnLCD(buffer);
	  uart_send_string(buffer);
	  _delay_ms(5000);
	   MedirVariables();
	  i2c_stop();
	
	  
	}
>>>>>>> Stashed changes
>>>>>>> Stashed changes

	

}
