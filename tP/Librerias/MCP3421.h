#ifndef MCP3421_H
#define MCP3421_H

#include <avr/io.h>

void TWI_ini(void);
void TWI_Start(void);
void TWI_Sendbyte(unsigned char byte);
void TWI_Receivebytes(void);
void TWI_Stop(void);
void MCP3421_config(void);
<<<<<<< Updated upstream
void MCP3421_read(void);
=======
int MCP3421_read(void);
int PesarAgua(void);
>>>>>>> Stashed changes

#endif // MCP3421_H
