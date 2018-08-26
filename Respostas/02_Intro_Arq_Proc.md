Quais as diferenças entre os barramentos de dados e de endereços?
	R = Barramento de dados tem a capacidade de informação de via dupla para ler ou escrever dados na memória, já o barramento de endereço é de informação de via única, onde a CPU indica em qual endereço da memória onde vai ser lido ou escrito o dado.

Quais são as diferenças entre as memórias RAM e ROM?
	R = Memória RAM(Random Access Memory) é a Memória de Acesso Randômico e pode ser acessada a qualquer momento pelo sistema operacional para carregar e sobrescrever informações com muita rapidez.  A ROM(Read-Only Memory) é a Memória Somente de Leitura, e está principalmente localizada no chip responsável pela iniciação do sistema – é lá que as informações básicas do computador ficam armazenadas, portanto não são afetadas quando o dispositivo é desligado.
	      Os dados armazenados pela memória ROM são pequenos, por isso sua capacidade de armazenamento não é muito alta. Já memórias RAM, que são muito mais exigidas em tarefas diárias, podem possuir capacidade de armazenamento. 

Considere o código abaixo:

#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}
Para este código, responda: 
(a) A variável i é armazenada na memória RAM ou ROM? Por quê? 
	R = Na memória RAM, porque "i" é uma variável temporária utilizada apenas para o cálculo, logo após a execução do programa ela é apagada. 
(b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?
	R = Nenhuma das duas, o arquivo ".exe" gerado pelo compilador é armazenado no HD.

Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?
	R = 
Considere a variável inteira i, armazenando o valor 0x8051ABCD. Se i é armazenada na memória a partir do endereço 0x0200, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian; (b) Big-endian.
	R = 
Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?
	R = O MSP430 utiliza dois registradores de 16 bits para armazenar cada variável, faz uso da variável temporária carry para contatenar a soma, e então armazena o resultado em outros dois registradores.





