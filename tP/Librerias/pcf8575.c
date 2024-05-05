/*
Libreria por David Gallo
ACA SE USA SOLO EL PCF8575 COMO SALIDAS DIGITALES
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pcf857.h"

#include "i2c.h" // Libreria de control del i2c

#define PCF8575_ADDRESS 0x27 // Esta es la dirección, atención; A1,A2 Y A3 a 5V
// Definimos los pines del expansor 
#define P0 0x0001
#define P1 0x0002
#define P2 0x0004
#define P3 0x0008
#define P4 0x0010
#define TODO 0XFFFF
#define NADA 0X0000
// yo agregue esos, vos podes añadir más
// En mi royecto no se requieren que se escriban dos pines a la vez, pero en caso de ser necesario, crea tu propia conbinación, tené en cuenta que:
// 0xFFFF >>TODO PRENDIDO 0X0000 >> TODO APAGADO

void EscribirPcf8575(uint16_t data) {
	cli();
	i2c_start();
	i2c_write(PCF8575_ADDRESS << 1); // Dirección del dispositivo I2C
	i2c_write(data & 0xFF); // Enviar byte bajo
	i2c_write(data >> 8); // Enviar byte alto
	i2c_stop();
	sei();
}
//Las siguientes son funciones propias de mis proyecto, pero siguen la estructura de mandarle un dato predeterminado a la anterior
void PrenderTodo() {
	EscribirPcf8575(TODO);}
void ApagarTodo() {
EscribirPcf8575(NADA);}