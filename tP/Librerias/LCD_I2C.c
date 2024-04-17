
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "LCD_I2C.h"


void enviarPulsoEnable()
{
TWDR |= 0x02;					//---PIN En la pantalla LCD en = 1; -----Enclavar datos en el registro de datos LCD usando una señal de alta a baja
TWCR = (1<<TWINT) | (1<<TWEN);	//---Habilita I2C y borra la interrupción- Esta linea y la siguiente simepre van despues de querer mandar un coamndo por TDWR
while  (!(TWCR &(1<<TWINT)));	//---Siempre poner despues de la linea anterior al mandar datos por TWDR
_delay_ms(1);
TWDR &= ~0x02;					//---PIN del Enable de la LCD en = 0;
TWCR = (1<<TWINT) | (1<<TWEN);	//---Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
}

void enviarComando4Bits(char v1)
{
TWDR &=~0x01;					//PIN RS de la pantalla LCD rs = 0; ----Seleccionar registro como registro de comando
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR &= 0x0F;					//----Enmascaramiento de 4 bits superiores y envío a LCD
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR |= (v1 & 0xF0);			//----
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
enviarPulsoEnable();
}

void enviarComando(char v2)
{
TWDR&=~0x01;					//rs = 0; ----Seleccionar registro como registro de comando
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));

TWDR &= 0x0F;                   //----borrando los 4 bits superiores
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR |= (v2 & 0xF0);			//----Enmascaramiento de 4 bits superiores y envío a LCD
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
enviarPulsoEnable();
	
TWDR &= 0x0F;                    //----borrando los 4 bits superiores
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR |= ((v2 & 0x0F)<<4);		//----Enmascaramiento de 4 bits inferiores y envío a LCD
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilite I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
enviarPulsoEnable();
}

void escribirDato(char v3)
{
TWDR|=0x01;						//RS = 1; ----Selecciona registro como registro de comando
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR &= 0x0F;				    //----borrando los 4 bits superiores
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR |= (v3 & 0xF0);			//----Enmascaramiento de 4 bits superiores y envío a LCD
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
enviarPulsoEnable();
	
TWDR &= 0x0F;					//----borrando los 4 bits superiores
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
TWDR |= ((v3 & 0x0F)<<4);		//----Enmascaramiento de 4 bits inferiores y envío a LCD
TWCR = (1<<TWINT) | (1<<TWEN);	//Habilita I2C y borra la interrupción
while  (!(TWCR &(1<<TWINT)));
enviarPulsoEnable();
}

void lcd_init() {
i2c_init(); //inciamos la comunicación i2c
i2c_start(); //Iniciamos el i2c
i2c_write(0x40); //Dirección del PCF8574
// Inicialización del LCD de 20x4 en modo 4 bits.
_delay_ms(5);
enviarComando4Bits(0x30); // 3 veces
_delay_ms(5);
enviarComando4Bits(0x30);
enviarComando4Bits(0x20); // Modo 4 bits
_delay_ms(5);
	
// Configuración del LCD de 20x4
enviarComando(0x28);      // Función de 4 bits, 2 líneas, fuente 5x8
enviarComando(0x0C);      // Encender el display, apagar el cursor
enviarComando(0x01);      // Borrar pantalla
enviarComando(0x06);      // Desplazamiento del cursor a la derecha
enviarComando(0x80);      // Posiciona el cursor en la primera línea, primera posición
}

void escribirEnLCD(char *c)
{
while(*c != 0)			//----Espere hasta que todas las cadenas pasen a la pantalla LCD.
escribirDato(*c++);		//----Enviar la cadena a la pantalla LCD
}

void limpiar_LCD()
{
enviarComando(0x01);	//Comando para limpar el lcd
_delay_us(100);
enviarComando (0x80);	//Setea el cursor en la posicion cero
}

