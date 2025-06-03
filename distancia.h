#ifndef DISTANCIA_H1337
#define DISTANCIA_H1337

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

double distanciaEuclidiana(Ponto* pon1, Ponto* pon2);


double **matrixDistancia(Ponto ** pontos, int qtdPontos);

void imprimeMatrixDistancia(double ** pontos, int qtdPontos);


void liberaMatriz(double ** matrix, int qtdPontos);

int comp(const void *a, const void *b);

void matrizToArr(double** matriz, int qtdPontos);

//bagunca experimental.
void meusortmatrix(double **arr, int qtdPontos);



#endif