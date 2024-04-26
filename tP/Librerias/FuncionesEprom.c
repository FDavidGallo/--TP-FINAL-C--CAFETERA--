#include "FuncionesEprom.h"
#include <avr/io.h> 
#include <stdlib.h>
/*
   Funciones Eprom es una librería pensada para un atmega328p, la misma esta pensada para trabajar con chars
   y strings. Para su uso con otros tipos de datos, podés usar la librería estandarizada  "stdlib.h
   Autoría: Fabricio David Gallo
   Basado en: "Free Laundry" de Marwan & Ahmed, dos chicos de Bharat
   
   Ejemplo de uso:
					char data_to_write[] = "Hello World"; // Creamos un vector con lo que queremos guaradar
					char read_data[15];// Creamos un vector con el tamaño de lo que querramos leer
   
					// Escribir en la EEPROM
					EPROM_Write_String(0, data_to_write); // Pasamos 1-> Dirección del Dato en Eeprom 2--> el dato a escribrir
														

					// Leer de la EEPROM
					 EPROM_Read_String(0, read_data, sizeof(data_to_write));  // 1->Dirección del dato.
																			 //  2-> Largo del dato a leer.
																		    //   3-> El largo del dato, por ejemplo 10.
				  // Al finalizar, el dato está en el vector "read_data"
*/

// Escribe un byte en una dirección específica de la EEPROM
void EPROM_Write(uint16_t uiAddress, uint8_t ucData) {
	while(EECR & (1<<EEPE)); // Espera a que se complete la escritura anterior
	EEAR = uiAddress;        // Configura el registro de dirección
	EEDR = ucData;           // Configura el registro de datos
	EECR |= (1<<EEMPE);      // Habilita la escritura maestra de la EEPROM
	EECR |= (1<<EEPE);       // Comienza la escritura en la EEPROM
}

// Lee un byte de una dirección específica de la EEPROM
uint8_t EPROM_Read(uint16_t uiAddress) {
	while(EECR & (1<<EEPE)); // Espera a que se complete la escritura anterior
	EEAR = uiAddress;        // Configura el registro de dirección
	EECR |= (1<<EERE);       // Comienza la lectura de la EEPROM
	return EEDR;             // Devuelve los datos del registro de datos
}


// Escribe un string en la EEPROM comenzando desde una dirección específica
void EPROM_Write_String(uint16_t uiAddress, const char* string) {
	// Escribe cada carácter en la EEPROM
	uint16_t i;
	for (i = 0; string[i] != '\0'; ++i) {
		// Lee el carácter actual en la EEPROM
		uint8_t ucCurrentData = EPROM_Read(uiAddress + i);
		// Compara el carácter actual con el carácter a escribir
		if (ucCurrentData != string[i]) {
			EPROM_Write(uiAddress + i, string[i]); // Escribe el carácter si es diferente, si es igual no
		}
	}
	// Verifica si el carácter nulo necesita ser escrito
	uint8_t ucCurrentData = EPROM_Read(uiAddress + i);
	if (ucCurrentData != '\0') {
		EPROM_Write(uiAddress + i, '\0'); // Escribe el carácter nulo al final del string
	}
}


// Lee un string de la EEPROM comenzando desde una dirección específica
void EPROM_Read_String(uint16_t uiAddress, char* buffer, uint16_t length) {
	for (uint16_t i = 0; i < length; ++i) {
		buffer[i] = EPROM_Read(uiAddress + i); // Lee cada carácter
	}
	buffer[length] = '\0'; // Termina el string con el carácter nulo
}


