Quais as diferen�as entre os barramentos de dados e de endere�os?
	R = Barramento de dados tem a capacidade de informa��o de via dupla para ler ou escrever dados na mem�ria, j� o barramento de endere�o � de informa��o de via �nica, onde a CPU indica em qual endere�o da mem�ria onde vai ser lido ou escrito o dado.

Quais s�o as diferen�as entre as mem�rias RAM e ROM?
	R = Mem�ria RAM(Random Access Memory) � a Mem�ria de Acesso Rand�mico e pode ser acessada a qualquer momento pelo sistema operacional para carregar e sobrescrever informa��es com muita rapidez.  A ROM(Read-Only Memory) � a Mem�ria Somente de Leitura, e est� principalmente localizada no chip respons�vel pela inicia��o do sistema � � l� que as informa��es b�sicas do computador ficam armazenadas, portanto n�o s�o afetadas quando o dispositivo � desligado.
	      Os dados armazenados pela mem�ria ROM s�o pequenos, por isso sua capacidade de armazenamento n�o � muito alta. J� mem�rias RAM, que s�o muito mais exigidas em tarefas di�rias, podem possuir capacidade de armazenamento. 

Considere o c�digo abaixo:

#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um n�mero inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}
Para este c�digo, responda: 
(a) A vari�vel i � armazenada na mem�ria RAM ou ROM? Por qu�? 
	R = Na mem�ria RAM, porque "i" � uma vari�vel tempor�ria utilizada apenas para o c�lculo, logo ap�s a execu��o do programa ela � apagada. 
(b) O programa compilado a partir deste c�digo � armazenado na mem�ria RAM ou ROM? Por qu�?
	R = Nenhuma das duas, o arquivo ".exe" gerado pelo compilador � armazenado no HD.

Quais s�o as diferen�as, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?
	R = 
Considere a vari�vel inteira i, armazenando o valor 0x8051ABCD. Se i � armazenada na mem�ria a partir do endere�o 0x0200, como ficam este byte e os seguintes, considerando que a mem�ria �: (a) Little-endian; (b) Big-endian.
	R = 
Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas vari�veis de 32 bits?
	R = O MSP430 utiliza dois registradores de 16 bits para armazenar cada vari�vel, faz uso da vari�vel tempor�ria carry para contatenar a soma, e ent�o armazena o resultado em outros dois registradores.





