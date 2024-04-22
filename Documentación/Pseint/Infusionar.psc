Algoritmo Infusionar(SelectorMenuLcd)
	Si BotonAceptar=1 Entonces
		BotonAceptar = 0
		Si SensorPuerta=0 Entonces
			Si SensorTaza=0 Entonces
				Segun SelectorMenuLCD Hacer
					1:
						PrepararBebida1()
						ServirBebida1()
					2:
						PrepararBebida2()
						ServirBebida2()
					3:
						PrepararBebida3()
						ServirBebida3()
					4:
						PrepararBebida4()
						ServirBebida4()
					De Otro Modo:
						SelectorMenuLcd = 1
						Infusionar(SelectorMenuLcd)
				FinSegun
				LcdInit()
				EscribirLcd("Disfrute")
				i2cStop()
			SiNo
				LcdInit()
				EscribirenLcd(" Falta la Taza")
				Reintente()
				i2cstop()
				MedirVariables()
				Infusionar(SelectorMenuLcd)
			FinSi
		SiNo
			lcdInit()
			EscribirenLcd(" Puerta Abierta")
			Reintente()
			i2cstop()
			MedirVariables()
			Infusionar(SelectorMenuLcd)
		FinSi
	FinSi
FinAlgoritmo
