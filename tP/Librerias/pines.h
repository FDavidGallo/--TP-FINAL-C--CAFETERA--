// pines.h
#define PD3 3 // Pin 3 (PD3) -- Sensor Taza
#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta
#define PPD5 5 // 
#define PPD6 6 // 
#ifndef PINES_H
#define PINES_H

int LeerSensorTaza(void);
int LeerSensorPuerta(void);
void ConfigurarPinesSensores(void);
void ConfigurarBotones(void);
int LeerBotonSeleccionar(void);
int LeerBotonAceptar(void);

#endif // PINES_H
