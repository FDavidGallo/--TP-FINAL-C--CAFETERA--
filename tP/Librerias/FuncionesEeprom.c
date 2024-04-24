

#include "FuncionesEeprom.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
/*
unsigned char LeerCharEprom(unsigned int Direccion) {
	cli();// Apagamos las interrupciones
	while (EECR & (1 << EEPE)); // Espera a que se complete la escritura anterior
	EEARH = (Direccion >> 8);   // Configura la dirección
	EEARL = Direccion;
	EECR |= (1 << EERE); // Inicia la lectura de la EEPROM
	sei(); // Habilita las interrupciones nuevamentente
	return EEDR;         // Devuelve el dato del registro de datos
	
}
 void ImprimirEpromNombre(char Direccion){
	for (int i = 0; i < 11; ++i) {
		char ch = LeerCharEprom(Direccion+i);
		uart_send_char(ch);
		
	}
}

*/
