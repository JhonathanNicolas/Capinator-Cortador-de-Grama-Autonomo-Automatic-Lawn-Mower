// Utiliza a Launchpad para enviar a todo momento
// uma string para o computador via UART indicando o estado
// do SENSOR-IR em P1.4. Envia a string "DETECTADO" se o sensor
// detectar o objeto e "NAO DETECTADO" se o sensor não estiver
// detectando o objeto.
//
// Utilizamos o monitor serial Tera Term para ver a string enviada.
//
// EH NECESSARIO MUDAR DUAS CONEXOES NA LAUNCHPAD
// PARA O CODIGO FUNCIONAR.
//
// Procure 5 jumpers na placa, como indicado abaixo:
// RXD | | | | |
// TXD | | | | |
//     T R R T V
//     X X S E C
//     D D T S C
//           T
//
// Mude a conexoes de 2 desses jumpers, como indicado abaixo:
// RXD --- | | |
// TXD --- | | |
    //     T R R T V
//     X X S E C
//     D D T S C
//           T

#include <msp430g2553.h>
#include <legacymsp430.h>

// Definição de entrada do SENSOR e
// demais definições para a comunicação UART
#define SENSOR BIT4
#define RX BIT1
#define TX BIT2

#define BAUD_9600   0
#define BAUD_19200  1
#define BAUD_38400  2
#define BAUD_56000  3
#define BAUD_115200 4
#define BAUD_128000 5
#define BAUD_256000 6
#define NUM_BAUDS   7

void Send_Data(unsigned char c);
void Send_String(char str[]);
void Init_UART(unsigned int baud_rate_choice);

int main(void)
{
    volatile int i = 0;
    WDTCTL = WDTPW + WDTHOLD; // Para WatchDogTimer

    // Escolha da frequência para 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1OUT = SENSOR;     //Define resistor do BIT5 como PullUp
    P1REN |= SENSOR;    //Define que usará resistor no BIT4
    P1DIR &= ~SENSOR;   //Define SENSOR como entrada


    Init_UART(BAUD_9600);
    _BIS_SR(GIE);
    //Detecção de obstáculo e resposta pelo sensor
    while(1)
    {

        if ((P1IN & SENSOR)==0)
            //Se SENSOR detectar obstáculo (SENSOR = 0)
            //envia string "DETECTADO"
            Send_String("\nDETECTADO\n");
        else
            //Se não detectar (SENSOR = 1) envia string "NAO DETECTADO"
            Send_String("\nNAO DETECTADO\n");

    }
    return 0;
}

//Função de envio de dados (utilizada em Send_String)
void Send_Data(unsigned char c)
{
    while((IFG2&UCA0TXIFG)==0);
    UCA0TXBUF = c;
}

// Função para enviar string
void Send_String(char str[])
{
    int i;
    for(i=0; str[i]!= '\0'; i++)
        Send_Data(str[i]);
}

//COMUNICAÇÃO UART
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
