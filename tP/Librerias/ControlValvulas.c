
#include "ControlValvulas.h"
#include "pcf857.h"
#include "FuncionesEeprom.h"
#include "UART.h"
/***
 *                                                                                                                                                          
 *        ,o888888o.        ,o888888o.     b.             8 8888888 8888888888 8 888888888o.       ,o888888o.     8 8888                                    
 *       8888     `88.   . 8888     `88.   888o.          8       8 8888       8 8888    `88.   . 8888     `88.   8 8888                                    
 *    ,8 8888       `8. ,8 8888       `8b  Y88888o.       8       8 8888       8 8888     `88  ,8 8888       `8b  8 8888                                    
 *    88 8888           88 8888        `8b .`Y888888o.    8       8 8888       8 8888     ,88  88 8888        `8b 8 8888                                    
 *    88 8888           88 8888         88 8o. `Y888888o. 8       8 8888       8 8888.   ,88'  88 8888         88 8 8888                                    
 *    88 8888           88 8888         88 8`Y8o. `Y88888o8       8 8888       8 888888888P'   88 8888         88 8 8888                                    
 *    88 8888           88 8888        ,8P 8   `Y8o. `Y8888       8 8888       8 8888`8b       88 8888        ,8P 8 8888                                    
 *    `8 8888       .8' `8 8888       ,8P  8      `Y8o. `Y8       8 8888       8 8888 `8b.     `8 8888       ,8P  8 8888                                    
 *       8888     ,88'   ` 8888     ,88'   8         `Y8o.`       8 8888       8 8888   `8b.    ` 8888     ,88'   8 8888                                    
 *        `8888888P'        `8888888P'     8            `Yo       8 8888       8 8888     `88.     `8888888P'     8 888888888888                            
 *    `8.`888b           ,8'          .8.          8 8888         `8.`888b           ,8' 8 8888      88 8 8888                  .8.             d888888o.   
 *     `8.`888b         ,8'          .888.         8 8888          `8.`888b         ,8'  8 8888      88 8 8888                 .888.          .`8888:' `88. 
 *      `8.`888b       ,8'          :88888.        8 8888           `8.`888b       ,8'   8 8888      88 8 8888                :88888.         8.`8888.   Y8 
 *       `8.`888b     ,8'          . `88888.       8 8888            `8.`888b     ,8'    8 8888      88 8 8888               . `88888.        `8.`8888.     
 *        `8.`888b   ,8'          .8. `88888.      8 8888             `8.`888b   ,8'     8 8888      88 8 8888              .8. `88888.        `8.`8888.    
 *         `8.`888b ,8'          .8`8. `88888.     8 8888              `8.`888b ,8'      8 8888      88 8 8888             .8`8. `88888.        `8.`8888.   
 *          `8.`888b8'          .8' `8. `88888.    8 8888               `8.`888b8'       8 8888      88 8 8888            .8' `8. `88888.        `8.`8888.  
 *           `8.`888'          .8'   `8. `88888.   8 8888                `8.`888'        ` 8888     ,8P 8 8888           .8'   `8. `88888.   8b   `8.`8888. 
 *            `8.`8'          .888888888. `88888.  8 8888                 `8.`8'           8888   ,d8P  8 8888          .888888888. `88888.  `8b.  ;8.`8888 
 *             `8.`          .8'       `8. `88888. 8 888888888888          `8.`             `Y88888P'   8 888888888888 .8'       `8. `88888.  `Y8888P ,88P' 
 *
 *     // ESTA LIBRERIA EN ESPECIFICO PODRIA CONSIDERARSE UNA DERIVACIÓN DE FUNCIONES EEPROM Y DE PCF8575
 *     // E INTERVIENEN ANTE TODO EN LAS RUTINAS DE SERVIDO DE CADA BEBIDA
 */
// DEFINIMOS QUE PINES DEL PCF8575 HACE USO CADA VALVULA
#define DOSIFICADOR1  0x0001  // VALVULA DOSIFICADORA
#define DOSIFICADOR2  0x0002  // VALVULA DOSIFICADORA
#define DOSIFICADOR3  0x0004  // VALVULA DOSIFICADORA
#define DOSIFICADOR4  0x0008  // VALVULA DOSIFICADORA
#define VALVULACALIENTE1  0x0010 //VALVULA DE AGUA CALIENTE
#define VALVULACALIENTE2  0x0020 //VALVULA DE AGUA CALIENTE
#define VALVULACALIENTE3  0x0040 //VALVULA DE AGUA CALIENTE
#define VALVULACALIENTE4  0x0080 //VALVULA DE AGUA CALIENTE
#define VALVULADESCARGA1  0x0100 // VALVULA DE DESCARGA
#define VALVULADESCARGA2  0x0200 // VALVULA DE DESCARGA
#define VALVULADESCARGA3 0x0400  // VALVULA DE DESCARGA
#define VALVULADESCARGA4 0x0800  // VALVULA DE DESCARGA

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
 *     #     #                                                                                                                                                    
 *     #     #    ##    #####   #    ##    #####   #       ######   ####        ####   #        ####   #####     ##    #       ######   ####       #####   ###### 
 *     #     #   #  #   #    #  #   #  #   #    #  #       #       #           #    #  #       #    #  #    #   #  #   #       #       #           #    #  #      
 *     #     #  #    #  #    #  #  #    #  #####   #       #####    ####       #       #       #    #  #####   #    #  #       #####    ####       #    #  #####  
 *     ##   #   ######  #####   #  ######  #    #  #       #            #      #  ###  #       #    #  #    #  ######  #       #            #      #    #  #      
 *       # #    #    #  #   #   #  #    #  #    #  #       #       #    #      #    #  #       #    #  #    #  #    #  #       #       #    #      #    #  #      
 *        #     #    #  #    #  #  #    #  #####   ######  ######   ####        ####   ######   ####   #####   #    #  ######  ######   ####       #####   ###### 
 *                                                                                                                                                                                                                                                                                                                            
 *     ######   ####   #####    ##         ####   ######   ####    ####   #   ####   #    #                                                                       
 *     #       #         #     #  #       #       #       #    #  #    #  #  #    #  ##   #                                                                       
 *     #####    ####     #    #    #       ####   #####   #       #       #  #    #  # #  #                                                                       
 *     #            #    #    ######           #  #       #       #       #  #    #  #  # #                                                                       
 *     #       #    #    #    #    #      #    #  #       #    #  #    #  #  #    #  #   ##                                                                       
 *     ######   ####     #    #    #       ####   ######   ####    ####   #   ####   #    #                                                                       
 *                                                                                                                                                                
 */
      int  Aux;
      char Buffer [8];
	  int  TiempoDeDosificacion;
	  int  TiempoDeAguaCaliente;
	  int  TiempoDeDescarga;
	
	// Función para crear un retardo en milisegundos con una variable
void RetardoPersonalizadosEnMs(int i){
	// Assembly code auto-generated
	// by utility from Bret Mulvey
	// Delay 16 000 cycles
	// 1ms at 16 MHz
	while (i>=0){
		asm volatile (
		"    ldi  r18, 21	\n"
		"    ldi  r19, 199	\n"
		"1:  dec  r19	\n"
		"    brne 1b	\n"
		"    dec  r18	\n"
		"    brne 1b	\n"
		);
	i--;}
}
void ServidoBebida1(void){
	//Leemos la cantidad de dosificación y calculamos el tiempo de ossification
	EPROM_Read_String(DosificacionB1,Buffer,3);
	Aux=atoi(Buffer);
	TiempoDeDosificacion=(((float)Aux)/15)*1000; // Esto da en milisegundos, 15 ml es una cucharada
	EscribirPcf8575(DOSIFICADOR1); // CAE EL POLVO DOSIFICADOR
	RetardoPersonalizadosEnMs(TiempoDeDosificacion);
	// Lo mismo con el agua caliente
	EPROM_Read_String(CAguaB1,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeAguaCaliente=((float)Aux/25)*1000;// Esto da en milisegundos, 25 ml es lo que cae en un segundo 
	EscribirPcf8575(VALVULACALIENTE1); // CAE EL AGUA CALIENTE
	RetardoPersonalizadosEnMs(TiempoDeAguaCaliente);
	// Lo mismo con lo de descarga
	EPROM_Read_String(PorcDescargaB1,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeDescarga = ((float)TiempoDeAguaCaliente * (1 + (float)(Aux / 100))) * 1000;
	EscribirPcf8575(VALVULADESCARGA1); // SE DESCARGA LA BEBIDA
	RetardoPersonalizadosEnMs(TiempoDeDescarga);
	ApagarTodo();
}
void ServidoBebida2(void){
	//Leemos la cantidad de dosificación y calculamos el tiempo de ossification
	EPROM_Read_String(DosificacionB2,Buffer,3);
	Aux=atoi(Buffer);
	TiempoDeDosificacion=(((float)Aux)/15)*1000; // Esto da en milisegundos, 15 ml es una cucharada
	EscribirPcf8575(DOSIFICADOR2); // CAE EL POLVO DOSIFICADOR
	RetardoPersonalizadosEnMs(TiempoDeDosificacion);
	// Lo mismo con el agua caliente
	EPROM_Read_String(CAguaB2,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeAguaCaliente=((float)Aux/25)*1000;// Esto da en milisegundos, 25 ml es lo que cae en un segundo
	EscribirPcf8575(VALVULACALIENTE2); // CAE EL AGUA CALIENTE
	RetardoPersonalizadosEnMs(TiempoDeAguaCaliente);
	// Lo mismo con lo de descarga
	EPROM_Read_String(PorcDescargaB2,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeDescarga = ((float)TiempoDeAguaCaliente * (1 + (float)(Aux / 100))) * 1000;
	EscribirPcf8575(VALVULADESCARGA2); // SE DESCARGA LA BEBIDA
	RetardoPersonalizadosEnMs(TiempoDeDescarga);
	ApagarTodo();
}
void ServidoBebida3(void){
	//Leemos la cantidad de dosificación y calculamos el tiempo de ossification
	EPROM_Read_String(DosificacionB3,Buffer,3);
	Aux=atoi(Buffer);
	TiempoDeDosificacion=(((float)Aux)/15)*1000; // Esto da en milisegundos, 15 ml es una cucharada
	EscribirPcf8575(DOSIFICADOR3); // CAE EL POLVO DOSIFICADOR
	RetardoPersonalizadosEnMs(TiempoDeDosificacion);
	// Lo mismo con el agua caliente
	EPROM_Read_String(CAguaB1,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeAguaCaliente=((float)Aux/25)*1000;// Esto da en milisegundos, 25 ml es lo que cae en un segundo
	EscribirPcf8575(VALVULACALIENTE3); // CAE EL AGUA CALIENTE
	RetardoPersonalizadosEnMs(TiempoDeAguaCaliente);
	// Lo mismo con lo de descarga
	EPROM_Read_String(PorcDescargaB3,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeDescarga = ((float)TiempoDeAguaCaliente * (1 + (float)(Aux / 100))) * 1000;
	EscribirPcf8575(VALVULADESCARGA3); // SE DESCARGA LA BEBIDA
	RetardoPersonalizadosEnMs(TiempoDeDescarga);
	ApagarTodo();
}
void ServidoBebida4(void){
	//Leemos la cantidad de dosificación y calculamos el tiempo de ossification
	EPROM_Read_String(DosificacionB4,Buffer,3);
	Aux=atoi(Buffer);
	TiempoDeDosificacion=(((float)Aux)/15)*1000; // Esto da en milisegundos, 15 ml es una cucharada
	EscribirPcf8575(DOSIFICADOR4); // CAE EL POLVO DOSIFICADOR
	RetardoPersonalizadosEnMs(TiempoDeDosificacion);
	// Lo mismo con el agua caliente
	EPROM_Read_String(CAguaB4,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeAguaCaliente=((float)Aux/25)*1000;// Esto da en milisegundos, 25 ml es lo que cae en un segundo
	EscribirPcf8575(VALVULACALIENTE4); // CAE EL AGUA CALIENTE
	RetardoPersonalizadosEnMs(TiempoDeAguaCaliente);
	// Lo mismo con lo de descarga
	EPROM_Read_String(PorcDescargaB4,Buffer,4);
	Aux=atoi(Buffer);
	TiempoDeDescarga = ((float)TiempoDeAguaCaliente * (1 + (float)(Aux / 100))) * 1000;
	EscribirPcf8575(VALVULADESCARGA4); // SE DESCARGA LA BEBIDA
	RetardoPersonalizadosEnMs(TiempoDeDescarga);
	ApagarTodo();
}
void SeleccionarMedida(int Selector){
	switch(Selector){
		case 1:
		ServidoBebida1();
		break;
		case 2:
		ServidoBebida2();
		break;
		case 3:
		ServidoBebida3();
		break;
		case 4:
		ServidoBebida4();
		break;
		default:
		//nada
		break;
	}
	
}