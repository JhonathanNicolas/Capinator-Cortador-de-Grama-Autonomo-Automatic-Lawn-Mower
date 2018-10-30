Para todas as questões, utilize os LEDs e/ou os botões da placa Launchpad do MSP430.

Escreva um código em C que pisca os LEDs ininterruptamente.
void pisca()
{
    while(true)
    	P1OUT ^= LEDS;
}
Escreva um código em C que pisca os LEDs ininterruptamente. No ciclo que pisca os LEDs, o tempo que os LEDs ficam ligados deve ser duas vezes maior do que o tempo que eles ficam desligados.
void piscaV2(volatile unsigned int Tdelay)
{
    P1OUT &= ~LEDS;
    while(true)
    {
    	P1OUT |= LEDS;
    	atraso(2*Tdelay);
    	P1OUT &= ~LEDS;
    	atraso(Tdelay);
    }
}
Escreva um código em C que acende os LEDs quando o botão é pressionado.
while(true)
{
    if(P1IN & BTN == 0)
    	P1OUT |= LEDS;
    else
    	P1OUT &~= LEDS;
}
Escreva um código em C que pisca os LEDs ininterruptamente somente se o botão for pressionado.
#include <msp430.h>
#define LED1 BIT0
#define LED2 BIT1
#define LEDS LED1|LED2
#define BTN BIT3

void main (void){
    WDTCTL = WDTPW|WDTHOLD;
    P1DIR |= LEDS;
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;
    P1OUT &= ~LEDS;
    while(1)
    {
        if((P2IN & BTN) == 0)
            P1OUT ^= LEDS;
        else
            P1OUT &= ~LEDS;
    }
}
Escreva um código em C que acende os LEDs quando o botão é pressionado. Deixe o MSP430 em modo de baixo consumo, e habilite a interrupção do botão.
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	P1DIR |= LEDS;
	P1DIR &= ~BTN;
	P1REN |= BTN;
	P1OUT |= BTN;
	P1IES |= BTN;
	P1IE |= BTN;
	_BIS_SR(GIE + LPM4_bits);
	return 0;
}

interrupt(PORT1_VECTOR) Interrupcao_P1(void)
{
	P1OUT |= LEDS;
	while((P1IN&BTN)==0);
	P1OUT &= ~LEDS;
	P1IFG &= ~BTN;
}
