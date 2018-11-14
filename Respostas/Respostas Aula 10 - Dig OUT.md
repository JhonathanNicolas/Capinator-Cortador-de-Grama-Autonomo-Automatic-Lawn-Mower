1. Projete o hardware necessário para o MSP430 controlar um motor DC de 12V e 4A. Utilize transistores bipolares de junção (TBJ) com Vbe = 0,7 V, beta = 100 e Vce(saturação) = 0,2 V. Além disso, considere que Vcc = 3 V para o MSP430, e que este não pode fornecer mais do que 10 mA por porta digital.

> Avaliamos se devemos usar Transistor Bipolar ou Par Darlington fazendo os cálculos da corrente de base (Ib deve ser menor de 10 mA).

`Ic = B*Ib`
`4 = 100*Ib`
`Ib = 40 mA`

> Devemos usar par Darlington. Calculemos a corrente de base e o resistor necessário.

`Ic = Ib*B**2`
`4 = Ib*100**2`
`Ib = 0.4 mA`

`Rb = (Vcc -2*Vbe)/Ib`
`Rb = (3 -2*0.7)/0.4*10**-3`
`Rb = 4 kOhm`

2. Projete o hardware necessário para o MSP430 controlar um motor DC de 10V e 1A. Utilize transistores bipolares de junção (TBJ) com Vbe = 0,7 V e beta = 120. Além disso, considere que Vcc = 3,5 V para o MSP430, e que este não pode fornecer mais do que 10 mA por porta digital.

> Avaliamos se devemos usar Transistor Bipolar ou Par Darlington fazendo os cálculos da corrente de base (Ib deve ser menor de 10 mA).

`Ic = B*Ib`
`1 = 120*Ib`
`Ib = 8.33 mA`

> Utilizamos somente um transistor. Calculamos a resistências necessária.

`Rb = (Vcc -Vbe)/Ib`
`Rb = (3.5 -0.7)/8.33*10**-3`
`Rb = 336 Ohm`

3. Projete o hardware utilizado para controlar 6 LEDs utilizando charlieplexing. Apresente os pinos utilizados no MSP430 e os LEDs, nomeados L1-L6.



4. Defina a função `void main(void){}` para controlar 6 LEDs de uma árvore de natal usando o hardware da questão anterior. Acenda os LEDs de forma que um ser humano veja todos acesos ao mesmo tempo.

```C
void main(void)
{
    while(1)
    {
		//Acendendo D1
		P1DIR = (P1DIR|(BIT1+BIT2))&(~BIT0)
		P1OUT = (P1OUT|BIT1)&(~BIT2);
        //Acendendo D2
		P1DIR = (P1DIR|(BIT1+BIT2))&(~BIT0)
		P1OUT = (P1OUT|BIT2)&(~BIT1);
        //Acendendo D3
		P1DIR = (P1DIR|(BIT0+BIT1))&(~BIT2)
		P1OUT = (P1OUT|BIT0)&(~BIT1);
        //Acendendo D4
		P1DIR = (P1DIR|(BIT0+BIT1))&(~BIT2)
		P1OUT = (P1OUT|BIT1)&(~BIT0);
        //Acendendo D5
		P1DIR = (P1DIR|(BIT0+BIT2))&(~BIT1)
		P1OUT = (P1OUT|BIT0)&(~BIT2);
        //Acendendo D6
		P1DIR = (P1DIR|(BIT0+BIT2))&(~BIT1)
		P1OUT = (P1OUT|BIT2)&(~BIT0);
	}
}
```

5. Defina a função `void main(void){}` para controlar 6 LEDs de uma árvore de natal usando o hardware da questão 3. Acenda os LEDs de forma que um ser humano veja os LEDs L1 e L2 acesos juntos por um tempo, depois os LEDs L3 e L4 juntos, e depois os LEDs L5 e L6 juntos.

```C
void main(void)
{
    volatile unsigned int i;
    while(1)
    {
		for(i = 330000; i > 0; i--)
		{
            //Acendendo D1
            P1DIR = (P1DIR|(BIT1+BIT2))&(~BIT0)
            P1OUT = (P1OUT|BIT1)&(~BIT2);
            //Acendendo D2
            P1DIR = (P1DIR|(BIT1+BIT2))&(~BIT0)
            P1OUT = (P1OUT|BIT2)&(~BIT1);
        }
        for(i = 330000; i > 0; i--)
		{
            //Acendendo D3
            P1DIR = (P1DIR|(BIT0+BIT1))&(~BIT2)
            P1OUT = (P1OUT|BIT0)&(~BIT1);
            //Acendendo D4
            P1DIR = (P1DIR|(BIT0+BIT1))&(~BIT2)
            P1OUT = (P1OUT|BIT1)&(~BIT0);
        }
        for(i = 330000; i > 0; i--)
		{
            //Acendendo D5
            P1DIR = (P1DIR|(BIT0+BIT2))&(~BIT1)
            P1OUT = (P1OUT|BIT0)&(~BIT2);
            //Acendendo D6
            P1DIR = (P1DIR|(BIT0+BIT2))&(~BIT1)
            P1OUT = (P1OUT|BIT2)&(~BIT0);
		}
	}
}
```

6. Defina a função `void EscreveDigito(volatile char dig);` que escreve um dos dígitos 0x0-0xF em um único display de 7 segmentos via porta P1, baseado na figura abaixo. Considere que em outra parte do código os pinos P1.0-P1.6 já foram configurados para corresponderem aos LEDs A-G, e que estes LEDs possuem resistores externos para limitar a corrente.

```
        ---  ==> A
       |   |
 F <== |   | ==> B
       |   |
        ---  ==> G
       |   |
 E <== |   | ==> C
       |   |
        ---  ==> D
```

```C

#define SA BIT0
#define SB BIT1
#define SC BIT2
#define SD BIT3
#define SE BIT4
#define SF BIT5
#define SG BIT6

void EscreveDigito(volatile char dig)
{
	P1OUT = 0;
	switch(dig)
	{
		case 'A':
			P1OUT |= (SA + SB + SC + SE + SF);
			break;
		case 'B':
			P1OUT |= (SF + SE + SC + SD + SG);
			break;
		case 'C':
			P1OUT |= (SA + SF + SE + SD);
			break;
		case 'D':
			P1OUT |= ~(SA + SF);
			break;
		case 'E':
			P1OUT |= ~(SB + SC);
			break;
		case 'F':
			P1OUT |= ~(SB + SC + SD);
			break;
		case '9':
			P1OUT |= ~(SD + SE);
			break;
		case '8':
			P1OUT ˆ= (P1OUT);
			break;
		case '7':
			P1OUT |= (SA + SB + SC);
			break;
		case '6':
			P1OUT |= ~(SB);
			break;
		case '5':
			P1OUT |= ~(SB + SE);
			break;
		case '4':
			P1OUT |= ~(SA + SE + SD);
			break;
		case '3':
			P1OUT |= ~(SF + SE);
			break;
		case '2':
			P1OUT |= ~(SF + SC);
			break;
		case '1':
			P1OUT |= (SB + SC);
			break;
		case '0':
			P1OUT |= ~(SG);
			break;	
		default:
			break;
	}
}
```

7. Multiplexe 2 displays de 7 segmentos para apresentar a seguinte sequência em loop:
	00 - 11 - 22 - 33 - 44 - 55 - 66 - 77 - 88 - 99 - AA - BB - CC - DD - EE - FF

```C
#define DISPLAYOUT P2OUT
#define DISPLAY1 BIT0
#define DISPLAY2 BIT1

void Atraso_ms(volatile unsigned int ms); //Função para delay com timer.

void SeqTeste()
{
	//Supondo cátodo comum ligado aos BITS 0 e 1 da porta 2.
	for(int i = 0; i <= 9; i++)
	{
		DISPLAYOUT |= DISPLAY1 + ~DISPLAY2;
		EscreveDigito((char) '0'+i);
		Atraso_ms(10);
		DISPLAYOUT |= DISPLAY2 + ~DISPLAY1;
		EscreveDigito((char) '0'+i);
		Atraso_ms(10);
	}
		for(int i = 0; i <= 6; i++)
	{
		DISPLAYOUT |= DISPLAY1 + ~DISPLAY2;
		EscreveDigito((char) 'A'+i);
		Atraso_ms(10);
		DISPLAYOUT |= DISPLAY2 + ~DISPLAY1;
		EscreveDigito((char) 'A'+i);
		Atraso_ms(10);
	}
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






