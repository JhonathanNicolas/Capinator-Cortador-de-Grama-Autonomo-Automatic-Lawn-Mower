#include <msp430g2553.h>


#define SEL1 BIT4
#define SEL0 BIT3
#define triggerC BIT1
#define triggerD BIT2
#define triggerE BIT4
#define triggerB BIT0 ///P2
#define echo BIT5
#define LED0 BIT0
#define LED1 BIT6
#define LED2 BIT5
#define LED3 BIT3
#define CENTRO 0
#define DIREITA 1
#define ESQUERDA 2
#define EMBAIXO 3


int miliseconds;

long sensor;


typedef struct sensoresUltrassonicos
  {
    int Medicao[4];// Medições para entrada do filtro média móvel
    int valorFinal; // Resultado do filtro média móvel

  }sensoresUltrassonicos;



void filtro_Media_movel(sensoresUltrassonicos *sensor);





int main(void)
{
    sensoresUltrassonicos distancia[4] = {{.Medicao = {0,0,0,0}, .valorFinal = 0},{.Medicao = {0,0,0,0}, .valorFinal = 0},{.Medicao = {0,0,0,0}, .valorFinal = 0},{.Medicao = {0,0,0,0}, .valorFinal = 0}};
    volatile int i,j = 0;
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    P2DIR |= SEL1;                            // P1.0 as output for LED
    P2OUT &= ~SEL1;
    P1DIR |= SEL0;
    P1OUT &= ~SEL0;
    P1DIR |= LED0;
    P1DIR |= LED1;
    P1OUT &= ~LED0;// P1.0 as output for LED
    P1OUT &= ~LED1;
    P2DIR |= LED2;
    P2OUT |= LED2;
    P2DIR |= LED3;
    P2OUT |= LED3;


    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 1000;                  // 1ms at 1mhz
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    _BIS_SR(GIE);
    volatile int nroSensor = 0;
    volatile int nroMedicao = 0;

     //inicializar_sensores

    while(1)
    {


        switch(nroSensor)
        {
            case CENTRO:

                P2OUT &= ~SEL1;
                P1OUT &= ~SEL0;
                while(nroMedicao <= 3)
                {
                 __delay_cycles(10000);             // for 10us
                  P1IE &= ~0x01;       // disable interupt
                  P1DIR |= triggerC;          // trigger pin as output
                  P1OUT |= triggerC;          // generate pulse
                  __delay_cycles(10);             // for 10us
                  P1OUT &= ~triggerC;                 // stop pulse
                  P1DIR &= ~echo;         // make pin P1.2 input (ECHO)
                  P1IFG = 0x00;                   // clear flag just in case anything happened before
                  P1IE |= echo;           // enable interupt on ECHO pin
                  P1IES &= ~echo;         // rising edge on ECHO pin
                distancia[CENTRO].Medicao[nroMedicao] = sensor/58;
                // Send_String("Distancia Centro:");
               // Send_Int(distancia[CENTRO].valorFinal);
                //Send_String("\n");

                nroMedicao++;

                }
                filtro_Media_movel(&distancia[CENTRO]);
                nroMedicao =0;

               if(distancia[CENTRO].valorFinal  < 30)
                   P1OUT |= LED0;
               else
                    P1OUT &= ~LED0;

            break;
            case DIREITA:
                P2OUT &= ~SEL1;
                P1OUT |= SEL0;

                while(nroMedicao <= 3)
                {
                    __delay_cycles(10000);             // for 10us

                P1IE &= ~0x01;       // disable interupt
                  P1DIR |= triggerD;          // trigger pin as output
                  P1OUT |= triggerD;          // generate pulse
                  __delay_cycles(10);             // for 10us
                  P1OUT &= ~triggerD;                 // stop pulse
                  P1DIR &= ~echo;         // make pin P1.2 input (ECHO)
                  P1IFG = 0x00;                   // clear flag just in case anything happened before
                  P1IE |= echo;           // enable interupt on ECHO pin
                  P1IES &= ~echo;         // rising edge on ECHO pin




                distancia[DIREITA].Medicao[nroMedicao] = sensor/58;
                //Send_String("Distancia Direita:");
                //Send_Int(distancia[DIREITA].valorFinal);
                //Send_String("\n");

                nroMedicao++;

                }
                nroMedicao = 0;
                filtro_Media_movel(&distancia[DIREITA]);
                if(distancia[DIREITA].valorFinal  < 30)
                    P1OUT |= LED1;
                else
                    P1OUT &= ~LED1;
            break;
            case ESQUERDA:


                P2OUT |= SEL1;
                P1OUT &= ~SEL0;


                while(nroMedicao <= 3)
                {
                    __delay_cycles(10000);             // for 10us

                  P1IE &= ~0x01;       // disable interupt
                  P1DIR |= triggerE;          // trigger pin as output
                  P1OUT |= triggerE;          // generate pulse
                  __delay_cycles(10);             // for 10us
                  P1OUT &= ~triggerE;                 // stop pulse
                  P1DIR &= ~echo;         // make pin P1.2 input (ECHO)
                  P1IFG = 0x00;                   // clear flag just in case anything happened before
                  P1IE |= echo;           // enable interupt on ECHO pin
                  P1IES &= ~echo;         // rising edge on ECHO pin



                distancia[ESQUERDA].Medicao[nroMedicao] = sensor/58;
                // Send_String("Distancia Esquerda:");
                //Send_Int(distancia[ESQUERDA].valorFinal);
                // Send_String("\n");

                nroMedicao++;


                }
                nroMedicao = 0;
                filtro_Media_movel(&distancia[ESQUERDA]);


                if(distancia[ESQUERDA].valorFinal  < 30)
                    P2OUT |= LED2;
                else
                    P2OUT &= ~LED2;

            break;
            case EMBAIXO:


                P2OUT |= SEL1;
                P1OUT |= SEL0;


                while(nroMedicao <= 3)
                {
                    __delay_cycles(10000);             // for 10us

                  P1IE &= ~0x01;       // disable interupt
                  P2DIR |= triggerB;          // trigger pin as output
                  P2OUT |= triggerB;          // generate pulse
                  __delay_cycles(10);             // for 10us
                  P2OUT &= ~triggerB;                 // stop pulse
                  P1DIR &= ~echo;         // make pin P1.2 input (ECHO)
                  P1IFG = 0x00;                   // clear flag just in case anything happened before
                  P1IE |= echo;           // enable interupt on ECHO pin
                  P1IES &= ~echo;         // rising edge on ECHO pin



                distancia[EMBAIXO].Medicao[nroMedicao] = sensor/58;
                //       Send_String("Distancia Embaixo:");
                //      Send_Int(distancia[EMBAIXO].valorFinal);
                //      Send_String("\n");

                nroMedicao++;

                }
                nroMedicao = 0;
                filtro_Media_movel(&distancia[EMBAIXO]);

            break;





}
        nroSensor = (nroSensor +1) % 4  ;

}}
void filtro_Media_movel(sensoresUltrassonicos *sensor)
{
    sensor->valorFinal= (sensor->Medicao[0]+ sensor->Medicao[1]+ sensor->Medicao[2] + sensor->Medicao[3])/4;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG&echo)  //is there interrupt pending?
        {
          if(!(P1IES&echo)) // is this the rising edge?
          {
            TACTL|=TACLR;   // clears timer A
            miliseconds = 0;
            P1IES |= echo;  //falling edge
          }
          else
          {
            sensor = (long)miliseconds*1000 + (long)TAR;    //calculating ECHO lenght

          }
    P1IFG &= ~echo;             //clear flag
    }
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  miliseconds++;
}
