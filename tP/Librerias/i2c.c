
#include "i2c.h"
int ejecucionUnica = 1;

void i2c_init() { //Se encarga de inicializar el bus I2C en modo maestro con una velocidad de transmisión de 100 kHz
	TWBR = 25; // Frecuencia de reloj de 16MHz / (16 + 2 * TWBR * 1) = 100 kHz {con 25242kHz}
	TWSR = 0;  // Prescaler de 1
}

void i2c_start(){	//Envía una condición de inicio al bus I2C.
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); // Condición de inicio
	while (!(TWCR & (1<<TWINT))); // Verificar la condición de inicio
}
	//TWINT (para limpiar la bandera de interrupción), 
	//TWEN (para habilitar el módulo I2C) y TWSTA (para enviar la condición de inicio). 

void i2c_write(char x){	//Se utiliza para escribir un byte de datos en el bus I2C. 
	TWDR = x; // Mover valor a I2C
	TWCR = (1<<TWINT) | (1<<TWEN); // Habilite I2C y borra la interrupción
	while (!(TWCR & (1<<TWINT)));
}

void i2c_stop(){	//Envía una condición de parada al bus I2C, indicando el final de la transmisión.
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
	while (TWCR&(1<TWSTO));	
}

