#include <stdio.h>
#include <stdlib.h>
#include "OrdenacaoExterna.h"
#define N 100
//  como se pudesse ter apenas 100 arquivos na memoria e vamos ordenar um arquivo com 1000

int compara(const void *a, const void *b){
    if(*(int*)a == *(int*)b)
        return 0;//iguais
    else
        if(*(int*)a < *(int*)b)
            return -1; //vem antes
        else
            return 1; //vem depois
}

void salvaArquivo(char *nome, int *V, int tam, int mudaLinhaFinal)
{
    int i;
    FILE *f = fopen(nome, "a");
    for(i = 0; i < tam-1; i++)
        fprintf(f, "%d\n", V[i]);

    if(mudaLinhaFinal == 0)
        fprintf(f, "%d", V[tam-1]);
    else
        fprintf(f, "%d\n", V[tam-1]);

    fclose(f);
}

void preencheBuffer(arquivo* arq, int K)
{
    int i;
    if(arq->f == NULL)
        return;
    arq->pos = 0;
    arq->MAX = 0;
    for(i = 0; i < K; i++)
    {
        if(!feof(arq->f))
        {
            fscanf(arq->f, "%d", &arq->buffer[arq->MAX]);
            arq->MAX++;
        }
        else
        {
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}

int procuraMenor(arquivo* arq, int numArqs, int K, int* P_menor)
{
    int i, idx = -1;
    for(i = 0; i < numArqs; i++)  //  procura menor posição
    {
        if(arq[i].pos < arq[i].MAX)
        {
            if(idx == -1)
                idx = i;
            else
            {
                if(arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos])
                    idx = i;
            }
        }
    }

    if(idx != -1)
    {
        *P_menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if(arq[idx].pos == arq[idx].MAX)
            preencheBuffer(&arq[idx], K);
        return 1;
    }
    else
        return 0;
}

void merge(char *nome, int numArqs, int K)
{
    char novo[20];
    int i;
    int *buffer = (int *) malloc(K*sizeof(int));  //  buffer de saida

    arquivo* arq;
    arq = (arquivo *) malloc(numArqs * sizeof(arquivo));
    for(i = 0; i < numArqs; i++)
    {
        sprintf(novo, "Temp%d.txt", i+1);
        arq[i].f = fopen(novo, "r");
        arq[i].MAX = 0;
        arq[i].pos = 0;
        arq[i].buffer = (int *) malloc(K * sizeof(int));
        preencheBuffer(&arq[i], K);
    }

    int menor, qtdBuffer = 0;
    while(procuraMenor(arq, numArqs, K, &menor) == 1)
    {
        buffer[qtdBuffer] = menor;
        qtdBuffer++;
        if(qtdBuffer == K)
        {
            salvaArquivo(nome, buffer, K, 1);
            qtdBuffer = 0;
        }
    }

    if(qtdBuffer != 0)
        salvaArquivo(nome, buffer, qtdBuffer, 1);

    for(i = 0; i < numArqs; i++)
        free(arq[i].buffer);
    free(arq);
    free(buffer);
}

int criaArquivosOrdenados(char *nome)
{
    int V[N], cont = 0, total = 0;
    char novo[20];
    FILE *f = fopen(nome, "r");
    while(!feof(f))
    {
        fscanf(f, "%d", &V[total]);
        total++;
        if(total == N)
        {
            cont++;
            sprintf(novo, "Temp%d.txt", cont);
            qsort(V, total, sizeof(int), compara);
            salvaArquivo(novo, V, total, 0);
            total = 0;
        }
    }
    if(total > 0) // se sobrar dados no buffer
    {
        cont++;
        sprintf(novo, "Temp%d.txt", cont);
        qsort(V, total, sizeof(int), compara);
        salvaArquivo(novo, V, total, 0);
    }
    fclose(f);
    return cont;
}

void mergeSortExterno(char *nome)
{
    char novo[20];
    int numArqs = criaArquivosOrdenados(nome);
    int i, K = N / (numArqs + 1);
    printf("Num Arqs: %i\n", numArqs);
    printf("K: %i", K);
    remove(nome);
    merge(nome, numArqs, K);

    for(i = 0; i < numArqs; i++)
    {
        sprintf(novo, "Temp%d.txt", i+1);
        remove(novo);
    }
}

void verificaArquivoOrdenado(char *nome){
    int v1,v2, erro = 0;
    FILE *f = fopen(nome,"r");
    fscanf(f,"%d",&v1);
    while(!feof(f)){
        fscanf(f,"%d",&v2);
        if (v2 < v1){
            erro = 1;
            break;
        }
    }
    fclose(f);
    if(erro)
        printf("Valores fora de ordem!\n");
    else
        printf("Arquivo corretamente ordenado!\n");
}
