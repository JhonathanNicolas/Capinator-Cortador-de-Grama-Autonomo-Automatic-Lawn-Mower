#include <msp430.h> 
#include <legacymsp430.h>


#define LED BIT6
#define APAGA_LED (P1OUT &= ~LED)
#define ACENDE_LED (P1OUT |= LED)

void Atraso(volatile unsigned int x);
void InicializaLED();
void PiscaLED(unsigned int frequenciaCTL);

int main(void)
{
    InicializaLED();
    unsigned int frequenciaCTL = 3; // variável para escolher as frequencias dos exercicios entre 0 e 3
    while(1){
    PiscaLED( frequenciaCTL); // garante com a operação %4 que a frequencia será entre 0 e 3
    }


}


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
void InicializaLED()
{
    P1DIR |= LED;
    P1OUT &= ~LED;

}
void PiscaLED(unsigned int frequenciaCTL)
{
   float frequencia[4] = {100, 20, 1, 0.5};// Vetor contendo as frequencias dos exercicios
   int Periodo_ms; // variável periodo em milisegundos
   Periodo_ms = (1000/frequencia[frequenciaCTL]); // periodo será igual ao inverso da frequencia escolhida
   ACENDE_LED; // acende o led
   Atraso(Periodo_ms/2);// Fica metade do pediodo acesso;
   APAGA_LED; //apaga o led;
   Atraso(Periodo_ms/2);// Fica metade do pediodo apagado;

}
