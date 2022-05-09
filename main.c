//Author : Gabriel Rodrigues de Souza - RA : 118038
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16

int main(){
    int numDecimal1, numDecimal2, binario1[BITS], binario2[BITS], numresult, restodiv;
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
                numresult = numDecimal1 * numDecimal2;
                printf("%d * %d = %d \n",numDecimal1,numDecimal2, numresult);
                multiplicacaoC2(numDecimal1,numDecimal2,binario1, binario2);
                break;
            case '/':
                if(numDecimal2 == 0){
                    printf("Nao eh possivel dividir por 0");
                }
                else{
                    if(numDecimal1< 0){
                        numDecimal1 = numDecimal1 * (-1);
                    }
                    if(numDecimal2< 0){
                        numDecimal2 = numDecimal2 * (-1);
                    }
                    if(numDecimal2>numDecimal1){
                        numresult = numDecimal1 / numDecimal2;
                        printf("Nao eh possivel fazer a divisao, pois o segundo numero eh maior que o primeiro\n");
                        printf("%d / %d = %d \n",numDecimal1,numDecimal2, numresult);
                        printf("Resto : %d", numDecimal2);
                        } 
                    else{
                        numresult = numDecimal1 / numDecimal2;
                        restodiv = numDecimal1 % numDecimal2;
                        printf("%d / %d = %d \n",numDecimal1,numDecimal2, numresult);
                        printf("Resto da divisao: %d\n",restodiv);
                        divisao(numDecimal1,numDecimal2, binario1, binario2);
                    }
                }  
                
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

    if(num_aux < 0){                      // apenas converte para o complemento de 2 se o numero for negativo
        converteComplementoDe2(vet_binario);
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
    auxA = A[0];                                      //Guardando o primeiro valor de A pois ele se mantem ao deslocar para a direita
    auxA1 = A[BITS-1];                                //Guardando o ultimo valor de A pois Q recebe este valor
    Q1 = Q[BITS-1];

    for(i = BITS-1; i >= 0; i--){
        A[i] = A[i-1];
        Q[i] = Q[i-1];
    }
    A[0] = auxA;
    Q[0] = auxA1;
    return Q1;
}

void DeslocaParaEsquerda(int A[BITS], int Q[BITS]){
    int i , auxQ, auxA;

    auxA = Q[0];

    for(i = 0; i < BITS-1; i++){ //
        A[i] = A[i+1];
        Q[i] = Q[i+1];
    }

    Q[BITS-1] = 0;
    A[BITS-1] = auxA;
}

void multiplicacaoC2(int num1,int num2,int binM[BITS], int binQ[BITS]){
    int sinalmult, Q1=0;
    int A[BITS], AUX[BITS],Complemento2[BITS], multresult[(BITS*2)-1]; // AUX para fazer a soma de A + M e depois passar o valor para A novamente e Complemento de 2 M para manter o bin M
    inicializaVetorZerado(A);
    inicializaVetorZerado(AUX);
    inicializaVetorZerado(Complemento2);

    converteParaBinario(num1 * -1, Complemento2);

    imprimeBin(binM);
    printf("*\n");
    imprimeBin(binQ);
    printf("\n-----------------------------------\n");
    printf("\nPasso a passo:\n");
    
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
            printf("\n");

            printf("Bit Q = %d e Q1 = %d, entao A = A - M (A = A + M')\n", binQ[BITS-1], Q1); // Somando A + M
            soma(A,Complemento2,AUX);
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
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
            imprimeBin(Complemento2);
            printf("\n");
            printf("------------------------------------------------------------\n");
        }
    }

    for(int i = 0; i <=(BITS*2)-1; i++){ //iniciando o vetor de 32 bits zerado
        multresult[i] = 0;
    }

    for(int i = 0, j = BITS; i < BITS; i++, j++){ //PARTE DO RESULTADO : A do 0 ao 15 e Q 
        multresult[i] = A[i];
        multresult[j] = binQ[i];
    }    
    
    printf("Binario Resultante -> A | Q :\n");
    printf("--------------------------------------------------------------------\n");
    printf("(%d)", multresult[0]);
    for(int i = 1; i <= (BITS*2)-1; i++){ 
        printf(" %d", multresult[i]);
    }
}

void divisao(int num1, int num2, int bin1[BITS], int bin2[BITS]){
    int A[BITS], AUX[BITS]; //A é o resto da divisao
    int complemento2M[BITS]; //Complemento de 2 de Q e M
    int auxnum1, auxnum2;
    auxnum1 = num1;
    auxnum2 = num2;

    if(auxnum1 < 0) {
        num1 = num1 * -1;
    }
    if(auxnum2 < 0){
        num2 = num2 * -1;
    }

    inicializaVetorZerado(A);
    inicializaVetorZerado(complemento2M);
    converteParaBinario(num2 * -1, complemento2M);

    for(int i = BITS-1; i >= 0; i--){
            printf("A : \n");
            imprimeBin(A);
            printf("Q : \n");
            imprimeBin(bin1);
            printf("M : \n");
            imprimeBin(bin2);
            printf("M' : \n");
            imprimeBin(complemento2M);
            printf("\nDeslocando A e Q um bit para a esquerda \n");
            DeslocaParaEsquerda(A, bin1);
            printf("A : \n");
            imprimeBin(A);
            printf("\n");
            printf("Q : \n");
            imprimeBin(bin1);
            printf("M : \n");
            imprimeBin(bin2);
            printf("M' : \n");
            imprimeBin(complemento2M);
        printf("Somando A com M' \n");
        soma(A,complemento2M,AUX); // soma A ao complemento de 2 de M (A = A + M')
        transfereBin(AUX,A);
        if(A[0] == 1){
            printf("A < 0 entao A = A + M e Q0 = 0'\n");
            printf("A : \n");
            imprimeBin(A);
            printf("\n");
            printf("Q : \n");
            imprimeBin(bin1);
            printf("M : \n");
            imprimeBin(bin2);
            printf("M' : \n");
            imprimeBin(complemento2M);
            bin1[BITS-1] = 0;
            soma(A,bin2,AUX);
            transfereBin(AUX, A);
            printf("\n");
        }
        else{
            printf("A > 0 entao Q0 = 1\n");
            printf("A : \n");
            imprimeBin(A);
            printf("\n");
            printf("Q : \n");
            imprimeBin(bin1);
            printf("M : \n");
            imprimeBin(bin2);
            printf("M' : \n");
            imprimeBin(complemento2M);
            bin1[BITS-1] = 1;
        }
    }

    printf("Resto (A): \n");
    imprimeBin(A);
    printf("\n");
    printf("Resultado (Q): \n");
    imprimeBin(bin1);

    // if(auxnum1 < 0 && auxnum2 < 0){ //binresult positivo e resto negativo
        
    // }
    // else if(auxnum1 < 0 && auxnum2 > 0){   //binresult negativo e resto negativo
        
        
    // }
    // else if(auxnum1 > 0 && auxnum2 < 0){ //binresult negativo e resto positivo
        
    // }
    // else{                      //binresult positivo e resto positivo
        
    // }

}