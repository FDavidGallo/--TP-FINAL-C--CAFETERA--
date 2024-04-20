/**
 * A PWM example for the ATmega328P using the 8-Bit Fast PWM mode.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

int main (void) {

	/**
	 * We will be using OCR1A as our PWM output register which is the
	 * same pin as PB1.
	 */
	DDRB |= _BV(PB1);

	/**
	 * There are quite a number of PWM modes available but for the
	 * sake of simplicity we'll just use the 8-bit Fast PWM mode.
	 * This is done by setting the WGM10 and WGM12 bits.  We 
	 * Setting COM1A1 tells the microcontroller to set the 
	 * output of the OCR1A pin low when the timer's counter reaches
	 * a compare value (which will be explained below).  CS10 being
	 * set simply turns the timer on without a prescaler (so at full
	 * speed).  The timer is used to determine when the PWM pin should be
	 * on and when it should be off.
	 */
	TCCR1A |= _BV(COM1A1) | _BV(WGM10);
	TCCR1B |= _BV(CS10) | _BV(WGM12);

	/**
	 *  This loop is used to change the value in the OCR1A register.
	 *  What that means is we're telling the timer waveform generator
	 *  the point when it should change the state of the PWM pin.
	 *  The way we configured it (with _BV(COM1A1) above) tells the
	 *  generator to have the pin be on when the timer is at zero and then
	 *  to turn it off once it reaches the value in the OCR1A register.
	 *
	 *  Given that we are using an 8-bit mode the timer will reset to zero
	 *  after it reaches 0xff, so we have 255 ticks of the timer until it
	 *  resets.  The value stored in OCR1A is the point within those 255
	 *  ticks of the timer when the output pin should be turned off
	 *  (remember, it starts on).
	 *
	 *  Effectively this means that the ratio of pwm / 255 is the percentage
	 *  of time that the pin will be high.  Given this it isn't too hard
	 *  to see what when the pwm value is at 0x00 the LED will be off
	 *  and when it is 0xff the LED will be at its brightest.
	 */
	uint8_t pwm = 0x00;
	bool up = true;
	for(;;) {

		OCR1A = pwm;

		pwm += up ? 1 : -1;
		if (pwm == 0xff)
			up = false;
		else if (pwm == 0x00)
			up = true;

		_delay_ms(10);
	}

}
