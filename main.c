#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OrdenacaoExterna.h"
void criaArquivoTeste(char *nome)
{
    int i;
    FILE *f = fopen(nome, "w");
    srand(time(NULL));
    for(i = 1; i < 1000; i++)
        fprintf(f, "%d\n", rand());
    fprintf(f, "%d", rand());
    fclose(f);
}

int main()
{
    criaArquivoTeste("dados.txt");
    mergeSortExterno("dados.txt");

    return 0;
}

//transformar menor em P_menor

