#include <avr/pgmspace.h>
#include "FuncionesEeprom.h"
/*
    _____               _   __              _            _       _
   / ____|             (_) /_/             | |          | |     | |
  | (___   ___  ___ ___ _  ___  _ __     __| | ___    __| | __ _| |_ ___  ___    ___ _ __
   \___ \ / _ \/ __/ __| |/ _ \| '_ \   / _` |/ _ \  / _` |/ _` | __/ _ \/ __|  / _ \ '_ \
   ____) |  __/ (_| (__| | (_) | | | | | (_| |  __/ | (_| | (_| | || (_) \__ \ |  __/ | | |
  |_____/ \___|\___\___|_|\___/|_| |_|  \__,_|\___|  \__,_|\__,_|\__\___/|___/  \___|_| |_|
  |  \/  |                         (_)           | |    | |
  | \  / | ___ _ __ ___   ___  _ __ _  __ _    __| | ___| |  _ __  _ __ ___   __ _ _ __ __ _ _ __ ___   __ _
  | |\/| |/ _ \ '_ ` _ \ / _ \| '__| |/ _` |  / _` |/ _ \ | | '_ \| '__/ _ \ / _` | '__/ _` | '_ ` _ \ / _` |
  | |  | |  __/ | | | | | (_) | |  | | (_| | | (_| |  __/ | | |_) | | | (_) | (_| | | | (_| | | | | | | (_| |
  |_|  |_|\___|_| |_| |_|\___/|_|  |_|\__,_|  \__,_|\___|_| | .__/|_|  \___/ \__, |_|  \__,_|_| |_| |_|\__,_|
                                                            | |               __/ |
                                                            |_|              |___/
*/  
const char TextoElegir[] PROGMEM = ">>Seleccione alguna de las anteriores opciones ";
const char TextoRegresar[] PROGMEM = ">>Aprete X para volver al menu inicial";
const char TextoExito[] PROGMEM = ">>¡Cambio exitoso!!<<";
const char TextoFracaso[] PROGMEM = ">>ERROR: LA CANTIDAD PROPUESTA ESTÁ FUERA DE RANGO O EN FORMATO ERRONEO";
const char TextoFracaso1[] PROGMEM = ">>Por favor, intentelo nuevamente más tarde. ACEPTAR: Aprete X";
// TEXTOS PARA LAS MEDICIONES
const char TextoTemperatura[] PROGMEM ="-Temperatura:";
const char TextoTemperatura0[] PROGMEM =" *C";
const char TextoVolumen[] PROGMEM ="-Volumen:";
const char TextoVolumen0[] PROGMEM =" mL";
const char TextoBidon[] PROGMEM =">>Bidon:";
const char TextoDosificador[] PROGMEM =">>Niveles de llenado de los dosificadores de premezcla (en %):";
//Bebida 1: bla bla



// TEXTO DE LOS MENUS

 
const char Bienvenida0[] PROGMEM =" +XXXXXXx    XX+   XXXXXXX+  +XXX   XX:  XXx    XX;  xXXXXXXx  :XXX:  XX+   XX;   XXXXXXX:    xXXXXXx ";
const char Bienvenida1[] PROGMEM =" +XX. ;XXx   XX+   XX+       +XXXx  XX:  +XX.  :XX.  xXx       :XXXX  XX+   XX;   XX+  +XX.  +XX. :XX+";
const char Bienvenida2[] PROGMEM =" +XX   XXx   XX+   XX+       +XXXX: XX:  :XX:  xXx   xXx       :XXXX; XX+   XX;   XX+  :XX;  xXX   XXx ";
const char Bienvenida3[] PROGMEM =" +XX. ;XX:   XX+   XX+       +Xx:Xx XX:   XX+  XX;   xXx       :XX XX XX+   XX;   XX+  :XX;  xXX   XXx ";
const char Bienvenida4[] PROGMEM =" +XXXXXXx    XX+   XXXXXX;   +Xx xX;XX:   XXX  XX:   xXXXXXx   :XX xX+XX+   XX;   XX+  :XX;  xXX   XXx ";
const char Bienvenida5[] PROGMEM =" +XX   XXX   XX+   XX+       +Xx :XXXX:   ;XX:;XX    xXx       :XX  XXXX+   XX;   XX+  :XX;  xXX   XXx ";
const char Bienvenida6[] PROGMEM =" +XX   +XX.  XX+   XX+       +Xx  xXXX:    XX+XX+    xXx       :XX  +XXX+   XX;   XX+  :XX;  xXX   XXx ";
const char Bienvenida7[] PROGMEM =" +XX   XXX   XX+   XX+       +Xx  :XXX:    xXXXX.    xXx       :XX  .XXX+   XX;   XX+  ;XX:  +XX. .XX+ ";
const char Bienvenida8[] PROGMEM =" +XXXXXXX    XX+   XXXXXXX+  +Xx   xXX:    +XXXX     xXXXXXXx  :XX   ;XX+   XX;   XXXXXXX+    xXXXXXx  ";
 
   
   
 const char Menu0_0[] PROGMEM =">> 1 Ver Mediciones";
 const char Menu0_1[] PROGMEM =">> 2 Ver configuraciones";
 const char Menu0_2[] PROGMEM =">> 3 Datos del Proyecto";
 const char Menu0_3[] PROGMEM =">> 4 Configurar";
 
 const char MenuMediciones0[] PROGMEM ="=======================>>";
 const char MenuMediciones1[] PROGMEM ="| MEDICIONES ACTUALES |>>";
 const char MenuMediciones2[] PROGMEM ="=======================>>";
 
 
 
const char Carpyy[] PROGMEM="                    90  400     TPFI... CATEDRA:    SISTEMAS DIGITALES IV";
const char Carpyy0[] PROGMEM="               1232800000000                    PROFESORES: ING EDUARDO VELAZQUEZ";
const char Carpyy1[] PROGMEM="            400000000000000007                                LIC JULIAN MINATEL";
const char Carpyy2[] PROGMEM="         400000000000  300000005      NOMBRE: FABRICIO DAVID GALLO";
const char Carpyy3[] PROGMEM="         0000 80000000000000000000";
const char Carpyy4[] PROGMEM="         4000000000000000000000000000             'CAFETERA' ES UN PROYECTO DONDE SE " ;
const char Carpyy5[] PROGMEM="         70000000000000000000000000000000               PUEDEN CONTROLAR TEMPERATURA, ";
const char Carpyy6[] PROGMEM="          00000000000000000000000000000000000000000004      CANTIDAD DE PREMEZCLA,ETC  ";
const char Carpyy7[] PROGMEM="           800000000000000000000000000000000000000000000001      PARA MODIFICAR ESTOS  ";
const char Carpyy8[] PROGMEM="                000000000000000000000000000000000000000000006            UTILICE ESTA   ";
const char Carpyy9[] PROGMEM="                   10000000000000000000000000000000000000000001              CONSOLA";
const char Carpyy10[] PROGMEM="                    00000000000000000000000000000000000000000000";
const char Carpyy11[] PROGMEM="                      90000000000000000000000000000000000000000000";
const char Carpyy12[] PROGMEM="     1  1             900000000000000000000000000000000000000000000";
const char Carpyy13[] PROGMEM="      1  1             000000000000000000000000000000000000000000000";
const char Carpyy14[] PROGMEM="     1  1              900000000000000000000000000000000000000000000";
const char Carpyy15[] PROGMEM="   00000000037          60000000000000000000000000000000000000000000";
const char Carpyy16[] PROGMEM="   000000009  9          0000000000000000000000000000000000000000000";
const char Carpyy17[] PROGMEM="   0000000002            900000000000000000000000000000000000000000";
const char Carpyy18[] PROGMEM="   000000009             900 00002 50000000000000000000000000000000";
const char Carpyy19[] PROGMEM="   000000006             900 8006       70000000000000000000000000";
const char Carpyy20[] PROGMEM="444666666666445         30006000                50000000000000000";

// TEXTO PARA LAS CONFIGURACIONES
const char MenuConfiguracion0[] PROGMEM=" A-Temperatura Deseada (60-95)*C =";
const char MenuConfiguracion1[] PROGMEM=" B-Nombre de la Bebida 1 (10 carácteres) =";
const char MenuConfiguracion2[] PROGMEM=" C-Nombre de la Bebida 2 (10 carácteres) =";
const char MenuConfiguracion3[] PROGMEM=" D-Nombre de la Bebida 3 (10 carácteres) =";
const char MenuConfiguracion4[] PROGMEM=" E-Nombre de la Bebida 4 (10 carácteres) =";
const char MenuConfiguracion5[] PROGMEM=" F-Nombre de la Bebida 1 (10 carácteres) =";
const char MenuConfiguracion6[] PROGMEM=" G-Constante Proporcional 'Kp':";
const char MenuConfiguracion7[] PROGMEM=" H-Cantidad de premezcla Bebida 1 (0 a 420 mL) =";
const char MenuConfiguracion8[] PROGMEM=" I-Cantidad de premezcla Bebida 2 (0 a 420 mL) =";
const char MenuConfiguracion9[] PROGMEM=" J-Cantidad de premezcla Bebida 3 (0 a 420 mL) =";
const char MenuConfiguracion10[] PROGMEM=" K-Cantidad de premezcla Bebida 4 (0 a 420 mL) =";
const char MenuConfiguracion11[] PROGMEM=" M-Cantidad de agua Caliente Bebida 1 (150 a 300 mL) =";
const char MenuConfiguracion12[] PROGMEM=" N-Cantidad de agua Caliente Bebida 2 (150 a 300 mL) =";
const char MenuConfiguracion13[] PROGMEM=" O-Cantidad de agua Caliente Bebida 3 (150 a 300 mL) =";
const char MenuConfiguracion14[] PROGMEM=" P-Cantidad de agua Caliente Bebida 4 (150 a 300 mL) =";
const char MenuConfiguracion15[] PROGMEM=" Q-Porcentaje de Tdescarga Bebida 1 (5 a 25%) =";
const char MenuConfiguracion16[] PROGMEM=" R-Porcentaje de Tdescarga Bebida 2 (5 a 25%) =";
const char MenuConfiguracion17[] PROGMEM=" S-Porcentaje de Tdescarga Bebida 3 (5 a 25%) =";
const char MenuConfiguracion18[] PROGMEM=" T-Porcentaje de Tdescarga Bebida 4 (5 a 25%) =";
const char MenuConfiguracion19[] PROGMEM=" U-Tamaño de Bidon (10 L -20 L) =";
// MENU TAMAÑO BIDON
const char MenuTamagno[] PROGMEM=">>Seleccione el nuevo volumen presionando una de estas letras:";
const char MenuTamagno0[] PROGMEM=" V- 10 L";
const char MenuTamagno1[] PROGMEM=" W- 20 L";

const char MenuCambioDeNombre0[] PROGMEM=" Para cambiar de nombre una bebida siga los siguientes pasos:";
const char MenuCambioDeNombre1[] PROGMEM="1)- Coloque letra por letra el nuevo nombre";
const char MenuCambioDeNombre2[] PROGMEM="2)- Coloque un guion bajo ('_') al final";
const char MenuCambioDeNombre3[] PROGMEM="3)- Aprete '2' hasta ver su cambio reflejado";
const char MenuCambioDeNombre4[] PROGMEM="============================================";
const char MenuCambioDeNombre5[] PROGMEM="| ¡ATENCION!: 10 CARACTERES, EN MAYUSCULA. |";
const char MenuCambioDeNombre6[] PROGMEM="============================================";

const char MenuCambioDeNumero0[] PROGMEM=" Para cambiar la variable siga los siguiente pasos:";
const char MenuCambioDeNumero1[] PROGMEM="1)- Coloque cifra por cifra segun sea el maximo. Por ejemplo:";
const char MenuCambioDeNumero2[] PROGMEM=" si el numero máximo es 100 y queremos poner 25-> '0' '2' '5' ";
const char MenuCambioDeNumero3[] PROGMEM="2)- Aprete '2' hasta ver su cambio reflejado";
const char MenuCambioDeNumero4[] PROGMEM="===========================================================";
const char MenuCambioDeNumero5[] PROGMEM="|  ¡ATENCION!: COLOQUE NUMEROS DENTRO DEL RANGO PERMITIDO |";
const char MenuCambioDeNumero6[] PROGMEM="===========================================================";
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


/*
   ____                _   __              _
  / ___|  ___  ___ ___(_) /_/  _ __     __| | ___
  \___ \ / _ \/ __/ __| |/ _ \| '_ \   / _` |/ _ \
   ___) |  __/ (_| (__| | (_) | | | | | (_| |  __/
  |____/ \___|\___\___|_|\___/|_| |_|  \__,_|\___|
   _____                 _                             _        _
  |  ___|   _ _ __   ___(_) ___  _ __   ___  ___    __| | ___  | | __ _
  | |_ | | | | '_ \ / __| |/ _ \| '_ \ / _ \/ __|  / _` |/ _ \ | |/ _` |
  |  _|| |_| | | | | (__| | (_) | | | |  __/\__ \ | (_| |  __/ | | (_| |
  |_|   \__,_|_| |_|\___|_|\___/|_| |_|\___||___/  \__,_|\___| |_|\__,_|
   _   _            _
  | | | | __ _ _ __| |_
  | | | |/ _` | '__| __|
  | |_| | (_| | |  | |_
   \___/ \__,_|_|   \__|   */
  
#include "UART.h"
char Buffer[10];
void uart_init() {
	// Configurar la velocidad de transmisión a 57600 baudios,
	UBRR0H = 0;
	UBRR0L = 16;

	// Habilitar el transmisor y el receptor
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// Configurar el formato del trama: 8 bits de datos, 1 bit de parada
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Enviar un solo carácter por la UART
void uart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar hasta que el buffer esté vacío
	UDR0 = c;
}

// Enviar una cadena (texto) terminada en nulo por la UART
void uart_send_string(const char* str) {
	while (*str) {
		uart_send_char(*str);
		str++;
	}
}

// Enviar un carácter de salto de línea por la UART
void uart_send_newline() {
	uart_send_char(13);
	uart_send_char(10);
}

// Recibir un carácter desde la UART
char uart_receive_char() {
	while (!(UCSR0A & (1 << RXC0))); // Esperar hasta que se reciba un dato
	char recibido = UDR0;
	if (recibido=='_'){ // Si envia un guión bajo devuelve un 0
		recibido='\0';  // esto es para que se pueda poner fin a un nuevo nombre
	}																	
	return recibido;
}

char echo_serialNobloqueante(int Bandera1,int Bandera3,int Bandera2) {// Lo que lo gace no bloqueante es que si alguna de las banderas está
	char recibido;													  // en alto, no se espera que se reciba un dato
	int BanderaBloqueo=((Bandera1)||(Bandera2)||(Bandera3));
	if (BanderaBloqueo){                                              // En C, todo valor distinto de 0 es verdadero
		recibido=';';
		return recibido;
	}else {
	char input = uart_receive_char(); // TENGO QUE PREGUNTARLE AL EDU PORQUE SI LLAMO AL NO BLOQUEANTE SE ROMPE TODO
	uart_send_char(input);
	recibido=input;
	return recibido;}
}
// Función para el eco serial  y recuperar el dato mandado vía uart

char echo_serial() {
	char input = uart_receive_char();
	uart_send_char(input);
	uart_send_newline();
	char recibido=input;
	return recibido;
}

void MandarStringdesdePrograma(const char *str) {
	char c;
	while ((c = pgm_read_byte(str++))) { // Leemos de la memoria del programa
		uart_send_char(c); // Enviamos un caracter
	}
}

void EnviarTextoSeleccionarOpcion(){
	uart_send_newline();
	MandarStringdesdePrograma(TextoElegir);
	
}

/*  ____                _   __              _
   / ___|  ___  ___ ___(_) /_/  _ __     __| | ___             /////    Las siguientes funciones sson solo menús
   \___ \ / _ \/ __/ __| |/ _ \| '_ \   / _` |/ _ \            /////     de la interfaz gráfica de la UART
    ___) |  __/ (_| (__| | (_) | | | | | (_| |  __/            /////    las funciones de acá en adelante son sólo 
   |____/ \___|\___\___|_|\___/|_| |_|  \__,_|\___|            /////    combinaciones de las anteriores...
   __  __              __
  |  \/  | ___ _ __  _/_/_ ___
  | |\/| |/ _ \ '_ \| | | / __|
  | |  | |  __/ | | | |_| \__ \
  |_|  |_|\___|_| |_|\__,_|___/
                                    */
void Bienvenida(void) {
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida0);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida1);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida2);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida3);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida4);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida5);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida6);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida7);
	uart_send_newline();
	MandarStringdesdePrograma(Bienvenida8);
	uart_send_newline();
	uart_send_newline(); // Espaciado queda más bonito UwU
}

void Carpy(void) {
	uart_send_newline();
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy0);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy1);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy2);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy3);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy4);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy5);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy6);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy7);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy8);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy9);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy10);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy11);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy12);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy13);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy14);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy15);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy16);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy17);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy18);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy19);
	uart_send_newline();
	MandarStringdesdePrograma(Carpyy20);
	uart_send_newline();
	uart_send_newline();
	MandarStringdesdePrograma(TextoElegir);
}
	
void MenuInicial(void){
	uart_send_newline();
	MandarStringdesdePrograma(Menu0_0);
	uart_send_newline();
	MandarStringdesdePrograma(Menu0_1);
	uart_send_newline();
	MandarStringdesdePrograma(Menu0_2);
	uart_send_newline();
	MandarStringdesdePrograma(Menu0_3);
	uart_send_newline();
	MandarStringdesdePrograma(TextoRegresar);
	uart_send_newline();
	MandarStringdesdePrograma(TextoElegir);
}	
void MenuMediciones(int PesoBidon,int TemperaturaBidon, int NivelPolvo1,int NivelPolvo2,int NivelPolvo3,int NivelPolvo4) {
	uart_send_newline();
	MandarStringdesdePrograma(MenuMediciones0);
	uart_send_newline();
	MandarStringdesdePrograma(MenuMediciones1);
	uart_send_newline();
	MandarStringdesdePrograma(MenuMediciones2);
	uart_send_newline();
	MandarStringdesdePrograma(TextoBidon);
	uart_send_newline();
	MandarStringdesdePrograma(TextoTemperatura);
	sprintf(Buffer, "%d", TemperaturaBidon);
	uart_send_string(Buffer);
	MandarStringdesdePrograma(TextoTemperatura0);
	uart_send_newline();
	MandarStringdesdePrograma(TextoVolumen);
	sprintf(Buffer, "%d", PesoBidon);
	uart_send_string(Buffer);
	MandarStringdesdePrograma(TextoVolumen0);
	uart_send_newline();
	MandarStringdesdePrograma(TextoDosificador);
	uart_send_newline();
	uart_send_string("Bebida 1 ->");EPROM_Read_String(NombreB1, Buffer, 12); uart_send_string(Buffer);uart_send_string(": ");
	sprintf(Buffer, "%d", NivelPolvo1);
	uart_send_string(Buffer); uart_send_string("%");
	uart_send_newline();
	uart_send_string("Bebida 2 ->");EPROM_Read_String(NombreB2, Buffer, 12); uart_send_string(Buffer);uart_send_string(": ");
	sprintf(Buffer, "%d", NivelPolvo2);
	uart_send_string(Buffer); uart_send_string("%");
	uart_send_newline();
	uart_send_string("Bebida 3 ->");EPROM_Read_String(NombreB3, Buffer, 12); uart_send_string(Buffer);uart_send_string(": ");
	sprintf(Buffer, "%d", NivelPolvo3);
	uart_send_string(Buffer); uart_send_string("%");
	uart_send_newline();
	uart_send_string("Bebida 4 ->");EPROM_Read_String(NombreB4, Buffer, 12); uart_send_string(Buffer);uart_send_string(": ");
	sprintf(Buffer, "%d", NivelPolvo4);
	uart_send_string(Buffer); uart_send_string("%");
	uart_send_newline();
	MandarStringdesdePrograma(TextoRegresar);
}
void MenuCambiarVolumenBidon(void) {
	
}
void MenuConfiguraciones(void) {
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion0);EPROM_Read_String(TemperaturaDeseada, Buffer, 10); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion1);EPROM_Read_String(NombreB1, Buffer, 12); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion2);EPROM_Read_String(NombreB2, Buffer, 12); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion3);EPROM_Read_String(NombreB3, Buffer, 10); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion4);EPROM_Read_String(NombreB4, Buffer, 10); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion6);EPROM_Read_String(KpEprom, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion7);EPROM_Read_String(DosificacionB1, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion8);EPROM_Read_String(DosificacionB2, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion9);EPROM_Read_String(DosificacionB3, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion10);EPROM_Read_String(DosificacionB4, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion11);EPROM_Read_String(CAguaB1, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion12);EPROM_Read_String(CAguaB2, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion13);EPROM_Read_String(CAguaB3, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion14);EPROM_Read_String(CAguaB4, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion15);EPROM_Read_String(PorcDescargaB1, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion16);EPROM_Read_String(PorcDescargaB2, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion17);EPROM_Read_String(PorcDescargaB3, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion18);EPROM_Read_String(PorcDescargaB4, Buffer, 3); uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion19);EPROM_Read_String(TamagnoBidon, Buffer, 3); uart_send_string(Buffer);
	uart_send_string("0 Litros");
	uart_send_newline();
	MandarStringdesdePrograma(TextoRegresar);
}

void MenuCambioDeNombre(void){
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre0);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre1);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre2);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre3);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre4);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre5);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNombre6);
	uart_send_newline();}
	
void Fracaso(void){
	uart_send_newline();
	MandarStringdesdePrograma(TextoFracaso);
	uart_send_newline();
	MandarStringdesdePrograma(TextoFracaso1);
	uart_send_newline();
	}
	
void CambioDeNumero(void){
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero0);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero1);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero2);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero3);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero4);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero5);
	uart_send_newline();
	MandarStringdesdePrograma(MenuCambioDeNumero6);
	uart_send_newline();
}

void MenuTamanho(void){
	uart_send_newline();
	MandarStringdesdePrograma(MenuTamagno);
	uart_send_newline();
	MandarStringdesdePrograma(MenuTamagno0);
	uart_send_newline();
	MandarStringdesdePrograma(MenuTamagno1);
	uart_send_newline();
}