

#include <msp430.h> 
#define BTN BIT3
#define LED BIT0
#define ACENDE_LED (P1OUT |= LED)
#define APAGA_LED (P1OUT &= ~LED)


int Debounce();
void espera_ms(int tempo);
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED;
	P1OUT &= ~LED;
	P1DIR &= ~BTN;
	P1REN |= BTN;
	P1OUT |= BTN;
	while(1)
	 Debounce() == 1 ? ACENDE_LED : APAGA_LED;

	return 0;
}



int Debounce()
{
    if((P1IN & BTN)==0)
    {
        espera_ms(30);
        if((P1IN & BTN) == 0)
            return 1;

    }
    return 0;
}

void espera_ms(int tempo)
{
    TACCR0 = 1000-1; // Preenche esse registador com um mutiplo de 10
    TACTL = TACLR; //limpa as configurações do timerA
    TACTL = TASSEL_2 + ID_0 + MC_1;
   while(tempo > 0)
    {
       while((TACTL&TAIFG) == 0);
       tempo--;
    }
   TACTL = TACLR;

}

