#include <msp430g2553.h>
#include <legacymsp430.h>

#define RX BIT1 //  Bit para comunicação serial RX
#define TX BIT2 //  Bit para comunicação serial TX
#define P1MOTORA BIT5 //Pino para o motor A
#define P1MOTORB BIT4 //Pino para o motor B

//Definições para comunicação uart
#define BAUD_9600   0
#define BAUD_19200  1
#define BAUD_38400  2
#define BAUD_56000  3
#define BAUD_115200 4
#define BAUD_128000 5
#define BAUD_256000 6
#define NUM_BAUDS   7
//----------------------------------

//Cabeçario para as funções---------------
void Send_Data(unsigned char c);
void Send_Int(int n);
void Send_String(char str[]);
void Init_UART(unsigned int baud_rate_choice);
//-------------------------------------------

volatile char direcao = 'P'; //Variável global

int main(void)
{
    volatile int i = 0; // Count

    WDTCTL = WDTPW + WDTHOLD; // Desliga o WDT

    //Definições para o timer A
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    //-------------------------

    //Inicializando os pinos dos motores1
    P1OUT &= ~P1MOTORA;
    P1OUT &= ~P1MOTORB;
    P1DIR |= P1MOTORA;
    P1DIR |= P1MOTORB;
    //----------------------

    //Habilita interrupções-----------------
    Init_UART(BAUD_9600);
    _BIS_SR(GIE);
    //--------------------------------------

    while(1)
    {
        // Trecho para imprimir a string na serial conforme o valor de direcao-----
        switch(direcao)
        {
        case 'P':
            Send_String("Direção Atual: Parado\n");
        break;
        case 'D':
             Send_String("Direção Atual: Direita\n");
        break;
        case'E':
             Send_String("Direção Atual: Esquerda\n");
        break;
        case 'F':
             Send_String("Direção Atual: Frente\n");
        break;
        default:
            Send_String("Direção Atual: Parado\n");
        //---------------------------------------------------------------------------
        __delay_cycles(10000);; //Aplica um delay para o envio na serial
        }
     }
    return 0;
}
//Função para a comunicação serial
void Send_Data(unsigned char c)
{
    while((IFG2&UCA0TXIFG)==0);
    UCA0TXBUF = c;
}
//---------------------------------


//Função para enviar a string----------
void Send_String(char str[])
{
    int i;
    for(i=0; str[i]!= '\0'; i++)
        Send_Data(str[i]);
}
//---------------------------------------

//Função para ultilizar a UART-------------------
void Init_UART(unsigned int baud_rate_choice)
{
    unsigned char BRs[NUM_BAUDS] = {104, 52, 26, 17, 8, 7, 3};
    unsigned char MCTLs[NUM_BAUDS] = {UCBRF_0+UCBRS_1,
                                        UCBRF_0+UCBRS_0,
                                        UCBRF_0+UCBRS_0,
                                        UCBRF_0+UCBRS_7,
                                        UCBRF_0+UCBRS_6,
                                        UCBRF_0+UCBRS_7,
                                        UCBRF_0+UCBRS_7};
    if(baud_rate_choice<NUM_BAUDS)
    {
        // Habilita os pinos para transmissao serial UART
        P1SEL2 = P1SEL = RX+TX;
        // Configura a transmissao serial UART com 8 bits de dados,
        // sem paridade, comecando pelo bit menos significativo,
        // e com um bit de STOP
        UCA0CTL0 = 0;
        // Escolhe o SMCLK como clock para a UART
        UCA0CTL1 = UCSSEL_2;
        // Define a baud rate
        UCA0BR0 = BRs[baud_rate_choice];
        UCA0BR1 = 0;
        UCA0MCTL = MCTLs[baud_rate_choice];
        // Habilita a interrupcao por chegada de dados via UART
        IE2 |= UCA0RXIE;
    }
}
//-----------------------------------------------------------------


//Função para interrupção-----------------------------------------
interrupt(USCIAB0RX_VECTOR) Receive_Data(void)
{
    unsigned char blink = UCA0RXBUF - '0';
    //Lógica para ligar e desligar os motores
    if(blink<10)
    {
        if(blink == 0)
        {
            P1OUT &= ~P1MOTORA;
            P1OUT &= ~P1MOTORB;
            direcao = 'P';

        }
        else if(blink == 1)
        {
            P1OUT |=  P1MOTORA;
            P1OUT &= ~P1MOTORB;
            direcao = 'E';

        }
        else if(blink == 2)
        {
            P1OUT |=  P1MOTORB;
            P1OUT &= ~P1MOTORA;
            direcao = 'D';


        }
        else if(blink == 4)
        {
            P1OUT |=  P1MOTORB;
            P1OUT |=  P1MOTORA;
            direcao = 'F';

        }
        else
        {
            P1OUT |=  P1MOTORB;
            P1OUT |=  P1MOTORA;
            direcao = 'F';

        }

    }
}
