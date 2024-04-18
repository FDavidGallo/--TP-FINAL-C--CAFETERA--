// pines.c
// AUTORES ORIGINALES:
// A LIBRARY BY: PALO PAJE TECH COOP
//  UWU 

#include "pines.h"
#include <avr/eeprom.h>
#include <stdio.h>
// Variables globales de los sensores de la puerta y de la taza
	uint8_t SensorTaza = 0; // Estado del sensor de la taza (0 o 1)
	uint8_t SensorPuerta = 0; // Estado del sensor de la puerta (0 o 1)
	uint8_t BotonSeleccionar = 0; // Estado del sensor de la taza (0 o 1)
	uint8_t BotonAceptar = 0; // Estado del sensor de la puerta (0 o 1)
	char Buffer[2];
void ConfigurarPinesSensores() {
	// ConfiGURAMOS CIERTOS PINES DEL PUERTO D COMO ENTRADAS DIGITALES
	DDRD &= ~(1 << PD3); // PD3 
	DDRD &= ~(1 << PD4); // PD4
	
	// Activamos las resistencias de pull-up internas
	// esto quiere decir que los sensores actuan por nivel bajo
	PORTD |= (1 << PD3); // PD3
	PORTD |= (1 << PD4); // PD4

}

int LeerSensorPuerta(void){   //NOTA: SE DA POR ENTENDIDO QUE SESNSOR PUERTA ESTÁ EN EL PIN PD3
						   //      Y SENSOR TAZA EN PD4
  SensorPuerta = !((PIND & (1 << PD4)) ? 1 : 0); // Obtiene el nivel  lógico del sensor de la puerta
  return SensorPuerta;
}

int LeerSensorTaza(void){   //NOTA: SE DA POR ENTENDIDO QUE SESNSOR PUERTA ESTÁ EN EL PIN PD3
	//      Y SENSOR TAZA EN PD4
	SensorTaza = !((PIND & (1 << PD3)) ? 1 : 0); // Obtiene el nivel lógico de SensorTaza
	return SensorTaza;
}
void ConfigurarBotones(void){
	DDRD &= ~(1 << PPD5); // PD5 como entrada
	DDRD &= ~(1 << PPD6); // PD6 como entrada
	PORTD |= (1 << PPD5); // Resistencia de pull up
	PORTD |= (1 << PPD6); // Resistencia de pull up
}
int LeerBotonSeleccionar(void){   //NOTA: SE DA POR ENTENDIDO QUE SESNSOR PUERTA ESTÁ EN EL PIN PD3
	//      Y SENSOR TAZA EN PD4
	BotonSeleccionar = !((PIND & (1 << PPD5)) ? 1 : 0); // Obtiene el nivel  lógico del sensor de la puerta
	return BotonSeleccionar;
}

int LeerBotonAceptar(void){   //NOTA: SE DA POR ENTENDIDO QUE SESNSOR PUERTA ESTÁ EN EL PIN PD3
	//      Y SENSOR TAZA EN PD4
	BotonAceptar = !((PIND & (1 << PPD6)) ? 1 : 0); // Obtiene el nivel lógico de SensorTaza
	return BotonAceptar;
}	
