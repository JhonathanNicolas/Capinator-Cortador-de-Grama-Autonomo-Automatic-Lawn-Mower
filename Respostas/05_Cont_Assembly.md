Para as questões 2 a 5, considere que as variáveis f, g, h, i e j são do tipo inteiro (16 bits na arquitetura do MSP430), e que o vetor A[] é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores: f: R4 g: R5 h: R6 i: R7 j: R8 A: R9 Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

Escreva os trechos de código assembly do MSP430 para:
(a) Somente setar o bit menos significativo de R5. BIS #1h,R5

(b) Somente setar dois bits de R6: o menos significativo e o segundo menos significativo. BIS #8001h,R6

(c) Somente zerar o terceiro bit menos significativo de R7. BIC #4h,R7 ; A funcao BIC inverte o operando src

(d) Somente zerar o terceiro e o quarto bits menos significativo de R8. BIC #Ch,R8

(e) Somente inverter o bit mais significativo de R9. XOR #8000h,R9

(f) Inverter o nibble mais significativo de R10, e setar o nibble menos significativo de R10. XOR #F000h,R10 BIS #Fh,R10

"Traduza" o seguinte trecho de código em C para o assembly do MSP430:
if(i>j) f = g+h+10;
else f = g-h-10;
MOV R5,R4 ;  f = g
CMP R7,R8 ; j < i ? jl TRUE : ;
jl TRUE
SUB #10,R4 ; f -= 10;
SUB R6,R4 ; f -= h;
JMP EXIT
TRUE:
ADD #10,R4 ; f += 10;
ADD R6,R4 ; f += h
EXIT:
"Traduza" o seguinte trecho de código em C para o assembly do MSP430:
while(save[i]!=k) i++;
WHILE:
mov R7,R12
rla R12
add R10,R12
cmp 0(R12),R9
jeq EXIT
inc R7
jump WHILE
EXIT:
"Traduza" o seguinte trecho de código em C para o assembly do MSP430:
for(i=0; i<100; i++) A[i] = i*2;
clr R7 ; i = 0
mov #100,R11 ; R11 = 100
FOR:
rla R7
mov R7,0(R9)
inc R7
add R7,R9
cmp R11,R7
jl FOR
"Traduza" o seguinte trecho de código em C para o assembly do MSP430:
for(i=99; i>=0; i--) A[i] = i*2;
mov #99,R7
mov #0,R11
FOR:
rla R7
mov R7,0(R9)
inc R7
add R7,R9
cmp R11,R7
jge FOR
