#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "ADC.h"
#define PD3 3
#define PD4 4

//volatile uint8_t pinState = 0;
//volatile uint32_t timerCounter = 0;

// Inicializa Timer0 para interrupci�n cada 1 ms
void Timer0_init() {
	TCCR0A = 0; // Establecer a cero
	TCCR0B = 0; // Establecer a cero
	TCNT0 = 0; // Inicializar contador

	// Establecer a CTC (Clear Timer on Compare Match)
	TCCR0A |= (1 << WGM01);

	// Establecer prescaler a 64 y empezar el timer
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Establecer valor de comparaci�n para 1ms
	OCR0A = 249;

	// Habilitar interrupci�n de comparaci�n A para Timer0
	TIMSK0 |= (1 << OCIE0A);

	// Habilitar interrupciones globales
}
/*
 * GccApplication1.c
 *
 * Created: 26/4/2024 22:21:09
 * Author : Usuario
 */ 

// Configuraci�n del Timer1 para interrumpir cada cierto intervalo
void setupTimer1() {
	TCCR1A = 0; // Poner registros a 0
	TCCR1B = 0; // Poner registros a 0

	// Establecer a CTC (Clear Timer on Compare Match)
	TCCR1B |= (1 << WGM12);

	// Establecer el valor de comparaci�n para el intervalo deseado
	OCR1A = 15624; // Este valor es un ejemplo, ajusta seg�n la frecuencia del reloj y el intervalo deseado

	// Habilitar la interrupci�n por comparaci�n de Timer1
	TIMSK1 |= (1 << OCIE1A);

	// Establecer el prescaler a 1024 y arrancar el timer
	TCCR1B |= (1 << CS12) | (1 << CS10);
}
 /*
// ISR para Timer1 Compare Match
ISR(TIMER1_COMPA_vect) {
	cli();
	// Cambiar el valor de myChar aqu�
	myChar = 0;
	uart_send_newline();
}

int main(void) {
	ConfigurarBotones();
	setupTimer1(); // Configurar el Timer
	Timer0_init();
	 // Habilitar interrupciones globales
    uart_init();
	while(1) {
		sei();
		// El c�digo principal va aqu�
		// Puedes verificar el valor de myChar y hacer algo con �l
		char Buffer[2];
		_delay_ms(4444);
		sprintf(Buffer, "%d", myChar);
		uart_send_string(Buffer);
	}
	
}

ISR(TIMER0_COMPA_vect) {
	// Incrementar contador de tiempo
	cli();
	timerCounter++;

	// Leer estado de los pines PD3 y PD4
	pinState = PIND & ((1 << PD3) | (1 << PD4));

	// Si ambos pines est�n en bajo y el contador ha alcanzado 5000 (5 segundos)
	if (pinState == 0 && timerCounter >= 5000) {
		// Aqu� se coloca el c�digo a ejecutar cuando se cumple la condici�n
		// ...
		uart_send_newline();
		uart_send_string(" UwU ");
		uart_send_newline();
		myChar = 4;
		// Reiniciar contador
		timerCounter = 0;
	}
}


#include "ADC.h"
#include "UART.h"
#include "timer.h"
#include "pines.h"
//#include "ADC.h"

// Interrupci�n cada 1 ms


// Inicializa Timer1 para interrupci�n cada 300 ms


// Interrupci�n cada 300 m*/
