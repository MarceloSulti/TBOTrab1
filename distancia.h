#ifndef DISTANCIA_H1337
#define DISTANCIA_H1337

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

typedef struct Aresta Aresta;



Aresta *montaArestaSVal(Ponto* pon1, Ponto* pon2);

Aresta *montaAresta(Ponto* pon1, Ponto* pon2, double distancia);

void imprimeAresta(Aresta *arestaA);

void ordenaAresta(Aresta **arestas, int qtdArestas);

int compAresta(const void *a, const void *b);

Ponto *retornaP1(Aresta *ar);

Ponto *retornaP2(Aresta *ar);

double retornaTamanhoAresta(Aresta *ar);

void liberaAresta(Aresta *arest);



double *arrayDistancia(Ponto ** pontos, int qtdPontos);


void imprimeArrayDistancia(double * pontos, int qtdPontos);


//


double distanciaEuclidiana(Ponto* pon1, Ponto* pon2);

int comp(const void *a, const void *b);

void matrizToArr(double** matriz, int qtdPontos);

#endif