#ifndef FUNCIONESEPROM_H
#define FUNCIONESEPROM_H

#include <stdint.h>

// Escribe un byte en una dirección específica de la EEPROM
void EPROM_Write(uint16_t uiAddress, uint8_t ucData);

// Lee un byte de una dirección específica de la EEPROM
uint8_t EPROM_Read(uint16_t uiAddress);

// Escribe un string en la EEPROM comenzando desde una dirección específica
void EPROM_Write_String(uint16_t uiAddress, const char* string);

// Lee un string de la EEPROM comenzando desde una dirección específica
void EPROM_Read_String(uint16_t uiAddress, char* buffer, uint16_t length);

#endif // FUNCIONESEPROM_H
