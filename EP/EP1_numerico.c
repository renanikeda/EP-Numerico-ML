// EP1 MAP3121 Machine Learning    //
//                                 //
// Aluno: Renan Ikeda Fernandes    //
// Nusp: 10439892                  //
// Aluno: Vinicius de Barros Silva //
// Nusp: 10335913                  //
// Turma: 01                       //
//                                 //

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// Declara��o das fun��es //

void imprimimatriz(float **A,int n,int m){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
float cgivens(float wik, float wjk){
// Calcula o cosseno que ser� usado na rota��o a partir dos wik e wjk
    float ta,c,aux;
    if(fabs(wik)>fabs(wjk)){
        ta=(-wjk/wik);
        c=1/(sqrt(1+(pow(ta,2))));
    }
    else{
        ta=(-wik/wjk);
        aux=1/(sqrt(1+(pow(ta,2))));
        c=aux*ta;
    }
return c;
}
float sgivens(float wik,float wjk){
// Calcula o seno que ser� usado na rota��o a partir dos wik e wjk
    float ta,s,aux;
    if(fabs(wik)>fabs(wjk)){
        ta=(-wjk/wik);
        aux=1/(sqrt(1+(pow(ta,2))));
        s=aux*ta;
    }
    else{
        ta=(-wik/wjk);
        s=1/(sqrt(1+(pow(ta,2))));
    }
return s;
}
void rotgivens(float **W,float **A,float c,float s,int i,int j,int k,int n,int m, int p){
// Faz a rota��o para as linhas i e j nas matrizes W e A
    int r;
    float aux,aux2;
    for(r=k;r<p;r++){
        aux= c*(W[i][r])- s*(W[j][r]);
        W[j][r]= s*(W[i][r]) + c*(W[j][r]);
        W[i][r]= aux;
    }
    for(r=0;r<m;r++){
        aux2= c*(A[i][r]) - s*(A[j][r]);
        A[j][r]= s*(A[i][r]) + c*(A[j][r]);
        A[i][r]= aux2;
    }
}
void escalonar(float **W, float **A,int n,int m,int p){
// Faz o escalonamento do sistema A = WH chamando a rotgivens, em cada coluna k se passa por todas suas linhas
//efetuando a rota��o de forma a escalonar a matriz
    int k,i,j;
    float c,s;
    for(k=0;k<p;k++){
        for(j=n-1;j>k;j--){
            i= j-1;
            if(W[j][k]!=0){
                c= cgivens(W[i][k],W[j][k]);
                s= sgivens(W[i][k],W[j][k]);
                rotgivens(W,A,c,s,i,j,k,n,m,p);
            }
        }
    }
}
void solve(float **R,float **H,float **A,int n,int m,int p){
// a partir do sistema escalonado ele resolve a matriz H a partir de A e W
    int k,j,r;
    float soma=0;
    for(k=p-1;k>=0;k--){
        for(j=0;j<m;j++){
            soma=0;
            if(k!=p-1){
                for(r=k+1;r<p;r++){
                    soma = soma + (R[k][r])*(H[r][j]);
                }
                H[k][j]=(A[k][j]-soma)/(R[k][k]);
            }

            else{
                H[k][j]=(A[k][j])/(R[k][k]);
            }

        }

    }
}
void transposta(float **ATUAL,float **NOVA,int n,int m){
// Calcula a matriz transposta de ATUAL e armazena na matriz NOVA
    int i,j,k;
    float aux;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            NOVA[j][i]=ATUAL[i][j];
        }

    }
}
void normalizar(float **M,int n, int m){
// Faz a normaliza��o da matriz pelas colunas
    int i,j;
    float aux;
    for(j=0;j<m;j++){
        aux=0;
        for(i=0;i<n;i++){
            aux = aux + pow(M[i][j],2);
        }
        aux=sqrt(aux);
        for(i=0;i<n;i++){
            M[i][j]=M[i][j]/aux;
        }
    }
}
void copiamatriz(float **ATUAL,float **NOVA,int n, int m){
// Copia a matriz ATUAL para a matriz NOVA
    int i,j;
    for(j=0;j<m;j++){
        for(i=0;i<n;i++){
            NOVA[i][j] = ATUAL[i][j];
        }
    }
}
void redefinir(float **A,int n, int m){
// Faz a redefini��o da matriz, fazendo o Aij = max{0,Aij}
    int i,j;
    float max=0;
    for(j=0;j<m;j++){
        for(i=0;i<n;i++){
            if(A[i][j]<=0){
                A[i][j]=0;
            }
        }
    }

}
void multiplica(float **W, float **H,float **WH, int n, int m, int p){
// Fun��o para fazer a multiplica��o ed matrizes
    int i,j,r;
    float aux;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            aux=0;
            for(r=0; r<p; r++){
                 aux=  aux + ((W[i][r])*(H[r][j]));
            }
            WH[i][j]=aux;
            aux=0;
        }
    }
}
float diff(float **A,float **WH,int n,int m){
// Calcula a norma da diferen�a da aproxima��o WH da matriz A
    float epsilon,ERRO,soma=0;
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            ERRO=A[i][j]-WH[i][j];
            soma=soma+pow(ERRO,2);
        }
    }
    soma = sqrt(soma);

return soma;
}
void diferenca(float **A,float **WH,float **B,int n, int m,int p){
// Calcula a diferen�a de duas matrizes e guarda em uma nova
    int i,j;
    for (i=0;i<n;i++){
        for(j=0;j<m;j++){
            B[i][j]=A[i][j]-WH[i][j];
        }
    }
}
float norma(float **C, int n, int j){
//Calcula normaliza uma coluna
    float a=0;
    int i=0;
    for(i=0;i<n;i++){
        a= a+pow(C[i][j],2);
    }
    a=sqrt(a);
    return a;
}

void minimosquadradosalternados(float **W,float **H,float **A, float **Wt,float **Ht,float **At,float **T,float **WH,int n,int ndig_treino, int p,int itermax,float epsilon){
// Fun��o principal da decomposi��o QR, utilizando o m�todo dos minimos quadrados alternados descrito no enunciado do EP
    int iter,i,j;
    float eps1=0,eps2;
    for(i=0;i<n;i++){
        for(j=0;j<ndig_treino;j++){
            A[i][j]= A[i][j]/255.0;
        }
    }
    for(iter=0;iter<itermax && epsilon>1.0/100000;iter++){
    normalizar(W,n,p);
    copiamatriz(A,T,n,ndig_treino);
    escalonar(W,A,n,ndig_treino,p);  // resolve em m�nimos quadrados para achar a matriz H
    solve(W,H,A,n,ndig_treino,p);
    redefinir(H,p,ndig_treino);      // redefine a matriz H com Hij = max{0,hij}
    transposta(T,At,n,ndig_treino);
    transposta(H,Ht,p,ndig_treino);
    transposta(W,Wt,n,p);
    escalonar(Ht,At,ndig_treino,n,p); // resolve o sistema transposto para achar a nova matriz W
    solve(Ht,Wt,At,ndig_treino,n,p);
    transposta(Wt,W,p,n);
    redefinir(W,n,p);   // redefine a matriz W com wij = max{0,wij}
    copiamatriz(T,A,n,ndig_treino);
    multiplica(W,H,WH,n,ndig_treino,p);
    eps2=diff(A,WH,n,ndig_treino);  // calcula o erro entre a aproxima��o WH da matriz A
    epsilon=fabs(eps1-eps2);  // compara a diferen�a entre duas itera��es para verificar se continuar� o la�o
    eps1=eps2;
    }
}
void normalizarA(float**A,int n,int m){
// Faz a normaliza��o da matriz de digitos, fazendo somente a divis�o por 255 que � o valor maximo possivel do pixel
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            A[i][j]= A[i][j]/255.0;
        }
    }
}


int main(){
// Inicializa��o das vari�veis
int n=784 ,m0=5923,m1=6742,m2=5958,m3=6131,m4=5842,m5=5421,m6=5918,m7=6265,m8=5851,m9=5949,p=10,i,j,iter=0,itermax=100;
// os mi, de i=0,1,...,9 obtidos num contador de palavras, utilizando o numero total de palavras no .txt e dividindo por 784
// que � o numero de linhas, apesar de n�o ser a solu��o mais elegante ela � funcional
float epsilon=1,eps1=0,eps2=0;
int ndig_treino=1000,n_test=10000;


// Inicializa��o das constantes p, ndig_treino, n_test pelo usu�rio
printf("Insira o numero p (5, 10 ou 15): ");
scanf("%i", &p);
printf("\n");
printf("Insira o numero de digitos de treino (ndig_treino = 100, 1000 ou 4000): ");
scanf("%i", &ndig_treino);
printf("\n");
printf("Insira o numero de digitos de test (n_test = 10000): ");
scanf("%i", &n_test);
printf("\n");

// Aloca��o de mem�ria pela fun��o malloc para inicializar as matrizes/vetores
// As Matrizes Wi s�o aquelas que v�o treinas os digitos i
float** W0=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W0[i]=malloc(p*sizeof(float*));

float** W1=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W1[i]=malloc(p*sizeof(float*));

float** W2=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W2[i]=malloc(p*sizeof(float*));

float** W3=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W3[i]=malloc(p*sizeof(float*));

float** W4=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W4[i]=malloc(p*sizeof(float*));

float** W5=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W5[i]=malloc(p*sizeof(float*));

float** W6=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W6[i]=malloc(p*sizeof(float*));

float** W7=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W7[i]=malloc(p*sizeof(float*));

float** W8=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W8[i]=malloc(p*sizeof(float*));

float** W9=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
W9[i]=malloc(p*sizeof(float*));

float** Wt=malloc(p*sizeof(float*));
for(i=0;i<p;++i)
Wt[i]=malloc(n*sizeof(float*));

// A matriz A e At (A transposta) s�o aquelas que v�o ler o train_digi.txt
float** A=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
A[i]=malloc(7000*sizeof(float*));

float** At=malloc(7000*sizeof(float*));
for(i=0;i<7000;++i)
At[i]=malloc(n*sizeof(float*));

// As matrizes H e Ht (H transpostas) ser�o utiizadas somente para fazer os treinos dos digitos i
float** H=malloc(p*sizeof(float*));
for(i=0;i<p;++i)
H[i]=malloc(ndig_treino*sizeof(float*));

float** Ht=malloc(ndig_treino*sizeof(float*));
for(i=0;i<ndig_treino;++i)
Ht[i]=malloc(p*sizeof(float*));

// A matriz Hteste � utilizada para fazer a solu��o do sistema, com o Wi j� treinado e a Matriz de teste
float** Hteste=malloc(p*sizeof(float*));
for(i=0;i<p;++i)
Hteste[i]=malloc(n_test*sizeof(float*));

// Matriz fruto da multiplica��o de W e H
float** WH=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
WH[i]=malloc(ndig_treino*sizeof(float*));

// Matriz que armazenar� a c�pia de A no processo de minimos quadrados alternados
float** T=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
T[i]=malloc(ndig_treino*sizeof(float));

// Matriz de digitos de testes, para averiguar o acerto da matriz Wi j� treinada
float** Teste=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
Teste[i]=malloc(n_test*sizeof(float*));

// Fruto da multiplica��o WH na fase de testes
float** WHteste=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
WHteste[i]=malloc(n_test*sizeof(float*));

// Matriz C � a diferen�a da matriz dos digitos de teste e da matriz WH de teste
float** C=malloc(n*sizeof(float*));
for(i=0;i<n;++i)
C[i]=malloc(n_test*sizeof(float*));

// cj � uma matriz 10 x n_test que quarda a norma do erro de C, em que cada linha ( de 0 a 9) corresponde a linha do Wi
float** cj=malloc(10*sizeof(float*));
for(i=0;i<=9;++i)
cj[i]=malloc(n_test*sizeof(float*));

// Vetor que armazena a resposta prov�vel de qual d�gito � cada coluna da matriz de teste
float* resposta=malloc(n_test*sizeof(float*));


// Inicializa��o do vetor de digitos
float digitos[10];
for(i=0;i<=9;i++)
    digitos[i]=0;

// Inicializa��o do vetor de ocorr�ncia do digito i
float ocorrencias[10];
for(i=0;i<=9;i++)
    ocorrencias[i]=0;

// Inicializa��o de H
for(i=0;i<p;i++){
    for(j=0;j<ndig_treino;j++){
        H[i][j]=0;
    }
}

// Inicializa��o aleat�ria das matrizes Wi, limitando seu valor em 500
srand(time(NULL));
for(i=0;i<n;i++){
    for(j=0;j<p;j++){
        W0[i][j]=rand()%500;
        W1[i][j]=rand()%500;
        W2[i][j]=rand()%500;
        W3[i][j]=rand()%500;
        W4[i][j]=rand()%500;
        W5[i][j]=rand()%500;
        W6[i][j]=rand()%500;
        W7[i][j]=rand()%500;
        W8[i][j]=rand()%500;
        W9[i][j]=rand()%500;
    }
}

// Foi feito um bloco de treino e teste para cada d�gito como segue a baixo
printf("####### treino digito 0 #########\n");
FILE *arq0;                                // Leitura do .txt do seu arquivo correspondente e quardando na Matriz A
arq0=fopen("train_dig0.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m0;j++){
        if(!fscanf(arq0,"%f", &A[i][j]))
            break;

        }
}
fclose(arq0);
minimosquadradosalternados(W0,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon); // � chamada a fun��o de minimos quadrados alternados para treinar a matriz Wi
FILE *test0;
test0=fopen("test_images.txt", "r");  // Em seguida � lido o .txt dos d�gitos de teste, armazenando-os na matriz Teste
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test0,"%f", &Teste[i][j]);
        }
}
fclose(test0);
normalizarA(Teste,n,n_test);    // Faz a normaliza��o da matriz Teste
escalonar(W0,Teste,n,n_test,p);      // Faz o escalonamento da matriz Wi e a matriz Teste
solve(W0,Hteste,Teste,n,n_test,p);   // Resolve o problema Teste = WiH
multiplica(W0,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);  // Calcula a diferen�a entre a aproxima��o WHteste e Teste
for(j=0;j<n_test;j++){
    cj[0][j]=norma(C,n,j);           // Adiciona a linha i da matriz cj a norma do erro entre WHteste e Teste
}
printf("Fim treino 0 \n\n");         // Fim da rotina de treino e teste para o digito i, embaixo segue a mesma rotina
                                     //para cada digito portanto n�o ser� comentada.


printf("####### treino digito 1 #########\n");
FILE *arq1;
arq1=fopen("train_dig1.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m1;j++){
        if(!fscanf(arq1,"%f", &A[i][j]))
            break;

        }
}
fclose(arq1);
minimosquadradosalternados(W1,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test1;
test1=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test1,"%f", &Teste[i][j]);
        }
}
fclose(test1);
normalizarA(Teste,n,n_test);
escalonar(W1,Teste,n,n_test,p);
solve(W1,Hteste,Teste,n,n_test,p);
multiplica(W1,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[1][j]=norma(C,n,j);
}
printf("Fim treino 1 \n \n");


printf("####### treino digito 2 #########\n");
FILE *arq2;
arq2=fopen("train_dig2.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m2;j++){
        if(!fscanf(arq2,"%f", &A[i][j]))
            break;

        }
}
fclose(arq2);
minimosquadradosalternados(W2,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test2;
test2=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test2,"%f", &Teste[i][j]);
        }
}
fclose(test2);
normalizarA(Teste,n,n_test);
escalonar(W2,Teste,n,n_test,p);
solve(W2,Hteste,Teste,n,n_test,p);
multiplica(W2,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[2][j]=norma(C,n,j);
}
printf("Fim treino 2 \n \n");


printf("####### treino digito 3 #########\n");
FILE *arq3;
arq3=fopen("train_dig3.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m3;j++){
        if(!fscanf(arq3,"%f", &A[i][j]))
            break;

        }
}
fclose(arq3);
minimosquadradosalternados(W3,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test3;
test3=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test3,"%f", &Teste[i][j]);
        }
}
fclose(test3);
normalizarA(Teste,n,n_test);
escalonar(W3,Teste,n,n_test,p);
solve(W3,Hteste,Teste,n,n_test,p);
multiplica(W3,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[3][j]=norma(C,n,j);
}
printf("Fim treino 3 \n \n");


printf("####### treino digito 4 #########\n");
FILE *arq4;
arq4=fopen("train_dig4.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m4;j++){
        if(!fscanf(arq4,"%f", &A[i][j]))
            break;

        }
}
fclose(arq4);
minimosquadradosalternados(W4,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test4;
test4=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test4,"%f", &Teste[i][j]);
        }
}
fclose(test4);
normalizarA(Teste,n,n_test);
escalonar(W4,Teste,n,n_test,p);
solve(W4,Hteste,Teste,n,n_test,p);
multiplica(W4,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[4][j]=norma(C,n,j);
}
printf("Fim treino 4 \n \n");


printf("####### treino digito 5 #########\n");
FILE *arq5;
arq5=fopen("train_dig5.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m5;j++){
        if(!fscanf(arq5,"%f", &A[i][j]))
            break;

        }
}
fclose(arq5);
minimosquadradosalternados(W5,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test5;
test5=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test5,"%f", &Teste[i][j]);
        }
}
fclose(test5);
normalizarA(Teste,n,n_test);
escalonar(W5,Teste,n,n_test,p);
solve(W5,Hteste,Teste,n,n_test,p);
multiplica(W5,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[5][j]=norma(C,n,j);
}
printf("Fim treino 5 \n \n");


printf("####### treino digito 6 #########\n");
FILE *arq6;
arq6=fopen("train_dig6.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m6;j++){
        if(!fscanf(arq6,"%f", &A[i][j]))
            break;

        }
}
fclose(arq6);
minimosquadradosalternados(W6,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test6;
test6=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test6,"%f", &Teste[i][j]);
        }
}
fclose(test6);
normalizarA(Teste,n,n_test);
escalonar(W6,Teste,n,n_test,p);
solve(W6,Hteste,Teste,n,n_test,p);
multiplica(W6,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[6][j]=norma(C,n,j);
}
printf("Fim treino 6 \n \n");


printf("####### treino digito 7 #########\n");
FILE *arq7;
arq7=fopen("train_dig7.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m7;j++){
        if(!fscanf(arq7,"%f", &A[i][j]))
            break;

        }
}
fclose(arq7);
minimosquadradosalternados(W7,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test7;
test7=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test7,"%f", &Teste[i][j]);
        }
}
fclose(test7);
normalizarA(Teste,n,n_test);
escalonar(W7,Teste,n,n_test,p);
solve(W7,Hteste,Teste,n,n_test,p);
multiplica(W7,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[7][j]=norma(C,n,j);
}
printf("Fim treino 7 \n \n");


printf("####### treino digito 8 #########\n");
FILE *arq8;
arq8=fopen("train_dig8.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m8;j++){
        if(!fscanf(arq8,"%f", &A[i][j]))
            break;

        }
}
fclose(arq8);
minimosquadradosalternados(W8,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test8;
test8=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test8,"%f", &Teste[i][j]);
        }
}
fclose(test8);
normalizarA(Teste,n,n_test);
escalonar(W8,Teste,n,n_test,p);
solve(W8,Hteste,Teste,n,n_test,p);
multiplica(W8,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[8][j]=norma(C,n,j);
}
printf("Fim treino 8 \n \n");


printf("####### treino digito 9 #########\n");
FILE *arq9;
arq9=fopen("train_dig9.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<m9;j++){
        if(!fscanf(arq9,"%f", &A[i][j]))
            break;

        }
}
fclose(arq9);
minimosquadradosalternados(W9,H,A,Wt,Ht,At,T,WH,n,ndig_treino,p,itermax,epsilon);
FILE *test9;
test9=fopen("test_images.txt", "r");
for(i=0;i<n;i++){
    for(j=0;j<n_test;j++){
        fscanf(test9,"%f", &Teste[i][j]);
        }
}
fclose(test9);
normalizarA(Teste,n,n_test);
escalonar(W9,Teste,n,n_test,p);
solve(W9,Hteste,Teste,n,n_test,p);
multiplica(W9,Hteste,WHteste,n,n_test,p);
diferenca(Teste,WHteste,C,n,n_test,p);
for(j=0;j<n_test;j++){
    cj[9][j]=norma(C,n,j);
}
printf("Fim treino 9 \n \n");
// Fim da rotina de treino e testes para todos os digitos



float aux;
int indice;

// O la�o percorre a matriz da norma da diferen�a (cj) por colunas, sendo o indice da menor norma � tomado como resposta
for(j=0;j<n_test;j++){
    aux=10000000;
    for(i=0;i<10;i++){
        if(cj[i][j]<aux){
            aux=cj[i][j];
            indice = i;
        }

    }
    resposta[j]=indice; // Dessa forma as respostas prov�veis s�o armazenadas no vetor respostas que tem n_test colunas
}
printf("\n INDICES ESTIMADOS\n");

float acertos=0;
float porcentagem=0;
float* real=malloc(n_test*sizeof(float*)); // vetor com os valores reais dos digitos lidos do test_index.txt
printf("\n");

FILE *indices;
indices=fopen("test_index.txt", "r");
for(i=0;i<n_test;i++){
    fscanf(indices,"%f", &real[i]);
    ocorrencias[(int)real[i]] = ocorrencias[(int)real[i]] + 1; // Para cada valor lido � incrementado na coluna i do vetor ocorrencias
    if(real[i]==resposta[i]){                                  //que armazena a quantidade de ocorr�ncias desse digito
        acertos=acertos+1 ;                                     // Analiza se a resposta estimada pelo algoritmo � igal com a resposta
        digitos[(int)real[i]] = digitos[(int)real[i]] + 1;     //verdadeira dada pelo vetor real
    }                                                          // Tamb�m � armazenada no vetor digitos a quantidade deacertos
}                                                              //do digito i em sua respectiva coluna i
fclose(indices);

porcentagem=(float)(acertos/n_test);  // Declaca a acur�cia total do algoritmo
printf("\n Acertos %f % \n",(porcentagem));
for(i=0;i<=9;i++){
    printf("\n Acertos digito %d: %f %", i, (float)(digitos[i]/ocorrencias[i]));  // Declara a acur�cia por digito
}

return 0;
}
