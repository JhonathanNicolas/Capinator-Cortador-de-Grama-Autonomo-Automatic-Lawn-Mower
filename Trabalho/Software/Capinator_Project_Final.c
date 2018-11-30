#include <msp430g2553.h>



//Motores
#define MOTORA1 BIT0 // P1
#define MOTORA2 BIT7 // P1
#define BTN BIT0//P2
#define TECY BIT1 //P2
#define TECP BIT7 //P2
#define BATEU BIT6//P2
#define MOTORB1 BIT6 // P1
#define MOTORB2 BIT5 // P2
#define LED1 BIT0
#define LED2 BIT6
#define LEDS LED2

//

#define MOTORCORTE BIT2 //P2 // LIGADO EM NIVEL LÓGICO BAIXO
#define LIGAMOTORA1 (P1OUT |= MOTORA1)
#define DESLIGAMOTORA1 (P1OUT &= ~MOTORA1)
#define LIGAMOTORA2 (P1OUT |= MOTORA2)
#define DESLIGAMOTORA2 (P1OUT &= ~MOTORA2)
#define LIGAMOTORB1 (P1OUT |= MOTORB1)
#define DESLIGAMOTORB1 (P1OUT &= ~MOTORB1)
#define LIGAMOTORB2 (P2OUT |= MOTORB2)
#define DESLIGAMOTORB2 (P2OUT &= ~MOTORB2)
#define LIGAMOTORCORTE (P2OUT &= ~MOTORCORTE)
#define DESLIGAMOTORCORTE (P2OUT |= MOTORCORTE)
#define TESTSECURE (P1IN&SECURESWITCH == 0)
//Seletora do multiplexador
#define SEL1 BIT4 //P2
#define SEL0 BIT3 //P2

//Sensores ultrasssonico
#define triggerC BIT1
#define triggerD BIT2
#define triggerE BIT4
#define triggerB BIT0 ///P2
#define echo BIT5

//LEDs para teste
#define LED0 BIT0
#define LED1 BIT6
#define LED2 BIT5

//Direções/
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


//Procedimentos
void filtro_Media_movel(sensoresUltrassonicos *sensor);
void viraParaDireita();
void viraParaEsquerda();
void ParaTudo();
void Reiniciar();
void ViraParaTras();
void vira180graus();
void SegueCortandoGrama();
void RecorecoCortandoGrama();
void InicizalizaPortas();
//Funções
int MedeFrente();
int MedeDireita();
int MedeEsquerda();
int MedeEmbaixo();




int main(void)
{
    InicizalizaPortas();
    DESLIGAMOTORCORTE;
    __delay_cycles(10000000);             // for 10us
    ViraParaTras();
    __delay_cycles(1000000);
    LIGAMOTORA1;
    DESLIGAMOTORA2;
    LIGAMOTORB1;
    DESLIGAMOTORB2;
    LIGAMOTORCORTE;
    int Frente = 0 , Direita = 0 ,Esquerda = 0 , Embaixo = 0;
    int Reco = 1;
    while(1)
    {



        while((P2IN&BTN)==0)
            ParaTudo();

        if((P2IN&BATEU)==0)
            vira180graus();
        if((P2IN&TECY)==0)
            Reco = -1;
        if((P2IN&TECP)==0)
            Reco = 0;




        Frente = MedeFrente();
        if(Frente < 30)
        {
            Esquerda =  MedeEsquerda();
            Direita = MedeDireita();
            if((Direita >Esquerda) && (Direita > 30))
                viraParaDireita();
            else if((Direita < Esquerda) && (Esquerda > 30))
                viraParaEsquerda();
            else
            {
                ViraParaTras();
                Direita = MedeDireita();
                Esquerda =  MedeEsquerda();
                if(Direita > 30)
                    viraParaEsquerda();
                else if(Esquerda > 30)
                    viraParaEsquerda();
                else
                    ParaTudo();

            }
        }

        else
        {

            if(Reco == -1)
                RecorecoCortandoGrama();
            else
                SegueCortandoGrama();


        }


    }

}


void vira180graus()
{

    do
    {
    ViraParaTras();
    if((MedeDireita() <30))
        viraParaDireita();
    else if((MedeDireita() <30))
        viraParaEsquerda();
    }while( (MedeFrente() < 30) );

}




void viraParaDireita()
{
    DESLIGAMOTORB1;
    DESLIGAMOTORB2;
    LIGAMOTORA1;
    DESLIGAMOTORA2;
    while((MedeFrente() < 30) || (MedeDireita() <30))
    __delay_cycles(3000);
    SegueCortandoGrama();

}

void viraParaEsquerda()
{

    DESLIGAMOTORA1;
    DESLIGAMOTORA2;
    LIGAMOTORB1;
    DESLIGAMOTORB2;
    while((MedeFrente() < 30) || (MedeEsquerda() <30))
    __delay_cycles(3000);

    SegueCortandoGrama();



}
void ParaTudo()
{
    DESLIGAMOTORA1;
    DESLIGAMOTORA2;
    DESLIGAMOTORB1;
    DESLIGAMOTORB2;
    DESLIGAMOTORCORTE;


}
void Reiniciar()
{
    LIGAMOTORA1;
    DESLIGAMOTORA2;
    LIGAMOTORB1;
    DESLIGAMOTORB2;
    LIGAMOTORCORTE;

}
void ViraParaTras()
{
    DESLIGAMOTORA1;
    DESLIGAMOTORB1;
    LIGAMOTORB2;
    LIGAMOTORA2;
    __delay_cycles(3000000);
    ParaTudo();

}

void SegueCortandoGrama()
{
    LIGAMOTORA1;
    DESLIGAMOTORA2;
    LIGAMOTORB1;
    DESLIGAMOTORB2;
    LIGAMOTORCORTE;

}
void RecorecoCortandoGrama()
{


    int tempo = 1;
    LIGAMOTORA1;
    DESLIGAMOTORA2;
    LIGAMOTORB1;
    DESLIGAMOTORB2;
    LIGAMOTORCORTE;
    __delay_cycles(300000);
    DESLIGAMOTORA1;
    DESLIGAMOTORB1;
    __delay_cycles(300000);
    LIGAMOTORA1;
    LIGAMOTORB1;



}
int MedeFrente()
{
    int nroMedicao = 0;
    sensoresUltrassonicos distancia = {.Medicao = {0,0,0,0}, .valorFinal = 0};

    P2OUT &= ~SEL1;
    P1OUT &= ~SEL0;
    __delay_cycles(100);
    while(nroMedicao <= 3)
    {
     __delay_cycles(10000);             // for 10us
      P1IE &= ~0x01;            // disable interupt
      P1DIR |= triggerC;          // trigger pin as output
      P1OUT |= triggerC;          // generate pulse
      __delay_cycles(10);             // for 10us
      P1OUT &= ~triggerC;                 // stop pulse
      P1DIR &= ~echo;         // make pin P1.2 input (ECHO)
      P1IFG = 0x00;                   // clear flag just in case anything happened before
      P1IE |= echo;           // enable interupt on ECHO pin
      P1IES &= ~echo;         // rising edge on ECHO pin
    distancia.Medicao[nroMedicao] = sensor/58;
    // Send_String("Distancia Centro:")
   // Send_Int(distancia[CENTRO].valorFinal);
    //Send_String("\n");

    nroMedicao++;

}
    filtro_Media_movel(&distancia);
    return distancia.valorFinal;
}

int MedeDireita()
{
    int nroMedicao = 0;
    sensoresUltrassonicos distancia = {.Medicao = {0,0,0,0}, .valorFinal = 0};

    P2OUT &= ~SEL1;
    P1OUT |= SEL0;
    __delay_cycles(100);
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

    distancia.Medicao[nroMedicao] = sensor/58;
    //Send_String("Distancia Direita:");
    //Send_Int(distancia[DIREITA].valorFinal);
    //Send_String("\n");

    nroMedicao++;

    }
    filtro_Media_movel(&distancia);
    return distancia.valorFinal;

}


int MedeEsquerda()
{

    int nroMedicao = 0;
    sensoresUltrassonicos distancia = {.Medicao = {0,0,0,0}, .valorFinal = 0};


    P2OUT |= SEL1;
    P1OUT &= ~SEL0;
    __delay_cycles(100);
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

    distancia.Medicao[nroMedicao] = sensor/58;
    //Send_String("Distancia Direita:");
    //Send_Int(distancia[DIREITA].valorFinal);
    //Send_String("\n");

    nroMedicao++;

    }
    filtro_Media_movel(&distancia);
    return distancia.valorFinal;


}
int MedeEmbaixo()
{
    int nroMedicao = 0;
    sensoresUltrassonicos distancia = {.Medicao = {0,0,0,0}, .valorFinal = 0};

    P2OUT |= SEL1;
    P2OUT |= SEL0;
    __delay_cycles(100);
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

    distancia.Medicao[nroMedicao] = sensor/58;
    //Send_String("Distancia Direita:");
    //Send_Int(distancia[DIREITA].valorFinal);
    //Send_String("\n");

    nroMedicao++;

    }
    filtro_Media_movel(&distancia);
    return distancia.valorFinal;

}




void filtro_Media_movel(sensoresUltrassonicos *sensor)
{
    sensor->valorFinal= (sensor->Medicao[0]*2+ sensor->Medicao[1]*3+ sensor->Medicao[2]*4 + sensor->Medicao[3]*5)/14;
}

void InicizalizaPortas()
{
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P2DIR |= SEL1;
    P2OUT &= ~SEL1;
    P2DIR |= LED2;
    P2OUT &= ~LED2;
    P1DIR |= SEL0;
    P1OUT &= ~SEL0;

// Motores
    P2SEL &= ~(BIT6 +BIT7+BIT0);
    P2SEL2 &= ~(BIT6 +BIT7+BIT0);

    P1DIR |= MOTORA1;
    P1OUT &= ~MOTORA1;
    P1DIR |= MOTORA2;
    P1OUT &= ~MOTORA2;
    P1DIR |= MOTORB1;
    P1OUT &= ~MOTORB1;
    P1DIR |= MOTORB2;
    P1OUT &= ~MOTORB2;
    P2DIR |= MOTORCORTE;
    P2OUT &= ~MOTORCORTE;
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;
    P2DIR &= ~BATEU;
    P2REN |= BATEU;
    P2OUT |= BATEU;
    P2DIR &= ~TECY;
    P2REN |= TECY;
    P2OUT |= TECY;
    P2DIR &= ~TECP;
    P2REN |= TECP;
    P2OUT |= TECP;

    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 1000;                  // 1ms at 1mhz
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    _BIS_SR(GIE);

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






