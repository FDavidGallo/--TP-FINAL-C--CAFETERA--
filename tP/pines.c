// pines.c
// AUTORES ORIGINALES:
// A LIBRARY BY: PALO PAJE TECH COOP
//  UWU 
#include "pines.h"
#include <avr/eeprom.h>
#define SENSOR_PIN_1 PD3
#define SENSOR_PIN_2 PD4

void ConfigurarPinesSensores() {
	// Configure sensor pins as inputs
	DDRD &= ~(1 << SENSOR_PIN_1); // PD3 as input
	DDRD &= ~(1 << SENSOR_PIN_2); // PD4 as input
}
// Función para escribir un entero en la EEPROM
void write_int_to_eeprom(int value, int address) {
	eeprom_write_word((int*)address, value);
}

// Función para convertir un entero en un carácter

