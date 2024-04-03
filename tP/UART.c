
#include "UART.h"
void uart_init() {
	// Configurar la velocidad de transmisión a 9600
	UBRR0H = 0;
	UBRR0L = 103;

	// Habilitar el transmisor y el receptor
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// Configurar el formato del trama: 8 bits de datos, 1 bit de parada
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Enviar un solo carácter por la UART
void uart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar hasta que el buffer esté vacío
	UDR0 = c;
}

// Enviar una cadena (texto) terminada en nulo por la UART
void uart_send_string(const char* str) {
	while (*str) {
		uart_send_char(*str);
		str++;
	}
}

// Enviar un carácter de salto de línea por la UART
void uart_send_newline() {
	uart_send_char(13);
	uart_send_char(10);
}

// Recibir un carácter desde la UART
char uart_receive_char() {
	while (!(UCSR0A & (1 << RXC0))); // Esperar hasta que se reciba un dato
	char recibido = UDR0;
	return recibido;
}

void Carpy() {
	uart_send_string("                        90  400     TPFI... CATEDRA:    SISTEMAS DIGITALES IV");
	uart_send_newline();
	uart_send_string("                     1232800000000                    PROFESORES: ING EDUARDO VELAZQUEZ");
	uart_send_newline();
	uart_send_string("                400000000000000007                                LIC JULIAN MINATEL   ");
	uart_send_newline();
	uart_send_string("             400000000000  300000005      NOMBRE: FABRICIO DAVID GALLO                 ");
	uart_send_newline();
	uart_send_string("            0000 800000000000000000000                                    ");
	uart_send_newline();
	uart_send_string("           40000000000000000000000000000            'CAFETERA' ES UN PROYECTO DONDE SE " );
	uart_send_newline();
	uart_send_string("           700000000000000000000000000000007              PUEDEN CONTROLAR TEMPERATURA, ");
	uart_send_newline();
	uart_send_string("            00000000000000000000000000000000000000000004      CANTIDAD DE PREMEZCLA,ETC  ");
	uart_send_newline();
	uart_send_string("             800000000000000000000000000000000000000000000001      PARA MODIFICAR ESTOS  ");
	uart_send_newline();
	uart_send_string("                  000000000000000000000000000000000000000000006       UTILICE LA UART   " );
	uart_send_newline();
	uart_send_string("                     10000000000000000000000000000000000000000001 ");
	uart_send_newline();
	uart_send_string("                      00000000000000000000000000000000000000000000 ");
	uart_send_newline();
	uart_send_string("                        900000000000000000000000000000000000000000000 ");
	uart_send_newline();
	uart_send_string("       1  1             9000000000000000000000000000000000000000000000 ");
	uart_send_newline();
	uart_send_string("        1  1             000000000000000000000000000000000000000000000");
	uart_send_newline();
	uart_send_string("       1  1              9000000000000000000000000000000000000000000008 ");
	uart_send_newline();
	uart_send_string("     00000000037          600000000000000000000000000000000000000000005 ");
	uart_send_newline();
	uart_send_string("     000000009  9          0000000000000000000000000000000000000000000  ");
	uart_send_newline();
	uart_send_string("     0000000002            900000000000000000000000000000000000000000  ");
	uart_send_newline();
	uart_send_string("     000000009             900 00002 50000000000000000000000000000000   ");
	uart_send_newline();
	uart_send_string("     000000006             900 8006       70000000000000000000000000  ");
	uart_send_newline();
	uart_send_string("  444666666666445         30006000                50000000000000000   ");
	uart_send_newline();
}
// Función para el eco serial
char echo_serialMenu() {
		char input = uart_receive_char();
		uart_send_char(input);
		uart_send_newline();
		char recibido=input;
		if (recibido=='3') {
			Carpy();
			
		}
		if (recibido=='1') {
			Opcion1();
			
		}
		return recibido;
}
void Opcion1() {
	uart_send_string("Editar valores");
	uart_send_newline();
}
char echo_serial() {
	char input = uart_receive_char();
	uart_send_char(input);
	uart_send_newline();
	char recibido=input;
	return recibido;
}