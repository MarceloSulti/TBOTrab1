#ifndef PONTO_H1337
#define PONTO_H1337

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// definir struct do ponto e suas funcoes
typedef struct Ponto Ponto;

Ponto *criaPonto(char *nome, int nDimensoes, double *valores);

Ponto *criaPontoNome(char *nome);

Ponto *addValor(Ponto *ponto,double valor);

int retornaQtdDimensao(Ponto *ponto);


double retornaValorPos(Ponto *ponto, int index);

double *retornaValores(Ponto *ponto);


Ponto *retornaPontoDentro(Ponto **pontos, int index);

size_t retornaTamanhoPonto();

void liberaPonto(Ponto *ponto);

void liberaPontos(Ponto **ponto, int qtdPontos);

#endif