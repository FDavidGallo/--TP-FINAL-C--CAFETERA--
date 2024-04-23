#include <avr/pgmspace.h>
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
const char TextoElegir[] PROGMEM = ">>Seleccione alguna de las siguientes opciones";
const char TextoRegresar[] PROGMEM = ">>Aprete X para volver al menu inicial";
const char TextoExito[] PROGMEM = ">>¡Cambio exitoso!!<<";
const char TextoFracaso[] PROGMEM = ">>ERROR: LA CANTIDAD PROPUESTA ESTÁ FUERA DE RANGO";
const char TextoFracaso1[] PROGMEM = ">>Por favor, intentelo nuevamente";
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
 
 
 
const char Carpyy[] PROGMEM="                         90  400     TPFI... CATEDRA:    SISTEMAS DIGITALES IV";
const char Carpyy0[] PROGMEM="                    1232800000000                    PROFESORES: ING EDUARDO VELAZQUEZ";
const char Carpyy1[] PROGMEM="                400000000000000007                                LIC JULIAN MINATEL   ";
const char Carpyy2[] PROGMEM="           400000000000  300000005      NOMBRE: FABRICIO DAVID GALLO                 ";
const char Carpyy3[] PROGMEM="           0000 800000000000000000000                                    ";
const char Carpyy4[] PROGMEM="           40000000000000000000000000000            'CAFETERA' ES UN PROYECTO DONDE SE " ;
const char Carpyy5[] PROGMEM="           700000000000000000000000000000007              PUEDEN CONTROLAR TEMPERATURA, ";
const char Carpyy6[] PROGMEM="            00000000000000000000000000000000000000000004      CANTIDAD DE PREMEZCLA,ETC  ";
const char Carpyy7[] PROGMEM="             800000000000000000000000000000000000000000000001      PARA MODIFICAR ESTOS  ";
const char Carpyy8[] PROGMEM="                  000000000000000000000000000000000000000000006            UTILICE ESTA   ";
const char Carpyy9[] PROGMEM="                     10000000000000000000000000000000000000000001              CONSOLA";
const char Carpyy10[] PROGMEM="                      00000000000000000000000000000000000000000000 ";
const char Carpyy11[] PROGMEM="                        900000000000000000000000000000000000000000000 ";
const char Carpyy12[] PROGMEM="       1  1             9000000000000000000000000000000000000000000000 ";
const char Carpyy13[] PROGMEM="        1  1             000000000000000000000000000000000000000000000";
const char Carpyy14[] PROGMEM="       1  1              9000000000000000000000000000000000000000000008 ";
const char Carpyy15[] PROGMEM="     00000000037          600000000000000000000000000000000000000000005 ";
const char Carpyy16[] PROGMEM="     000000009  9          0000000000000000000000000000000000000000000  ";
const char Carpyy17[] PROGMEM="     0000000002            900000000000000000000000000000000000000000  ";
const char Carpyy18[] PROGMEM="     000000009             900 00002 50000000000000000000000000000000   ";
const char Carpyy19[] PROGMEM="     000000006             900 8006       70000000000000000000000000  ";
const char Carpyy20[] PROGMEM="  444666666666445         30006000                50000000000000000   ";

// TEXTO PARA LAS CONFIGURACIONES
const char MenuConfiguracion0[] PROGMEM=" A-Temperatura Deseada (60-95)*C";
const char MenuConfiguracion1[] PROGMEM=" B-Nombre de la Bebida 1 (10 carácteres)";
const char MenuConfiguracion2[] PROGMEM=" C-Nombre de la Bebida 2 (10 carácteres)";
const char MenuConfiguracion3[] PROGMEM=" D-Nombre de la Bebida 3 (10 carácteres)";
const char MenuConfiguracion4[] PROGMEM=" E-Nombre de la Bebida 4 (10 carácteres)";
const char MenuConfiguracion5[] PROGMEM=" F-Nombre de la Bebida 1 (10 carácteres)";
const char MenuConfiguracion6[] PROGMEM=" G-Constante Proporcional 'Kp':";
const char MenuConfiguracion7[] PROGMEM=" H-Cantidad de premezcla Bebida 1 (0 a 420 mL)";
const char MenuConfiguracion8[] PROGMEM=" I-Cantidad de premezcla Bebida 2 (0 a 420 mL)";
const char MenuConfiguracion9[] PROGMEM=" J-Cantidad de premezcla Bebida 3 (0 a 420 mL)";
const char MenuConfiguracion10[] PROGMEM=" K-Cantidad de premezcla Bebida 4 (0 a 420 mL)";
const char MenuConfiguracion11[] PROGMEM=" M-Cantidad de agua Caliente Bebida 1 (150 a 300 mL)";
const char MenuConfiguracion12[] PROGMEM=" N-Cantidad de agua Caliente Bebida 2 (150 a 300 mL)";
const char MenuConfiguracion13[] PROGMEM=" O-Cantidad de agua Caliente Bebida 3 (150 a 300 mL)";
const char MenuConfiguracion14[] PROGMEM=" P-Cantidad de agua Caliente Bebida 4 (150 a 300 mL)";
const char MenuConfiguracion15[] PROGMEM=" Q-Porcentaje de Tdescarga Bebida 1 (5 a 25%)";
const char MenuConfiguracion16[] PROGMEM=" R-Porcentaje de Tdescarga Bebida 2 (5 a 25%)";
const char MenuConfiguracion17[] PROGMEM=" S-Porcentaje de Tdescarga Bebida 3 (5 a 25%)";
const char MenuConfiguracion18[] PROGMEM=" T-Porcentaje de Tdescarga Bebida 4 (5 a 25%)";
const char MenuConfiguracion19[] PROGMEM=" U-Tamaño de Bidon (10 L -20 L)";
// MENU TAMAÑO BIDON
const char MenuTamagno[] PROGMEM=">>Seleccione el nuevo volumen:";
const char MenuTamagno0[] PROGMEM="V- 10 L";
const char MenuTamagno1[] PROGMEM="W- 20 L";

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
	// Configurar la velocidad de transmisión a 9600
	UBRR0H = 0;
	UBRR0L = 103;

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
	return recibido;
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
}

void Carpy() {
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
	uart_send_string("Bebida 1: ");
	sprintf(Buffer, "%d", NivelPolvo1);
	uart_send_string(Buffer);
	uart_send_newline();
	uart_send_string("Bebida 2: ");
	sprintf(Buffer, "%d", NivelPolvo2);
	uart_send_string(Buffer);
	uart_send_newline();
	uart_send_string("Bebida 3: ");
	sprintf(Buffer, "%d", NivelPolvo3);
	uart_send_string(Buffer);
	uart_send_newline();
	uart_send_string("Bebida 4: ");
	sprintf(Buffer, "%d", NivelPolvo4);
	uart_send_string(Buffer);
	uart_send_newline();
	MandarStringdesdePrograma(TextoRegresar);
}
void MenuCambiarVolumenBidon(void) {
	
}
void MenuConfiguraciones(void) {
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion0);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion1);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion2);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion3);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion4);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion5);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion6);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion7);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion8);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion9);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion10);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion11);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion12);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion13);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion14);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion15);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion16);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion17);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion18);
	uart_send_newline();
	MandarStringdesdePrograma(MenuConfiguracion19);
	uart_send_newline();
	MandarStringdesdePrograma(TextoRegresar);
}
