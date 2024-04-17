
#ifndef UART_H_
#define UART_H_

//#define F_CPU 16000000
#include <avr/io.h>
char recibido;
void USART_Transmit(uint8_t data);
//void MenuUart();
void Opcion1();
void uart_init();
void uart_send_char(char c);
void uart_send_string(const char* str);
void uart_send_newline();
char echo_serial();
char uart_receive_char();
void Carpy();
char echo_serialMenu();
#include <util/delay.h>
#include <stdio.h>

#endif /* UART_H_ */