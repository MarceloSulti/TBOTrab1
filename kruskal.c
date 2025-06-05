#include "kruskal.h"

struct UFSet
{
    int *id;
    int *sz;
    
    int qtdNodes; // quantidade de elementos no UF
};



UFSet *UF_init(int size) 
{
    UFSet *newUF = malloc(sizeof(UFSet));
    newUF->id = malloc(sizeof(int) * size);
    newUF->sz = malloc(sizeof(int) * size);
    int *id = newUF->id;
    int *sz = newUF->sz;
    for (int i = 0; i < size; i++) 
    {
        id[i] = i; // Cada objeto comeca na sua propria componente.
        sz[i] = 0;

    } // N acessos ao array.]
    newUF->qtdNodes = 0;

    return newUF;
}


void UF_free(UFSet *ufset)
{
    if(ufset)
    {
        free(ufset->id);
        free(ufset->sz);
        free(ufset);
        ufset = NULL;
    }
}
int UF_find(UFSet *ufset,int i) 
{
    int* id = ufset->id;

    // pegar um numero int dentro de ufset e chegar no parente de outro (na posicao)
    while (i != id[i]) 
    {
        id[i] = id[id[i]]; // Uma unica linha de codigo adicional.
        i = id[i]; // Cada passo agora requer 5 acessos.
    }
    return i;
}

void UF_union(UFSet *ufset,int p, int q) 
{
    int* id = ufset->id;
    int* sz = ufset->sz;

    int i = UF_find(ufset, p); // Pendure a arvore menor sob a maior.
    int j = UF_find(ufset, q); // Profundidade de ? acessos.
    if(i == j) return;
    if(sz[i] < sz[j]) 
    { 
        id[i] = j; sz[j] += sz[i]; 
    }
    else 
    { 
        id[j] = i; sz[i] += sz[j]; 
    }
}

bool UF_connected(UFSet *ufset,int p, int q) 
{
    return UF_find(ufset, p) == UF_find(ufset, q);
}

// pega o indice/posicao de um Ponto no ufset, para fazer operacoes dele no UFSet. tem que ser unico.
// ideia: ja que nome eh unico, compara nome do Ponto que vc quer buscar o index com os pontos iterando.
int retornaIndexPontoUF(UFSet *ufset, Ponto **pontos, int qtdPontos, char*nome)
{
    for(int i=0;i<qtdPontos;i++)
    {
        if(strcmp(retornaNome(pontos[i]), nome))
        {
            printf("Ponto %s encontrado na posicao %d do UFSet\n", nome, i);
            return i;
        }
    }

    return -1;
    
}


void algoritmo_kruskal(Ponto **pontos, int qtdPontos,
                             Aresta **arestas_ordenadas, int qtdArestas,
                             int *tamanho_mst_resultado, double *custo_total_mst)
{
                                // adicionar k de alguma forma pra tamanho max
    // ver como obter uma floresta em vez de uma arvore (desconexos com base em k)

    
    *tamanho_mst_resultado = 0;
    *custo_total_mst = 0.0;

    // inicia o set union-find
    UFSet *ufset = UF_init(qtdPontos);


    int arestas_adicionadas = 0;
    double custo_acumulado = 0.0;

    // Iterate through all sorted edges
    for (int i = 0; i < qtdArestas; i++) {
        Aresta *aresta_atual = arestas_ordenadas[i];
    
        // pega
        // pega p1 e p2 da Aresta (seu index no UFSet?)
        //int p1 = retornaIndexPontoUF(ufset, pontos, qtdPontos,);

        
        /*
            Check if p1 and p2 are already connected (in the same set)

            (union find vai ter os pontos (indices???), MST vai ter Arestas (ordenadas, para qnd da a qtd pedida))
            Checar as raizes de p1 e p2.
        
    
        se nao eh do msm conjunto: 


    
        // se nao eh do mesmo conjunto
        
        tenta adicionar Aresta a MST se tiver espaco (se nao ja tiver o minimo de componentes). aqui vai um if pra isso. 
        if(arestas_adicionadasMST < maximo_arestas) < se ainda tiver espaco.
            union (p1,p2) < une os pontos no UF. 
            mst_arestas[arestas_adicionadas] = aresta_atual; // adiciona aresta na MST.
            custo_acumulado += retornaTamanhoAresta(aresta_atual);
            arestas_adicionadas++;
        
        
        se o if falhar, pula até o final e da break no comando?
        if(arestasa_adicionadasMST >= maximo_arestas)
            ve como fazer pra obter a floresta pq ja esta pronto. aqui eh o fim do bgl e tera o break.
        //if (arestas_adicionadasMST == qtdPontos -1 (ou k) && qtdPontos >0) << isso pode ajudar ou ate ser melhor q o previo
        */

    }

    *tamanho_mst_resultado = arestas_adicionadas;
    *custo_total_mst = custo_acumulado;
    
    

    return;
}