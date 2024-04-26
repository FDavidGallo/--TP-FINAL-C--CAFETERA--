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
	#include "Librerias/FuncionesEeprom.h"
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include  <avr/eeprom.h>
	#include <avr/io.h>
	#include <stdlib.h> 
	//
	#define cpu_1600000
	#define PCA8575_ADDRESS 0x20
	// Definición de pines para los sensores
	#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
	#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
	#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421

	// Configuración de la UART 
	#define BAUD_RATE 9600

/***
 *                                                                                                                         
 *     #    #   ##   #####  #   ##   #####  #      ######  ####     ####  #       ####  #####    ##   #      ######  ####  
 *     #    #  #  #  #    # #  #  #  #    # #      #      #        #    # #      #    # #    #  #  #  #      #      #      
 *     #    # #    # #    # # #    # #####  #      #####   ####    #      #      #    # #####  #    # #      #####   ####  
 *     #    # ###### #####  # ###### #    # #      #           #   #  ### #      #    # #    # ###### #      #           # 
 *      #  #  #    # #   #  # #    # #    # #      #      #    #   #    # #      #    # #    # #    # #      #      #    # 
 *       ##   #    # #    # # #    # #####  ###### ######  ####     ####  ######  ####  #####  #    # ###### ######  ####  
 *                                                                                                                         
 */

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
		int Auxiliar;
		uint8_t SensorrTaza = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t SensorrPuerta = 0; // Estado del sensor de la puerta (0 o 1)
        uint8_t SelectorMenuLCD=0; // Menús de selección de bebidas
		uint8_t BotonSeleccionarr = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t BotonAceptarr = 0; // Estado del sensor de la puerta (0 o 1)
		volatile int ContadorAuxiliar=0; // Esto va a contar cuanto tiempo vienen presionado en simultaneo los botones "Aceptar" y "Seleccionar"
		                                    // ATENCION: es del tipo volatile ya que cambien por interrupción
         volatile int ContadorTiempo=0; // Esto va a contar cuanto tiempo vienen presionado en simultaneo los botones "Aceptar" y "Seleccionar"
										// ATENCION: es del tipo volatile ya que cambien por interrupción
        uint8_t Simultaneidad = 0; // ¿Hay simultaneidad de presionamiento de los botones por más de 5 segundos? (0 o 1)
		char DecisionMenuUart ;

/***
 *                                                                                                                             
 *     #    #   ##   #####  #   ##   #####  #      ######  ####    ###### #    #     ###### ###### #####  #####   ####  #    # 
 *     #    #  #  #  #    # #  #  #  #    # #      #      #        #      ##   #     #      #      #    # #    # #    # ##  ## 
 *     #    # #    # #    # # #    # #####  #      #####   ####    #####  # #  #     #####  #####  #    # #    # #    # # ## # 
 *     #    # ###### #####  # ###### #    # #      #           #   #      #  # #     #      #      #####  #####  #    # #    # 
 *      #  #  #    # #   #  # #    # #    # #      #      #    #   #      #   ##     #      #      #      #   #  #    # #    # 
 *       ##   #    # #    # # #    # #####  ###### ######  ####    ###### #    #     ###### ###### #      #    #  ####  #    # 
 *                                                                                                                             
 */ 
// Atención: B1=Bebida1 ; B2=Bebida2; B3=Bebida3;B 4=Bebida4. CAgua=Cantidad de Agua caliente. 
//========== PorcDescarga=Porcentaje del tiempo de descarga extra al que es igual al "tiempo de dosificación" (ver documentación para mayor detalle)
// Si tienen una P al final es porque pertenecen al programa, no a la eprom...
// Las direcciones son:
	#define NombreB1 10
	#define NombreB2 25
	#define NombreB3 40
	#define NombreB4 55
	#define DosificacionB1 280
	#define DosificacionB2 70
	#define DosificacionB3 80
	#define DosificacionB4 90
    #define CAguaB1 100
	#define CAguaB2 110
	#define CAguaB3 120
	#define CAguaB4 130
	#define PorcDescargaB1 140
	#define PorcDescargaB2 145
	#define PorcDescargaB3 150
	#define PorcDescargaB4 155
	#define TamagnoBidon 160
	#define KpEprom 170
	#define TemperaturaDeseada 180


/***
 *     #######                                                                 #     #                                                                    
 *     #        #    #  #    #   ####   #   ####   #    #  ######   ####       ##    #  ######   ####   ######   ####     ##    #####   #    ##     ####  
 *     #        #    #  ##   #  #    #  #  #    #  ##   #  #       #           # #   #  #       #    #  #       #        #  #   #    #  #   #  #   #      
 *     #####    #    #  # #  #  #       #  #    #  # #  #  #####    ####       #  #  #  #####   #       #####    ####   #    #  #    #  #  #    #   ####  
 *     #        #    #  #  # #  #       #  #    #  #  # #  #            #      #   # #  #       #       #            #  ######  #####   #  ######       # 
 *     #        #    #  #   ##  #    #  #  #    #  #   ##  #       #    #      #    ##  #       #    #  #       #    #  #    #  #   #   #  #    #  #    # 
 *     #         ####   #    #   ####   #   ####   #    #  ######   ####       #     #  ######   ####   ######   ####   #    #  #    #  #  #    #   ####  
 *                                                                                                                                                        
 */
void ConfiguracionPredeterminada(void){
	char BufferAuxiliar[10]="2";
	EPROM_Write_String(TamagnoBidon, BufferAuxiliar); // Por defecto el bidón es de 20 litros
	char BufferAuxiliar0[10]="CAFFE";
	EPROM_Write_String(NombreB1, BufferAuxiliar0); // 
	EPROM_Read_String(NombreB1, Buffer, 10);//  
	uart_send_string(" ->");
	uart_send_string(Buffer);
	char BufferAuxiliar2[10]="TE";
	EPROM_Write_String(NombreB2, BufferAuxiliar2); //
	EPROM_Read_String(NombreB2, Buffer, 10);//
	uart_send_string(" ->");
	uart_send_string(Buffer);
	char BufferAuxiliar3[10]="YERBIADO";
	EPROM_Write_String(NombreB3, BufferAuxiliar3); //
	EPROM_Read_String(NombreB3, Buffer, 10);//
	uart_send_string(" ->");
	uart_send_string(Buffer);
	char BufferAuxiliar4[10]="LATTE";
	EPROM_Write_String(NombreB4, BufferAuxiliar4); //
	EPROM_Read_String(NombreB4, Buffer, 10);//
	uart_send_string(" ->");
	uart_send_string(Buffer);
}
	
void ConfiguracionIncialEeprom(void){
	// Esta configuración Inicial sólo se dá si anteriormente el micro no trabajó con este programa, para ello,
	// nos fijamos si el tamaño del bidón en la eprom tiene un valor en decilitros válido (1 o 2).
	EPROM_Read_String(TamagnoBidon, Buffer, 10);// 10, para estar seguros 
	int VerificadorEprom=atoi(Buffer); // Atoi busca el tamaño del bidón, guardado como ASCII y lo  guarda en "VerificadorEeprom"
	if ((VerificadorEprom!=1)&(VerificadorEprom!=2)){ // Caso en que el tamaño del bidón no sea o 1 o 2, hay que configurar los valores de la eprom
		ConfiguracionPredeterminada();
		uart_send_newline();
		uart_send_string(" La cafetera fue configurada exitosamente :)");
	}
	else { // Caso contrario la cafetera está configurada y lista para ser usada
	uart_send_newline();
	uart_send_string("La cafetera esta configurada y lista :)");} // le notificamos de eso al técnico
}								
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

void LeerBotones(void) {
	BotonSeleccionarr = LeerBotonSeleccionar();
	BotonAceptarr = LeerBotonAceptar();

	if (BotonSeleccionarr == 1) {
		SelectorMenuLCD = SelectorMenuLCD + 1;
			if (SelectorMenuLCD == 5) {
				SelectorMenuLCD = 1;
				}

		/*while (BotonSeleccionarr == 1) {  // Para evitar rebotes
			if (Simultaneidad==0){
			BotonSeleccionarr = LeerBotonSeleccionar();}  // Esperar a que se suelte el botón
		}*/
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
	   Bienvenida();
	   ConfiguracionIncialEeprom();     // Verificamos que la configuración inicial esté en la eprom, caso contrario la configuramos
	   MenuInicial();                   // Menu de inicio owo
	  
	   sei();                           // Habilitar interrupciones globales
   }
void MenuUart(void) {
	DecisionMenuUart=echo_serial();
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


/* ===========================================================================================================
 *     #######  #     #  #     #   #####   ###  #######  #     #          #     #     #     ###  #     # 
 *     #        #     #  ##    #  #     #   #   #     #  ##    #          ##   ##    # #     #   ##    # 
 *     #        #     #  # #   #  #         #   #     #  # #   #          # # # #   #   #    #   # #   # 
 *     #####    #     #  #  #  #  #         #   #     #  #  #  #          #  #  #  #     #   #   #  #  # 
 *     #        #     #  #   # #  #         #   #     #  #   # #          #     #  #######   #   #   # # 
 *     #        #     #  #    ##  #     #   #   #     #  #    ##          #     #  #     #   #   #    ## 
 *     #         #####   #     #   #####   ###  #######  #     #          #     #  #     #  ###  #     # 
 *                                                                                                       
 * ==========================================================================================================*/

   
int main(void){ 
	    char data_to_write[2]="03";
	   	EPROM_Write_String(TamagnoBidon, data_to_write);
	   ConfiguracionIncial();//Configuramos todo
	 //  EnviarTextoSeleccionarOpcion();
	  

	
	while(1){	 
	MenuUart();
   
	
	}
	return 0;
} 


/***
 *     ###  #     #  #######  #######  ######   ######   #     #  ######    #####   ###  #######  #     #  #######   #####  
 *      #   ##    #     #     #        #     #  #     #  #     #  #     #  #     #   #   #     #  ##    #  #        #     # 
 *      #   # #   #     #     #        #     #  #     #  #     #  #     #  #         #   #     #  # #   #  #        #       
 *      #   #  #  #     #     #####    ######   ######   #     #  ######   #         #   #     #  #  #  #  #####     #####  
 *      #   #   # #     #     #        #   #    #   #    #     #  #        #         #   #     #  #   # #  #              # 
 *      #   #    ##     #     #        #    #   #    #   #     #  #        #     #   #   #     #  #    ##  #        #     # 
 *     ###  #     #     #     #######  #     #  #     #   #####   #         #####   ###  #######  #     #  #######   #####  
 *                                                                                                                          
 */
	
ISR(TIMER1_COMPA_vect) {
	ContadorAuxiliar++;
		
	if (ContadorAuxiliar==60){
		MedirVariables();
	}
	if (ContadorAuxiliar==120){
		ControlarTemperatura();
		ContadorAuxiliar=0;
	}
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

	