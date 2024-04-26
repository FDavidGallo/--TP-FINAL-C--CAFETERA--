#include "FuncionesEprom.h"
#include <avr/io.h> 
#include <stdlib.h>
/*
   Funciones Eprom es una librer�a pensada para un atmega328p, la misma esta pensada para trabajar con chars
   y strings. Para su uso con otros tipos de datos, pod�s usar la librer�a estandarizada  "stdlib.h
   Autor�a: Fabricio David Gallo
   Basado en: "Free Laundry" de Marwan & Ahmed, dos chicos de Bharat
   
   Ejemplo de uso:
					char data_to_write[] = "Hello World"; // Creamos un vector con lo que queremos guaradar
					char read_data[15];// Creamos un vector con el tama�o de lo que querramos leer
   
					// Escribir en la EEPROM
					EPROM_Write_String(0, data_to_write); // Pasamos 1-> Direcci�n del Dato en Eeprom 2--> el dato a escribrir
														

					// Leer de la EEPROM
					 EPROM_Read_String(0, read_data, sizeof(data_to_write));  // 1->Direcci�n del dato.
																			 //  2-> Largo del dato a leer.
																		    //   3-> El largo del dato, por ejemplo 10.
				  // Al finalizar, el dato est� en el vector "read_data"
*/

// Escribe un byte en una direcci�n espec�fica de la EEPROM
void EPROM_Write(uint16_t uiAddress, uint8_t ucData) {
	while(EECR & (1<<EEPE)); // Espera a que se complete la escritura anterior
	EEAR = uiAddress;        // Configura el registro de direcci�n
	EEDR = ucData;           // Configura el registro de datos
	EECR |= (1<<EEMPE);      // Habilita la escritura maestra de la EEPROM
	EECR |= (1<<EEPE);       // Comienza la escritura en la EEPROM
}

// Lee un byte de una direcci�n espec�fica de la EEPROM
uint8_t EPROM_Read(uint16_t uiAddress) {
	while(EECR & (1<<EEPE)); // Espera a que se complete la escritura anterior
	EEAR = uiAddress;        // Configura el registro de direcci�n
	EECR |= (1<<EERE);       // Comienza la lectura de la EEPROM
	return EEDR;             // Devuelve los datos del registro de datos
}


// Escribe un string en la EEPROM comenzando desde una direcci�n espec�fica
void EPROM_Write_String(uint16_t uiAddress, const char* string) {
	// Escribe cada car�cter en la EEPROM
	uint16_t i;
	for (i = 0; string[i] != '\0'; ++i) {
		// Lee el car�cter actual en la EEPROM
		uint8_t ucCurrentData = EPROM_Read(uiAddress + i);
		// Compara el car�cter actual con el car�cter a escribir
		if (ucCurrentData != string[i]) {
			EPROM_Write(uiAddress + i, string[i]); // Escribe el car�cter si es diferente, si es igual no
		}
	}
	// Verifica si el car�cter nulo necesita ser escrito
	uint8_t ucCurrentData = EPROM_Read(uiAddress + i);
	if (ucCurrentData != '\0') {
		EPROM_Write(uiAddress + i, '\0'); // Escribe el car�cter nulo al final del string
	}
}


// Lee un string de la EEPROM comenzando desde una direcci�n espec�fica
void EPROM_Read_String(uint16_t uiAddress, char* buffer, uint16_t length) {
	for (uint16_t i = 0; i < length; ++i) {
		buffer[i] = EPROM_Read(uiAddress + i); // Lee cada car�cter
	}
	buffer[length] = '\0'; // Termina el string con el car�cter nulo
}


