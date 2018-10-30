(a) Escreva uma função em C que calcule a raiz quadrada x de uma variável S do tipo float, utilizando o seguinte algoritmo: após n+1 iterações, a raiz quadrada de S é dada por
x(n+1) = (x(n) + S/x(n))/2
O protótipo da função é:

unsigned int Raiz_Quadrada(unsigned int S);
unsigned int Raiz_Quadrada(unsigned int S)
{
	int counter, x = 1; // x é o valor inicial para o problema
    if (S < 2)
    	return s;
    else
    {
        for(counter = 0; counter < 10; counter ++)
            x = (x + S/x)/2;
        return x;
    }
}
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável S é fornecida pelo registrador R15, e a raiz quadrada de S (ou seja, a variável x) é fornecida pelo registrador R15 também.

Raiz_Quadrada: cmp #2,R15 ; compara se o valor de x**2 é 1 ou 0, evitando calculos
jge Raiz_Nao_Trivial
ret
Raiz_Nao_Trivial: push R5 ; guarda o valor de R5 na pilha
push R6 ; guarda R6 na pilha
mov R15, R5 ; R5 = s
inc R5 ; s+=1
rra R5 ; s = (s+1)/2
clr R6 ; limpa R6
Raiz_Loop: cmp #10000,R6 ; verifica se n é menor do que 10**4
jeq Raiz_End
push R15
mov R5,R14
call #Div ; implementar a sub-rotina de divisao
add R15,R5
rra R5
pop R15
inc R6
jump Raiz_Loop
Raiz_End: mov R5,R15
pop R6
pop R5
ret
(a) Escreva uma função em C que calcule x elevado à N-ésima potência, seguindo o seguinte protótipo:
int Potencia(int x, int N);
int Multiplica(int a, int b)
{
    int res = 0;
    for (int i = 0; i < b; i++) // Laço de multiplicação
    {
        res += a;
    }
    return res;
}

int Potencia(int x, int N)
{
	int res = x;
    if(N == 1)
    	return x;
    else if(N == 0)
    	return 1;
    else
    {
	    for (int k = 0; k < N-1; k++)
		{
			res = Multiplica(res,x); 
		}
	}
	return res;
}
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. x e n são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida no registrador R15.

POT: NOP
cmp #0,R14
jne POTC
mov #1,R15
ret

cmp #1,R14
jne POTC
ret 

POTC: NOP
sub #1,R14
push R13
push R12
push R11
mov #0,R13 ;r13 é k
mov R15,R12 ;r12 é res=x
mov R15,R11 ;R11 é x
POTL: cmp R13,R14
jeq POTE
;res = Multiplica(res,x)
push R15
mov R12,R15
push R14
mov R11,R14
call #MULT
pop R14
mov R15,R12
pop R15
inc R13
jmp POTL
POTE: mov R12,R15
pop R11
pop R12
pop R13
ret

MULT: NOP
push R13
push R12
mov #0,R13
mov #0,R12
MFOR: NOP
cmp R12,R14
jeq MEXIT
add R15,R13
inc R12
jmp MFOR
MEXIT: mov R13,R15
pop R12
pop R13
ret
Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula a divisão de a por b, onde a, b e o valor de saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.
DIV: NOP
cmp #0,R14
jne DI2
mov #-1,R15
ret
DI2: cmp R14,R15
jge DIVL
mov #0,R15
ret
DIVL: NOP
push R13 ; R13 é i
push R12 ; R12 é res
mov #1,R13
DIVT: NOP
push R15
mov R13,R15
call #MULT
mov R15,R12
pop R15
cmp R15,R12
jge DIVE
inc R13
jmp DIVT
DIVE: NOP
mov R13,R15
dec R15
pop R12
pop R13
ret
Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o resto da divisão de a por b, onde a, b e o valor de saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.
MODF: NOP
push R13
push R12
mov R15,R13
mov R14,R12
call #DIV
mov R12,R14
call #MULT
sub R15,R13
mov R13,R15
pop R12
pop R13
ret
(a) Escreva uma função em C que indica a primalidade de uma variável inteira sem sinal, retornando o valor 1 se o número for primo, e 0, caso contrário. Siga o seguinte protótipo:
int Primalidade(unsigned int x);
int Primalidade(unsigned int x)
{
	int i,k;

	if(x < 2)
		return 0;
	else if(x < 4)
		return 1;
	else if(x % 2 == 0)
		return 0;
	else if(x % 3 == 0)
		return 0;
	i = 5;
	while(Multiplica(i,i) <= x)
	{
		k = i+2;
		if(x % i == 0)
			return 0;
		if(x % k == 0)
			return 0;
		i += 6;
	}
	return 1;
}
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável de entrada é fornecida pelo registrador R15, e o valor de saída também.

PRIM: NOP
push R14 ; cópia de x
push R13 ; i
push R12 ; k
mov R15,R14
cmp #2,R15
jl NPRIM
cmp #4,R15
jl SPRIM

push R14
mov #2,R14
call #MODF
pop R14
cmp #0,R15
jeq NPRIM

push R14
mov #3,R14
call #MODF
pop R14
cmp #0,R15
jeq NPRIM

mov #5,R13
PRW: NOP
push R15
push R14
mov R13,R15
mov R13,R14
call #MULT
mov R15,R13
pop R14
pop R15
cmp R13,R15
jge PROPER
jmp SPRIM

PROPER: NOP
mov R13,R12
add #2,R12

push R14
push R15
mov R13,R14
call #MODF
cmp #0,R15
jeq NPRIM
pop R15
mov R12,R14
cmp #0,R15
jeq NPRIM        
pop R14

add #6,R13
jmp PRW

NPRIM: mov #0,R15
jmp PRIME

SPRIM: mov #1, R15
jmp PRIME

PRIME: NOP
pop R12
pop R13
pop R14
ret
Escreva uma função em C que calcula o duplo fatorial de n, representado por n!!. Se n for ímpar, n!! = 135*...n, e se n for par, n!! = 246...n. Por exemplo, 9!! = 13579 = 945 e 10!! = 2468*10 = 3840. Além disso, 0!! = 1!! = 1.
unsigned long long duploFatorial(unsigned long long n)
{
    if (n == 0 || n==1)
      return 1;
    return n*doublefactorial(n-2);
}
(a) Escreva uma função em C que calcula a função exponencial utilizando a série de Taylor da mesma. Considere o cálculo até o termo n = 20. O protótipo da função é double ExpTaylor(double x);
double ExpTaylor(double x)
{
	double exp = 1;

	for(int powerValue = 1; powerValue <= 21 ; powerValue++)
	{
	exp += pow(x,powerValue)/fatorial(powerValue);
	}
	return exp;
{
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430, mas considere que os valores de entrada e de saída são inteiros de 16 bits. A variável de entrada é fornecida pelo registrador R15, e o valor de saída também.

ExpTaylor: ; R15 = x
	push R5 ; guarda R5 na pilha
	push R6 ; guarda R6 na pilha
	clr R5 ; n = 0
	clr R6 ; sum = 0

Forloop:
	cmp #20, R5
	jge For_Loop_End ; se R5 >= #20, sai do loop
	mov.w R5, R14 ; R14 = R5 = n
	call Potencia ; R15 = x**n
	push R15 ; guarda x**n na pilha

	mov.w R5, R15 ; R15 = n
	call Fatorial ; fatorial de R15 = fatorial(n)
	mov.w R15, R14 ; R14 = fatorial(n)
	pop R15 ; recupera x**n da pilha em R15

	call Div ; R15 = (x**n)/fatorial(n)

	add.w R15, R6 ; sum+= (x**n)/fatorial(n)
	jmp Forloop

For_Loop_End:
	pop R6 ; recupera R6 da pilha
	pop R5 ; recuepra R6 da pilha
	ret
Escreva uma sub-rotina na linguagem Assembly do MSP430 que indica se um vetor esta ordenado de forma decrescente. Por exemplo: [5 4 3 2 1] e [90 23 20 10] estão ordenados de forma decrescente. [1 2 3 4 5] e [1 2 3 2] não estão. O primeiro endereço do vetor é fornecido pelo registrador R15, e o tamanho do vetor é fornecido pelo registrador R14. A saída deverá ser fornecida no registrador R15, valendo 1 quando o vetor estiver ordenado de forma decrescente, e valendo 0 em caso contrário.
OrdemDec:
	push.w R5
	push.w R6
	mov.w R15, R6 ; R6 = &a[0]
	mov.w R14, R5; R5 = len(a)
	mov.w R6 ,R14
	incd.w R14

CompLoop:
	cmp R15, R14
	jl Naodec ; se a(x+1)<a(x), não é decrescente
	incd.w R15
	incd.w R14
	dec.w R5
	cmp R5, #0
	jne CompLoop ; se R5 = 0, é decrescente
	pop.w R6
	pop.w R5
	mov.w #1, R15
	ret

NaoDec:
	pop.w R6
	pop.w R5
	clr R15
	ret
Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o produto escalar de dois vetores, a e b. O primeiro endereço do vetor a deverá ser passado através do registrador R15, o primeiro endereço do vetor b deverá ser passado através do registrador R14, e o tamanho do vetor deverá ser passado pelo registrador R13. A saída deverá ser fornecida no registrador R15.
Prod_Int:
	push R5 ; guarda R5 na pilha
	mov.w R14, R5 ; R5 = &b(0)
	push R6 ; guarda R6 na pilha
	mov.w R15, R6 ; R6 = &a(0)
	clr R12 ; R12 = 0

PI_Loop:
	mov.w 0(R6), R15
	mov.w 0(R5), R14
	call Multiplica ; r15 = R15 * R14
	add.w R15, R12
	incd.w R6
	incd.w R5
	dec.w R13

Primo_Loop_End:
	mov.w R12, R15
	pop R6
	pop R5
	ret
(a) Escreva uma função em C que indica se um vetor é palíndromo. Por exemplo: [1 2 3 2 1] e [0 10 20 20 10 0] são palíndromos. [5 4 3 2 1] e [1 2 3 2] não são. Se o vetor for palíndromo, retorne o valor 1. Caso contrário, retorne o valor 0. O protótipo da função é:
int Palindromo(int vetor[ ], int tamanho);
int Palindromo(int vetor[ ], int tamanho){
	int count = 0;
	
	while(vetor[count] == vetor[tamanho-1 -count] && count < tamanho)
		count++;
return count == tamanho ? 1 : 0; // 1 para palindromo e 0 para nao palindromo
}
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. O endereço do vetor de entrada é dado pelo registrador R15, o tamanho do vetor é dado pelo registrador R14, e o resultado é dado pelo registrador R15.

Palindromo:
	push R6 ; guarda R6 na pilha
	mov.w R14, R6 ; R6 = tamanho
	clr R13 ; R13 = 0
	dec R14 ; tamanho--
	rla R14 ; tamanho = 2 * tamanho
	add R15, R14 ; R14 = &a[tamanho-1]

Palin_Loop:
	cmp R6, R13
	jge Palin_Loop_End ; se count >= tamanho, sai do loop
	cmp 0(R15), 0(R14)
	jne Palin_Loop_End ; se vetor[count] == vetor[tamanho-1 -count, continua no loop

	incd.w R15
	decd.d R14
	inc.w R13 ; count++

	jmp Palin_Loop

Palin_Loop_End:
	cmp R13, R6 ; se count = tamanho, ret 1
	jne Palin_False
	pop R6 ; recupera R6 da pilha
	mov.w #1, R15
	ret
	
Palin_False: 
	pop R6 ; recupera R6 da pilha
	clr R15 ; se count != tamanho, ret 0
	ret
