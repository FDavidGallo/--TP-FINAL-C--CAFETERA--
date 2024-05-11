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
    #include "Librerias/timer.h"
	#include "Librerias/FuncionesDerivadas.h"
	#include "Librerias/ControlValvulas.h"
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include  <avr/eeprom.h>
	#include <avr/io.h>
	#include <stdlib.h> 
	// DEFINICIONES NECESARIAS
	#define cpu_1600000
	#define PCA8575_ADDRESS 0x20
	// Definición de pines para los sensores
	#define PD3 3 // Pin 3 (PD3) -- Sensor Taza 
	#define PD4 4 // Pin 4 (PD4) -- Sensor Puerta 
	#define MCP3421_ADDRESS 0x68 // Direccion I2C del Mcp3421
	

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
		int Aux;
		char VectorTamagnoBidon[2];
		int NivelPolvo1,NivelPolvo2, NivelPolvo3,NivelPolvo4; //Niveles de polvo de premezcla (medidos via adc, estan en porcentaje)
		volatile int TemperaturaBidon;
		volatile int PesoBidon;
		volatile int Auxiliar;
		uint8_t SensorrTaza = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t SensorrPuerta = 0; // Estado del sensor de la puerta (0 o 1)
        uint8_t SelectorMenuLCD=0; // Menús de selección de bebidas
		uint8_t BotonSeleccionarr = 0; // Estado del sensor de la taza (0 o 1)
		uint8_t BotonAceptarr = 0; // Estado del sensor de la puerta (0 o 1)
		volatile uint8_t pinState = 0;
		volatile uint32_t timerCounter = 0; // tiene que llegar a 5 mil, por eso le mando un formato grande, cosa de no quedarme cortp
        volatile int  Simultaneidad = 0; // ¿Hay simultaneidad de presionamiento de los botones por más de 5 segundos? (0 o 1)
		volatile char DecisionMenuUart ;
		volatile int ContadorControlarBotones=0;
		volatile uint8_t BanderaServido=0; //Esta la usaremos para indicar si hay que servir alguna bebidda
		uint8_t BanderaBienvenida = 0;
		volatile uint8_t BanderaError=0;
          volatile  char received_data;
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
// Algunas tiene un "Tipo", este es un caracter que se le asigna tal que despues podamos definir sus condiciones de entrada de la modificacion
// de datos vía UART.   ATENCIÓN:
//
//   TIPO 'D' --> DOSIFICADORES (CANTIDAD DE PREMEZCLA)--> 0 a 420 mL
//   TIPO 'A' --> CANTIDAD DE AGUA --> 150 a 300 mL
//   TIPO 'P' --> PORCENTAJE DE TIEMPO DE DESCARGA --> 5% AL 25%
//   TIPO 'V' --> TAMAÑO DEL BIDÓN --> 1 A 2 DL (DECALITROS)
//   TIPO 'K' --> CONSTANTE PROPORCIONAL (KP) --> 0 A 100
//   TIPO 'T' -->  TEMPERATURA DESEADA --> (60-95)*C
//
// Las direcciones son:
	#define NombreB1 10
	#define NombreB2 25
	#define NombreB3 40
	#define NombreB4 55
	#define DosificacionB1 280 // TIPO D
	#define DosificacionB2 70  // TIPO D
	#define DosificacionB3 80  // TIPO D
	#define DosificacionB4 90  // TIPO D
    #define CAguaB1 100        // TIPO A
	#define CAguaB2 110		   // TIPO A
	#define CAguaB3 120		   // TIPO A
	#define CAguaB4 130        // TIPO A
	#define PorcDescargaB1 140 // TIPO P
	#define PorcDescargaB2 145 // TIPO P
	#define PorcDescargaB3 150 // TIPO P
	#define PorcDescargaB4 155 // TIPO P
	#define TamagnoBidon 160   // TIPO V
	#define KpEprom 170        // TIPO K
	#define TemperaturaDeseada 180 //TIPO T


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
void DetectarError(void){
	 SensorrTaza=LeerSensorTaza();
	 SensorrPuerta=LeerSensorPuerta();
	 BanderaError=SensorrPuerta||SensorrTaza;
	if(BanderaError!=0){
		lcd_init();
		limpiar_LCD();
		lcd_init();
		escribirEnLCD(" ERROR PUERTA ");
		_delay_ms(711);
		limpiar_LCD();
		escribirEnLCD(" ABIERTA O");
		_delay_ms(711);
		limpiar_LCD();
		escribirEnLCD(" TAZA MAL PUESTA");
		_delay_ms(711);
		limpiar_LCD();
		uart_send_newline();
		uart_send_string(">>ERROR: Cierre la puerta o coloque bien la taza para continuar...")
		;
		ApagarTodo(); // Por las dudas
		asm volatile ("jmp 0"); // Reiniciamos el micro
	
	}}
void Servido (void){
	DetectarError();
	if ((BanderaServido!=0)&&(BanderaError==0)){
			lcd_init();
		limpiar_LCD();
	   uart_send_newline();
	     uart_send_string("Se inició el servido...");
		 uart_send_string("Consola bloqueada hasta terminar  el proceso...");
		escribirEnLCD(" Sirviendo...");
		_delay_ms(15);
		SeleccionarMedida(SelectorMenuLCD);
			lcd_init();
			limpiar_LCD();
		BanderaServido=0;	
		uart_send_string(">>Servido finalizado");																																																																			//;main(); // Terminada la operacion de servido, volvamos a la main. 
	}else{DetectarError();}
	
}
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
	char BufferAuxiliar5[5]="100"; //Por defecto todas las bebidas dosifican 100 mL
	EPROM_Write_String(DosificacionB1, BufferAuxiliar5); // 
    EPROM_Write_String(DosificacionB2, BufferAuxiliar5); //
	EPROM_Write_String(DosificacionB3, BufferAuxiliar5); //
	EPROM_Write_String(DosificacionB4, BufferAuxiliar5); //
	char BufferAuxiliar6[5]="200"; //Por defecto todas las se llenan con 200mL
	EPROM_Write_String(CAguaB1,BufferAuxiliar6); //
	EPROM_Write_String(CAguaB2,BufferAuxiliar6); //
	EPROM_Write_String(CAguaB3,BufferAuxiliar6); //
	EPROM_Write_String(CAguaB4,BufferAuxiliar6); //
	char BufferAuxiliar7[5]="10"; //Por defecto EL PORCENTAJE DE TIEMPO DE DESCARGA ES DEL 10%
	EPROM_Write_String(PorcDescargaB1,BufferAuxiliar7); //
	EPROM_Write_String(PorcDescargaB2,BufferAuxiliar7); //
	EPROM_Write_String(PorcDescargaB3,BufferAuxiliar7); //
	EPROM_Write_String(PorcDescargaB4,BufferAuxiliar7); //
	char BufferAuxiliar8[5]="2"; //Por defecto el tamaño del bidón es de 20 litros
	EPROM_Write_String(TamagnoBidon,BufferAuxiliar8); //
	char BufferAuxiliar9[5]="85"; //Por defecto la temperatura deseada es de 85*C
	EPROM_Write_String(TemperaturaDeseada,BufferAuxiliar9); //
	char BufferAuxiliar10[5]="1"; //Por DEFECTO LA CONSTANTE PROPORCIONAL ES 1
	EPROM_Write_String(KpEprom,BufferAuxiliar10); //
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
	MedirBidon(); // Medimos tanto volumen de agua como su temperatura
	int Auxiliar=0;
	while (Auxiliar!=5) // Esto es para tener 5 ciclos de control por cada vez que se lo invoca
	{   
		Auxiliar++;
		EPROM_Read_String(KpEprom,Buffer,4);
		int Kp=atoi(Buffer);
		EPROM_Read_String(TemperaturaDeseada,Buffer,4);
		int TemperaturaSetpoinr=atoi(Buffer);
		int Error=TemperaturaSetpoinr-TemperaturaBidon;
		if(PesoBidon!=0) // Si no hay agua que no caliente 
		{
		PWM_update(Kp,Error);}
		else{PWM_update(1,0);}} //Si no hay agua hacemos que el error sea 0, tal que no controle la temperatura
	}
	
void MenuNivelesLcd(void){ //Esto se ejecuta só´lo si se han presionado "Seleccionar" y "Aceptar" por más de 5 segundos
	cli();
	i2c_stop();
	i2c_init();
	lcd_init();
	escribirEnLCD(" Medidas");
	_delay_ms(2111);
	limpiar_LCD();
	escribirEnLCD(" Niveles de");
	_delay_ms(2111);
	limpiar_LCD();
	escribirEnLCD(" Polvos %");
	_delay_ms(2111);
	limpiar_LCD();
	escribirEnLCD(" ( en %)");
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");// Este espacio soluciona un bug
	EPROM_Read_String(NombreB1, Buffer, 10);//
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	 sprintf(Buffer, "%d", NivelPolvo1);
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	EPROM_Read_String(NombreB2, Buffer, 10);//
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	limpiar_LCD();
	escribirEnLCD(" ");
	sprintf(Buffer, "%d", NivelPolvo2);
	escribirEnLCD(Buffer);
_delay_ms(4111);
limpiar_LCD();
escribirEnLCD(" ");
EPROM_Read_String(NombreB3, Buffer, 10);//
escribirEnLCD(Buffer);
_delay_ms(4111);
limpiar_LCD();
escribirEnLCD(" ");
	sprintf(Buffer, "%d", NivelPolvo3);
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	EPROM_Read_String(NombreB4, Buffer, 10);//
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	limpiar_LCD();
	escribirEnLCD(" ");
	sprintf(Buffer, "%d", NivelPolvo4);
	escribirEnLCD(Buffer);
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" Bidon:");
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	escribirEnLCD(">Temperatura");
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	sprintf(Buffer, "%d", TemperaturaBidon);
	escribirEnLCD(Buffer);
	escribirEnLCD("*C");
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	escribirEnLCD(">Volumen");
	_delay_ms(4111);
	limpiar_LCD();
	escribirEnLCD(" ");
	sprintf(Buffer, "%d", PesoBidon);
	escribirEnLCD(Buffer);
	escribirEnLCD("ml");
	_delay_ms(1212);
	_delay_ms(4111);
	limpiar_LCD();
}



void LeerBotones(void) {
	BotonSeleccionarr = LeerBotonSeleccionar();
	BotonAceptarr = LeerBotonAceptar();
	if (BanderaServido==0){
	if (BotonSeleccionarr == 1) {
		SelectorMenuLCD = SelectorMenuLCD + 1;
			if (SelectorMenuLCD == 5) {
				SelectorMenuLCD = 1;
				}
			lcd_init(); // Inicializar el LCD
			 
			 if (Simultaneidad==1){
				MenuNivelesLcd();
			 Simultaneidad=0;
		 }
			switch (SelectorMenuLCD) {
			case 1:
			EPROM_Read_String(NombreB1, Buffer, 10);//
			escribirEnLCD("-"); // Esto arregla un bug
			escribirEnLCD(Buffer);
			break;
			case 2:
			EPROM_Read_String(NombreB2, Buffer, 10);//
			escribirEnLCD("-"); // Esto arregla un bug
			escribirEnLCD(Buffer);
			break;
			case 3:
			EPROM_Read_String(NombreB3, Buffer, 10);//
			escribirEnLCD("-"); // Esto arregla un bug
			escribirEnLCD(Buffer);
			break;
			case 4:
			EPROM_Read_String(NombreB4, Buffer, 10);//
			escribirEnLCD("-"); // Esto arregla un bug
			escribirEnLCD(Buffer);
			break;
			default:
			SelectorMenuLCD=1;
			LeerBotones();
			break;
			
		i2c_stop();}
	}
	}}
void LeerSensores(void){
	 SensorrTaza=LeerSensorTaza();
	 SensorrPuerta=LeerSensorPuerta();
	 BanderaError=SensorrPuerta||SensorrTaza;
	 if(BanderaError!=0){DetectarError();}
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
	   ApagarTodo();					//Apagamos todo el Pcs8575, que por defecto está todo prendido
	   iniciar_ADC();					// Inicializamos el ADC
       uart_init();						//Inicializamos la uart
	   ConfigurarPinesSensores();		//Configuramos los pines de los sensores 
	   ConfigurarBotones();				//Configuramos los botones.
	   PWM_init();                      // Configuramos el PWM
	   if((BanderaBienvenida==0)&&(BanderaError==0)){        // Primer ejecución del programa
		    Bienvenida();
			BanderaBienvenida=1;
			lcd_init();
			escribirEnLCD(" Bienvenido UwU");
			i2c_stop();
	   } 
	   ConfiguracionIncialEeprom();     // Verificamos que la configuración inicial esté en la eprom, caso contrario la configuramos
	   MenuInicial();                   // Menu de inicio owo
	   Timer0_init();
	   setupTimer1();
   }
void MenuUart(void) 
    {; // se recibe el dato de forma no bloqueante
		DecisionMenuUart=UART_receive_non_blocking();
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
		uart_send_string(">>Del siguiente listado, escoja que configurar:");
		MenuConfiguraciones();
		uart_send_newline();
	    uart_send_string(">>Seleccione una de las anteriores opciones y siga las instrucciones ");
		uart_send_newline();
		// Recibir Configuracion
		DecisionMenuUart=",";
		break;
		case 'A':
		LlenarVectorConDosCaracteres(TemperaturaDeseada);
		DecisionMenuUart=",";
		break;
		case 'B':
		MenuCambioDeNombre();
		LlenarVectorConDiezCaracteres(NombreB1);
		DecisionMenuUart=",";
		break;
		case 'C':
		MenuCambioDeNombre();
		LlenarVectorConDiezCaracteres(NombreB2);
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'D':
		MenuCambioDeNombre();
		LlenarVectorConDiezCaracteres(NombreB3);
		DecisionMenuUart=",";
		break;
		case 'E':
		MenuCambioDeNombre();
		LlenarVectorConDiezCaracteres(NombreB4);
		DecisionMenuUart=",";
		break;
		case 'F':
		DecisionMenuUart=",";
		break;
		case 'G':
		LlenarVectorConDosCaracteres(KpEprom);
		DecisionMenuUart=",";
		break;
		DecisionMenuUart=",";
		case 'H':
		LlenarVectorConTresCaracteres(DosificacionB1);
		DecisionMenuUart=",";
		break;
		case 'I':
		LlenarVectorConTresCaracteres(DosificacionB2);
		break;
		case 'J':
		LlenarVectorConTresCaracteres(DosificacionB3);
		DecisionMenuUart=",";
		break;
		case 'K':
		LlenarVectorConTresCaracteres(DosificacionB4);
		DecisionMenuUart=",";
		break;
	
		case 'M':
		LlenarVectorConTresCaracteres(CAguaB1);
		DecisionMenuUart=",";
		DecisionMenuUart=",";
		break;
		case 'L':
		DecisionMenuUart=",";
		LlenarVectorConTresCaracteres(CAguaB2);
		break;
		case 'O':
		DecisionMenuUart=",";
		LlenarVectorConTresCaracteres(CAguaB3);
		break;
		
		case 'P':
		DecisionMenuUart=",";
		LlenarVectorConTresCaracteres(CAguaB4);
		DecisionMenuUart=",";
		break;
		case 'Q':
		DecisionMenuUart=",";
		LlenarVectorConDosCaracteres(PorcDescargaB1);
		break;
		case 'R':
		DecisionMenuUart=",";
		LlenarVectorConDosCaracteres(PorcDescargaB2);
		break;
		case 'S':
		DecisionMenuUart=",";
		LlenarVectorConDosCaracteres(PorcDescargaB3);
		break;
		DecisionMenuUart=",";
		case 'T':
		DecisionMenuUart=",";
		LlenarVectorConDosCaracteres(PorcDescargaB4);
		break;
		case 'U':
		MenuTamanho();
		DecisionMenuUart=",";
		break;
		case 'V':
		EPROM_Write_String(TamagnoBidon, "1"); // Guaradamos
		uart_send_newline();
		MenuInicial();
		uart_send_newline();
		DecisionMenuUart=",";																																														
		break;
		case 'W':
		uart_send_newline();
		EPROM_Write_String(TamagnoBidon, "2"); // Guaradamos
		MenuInicial();
		uart_send_newline();
		DecisionMenuUart=",";																																														
		break;
		case 'X':
		MenuInicial();
		DecisionMenuUart=",";
		break;
		case 'Z':
		ConfiguracionPredeterminada();// Reseteo de fabrica
		DecisionMenuUart=",";
		break;
		default:
		// Ninguna opción válida, 
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
	   cli(); // NOS ASEGURAMOS QUE LAS INTERRUPCIONES ESTEN DESACTIVADAS
	   ConfiguracionIncial();//Configuramos todo
	    
	 //  EnviarTextoSeleccionarOpcion();
	 for (int i = 0; i < 6; i++) // Hay que medir varias veces, porque las primeras mediciones pueden ser erradas
	 {MedirVariables(); //Medición inicial
	 }
	    sei(); // Prendendemos las interrupciones
		DetectarError();// Por si llegare a iniciarse con algo mal
	while(1){
		  sei();
		  
	DetectarError();
	Servido();
		 
	MenuUart();
	//fin
	
   
	
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
	
ISR(TIMER1_COMPA_vect) {// Esto se ejecuta cada 1 segundo
	 MedirVariables();
	ControlarTemperatura();         // Se controla la temperatura por interrupción
	
}//Fin
ISR(TIMER0_COMPA_vect) {
	 int BotonAceptarRR = !((PIND & (1 << PPD6)) ? 1 : 0); // lee el botón aceptar
	// Incrementar contador de tiempo
	ContadorControlarBotones++; 
	if (ContadorControlarBotones==55) // Para que se active por cada 56 ms
	{LeerBotones();
     LeerSensores();
	ContadorControlarBotones=0 //Reiniciamos contador
	;};
	// Incrementar contador de tiempo si los dos botones están presionados
    
	// Leer estado de los pines PD3 y PD4
	pinState = (BotonAceptarr && BotonSeleccionarr);
	if (pinState != 0){timerCounter++;}
    else { if ((BotonAceptarRR != 0)&& (BotonSeleccionarr==0))  //Se activa si sólo se presionó el botón Seleccionar
	{BanderaServido=1;	 																																																																																						   
    }
    }
	// Si ambos pines están en bajo y el contador ha alcanzado 2500 (5 segundos)
	if (pinState != 0 && timerCounter >= 2500) {
		Simultaneidad=1;
		// Reiniciar contador
		timerCounter = 0;
	} 
} //Fin
	
//ISR(USART_RX_vect) {
	//received_data = UDR0; // Lee el dato recibido y lo guarda en una variable global
//}
	