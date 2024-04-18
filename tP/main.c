// Inclusión de Librerias necesarias
	#include "Librerias/mcp9800.h"
	#include "Librerias/MCP3421.h"
	#include "Librerias/pcf857.h"
	#include "Librerias/LCD_I2C.h"
	#include "Librerias/i2c.h"
	#include "Librerias/UART.h"
	#include "Librerias/pines.h"
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include  <avr/eeprom.h>
	#include <avr/io.h>
//
#define cpu_1600000
#define PCA8575_ADDRESS 0x20
// Definición de pines para los sensores
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421

// Configuración de la UART (para AVR)
#define BAUD_RATE 9600

// Definición de variables Globales
	//Variables necesarias para las librerias
		int Temp1=0; //Necesaria para el mcp9800
		int resultado=12;//Necesaria para el mcp9800
		long int a1,a2,a3;//Necesaria para el mcp9800
		char sign;//Necesaria Para el Mcp3421
		float a;//Necesaria para el Mcp3421
		char str[12];//Buffer auxiliar del mcp3421
		char Buffer[24]; //Buffer usado para mandar datos por uart y lcd
	//Necesarias para los sensores
		
		int NivelPolvo1,NivelPolvo2, NivelPolvo3,NivelPolvo4; //Niveles de polvo de premezcla (medidos via adc, estan en porcentaje)
		int TemperaturaBidon;
		int PesoBidon;
		uint8_t SensorrTaza = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t SensorrPuerta = 0; // Estado del sensor de la puerta (0 o 1)
        uint8_t SelectorMenuLCD=1; // Menús de selección de bebidas
		uint8_t BotonSeleccionarr = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t BotonAceptarr = 0; // Estado del sensor de la puerta (0 o 1)
		
void LeerBotones(void){
		BotonSeleccionarr=LeerBotonSeleccionar();
		BotonAceptarr=LeerBotonAceptar();
		if (BotonSeleccionarr==1){
			    SelectorMenuLCD=SelectorMenuLCD+1;
				while(BotonSeleccionarr==1){  // ESTO ES PARA EVITAR REBOTES
		         BotonSeleccionarr=LeerBotonSeleccionar();  // HASTA QUE EL USUARIO NO SUELTA EL BOTON  NO HACE NADA
				 if(BotonAceptarr==1){ // ESTO SE EJECUTA SI AMBOS BOTONES SON PRESIONADO A LA VEZ
		          lcd_init();
				  escribirEnLCD(" aca van estd");
				  i2c_stop();
				 }
				}
				if (SelectorMenuLCD==5){
	            SelectorMenuLCD=1;
				escribirEnLCD(" Bebida 1");
				}
			lcd_init(); //Inicializamos el Lcd 
			if (SelectorMenuLCD==1){
				 escribirEnLCD(" Bebida 1");	
				 i2c_stop();}
			if (SelectorMenuLCD==2){
				escribirEnLCD(" Bebida2");
				i2c_stop();}
			if (SelectorMenuLCD==3){
				escribirEnLCD(" Bebida3");
			i2c_stop();}
			if (SelectorMenuLCD==4){
				escribirEnLCD(" Bebida4");
			i2c_stop();}
	}
	   
	  
   }
	

void LeerSensores(void){
	 SensorrTaza=LeerSensorTaza();
	 SensorrPuerta=LeerSensorPuerta();
	 }
	 
void MedicionPolvos(void){
	leer_ADC(0); // Lee el valor del pin PC0
	NivelPolvo1 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
    leer_ADC(1); // Lee el valor del pin PC0
    NivelPolvo2 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	 leer_ADC(2); // Lee el valor del pin PC0
	 NivelPolvo3 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	leer_ADC(3); // Lee el valor del pin PC0
	 NivelPolvo4 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	};
	
void MedirBidon(void){
	TWI_ini(); //INCIALIZA EL i2c del mcp3421 (TIENE UNA CONFIGURACIÓN ESPECIAL, NO HAY QUE TOCAR)
	MCP3421_config(); //configura el sensor MCP3421
	MCP3421_read(); //Leemos el dato
	PesoBidon = (((int)a1 << 10) | ((int)a2 << 2) | ((int)a3 >> 6))-2;
	TWI_Stop(); //cerramos 
	TemperaturaBidon=LeerTemperatura();
	}
	
void MedirVariables(void){
		MedicionPolvos();
		MedirBidon();
        LeerSensores();
		LeerBotones();
	}
   void ConfiguracionIncial(void){
	   iniciar_ADC();					// Inicializamos el ADC
       uart_init();						//Inicializamos la uart
	   ConfigurarPinesSensores();		//Configuramos los pines de los sensores 
	   ConfigurarBotones();				//Configuramos los botones.
   }
   
   
   int main(void){
	   ConfiguracionIncial();//Configuramos todo
	while(1){	 
	MedirVariables();// Sensamos todas nuestras variables
	}
	return 0;
}
