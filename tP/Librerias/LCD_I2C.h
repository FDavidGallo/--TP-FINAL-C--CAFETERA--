#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <avr/io.h>
#include <util/delay.h>
void lcd_init();
void enviarPulsoEnable();
void enviarComando4Bits(char);
void enviarComando(char);
void escribirDato(char);
void escribirEnLCD(char *c);
void limpiar_LCD();

extern int ejecucionUnica;
#endif
