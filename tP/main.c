// Inclusión de Librerias necesarias
	#include "Librerias/mcp9800.h"
	#include "Librerias/MCP3421.h"
	#include "Librerias/pcf857.h"
	#include "Librerias/LCD_I2C.h"
	#include "Librerias/i2c.h"
	#include "Librerias/UART.h"
	#include "Librerias/pines.h"
	#include "Librerias/PWM.h"
	#include "Librerias/ADC.h"
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include  <avr/eeprom.h>
	#include <avr/io.h>
	//
	#define cpu_1600000
	#define PCA8575_ADDRESS 0x20
	// Definición de pines para los sensores
	#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
	#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
	#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421

	// Configuración de la UART 
	#define BAUD_RATE 9600

	// Definición de variables Globales
	//Variables necesarias para las librerias
		int Temp1=0; //Necesaria para el mcp9800
		int resultado=12;//Necesaria para el mcp9800
		long int a1,a2,a3;//Necesaria para el mcp9800
		char sign;//Necesaria Para el Mcp3421
		float a;//Necesaria para el Mcp3421
		char str[12];//Buffer auxiliar del mcp3421
		char Buffer[24]; //Buffer usado para mandar datos por uart y lcd
	//Necesarias para los sensores
		
		int NivelPolvo1,NivelPolvo2, NivelPolvo3,NivelPolvo4; //Niveles de polvo de premezcla (medidos via adc, estan en porcentaje)
		int TemperaturaBidon;
		int PesoBidon;
		uint8_t SensorrTaza = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t SensorrPuerta = 0; // Estado del sensor de la puerta (0 o 1)
        uint8_t SelectorMenuLCD=0; // Menús de selección de bebidas
		uint8_t BotonSeleccionarr = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t BotonAceptarr = 0; // Estado del sensor de la puerta (0 o 1)
		volatile int ContadorSimultaneidad=0; // Esto va a contar cuanto tiempo vienen presionado en simultaneo los botones "Aceptar" y "Seleccionar"
		                                    // ATENCION: es del tipo volatile ya que cambien por interrupción
        int ContadorTiempo=0; // Esto va a contar cuanto tiempo vienen presionado en simultaneo los botones "Aceptar" y "Seleccionar"
										// ATENCION: es del tipo volatile ya que cambien por interrupción
        uint8_t Simultaneidad = 0; // ¿Hay simultaneidad de presionamiento de los botones por más de 5 segundos? (0 o 1)
											
// Configurar el Timer1 para que interrumpa 
void MedirBidon(void){
	TWI_ini(); //INCIALIZA EL i2c del mcp3421 (TIENE UNA CONFIGURACIÓN ESPECIAL, NO HAY QUE TOCAR)
	MCP3421_config(); //configura el sensor MCP3421
	PesoBidon=PesarAgua();
	TWI_Stop(); //cerramos
	TemperaturaBidon=LeerTemperatura();
}
void ControlarTemperatura (void){
	int Auxiliar=0;
	while (Auxiliar!=10) // Esto es para tener 10 ciclos de control por cada vez que se lo invoca
	{   TemperaturaBidon=LeerTemperatura();
		Auxiliar++;
		int Kp=1;
		int Error=90-TemperaturaBidon;
		PWM_update(Kp,Error);
	}
	
}
void MenuNivelesLcd(void){ //Esto se ejecuta só´lo si se han presionado "Seleccionar" y "Aceptar" por más de 5 segundos
	escribirEnLCD(" Medidas");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	escribirEnLCD("Niveles de");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	escribirEnLCD("Polvos %");
	SiguienteTextoLCD();
	escribirEnLCD("( en %)");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	 sprintf(Buffer, "%d", NivelPolvo1);
	escribirEnLCD(Buffer);
	SiguienteTextoLCD();
	 ControlarTemperatura();
	sprintf(Buffer, "%d", NivelPolvo2);
	escribirEnLCD(Buffer);
	SiguienteTextoLCD();
	 ControlarTemperatura();
	sprintf(Buffer, "%d", NivelPolvo3);
	escribirEnLCD(Buffer);
	SiguienteTextoLCD();
	 ControlarTemperatura();
	sprintf(Buffer, "%d", NivelPolvo4);
	escribirEnLCD(Buffer);
	SiguienteTextoLCD();
	 ControlarTemperatura();
	escribirEnLCD("Bidon:");
	SiguienteTextoLCD();
	escribirEnLCD(">Temperatura");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	sprintf(Buffer, "%d", TemperaturaBidon);
	escribirEnLCD(Buffer);
	escribirEnLCD("*C");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	escribirEnLCD(">Volumen");
	SiguienteTextoLCD();
	 ControlarTemperatura();
	sprintf(Buffer, "%d", PesoBidon);
	escribirEnLCD(Buffer);
	escribirEnLCD("ml");
	_delay_ms(1212);
	SiguienteTextoLCD();
	 ControlarTemperatura();
}
void IniciarTemporizador(void) {
	TCCR1B |= (1 << WGM12); // Modo CTC
	OCR1A = 64; // 
	TIMSK1 |= (1 << OCIE1A); // Habilitar interrupción por comparación
	TCCR1B |= (1 << CS11) | (1 << CS10); // 
}
// Rutina de servicio de interrupción para EL TEMPORIZADOR
ISR(TIMER1_COMPA_vect) {
	if ((BotonSeleccionarr == 1) && (BotonAceptarr == 1)) {
	     ContadorTiempo++;
		 Simultaneidad=0;
		 ControlarTemperatura(); // Para no perder control tanto tiempo
		} else {
		 // Reiniciar contador si el botón no está presionado
		ContadorTiempo=0;
		Simultaneidad=0;
	}
     if (ContadorTiempo == 3800) { //cada 1 segundo
		 MedirBidon(); // Se mide el bidón automaticamente cada un segundo, porque  
					   //  allí están nuestras variables controladas
	 }
		 // Incrementar el contador de tiempo

	if (ContadorTiempo == 18999) { // 4978 m ~5 seg
		 Simultaneidad=1; // 
		 //ControlarTemperatura(); //para evitar que se pierda mucho tiempo el control
		 ContadorTiempo = 0; // Reiniciar el contador de tiempo
		 sprintf(Buffer, "%d", Simultaneidad); // Convierte el entero a una cadena
		 uart_send_string(Buffer);
		  lcd_init();
		  MenuNivelesLcd();
		 i2c_stop();
	}
}
void LeerBotones(void) {
	BotonSeleccionarr = LeerBotonSeleccionar();
	BotonAceptarr = LeerBotonAceptar();

	if (BotonSeleccionarr == 1) {
		SelectorMenuLCD = SelectorMenuLCD + 1;
			if (SelectorMenuLCD == 5) {
				SelectorMenuLCD = 1;
				}

		while (BotonSeleccionarr == 1) {  // Para evitar rebotes
			if (Simultaneidad==0){
			BotonSeleccionarr = LeerBotonSeleccionar();}  // Esperar a que se suelte el botón
		}
			lcd_init(); // Inicializar el LCD
			switch (SelectorMenuLCD) {
			case 1:
			escribirEnLCD(" Bebida 1");
			break;
			case 2:
			escribirEnLCD(" Bebida 2");
			break;
			case 3:
			escribirEnLCD(" Bebida 3");
			break;
			case 4:
			escribirEnLCD(" Bebida 4");
			break;
			default:
			SelectorMenuLCD=1;
			escribirEnLCD(" Bebida 1");
			break;
		i2c_stop();}
	}
}
void LeerSensores(void){
	 SensorrTaza=LeerSensorTaza();
	 SensorrPuerta=LeerSensorPuerta();
	 } 
void MedicionPolvos(void){
	leer_ADC(0); // Lee el valor del pin PC0
	NivelPolvo1 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
    leer_ADC(1); // Lee el valor del pin PC0
    NivelPolvo2 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	 leer_ADC(2); // Lee el valor del pin PC0
	 NivelPolvo3 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	leer_ADC(3); // Lee el valor del pin PC0
	 NivelPolvo4 = ((float)ADC/1023)*100; // Guarda el valor del ADC en porcentaje (por eso dividimos por la resolución y por 100)
	};	

void MedirVariables(void){
		MedicionPolvos();
		MedirBidon();
        LeerSensores();
		LeerBotones();
	}
void ConfiguracionIncial(void){
	   iniciar_ADC();					// Inicializamos el ADC
       uart_init();						//Inicializamos la uart
	   ConfigurarPinesSensores();		//Configuramos los pines de los sensores 
	   ConfigurarBotones();				//Configuramos los botones.
	   IniciarTemporizador();           // Configuramos el timer.
	   PWM_init();                      // Configuramos el PWM
	   sei();                           // Habilitar interrupciones globales
   }
void MenuUart(void) {
	char DecisionMenuUart = echo_serial();
	uart_send_newline();
	switch (DecisionMenuUart) {
		case '1':
		MenuMediciones(PesoBidon,TemperaturaBidon,NivelPolvo1,NivelPolvo2,NivelPolvo3,NivelPolvo4);
		DecisionMenuUart=","; // Esto se va a repetir de ahora en adelante, es sólo para "limpiar" la variable.
		break;
		case '2':
		MenuConfiguraciones();
		DecisionMenuUart=",";
		break;
		case '3':
		Carpy();
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case '4':
		uart_send_newline();
		uart_send_string(">> Del siguiente listado, escoja que configurar:");
		MenuConfiguraciones();
		// Recibir Configuracion
		DecisionMenuUart=",";
		break;
		case 'A':
		DecisionMenuUart=",";
		break;
		case 'B':
		DecisionMenuUart=",";
		break;
		case 'C':
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'D':
		DecisionMenuUart=",";
		break;
		case 'E':
		Carpy();
		DecisionMenuUart=",";
		break;
		case 'F':
		DecisionMenuUart=",";
		break;
		case 'G':
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'H':
		DecisionMenuUart=",";
		break;
		case 'I':
		Carpy();
		break;
		case 'J':
		DecisionMenuUart=",";
		break;
		case 'K':
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'M':
		DecisionMenuUart=",";
		break;
		case 'L':
		Carpy();
		DecisionMenuUart=",";
		break;
		case 'O':
		DecisionMenuUart=",";
		break;
		case 'P':
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'Q':
		DecisionMenuUart=",";
		break;
		case 'R':
		DecisionMenuUart=",";
		break;
		case 'S':
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'T':
		DecisionMenuUart=",";
		break;
		case 'U':
		DecisionMenuUart=",";
		break;
		case 'V':
		DecisionMenuUart=",";
		break;
		case 'W':
		DecisionMenuUart=",";
		break;
		case 'X':
		MenuInicial();
		DecisionMenuUart=",";
		break;
		default:
		// Ninguna opción válida, continuar
		break;
	}
}

/*
==============================
vvvvvv   Función main  vvvvvvv
==============================
*/
   
int main(void){ 
	
	   ConfiguracionIncial();//Configuramos todo
	   Bienvenida();
	   EnviarTextoSeleccionarOpcion();
	   MenuInicial();
	while(1){	 
	MedirVariables();// Sensamos todas nuestras variables
	ControlarTemperatura(); //Controlamos la Temperatura
	MenuUart();
   
	
	}
	return 0;
} 

	

	