Para todas as questões abaixo, utilize o modo de comparação do Timer A.

1. Para os itens abaixo, confira a diferença no brilho do LED.
	(a) Pisque o LED no pino P1.6 numa frequência de 100 Hz e ciclo de trabalho de 25%.	
> Função utilizada: `ConfigPWM(100,25);`. Foi possível notar um reduzido brilho do led para o ciclo de trabalho adotado.
	
	(b) Pisque o LED no pino P1.6 numa frequência de 100 Hz e ciclo de trabalho de 50%.
> Função utilizada: `ConfigPWM(100,50);`. Foi possível notar um leve brilho do led para o ciclo de trabalho adotado.
	
	(c) Pisque o LED no pino P1.6 numa frequência de 100 Hz e ciclo de trabalho de 75%.
> Função utilizada: `ConfigPWM(100,75);`. Foi possível notar um médio brilho do led para o ciclo de trabalho adotado.
	
Código para o modo de comparação do timer A
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

2. Pisque o LED no pino P1.6 numa frequência de 1 Hz e ciclo de trabalho de 25%.
Utilizar `void ConfigPwm1Hz(25)` para a questão proposta.

3. Pisque o LED no pino P1.6 numa frequência de 1 Hz e ciclo de trabalho de 50%.
Utilizar `void ConfigPwm1Hz(50)` para a questão proposta.

4. Pisque o LED no pino P1.6 numa frequência de 1 Hz e ciclo de trabalho de 75%.
Utilizar `void ConfigPwm1Hz(75)` para a questão proposta.

> Timer A configurado com o MCLK como clock de entrada, sendo dividido por 8 e com período de 500ms. Ao acionar o modo toggle dobra-se o período da onda e por meio do registrador TA0CCR1 é possível configurar o ciclo de trabalho para o exercício.
```C
void ConfigPwm1Hz(volatile unsigned int ciclo)
{
	TACCR0 = 62500-1;
	TACCR1 = (ciclo*62500/100)-1;
	TACCTL1 = OUTMOD_4; //Modo Toggle para dobrar período
	TACTL = TASSEL_2 + ID_3 + MC_3;
}
```

