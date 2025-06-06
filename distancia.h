#ifndef DISTANCIA_H1337
#define DISTANCIA_H1337

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

typedef struct Aresta Aresta;

Aresta *montaArestaSVal(Ponto* pon1, Ponto* pon2);

Aresta *montaAresta(Ponto* pon1, Ponto* pon2, double distancia);

int compAresta(const void *a, const void *b);

void ordenaAresta(Aresta **arestas, int qtdArestas);

Ponto *retornaP1(Aresta *ar);

Ponto *retornaP2(Aresta *ar);

double retornaTamanhoAresta(Aresta *ar);

void imprimeAresta(Aresta *arestaA);

void liberaAresta(Aresta *arest);

void liberaArestas(Aresta **arrArestas, int qtdArestas);

double distanciaEuclidiana(Ponto* pon1, Ponto* pon2);

double *arrayDistancia(Ponto ** pontos, int qtdPontos);

void imprimeArrayDistancia(double * pontos, int qtdPontos);

int comp(const void *a, const void *b);

#endif