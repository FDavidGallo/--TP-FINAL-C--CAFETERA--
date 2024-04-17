#ifndef PCF8575_H
#define pcd8575_H

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define PCF8575_ADDRESS 0x27
#define P0 0x0001
#define P1 0x0002
#define P2 0x0004
#define P3 0x0008
#define P4 0x0010
#define TODO 0XFFFF
#define NADA 0X0000

void EscribirPcf8575(uint16_t data);
void PrenderTodo();
void ApagarTodo();

#endif // PCF8575_H
