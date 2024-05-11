#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "ADC.h"
#define PD3 3
#define PD4 4

//volatile uint8_t pinState = 0;
//volatile uint32_t timerCounter = 0;

// Inicializa Timer0 para interrupción cada 1 ms
void Timer0_init() {
	TCCR0A = 0; // Establecer a cero
	TCCR0B = 0; // Establecer a cero
	TCNT0 = 0; // Inicializar contador

	// Establecer a CTC (Clear Timer on Compare Match)
	TCCR0A |= (1 << WGM01);

	// Establecer prescaler a 64 y empezar el timer
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Establecer valor de comparación para 1ms
	OCR0A = 255;

	// Habilitar interrupción de comparación A para Timer0
	TIMSK0 |= (1 << OCIE0A);

}


// Configuración del Timer1 para interrumpir cada cierto intervalo
void setupTimer1() {
	TCCR1A = 0; // Poner registros a 0
	TCCR1B = 0; // Poner registros a 0

	// Establecer a CTC (Clear Timer on Compare Match)
	TCCR1B |= (1 << WGM12);

	// Establecer el valor de comparación para el intervalo deseado
	OCR1A = 15624; // Este valor nos da, pero se puede ajustar

	// Habilitar la interrupción por comparación de Timer1
	TIMSK1 |= (1 << OCIE1A);

	// Establecer el prescaler a 1024 y arrancar el timer
	TCCR1B |= (1 << CS12) | (1 << CS10);
}
 
 
 
