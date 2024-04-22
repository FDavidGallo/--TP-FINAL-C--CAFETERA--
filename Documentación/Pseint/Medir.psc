Algoritmo Medir
	// Esta funci�n tiene por misi�n Leer Todo lo Necesario
	// Lo �nico que no se lee ac� son los sensores puerta y taza
	MedicionBotones()
	MedirTemperaturaTanque()
	PesarTanque()
	MedirDosificadores()
FinAlgoritmo

Funcion MedicionBotones
	Leer BotonSelecionar
	Si BotonSeleccionar=1 Entonces
		SelectorMenuLCD = SelectorMenuLcd+1
		Si SelectorMenuLcd=5 Entonces
			SelectorMenuLcd = 1
		FinSi
		Segun SelectorMenuLcd Hacer
			1:
				Escribir Mostrar Bedida1
			2:
				Escribir Mostrar Bebida2
			3:
				Escribir Mostrar Bebida3
			4:
				Escribir Mostrar Bebida4
			De Otro Modo:
				SelectorMenuLcd = 1
				Escribir Mostrar Bebida1
		FinSegun
	FinSi
	Leer BotonAceptar
	Si BotonAceptar=1 Entonces
		ServirBebida(SelectorMenuLcd)
	FinSi
FinFuncion

Funcion MedirTemperaturaTanque
	Temperatura = LeerTemperatura()
FinFuncion

Funcion PesarTanque
	// Esto da en cm3
	int ValorLeido = Mcp3421_read()
	Leer de Eprom Tama�oTanque
	int Peso = (((((float)ValorLeido+2)*1000)/2047)*Tama�oTanque)
	// El valor leido se lo pasa a cm3, 
	// al fondo de escala, partido por el tama�o del tanque
FinFuncion

Funcion MedirDosificadores
	iniciar_Adc()
	LeerADC(0)
	NivelPolvo1 = (ADC/1023)*100
	// La anterior ecuaci�n agarra lo medido mediante el ADC
	// y lo pone en porcentaje con precisi�n entera.
	Repetimos con NivelPolvo2,3 y 4
FinFuncion
