
#ifndef UART_H_
#define UART_H_

//#define F_CPU 16000000
#include <avr/io.h>
;;;;;;;
void USART_Transmit(uint8_t data);
//void MenuUart();
void uart_init(void);
void uart_send_char(char c);
void Bienvenida(void);
void MenuInicial(void);
void uart_send_string(const char* str);
void uart_send_newline();
char echo_serial();
char uart_receive_char();
void Carpy();
char echo_serialMenu();
void MenuMediciones(int PesoBidon,int TemperaturaBidon, int NivelPolvo1,int NivelPolvo2,int NivelPolvo3,int NivelPolvo4);
void MenuCambiarVolumenBidon(void);
void MenuConfiguraciones(void);
void MandarStringdesdePrograma(const char *str);
void MenuCambioDeNombre(void);
void Fracaso(void);
void CambioDeNumero(void);
#include <util/delay.h>
#include <stdio.h>

#endif /* UART_H_ */