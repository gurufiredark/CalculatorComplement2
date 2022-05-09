//Author : Gabriel Rodrigues de Souza - RA : 118038
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16

int main(){
    int numDecimal1, numDecimal2, binario1[BITS], binario2[BITS];
    char op;

    printf("Digite o primeiro numero: \n");
    scanf("%d", &numDecimal1);
    fflush(stdin);
    printf("Digite a operacao: ( * ou / ) ou 's' para Sair do Programa\n");
    scanf("%c", &op);
    fflush(stdin);
    printf("Digite o segundo numero: \n");
    scanf("%d", &numDecimal2);

    if(numDecimal1 >= pow(2,BITS-1) || numDecimal2 >= pow(2,BITS-1)){
        printf("Um dos numeros eh maior que o permitido para a representacao de BITS permitido: %d\n", BITS);
    }
    else if(numDecimal1 <= (pow(2,BITS-1) * -1) || numDecimal2 <= (pow(2,BITS-1))*-1){
        printf("Um dos numeros eh maior que o permitido para a representacao de BITS permitido: %d\n", BITS);
    }
    else{

        inicializaVetorZerado(binario1);
        inicializaVetorZerado(binario2);
        converteParaBinario(numDecimal1, binario1);
        converteParaBinario(numDecimal2, binario2);

        switch(op)
        {
            case '*':
                multiplicacaoC2(binario1, binario2);
                break;
            case '/':
                
                break;
            case 's':
                printf("SAINDO DO PROGRAMA...");
                break;
            default:
                printf("RESPOSTA INVALIDA");
                break;
        }
    }
}

void converteParaBinario(int numdec, int vet_binario[BITS]){
    inicializaVetorZerado(vet_binario);
    int i, num_aux = numdec; //num_aux = numdec para ver se era um numero negativo e adicionar 1 no inicio depois
    
    if(numdec < 0){
        numdec = numdec * (-1); // deixar o numero decimal positivo
    }

    for(i = BITS - 1 ; i >= 0; i--){ //bits - 1 pois é do 15 até o 0 (16)
        if(numdec % 2 == 0 ){
            vet_binario[i] = 0;     
        }
        else{
            vet_binario[i] = 1;
        }
        numdec = numdec/2;

    }
    
    if(num_aux < 0){             
        vet_binario[0] = 1;  
    }
    printf("\n");
}

void inicializaVetorZerado(int vetor[BITS]){ //zerando o vetor
    for (int i = 0; i < BITS; i++){            
        vetor[i] = 0;          
    }
}

void imprimeBin(int bin[BITS]){
    for (int i = 0; i < BITS; i++){
        if(i==0){
            printf("(%d)", bin[i]);
        }
        else{
            printf(" %d", bin[i]);
        }
    }
    printf("\n");
}

void transfereBin(int bin1[BITS], int bin2[BITS]){
    for(int i = 0; i < BITS; i++){
        bin2[i] = bin1[i];
    }
}

void converteComplementoDe2(int bin[BITS]){
    int i, binvalor1[BITS], AUX[BITS]; //binario valor 1 é o binario ...01 para somar
    inicializaVetorZerado(binvalor1);
    inicializaVetorZerado(AUX);
    binvalor1[BITS-1] = 1;

    printf("Binario antes de complemento de 2: \n");
    imprimeBin(bin);
    printf("\n");

        printf("Trocando todos os 1s por 0s e todos os 0s por 1s: \n");
        for(i=0; i<BITS; i++){
            if(bin[i] == 0){
                bin[i] = 1;
            }
            else{
                bin[i] = 0;
            }
        }
        imprimeBin(bin);
        printf("\n");
        printf("Somando o complemento de 2: \n");
        soma(bin, binvalor1, AUX);
        transfereBin(AUX, bin);
        printf("\n");
        
        printf("Binario em Complemento de 2 : \n");
        imprimeBin(bin);
        printf("\n");
}

void converteResultComplementoDe2(int bin[(BITS*2)-2]){
    int i, binvalor1[BITS], AUX[BITS]; //binario valor 1 é o binario ...01 para somar
    inicializaVetorZerado(binvalor1);
    inicializaVetorZerado(AUX);
    binvalor1[BITS-1] = 1;

    printf("Binario antes de complemento de 2: \n");
    imprimeBin(bin);
    printf("\n");

        printf("Trocando todos os 1s por 0s e todos os 0s por 1s: \n");
        for(i=0; i<(BITS*2)-2; i++){
            if(bin[i] == 0){
                bin[i] = 1;
            }
            else{
                bin[i] = 0;
            }
        }
        imprimeBin(bin);
        printf("\n");
        printf("Somando o complemento de 2: \n");
        soma(bin, binvalor1, AUX);
        transfereBin(AUX, bin);
        printf("\n");
        
        printf("Binario em Complemento de 2 : \n");
        imprimeBin(bin);
        printf("\n");
}

void soma(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    int carry=0, of;
        printf("Carry:"); 
    for(int i = BITS-1; i >= 0; i--){             //operador XOR / 0 ^ 0 da 0 / 0 ^ 1 da 1 / 1 ^ 0 da 1 / 1 ^ 1 da 0 / Faz com os numeros dos binarios e dps com Carry
        printf(" %d",carry);                     //for até >= 0 para tratar overflow caso tenha
        binresult[i] = bin1[i]^bin2[i]^carry;
        carry = carry + bin1[i] + bin2[i];     //carry recebendo a soma , se for > 1 é pq teve q passar 1 
        if(carry > 1){
            carry = 1;
        }
        else{ 
            carry = 0;
        } 
    }

    of = overflow(bin1,bin2,binresult);

    if(of == 1){
        printf("Overflow\n");
        printf("1 a mais ignorado\n");
    }
    else{
        printf("\n");
        imprimeBin(bin1);
        printf("+\n");
        imprimeBin(bin2);
        printf("----------------------------------\n");
        imprimeBin(binresult);
    }
}

int overflow(int bin1[BITS], int bin2[BITS],int binresult[BITS]){ // em Complemento de 2 o overflow é "ignorado", deixamos de lado o 1 a mais 
    if(bin1[0] == 1 && bin2[0] == 1){                                        
        printf("\n");
        imprimeBin(bin1);
        printf("+\n");
        imprimeBin(bin2);
        printf("----------------------------------\n");
        imprimeBin(binresult);
        return 1;                                             //se deu overflow retorna 1 
    }
    return 0;
}

int DeslocaParaDireita(int Q1, int A[BITS], int Q[BITS]){
    int i, auxA, auxA1;
    auxA = A[0];
    auxA1 = A[BITS-1];
    Q1 = Q[BITS-1];

    for(i = BITS-1; i >= 0; i--){
        A[i] = A[i-1];
        Q[i] = Q[i-1];
    }
    A[0] = auxA;
    Q[0] = auxA1;
    return Q1;
}

void multiplicacaoC2(int binM[BITS], int binQ[BITS]){
    int sinalmult, Q1=0;
    int A[BITS], AUX[BITS],Complemento2M[BITS], multresult[(BITS*2)-2]; // AUX para fazer a soma de A + M e depois passar o valor para A novamente e Complemento de 2 M para manter o bin M
    inicializaVetorZerado(A);
    inicializaVetorZerado(AUX);
    inicializaVetorZerado(Complemento2M);
    transfereBin(binM, Complemento2M);
    converteComplementoDe2(Complemento2M);
    imprimeBin(Complemento2M);

    imprimeBin(binM);
    printf("*\n");
    imprimeBin(binQ);
    printf("\n-----------------------------------\n");
    printf("\nPasso a passo:\n");
    

    if(binM[0] == 1 && binQ[0] == 0){ //se algum dos dois sinais for 1, guardar o sinal para colocar no final
        sinalmult = 1;
    }
    else if(binM[0] == 0 && binQ[0] == 1){
        sinalmult = 1;
    }
    else{
        sinalmult = 0;
    }

    for(int i = BITS-1; i >= 0; i--){ // começando do 15 e indo até o 0 pq inclui o bit de sinal
        if(binQ[BITS-1] == 0 && Q1 == 1){      // o bit Q = 0 e Q1 = 1 então A = A + M
            printf("A : \n");   // imprime os vetores iniciais
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");

            printf("Bit Q = %d e Q1 = %d, entao A = A + M\n", binQ[BITS-1], Q1); // Somando A + M
            soma(A,binM,AUX);
            transfereBin(AUX,A);
            printf("\n");

            printf("\nBinario A depois de somar com M : \n");
            imprimeBin(A);
            printf("\n");

            printf("\nA, Q e Q1 serao deslocados um bit para a direita \n"); // Antes de todos deslocar um bit para direita
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");

            printf("\nDeslocando A, Q e Q1 um bit para a direita \n"); // Apos o deslocamento de todos um bit para direita
            Q1 = DeslocaParaDireita(Q1,A,binQ);
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");
            printf("------------------------------------------------------------\n");
        }
        else if(binQ[BITS-1] == 1 && Q1 == 0){ // o bit Q = 1 e Q1 = 0 então A = A - M (A = + M')
            printf("A : \n");   // imprime os vetores iniciais
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");

            printf("Bit Q = %d e Q1 = %d, entao A = A - M (A = A + M')\n", binQ[BITS-1], Q1); // Somando A + M
            soma(A,Complemento2M,AUX);
            transfereBin(AUX,A);
            printf("\n");

            printf("\nBinario A depois de somar com M' : \n");
            imprimeBin(A);
            printf("\n");

            printf("\nA, Q e Q1 serao deslocados um bit para a direita \n"); // Antes de todos deslocar um bit para direita
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");

            printf("\nDeslocando A, Q e Q1 um bit para a direita \n"); // Apos o deslocamento de todos um bit para direita
            Q1 = DeslocaParaDireita(Q1,A,binQ);
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");
            printf("------------------------------------------------------------\n");
        }
        else{
            printf("------------------------------------------------------------\n");
            printf("A : \n");   // imprime os vetores iniciais
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");

            printf("Bit Q = %d e Q1 = %d, entao apenas sera feito o deslocamento para a direita\n", binQ[BITS-1], Q1);
            printf("\nA, Q e Q1 serao deslocados um bit para a direita \n"); // Antes de todos deslocar um bit para direita
            printf("\nDeslocando A, Q e Q1 um bit para a direita \n"); // Apos o deslocamento de todos um bit para direita
            Q1 = DeslocaParaDireita(Q1,A,binQ);
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(binQ);
            printf("Q1 : %d\n", Q1);
            printf("M : \n");
            imprimeBin(binM);
            printf("M' : \n"); //Complemento de 2 de M
            imprimeBin(Complemento2M);
            printf("\n");
            printf("------------------------------------------------------------\n");
        }
    }

    for(int i = 0; i <=(BITS*2)-2; i++){ //iniciando o vetor de 32 bits zerado
        multresult[i] = 0;
    }

    for(int i = 0; i < BITS; i++){ //PARTE DO RESULTADO : A do 0 ao 15
        multresult[i] = A[i];
    }    
    for(int i = BITS; i <=(BITS*2)-2; i++){ //PARTE DO RESULTADO : Q do 16 ao 30
        multresult[i] = binQ[(i+1)-BITS];  
    }
    if(sinalmult == 1){
        converteResultComplementoDe2(multresult);
    }
    printf("Binario Resultante -> A | Q :\n");
    printf("--------------------------------------------------------------------\n");
    printf("(%d)", multresult[0]);
    for(int i = 1; i <= (BITS*2)-2; i++){ 
        printf(" %d", multresult[i]);
    }
}