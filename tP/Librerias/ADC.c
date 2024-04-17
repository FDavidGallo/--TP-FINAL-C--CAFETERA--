

#include "ADC.h"

void iniciar_ADC(void){
ADMUX |= (1 << REFS0); // Voltaje de referencia AVCC con capacitor externo en AREF (tension de referencia)
ADMUX &= ~(1 << ADLAR); // ADC derecho justificado, los bits mas significativos se ubicaran en los bits mas altos del registo de resultado ADC
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Prescaler en 128, divide la frecuencia del ADC por 128, esto hace que la conversion sea mas lenta pero precisa.
ADCSRA |= (1 << ADEN); // Habilita el ADC, el bit ADEN en 1 permite que se realicen las conversiones ADC
}

void leer_ADC(char canal){
ADMUX &= 0xF0; // Limpiar bits de selección de canal, hace una AND con 0xF0 (11110000) es para asegurar que los bits de seleccion de canal esten en 0 antes de seleccionarlos
ADMUX |= (0x00+canal); // Selecciona el pin analogico que deseamos, en el main por ej utilizamos con canales a0 (canal 0) y a1 (canal 1)
ADCSRA |= (1 << ADSC); // Iniciar conversión
while(ADCSRA & (1 << ADSC)); // Espera a que termine la conversión
}