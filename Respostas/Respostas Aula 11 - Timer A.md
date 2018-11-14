1. Defina a função `void Atraso(volatile unsigned int x);` que fornece um atraso de `x` milissegundos. Utilize o Timer_A para a contagem de tempo, e assuma que o SMCLK já foi configurado para funcionar a 1 MHz. Esta função poderá ser utilizada diretamente nas outras questões desta prova.


```C
void Atraso(volatile unsigned int x)
{
    TA0CCR0 = 1000-1; //Contando de 0-999, SMCLK 1MHz -> 1000*1us = 1ms
	// Selecionando SMCLK como entrada para o timer com TASSEL_2
	// Dividindo o clock de entrada por 1 com ID_0 e acionando modo UP com MC_1
	TA0CTL = TASSEL_2 + ID_0 + MC_1;
	while(x > 0)
	{
        while((TA0CTL & TAIFG)==0);
        x--;
        TA0CTL &= ~TAIFG;
	}
	TA0CTL |= TACLR; //Resetando e parando o TimerA
}
```

2. Pisque os LEDs da Launchpad numa frequência de 100 Hz.
3. Pisque os LEDs da Launchpad numa frequência de 20 Hz.
4. Pisque os LEDs da Launchpad numa frequência de 1 Hz.
5. Pisque os LEDs da Launchpad numa frequência de 0,5 Hz.

```C
void pisca(unsigned int freq, unsigned int deciHz)
{
	int T;
	deciHz == 1 ? T=1000/f : T=10000/f;
	T = T/2;
	P1OUT |= LEDS;
	atraso(T);
	P1OUT &= ~LEDS;
	atraso(T);
}
```

6. Repita as questões 2 a 5 usando a interrupção do Timer A para acender ou apagar os LEDs.

```C
void Atraso(volatile unsigned int x)
{
    TA0CCR0 = 1000-1; //Contando de 0-999, SMCLK 1MHz -> 1000*1us = 1ms
	// Selecionando SMCLK como entrada para o timer com TASSEL_2
	// Dividindo o clock de entrada por 1 com ID_0 e acionando modo UP com MC_1
	TA0CTL = TASSEL_2 + ID_0 + MC_1 + TAIE;
}

interrupt(TIMER0_A1_VECTOR) TA0_ISR(void)
{
	x--;
	if(x == 0)
		P1OUT ^= LED;
	TA0CTL &= ~TAIFG;
}
```

7. Defina a função `void paralelo_para_serial(void);` que lê o byte de entrada via porta P1 e transmite os bits serialmente via pino P2.0. Comece com um bit em nivel alto, depois os bits na ordem P1.0 - P1.1 - … - P1.7 e termine com um bit em nível baixo. Considere um período de 1 ms entre os bits.

```C
#define SAIDASERIAL P2OUT
#define ENTRADAPAR P1IN

void Atraso_ms(volatile unsigned int ms); //Função para delay com timer.

void paralelo_para_serial(void)
{
	char seq[] = {BIT0, BIT1, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};	
	SAIDASERIAL |= BIT0;
	for(int i = 0; i < 8; i++)
	{
		if((ENTRADAPAR & seq[i]) == 1)
			SAIDASERIAL |= BIT0;
		else
			SAIDASERIAL &= ~BIT0;
		Atraso_ms(1);
	}
	SAIDASERIAL &= ~BIT0;
}

void Atraso_ms(volatile unsigned int ms)
{
	TACCR0 = 1000-1;
	TACTL = TACLR;
	TACTL = TASSEL_2 + ID_0 + MC_1;
	while(ms--)
	{
		while((TACTL&TAIFG)==0);
		TACTL &= ~TAIFG;
	}
	TACTL = MC_0;
}
```

8. Faça o programa completo que lê um byte de entrada serialmente via pino P2.0 e transmite este byte via porta P1. O sinal serial começa com um bit em nivel alto, depois os bits na ordem 0-7 e termina com um bit em nível baixo. Os pinos P1.0-P1.7 deverão corresponder aos bits 0-7, respectivamente. Considere um período de 1 ms entre os bits.

```C
#define SAIDAPAR P1OUT
#define ENTRADASER P2IN

void Atraso_ms(volatile unsigned int ms); //Função para delay com timer.

void serial_para_paralelo(void)
{
	char seq[] = {BIT0, BIT1, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};
	
	while((ENTRADASER & BIT0) == 0); // Aguarda bit em nível alto para iniciar transmissão.
	Atraso_ms(1);
	for(int i = 0; i < 8; i++)
	{
		if((ENTRADASER & seq[i]) == 1)
			SAIDAPAR |= seq[i];
		else
			SAIDAPAR &= ~seq[i];
		Atraso_ms(1);
	}
	while((ENTRADASER & BIT0) == 1); // Aguarda bit em nível baixo	
}

void Atraso_ms(volatile unsigned int ms)
{
	TACCR0 = 1000-1;
	TACTL = TACLR;
	TACTL = TASSEL_2 + ID_0 + MC_1;
	while(ms--)
	{
		while((TACTL&TAIFG)==0);
		TACTL &= ~TAIFG;
	}
	TACTL = MC_0;
}
```

9. Defina a função `void ConfigPWM(volatile unsigned int freqs, volatile unsigned char ciclo_de_trabalho);` para configurar e ligar o Timer_A em modo de comparação. Considere que o pino P1.6 já foi anteriormente configurado como saída do canal 1 de comparação do Timer_A, que somente os valores {100, 200, 300, …, 1000} Hz são válidos para a frequência, que somente os valores {0, 25, 50, 75, 100} % são válidos para o ciclo de trabalho, e que o sinal de clock SMCLK do MSP430 está operando a 1 MHz.

```C
void ConfigPWM(volatile unsigned int freqs, volatile unsigned char ciclo_de_trabalho)
{
	unsigned int T = 500000/f; //T em us.
	
	//Carrega o período da onda em us para contagem no Timer.
	TACCR0 = T-1;
	//Calcula ciclo de trabalho baseado na entrada.
	TACCR1 = (_ciclo_de_trabalho*T/100)-1;
	TACCTL1 = OUTMOD_7; // Modo reset/set para saída da comparação.
    // Entrada de clock é SMCLK dividido por 2 em modo UP.
    TACTL = TASSEL_2 + ID_1 + MC_1;
}
```

