1. Dada uma variável `a` do tipo `char` (um byte), escreva os trechos de código em C para:
  (a) Somente setar o bit menos significativo de `a`.
  ```c
  a |= 1 << 0;
  ```
  (b) Somente setar dois bits de `a`: o menos significativo e o segundo menos significativo.
  ```c
  a |= 03; //Mask: 0x03
  ```
  (c) Somente zerar o terceiro bit menos significativo de `a`.
  ```c
  a &= 0 << 2;
  ```
  (d) Somente zerar o terceiro e o quarto bits menos significativo de `a`.
  ```c
  a &= 12; //Mask: 0x04
  ```
  (e) Somente inverter o bit mais significativo de `a`.
  ```c
  a ^= 1 << 7;
  ```
  (f) Inverter o nibble mais significativo de `a`, e setar o nibble menos significativo de `a`.
  ```c
  a ^= 240; //Mask: 1111 0000
  a |= 14; //Mask: 0000 1111
  ```

2. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar os dois LEDs ininterruptamente.
  ```c
  #include <msp430g2553.h>
  #define LED1 BIT0
  #define LED2 BIT6

  void main (void) {
    int contadorEspera = 0;
    
    WDTCTL = WDTPW | WDTHOLD; //Reseta o Watch dog timer de acordo com o reg. de Hold
    P1DIR = LED1 + LED2;
    P1OUT = LED1 + LED2;
    while (true) {
    	P1OUT ^= LED1 + LED2;
      for (contadorEspera = 0; contadorEspera <= 10000; contadorEspera++);
    }
  }
  ```

3. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar duas vezes os dois LEDs sempre que o usuário pressionar o botão.
  ```c
  /*MSP430FR2433*/
  #include <msp430.h>

  #define LED1 BIT0
  #define LED2 BIT1
  #define BTN BIT7
  #define COUNTER 32768

  void main(void)
  {
      long int contadorEspera;
      int i;
  	WDTCTL = WDTPW | WDTHOLD;
  	PM5CTL0 &= ~LOCKLPM5; //Desabilitando modo de alta impedância
  	P1DIR = LED1 + LED2;
  	P1OUT = ~(LED1 + LED2);
  	P2OUT = 0xFF;
  	P2DIR = 0xF7;
  	while(true){
        P1OUT ^= (LED1 + LED2);
        while((P2IN & BTN)){}
        for(i=0;i < 2; i++){
          P1OUT = LED1 + LED2;
          for(contadorEspera = 0; contadorEspera < COUNTER; contadorEspera++);
          P1OUT ^= (LED1 + LED2);
          for(contadorEspera = 0; contadorEspera < COUNTER; contadorEspera++);
        }
        while(!(P2IN & BTN)){}
      }
  }
  ```

4. Considerando a placa Launchpad do MSP430, faça uma função em C que pisca os dois LEDs uma vez.
  ```c
  #define COUNTER 32768

  void blink () {
    int auxCount;
    P1OUT = LED1 + LED2; 
    for(auxCount = 0; auxCount < COUNTER; auxCount++); 
    P1OUT ^= (LED1 + LED2); 
    for(auxCount = 0; auxCount < COUNTER; auxCount++); 
  }
  ```
5. Reescreva o código da questão 2 usando a função da questão 4.
  ```c
    #include <msp430g2553.h>
    #define LED1 BIT0
    #define LED2 BIT6

    void main (void) {
      int contadorEspera = 0;

      WDTCTL = WDTPW | WDTHOLD; //Reseta o Watch dog timer de acordo com o reg. de Hold
      P1DIR = LED1 + LED2;
      P1OUT = LED1 + LED2;
      while (true) {
      	blink();
      }
    }
  ```
6. Reescreva o código da questão 3 usando a função da questão 4.
  ```c
    /*MSP430FR2433*/
    #include <msp430.h>

    #define LED1 BIT0
    #define LED2 BIT1
    #define BTN BIT7
    #define COUNTER 32768

    void main(void)
    {
        long int contadorEspera;
        int i;
      WDTCTL = WDTPW | WDTHOLD;
      PM5CTL0 &= ~LOCKLPM5; //Desabilitando modo de alta impedância
      P1DIR = LED1 + LED2;
      P1OUT = ~(LED1 + LED2);
      P2OUT = 0xFF;
      P2DIR = 0xF7;
      while(true){
          P1OUT ^= (LED1 + LED2);
          while((P2IN & BTN)){}
          for(i=0;i < 2; i++){
            blink();
          }
          while(!(P2IN & BTN)){}
        }
    }
  ```