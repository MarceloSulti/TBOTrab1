      
#ifndef KRUSKAL_H1337
#define KRUSKAL_H1337

#include <stdlib.h>    
#include <stdio.h>
#include <stdbool.h>
#include "ponto.h"     
#include "distancia.h" 

typedef struct UFSet UFSet;

UFSet *UF_init(int size);

void UF_free(UFSet *ufset);

int UF_find(UFSet *ufset,int i);

void UF_union(UFSet *ufset,int p, int q);

void printUnion(UFSet *ufset, int qtd);

bool UF_connected(UFSet *ufset,int p, int q);

int retornaIndexPontoUF(UFSet *ufset, Ponto **pontos, int qtdPontos, 
    Ponto* ponto);


    void algoritmo_kruskal(Ponto **pontos, int qtdPontos,
                             Aresta **arestas_ordenadas, int qtdArestas,
                             int *tamanho_mst_resultado, double *custo_total_mst,
                            int k);

#endif
