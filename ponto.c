#include "ponto.h"

/* aqui sera o TAD armazenando o:

Nome do ponto.

quantidade de dimensoes 

valor[qtdDimensoes]

*/

struct Ponto{

    char * nome;
    double * valores;
    int nDimensoes;
};

Ponto *criaPonto(char *nome, int nDimensoes, double *valores)
{
    Ponto *newPonto = malloc(sizeof(Ponto));
    newPonto->nome = malloc(sizeof(char) * (strlen(nome)+1));
    strcpy(newPonto->nome,nome);
    newPonto->valores = malloc(sizeof(double) * nDimensoes);
    for(int i=0;i<nDimensoes;i++)
    {
        newPonto->valores[i] = valores[i];
    }

    return newPonto;
};

// cria ponto com apenas o nome, sem alocar nenhum valor.
Ponto *criaPontoNome(char *nome)
{

    Ponto *newPonto = malloc(sizeof(Ponto));
    newPonto->nome = malloc(sizeof(char)  * (strlen(nome)+ 1));
    strcpy(newPonto->nome, nome);

    newPonto->valores = NULL;
    newPonto->nDimensoes = 0;

    return newPonto;
}

// adiciona valores ao ponto, e acresce uma dimensao. << pode ser mais eficiente? realloc toda vez?
Ponto *addValor(Ponto *ponto,double valor)
{
    if(ponto)
    {
        ponto->nDimensoes++;
        void* rlc = realloc(ponto->valores, sizeof(double) * (ponto->nDimensoes));
        if(rlc)
        {
            ponto->valores = rlc;
            ponto->valores[ponto->nDimensoes-1] = valor;
        }
    }
    

    return ponto;
}

int retornaQtdDimensao(Ponto *ponto)
{
    return ponto->nDimensoes;
}


double *retornaValores(Ponto *ponto)
{
    return ponto->valores;
}

double retornaValorPos(Ponto *ponto, int index)
{
    return ponto->valores[index];
}

Ponto *retornaPontoDentro(Ponto **pontos, int index)
{
    return pontos[index];
}

char* retornaNome(Ponto *ponto)
{
    return ponto->nome;
}

size_t retornaTamanhoPonto()
{
    return(sizeof(Ponto));
}

void liberaPonto(Ponto *ponto)
{
    if(ponto)
    {
        free(ponto->nome);
        free(ponto->valores);
        free(ponto);
        ponto = NULL;
    }
}

void liberaPontos(Ponto **ponto, int qtdPontos)
{
    if(ponto)
    {
        for(int i=0; i<qtdPontos;i++)
        {
            free(ponto[i]->nome);
            free(ponto[i]->valores);
            free(ponto[i]);
        }
        free(ponto);
        ponto = NULL;
    }
}