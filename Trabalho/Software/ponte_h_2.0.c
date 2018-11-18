/*#include <msp430g2553.h>
#include <legacymsp430.h> // Para rodar interrupcoes

#define MOTORA1 BIT0
#define MOTORA2 BIT1
#define MOTORB1 BIT6
#define MOTORB2 BIT3
#define BTN  BIT3

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT &= ~MOTORB1;
    P1OUT &= ~MOTORB2;
    P1DIR |= MOTORA1;
    P1DIR |= MOTORA2;
    P1DIR |= MOTORB1;
    P1DIR |= MOTORB2;
    P1DIR &= ~BTN;
    P1REN |= BTN;
    P1OUT |= BTN;
    P1IES |= BTN;
    P1IE |= BTN;

    TA0CCR0 = 62500-1; //10000-1;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    while(1)
    {
        while((TA0CTL & TAIFG)==0);
        frente();
        __delay_cycles(9000000);
        direita();
        __delay_cycles(3000000);             // for 10us
        TA0CTL &= ~TAIFG;
        frente();
        __delay_cycles(9000000);
        esquerda();
        __delay_cycles(3000000);


    }
}

void frente()
{
    P1OUT |= MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT |= MOTORB1;
    P1OUT &= ~MOTORB2;


}
void direita()
{
    P1OUT |= MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT &= ~MOTORB1;
    P1OUT &= ~MOTORB2;


}
void esquerda()
{
    P1OUT &= ~MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT |= MOTORB1;
    P1OUT &= ~MOTORB2;


} */
#include <msp430g2553.h>
#include <legacymsp430.h> // Para rodar interrupcoes
#define BTN  BIT3
#define MOTORA1 BIT0
#define LEDS (MOTORA1|MOTORB1)
#define MOTORA2 BIT1
#define MOTORB1 BIT6
#define MOTORB2 BIT2


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR &= ~BTN;
    P1REN |= BTN;
    P1OUT |= BTN;
    P1IES |= BTN;
    P1IE |= BTN;
    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT &= ~MOTORB1;
    P1OUT &= ~MOTORB2;
    P1DIR |= MOTORA1;
    P1DIR |= MOTORA2;
    P1DIR |= MOTORB1;
    P1DIR |= MOTORB2;
    TA0CCR0 = 62500-1; //10000-1;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    _BIS_SR(GIE);
    while(1)
    {
        while(1)
        {
            while((TA0CTL & TAIFG)==0);
            frente();
            __delay_cycles(9000000);
            direita();
            __delay_cycles(3000000);             // for 10us
            TA0CTL &= ~TAIFG;
            frente();
            __delay_cycles(9000000);
            esquerda();
            __delay_cycles(3000000);

    }
    return 0;
}}

interrupt(PORT1_VECTOR) Interrupcao_P1(void)
{
    while((P1IN&BTN)==0){
        P1OUT &= ~MOTORA1;
        P1OUT &= ~MOTORA2;
        P1OUT &= ~MOTORB1;
        P1OUT &= ~MOTORB2;}
    P1IFG &= ~BTN;
}


void frente()
{
    P1OUT |= MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT |= MOTORB1;
    P1OUT &= ~MOTORB2;


}
void direita()
{
    P1OUT |= MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT &= ~MOTORB1;
    P1OUT &= ~MOTORB2;


}
void esquerda()
{
    P1OUT &= ~MOTORA1;
    P1OUT &= ~MOTORA2;
    P1OUT |= MOTORB1;
    P1OUT &= ~MOTORB2;


}


