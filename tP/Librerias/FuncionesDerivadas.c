
/***
 *     #######                                                                 ######                                                             
 *     #        #    #  #    #   ####   #   ####   #    #  ######   ####       #     #  ######  #####   #  #    #    ##    #####     ##     ####  
 *     #        #    #  ##   #  #    #  #  #    #  ##   #  #       #           #     #  #       #    #  #  #    #   #  #   #    #   #  #   #      
 *     #####    #    #  # #  #  #       #  #    #  # #  #  #####    ####       #     #  #####   #    #  #  #    #  #    #  #    #  #    #   ####  
 *     #        #    #  #  # #  #       #  #    #  #  # #  #            #      #     #  #       #####   #  #    #  ######  #    #  ######       # 
 *     #        #    #  #   ##  #    #  #  #    #  #   ##  #       #    #      #     #  #       #   #   #   #  #   #    #  #    #  #    #  #    # 
 *     #         ####   #    #   ####   #   ####   #    #  ######   ####       ######   ######  #    #  #    ##    #    #  #####   #    #   ####  
 *                                                                                                                                                
 */// >>>>>>>>>>AC� PUSE TODAS LAS FUNCIONES QUE NO QUERIA PONER EN MAIN (POR TENER UN INTENTO DE PROLIJIDAD), SON DE USO DERIVADO DEL RESTO DE LIBRERIAS
#include "FuncionesEprom.h"
#include "UART.h" // Esto es para las pruebas
#include "FuncionesDerivadas.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
const char TextoExito2[] PROGMEM = ">>�Cambio exitoso!!<<";
const char TextoFracaso12[] PROGMEM = ">>Por favor, intentelo nuevamente";
int Aux=0; // Esta variable  global es auxiliar para el  llenado de vectores

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
// Atenci�n: B1=Bebida1 ; B2=Bebida2; B3=Bebida3;B 4=Bebida4. CAgua=Cantidad de Agua caliente. 
//========== PorcDescarga=Porcentaje del tiempo de descarga extra al que es igual al "tiempo de dosificaci�n" (ver documentaci�n para mayor detalle)
// Si tienen una P al final es porque pertenecen al programa, no a la eprom... 
// Algunas tiene un "Tipo", este es un caracter que se le asigna tal que despues podamos definir sus condiciones de entrada de la modificacion
// de datos v�a UART.   ATENCI�N:
//
//   TIPO 'D' --> DOSIFICADORES (CANTIDAD DE PREMEZCLA)--> 0 a 420 mL
//   TIPO 'A' --> CANTIDAD DE AGUA --> 150 a 300 mL
//   TIPO 'P' --> PORCENTAJE DE TIEMPO DE DESCARGA --> 5% AL 25%
//   TIPO 'V' --> TAMA�O DEL BID�N --> 1 A 2 DL (DECALITROS)
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

// ====================================================================================================================================================
char DetectarTipo(uint16_t uiAddress){ // ESTO ES PARA DETECTAR QUE CONDICION SE LE DEBE APLICAR Al nuevo valor ingresado por UART
									   // ESTA FUNCI�N SOLO SER� LLAMADA AC�, POR LO QUE NO HACE FALTA PONERLA EN EL HEADER
	char Tipo;
	if ((uiAddress==DosificacionB1)|| (uiAddress==DosificacionB2)|| (uiAddress==DosificacionB3)|| (uiAddress==DosificacionB4)) {
		Tipo='D';
		return Tipo;
	}
	if ((uiAddress==CAguaB1)|| (uiAddress==CAguaB2)|| (uiAddress==CAguaB3)|| (uiAddress==CAguaB4)) {
		Tipo='A';
		return Tipo;
	}
	if ((uiAddress==PorcDescargaB1)|| (uiAddress==PorcDescargaB2)|| (uiAddress==PorcDescargaB3)|| (uiAddress==PorcDescargaB4)) {
		Tipo='P';
		return Tipo;
	}
	if (uiAddress==TamagnoBidon) {
		Tipo='V';
		return Tipo;
	}
	if (uiAddress==KpEprom) {
		Tipo='K';
		return Tipo;
	}
	if (uiAddress==TemperaturaDeseada) {
		Tipo='T';
		return Tipo;
	}
}
void LlenarVectorConDosCaracteres(uint16_t uiAddress) {//le damos -La direcci�n de eeprom a la cual guardar ej: TemperaturaDeseada
	CambioDeNumero();
	char Vector[3]; // Vector auxiliar para el llenado, con la ultima posici�n para el caracter nulo
	 Aux=0;  
		Vector[Aux] = echo_serial(); //Primer d�gito
	 Aux=1;
	    Vector[Aux] = echo_serial(); //Segundo d�gito
	   Vector[2] = '\0';			 //Terminamos el dato con el caracter nulo.
	   char Tipo=DetectarTipo(uiAddress);
	   if (Tipo=='T')
	   {if ((atoi(Vector)<=95)&&(atoi(Vector)>=60)){ //Condici�n para la Temperatura Deseada
		   EPROM_Write_String(uiAddress, Vector); // Guaradamos ;
	   }else{Fracaso();}
		}
		if (Tipo=='K')
		{if ((atoi(Vector)!=0)){ //Condici�n para Kp, de 1 a 99; el numero es a ingresar est� de 00 a 99,
								 // por eso restringimos el 0
			EPROM_Write_String(uiAddress, Vector); // Guaradamos ;
			}else{Fracaso();}
			//EPROM_Write_String(uiAddress, Vector); // Guaradamos
		}
		if (Tipo=='P')
		{if ((atoi(Vector)<=25)&&(atoi(Vector)>=5)){ //Condici�n el porcentaje del tiempo de descarga
			EPROM_Write_String(uiAddress, Vector); // Guaradamos ;
			}else{Fracaso();}
		}
	   }
		
void LlenarVectorConDiezCaracteres(uint16_t uiAddress) {//le damos -La direcci�n de eeprom a la cual guardar ej: TemperaturaDeseada
	char Vector[11]; // Vector auxiliar para el llenado, con la ultima posici�n para el caracter nulo
	Aux=0;
	Vector[Aux] = echo_serial(); //
	Aux=1;
	Vector[Aux] = echo_serial(); //
	Aux=2;
	Vector[Aux] = echo_serial(); //
	Aux=3;
	Vector[Aux] = echo_serial(); //
	Aux=4;
	Vector[Aux] = echo_serial(); //
	Aux=5;
	Vector[Aux] = echo_serial(); //
	Aux=6;
	Vector[Aux] = echo_serial(); //
	Aux=7;
	Vector[Aux] = echo_serial(); //
	Aux=8;
	Vector[Aux] = echo_serial(); //
	Aux=9;
	Vector[Aux] = echo_serial(); //
	Vector[11] = '\0';			 //Terminamos el dato con el caracter nulo.
	
	EPROM_Write_String(uiAddress, Vector); // Guaradamos
	MandarStringdesdePrograma(TextoExito2);
	uart_send_newline();
}

void LlenarVectorConTresCaracteres(uint16_t uiAddress) {//le damos -La direcci�n de eeprom a la cual guardar ej: TemperaturaDeseada
	CambioDeNumero();
	char Vector[4]; // Vector auxiliar para el llenado, con la ultima posici�n para el caracter nulo
	Aux=0;
	Vector[Aux] = echo_serial(); //Primer d�gito
	Aux=1;
	Vector[Aux] = echo_serial(); //Segundo d�gito
	Aux=2;
	Vector[Aux] = echo_serial(); //Tercer d�gito
	Vector[3] = '\0';			 //Terminamos el dato con el caracter nulo.
	char Tipo=DetectarTipo(uiAddress);
	if (Tipo=='D')
	{if (((atoi(Vector)<=420)&&(atoi(Vector)>=00))){ //Condici�n para Dosificacion
		EPROM_Write_String(uiAddress, Vector); // Guaradamos ;
		}else{Fracaso();}
	}
	if (Tipo=='A')
	{if (((atoi(Vector)<=300)&&(atoi(Vector)>=150))){ //Condici�n para la cantidad de Agua caliente
		EPROM_Write_String(uiAddress, Vector); // Guaradamos ;
		}else{Fracaso();}
	}
}