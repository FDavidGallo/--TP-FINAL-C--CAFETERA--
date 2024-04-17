// pines.h
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta
#ifndef PINES_H
#define PINES_H


// Define the pin numbers for sensors
#define SENSOR_PIN_1 PD3
#define SENSOR_PIN_2 PD4

// Function to configure sensor pins as digital inputs
void ConfigurarPinesSensores();
void write_int_to_eeprom(int value, int address);
char int_to_char(int value);
#endif // PINES_H
