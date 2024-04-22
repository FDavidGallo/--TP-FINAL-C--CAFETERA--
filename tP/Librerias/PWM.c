#include "PWM.h"


// Inicializa el PWM y el Timer 2
void PWM_init(void) {
	// Configura el puerto B como salida
	DDRB |= (1 << PB3); // PB3 es OC2A en ATmega328P

	// Configura el Timer 2 en modo Fast PWM
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << CS21); // Prescaler: divide el reloj por 8

	// Configura el modo no invertido
	TCCR2A |= (1 << COM2A1);
}

// Función para actualizar el valor de PWM basado en la diferencia de entrada e
void PWM_update(int Error,int Kp) {
	// Calcula el valor de PWM basado en k * e
	int pwm_value = Kp * Error;

	// Limita el valor de PWM al rango de 0 a 255
	if (pwm_value > 255) {
		pwm_value = 255;
		} else if (pwm_value < 0) {
		pwm_value = 0;
	}

	// Actualiza el valor de PWM
	OCR2A = pwm_value;
}
