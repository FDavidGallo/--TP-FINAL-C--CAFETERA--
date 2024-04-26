#ifndef FUNCIONESEPROM_H
#define FUNCIONESEPROM_H

#include <stdint.h>

// Escribe un byte en una direcci�n espec�fica de la EEPROM
void EPROM_Write(uint16_t uiAddress, uint8_t ucData);

// Lee un byte de una direcci�n espec�fica de la EEPROM
uint8_t EPROM_Read(uint16_t uiAddress);

// Escribe un string en la EEPROM comenzando desde una direcci�n espec�fica
void EPROM_Write_String(uint16_t uiAddress, const char* string);

// Lee un string de la EEPROM comenzando desde una direcci�n espec�fica
void EPROM_Read_String(uint16_t uiAddress, char* buffer, uint16_t length);

#endif // FUNCIONESEPROM_H
