#ifndef ORDENACAOEXTERNA_H_INCLUDED
#define ORDENACAOEXTERNA_H_INCLUDED
typedef struct Arquivo
{
    FILE *f;
    int pos, MAX, *buffer;
} arquivo;

void mergeSortExterno(char *nome);
void verificaArquivoOrdenado(char *nome);


#endif // ORDENACAOEXTERNA_H_INCLUDED
