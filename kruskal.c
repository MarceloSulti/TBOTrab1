#include "kruskal.h"

struct UFSet
{
    int *id;
    int *sz;
};


// Inicializa a struct UFSet com tamanho "size".
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
        sz[i] = 0; // comecam com tamanho 0
    } 

    return newUF;
}

// Libera a struct UFSet.
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


// funciona
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

void printUnion(UFSet *ufset, int qtd)
{
    for(int i=0;i<qtd;i++)
    {
        printf("elem %d; grupo %d\n", i, ufset->id[i]);
    }
}

// funciona
bool UF_connected(UFSet *ufset,int p, int q) 
{
    return (UF_find(ufset, p) == UF_find(ufset, q));
}

// pega o indice/posicao de um Ponto no ufset, para fazer operacoes dele no UFSet. tem que ser unico.
// ideia: ja que nome eh unico, compara nome do Ponto que vc quer buscar o index com os pontos iterando.
// o ultimo argumento vai ser oq vai ser usado pra achar o ponto
int retornaIndexPontoUF(UFSet *ufset, Ponto **pontos, int qtdPontos, Ponto* ponto)
{
    for(int i=0;i<qtdPontos;i++)
    {
        //TODO: se nao funcionar, usar strcmp (menos eficiente?)
        if(pontos[i] == ponto)
        {
            return i;
        }
    }

    return -1;
    
}

/*
    Problemas atuais:

    1- Pegar o index do ponto atual pra modificar/checar na struct UF.
     < possivel solucao: comparar ponteiros
    


    - Minimum-Spanning-Forest em vez de MST (Retornar/Imprimir TODOS os grupos, 
    nao so um conectado)


*/
void algoritmo_kruskal(Ponto **pontos, int qtdPontos,
                             Aresta **arestas_ordenadas, int qtdArestas,
                             int *tamanho_mst_resultado, double *custo_total_mst, 
                             int k)
{
                                // adicionar k de alguma forma pra tamanho max
    // ver como obter uma floresta em vez de uma arvore (desconexos com base em k)


    // variavel que fala qnts arestas foram adicionadas na mst
    int arestas_adicionadasMST = 0;     
    // maximo de arestas que podem ter na MST com base em K de argv[2].
    int maxArestasMST = (qtdPontos - (k)); 
    // variaveis de retorno, posso remover.
    *tamanho_mst_resultado = 0;
    *custo_total_mst = 0.0;

    // inicia o set union-find
    UFSet *ufset = UF_init(qtdPontos);

    // Array com as arestas dentro da MST (ja alocadas com o tamanho necessario).
    Aresta **arestasMST = malloc(sizeof(Aresta*) * maxArestasMST);
    double tamanhoTotalMST = 0.0;

    for (int i = 0; i < qtdArestas; i++) 
    {
        Aresta *aresta_atual = arestas_ordenadas[i];
        
        int indexP1 = retornaIndexPontoUF(ufset, pontos, qtdPontos, retornaP1(aresta_atual));
        int indexP2 = retornaIndexPontoUF(ufset, pontos, qtdPontos, retornaP2(aresta_atual));
        //printf("id1: %d (%s) id2: %d (%s)\n", indexP1, retornaNome(retornaP1(aresta_atual)), indexP2, retornaNome(retornaP2(aresta_atual)));

        
        if(!UF_connected(ufset,indexP1,indexP2))
        {
            if(arestas_adicionadasMST < maxArestasMST)
            {
                UF_union(ufset, indexP1,indexP2);
                tamanhoTotalMST+= retornaTamanhoAresta(aresta_atual);
                arestasMST[arestas_adicionadasMST] = aresta_atual;
                // adiciona na MST e etc.
                //TODO: adiciona a aresta na estrutura do kruskal? 
                // ou em algum lugar
                arestas_adicionadasMST++;
            }
            else
            {
                // acabou a MST, fazer funcoes pra finalizar.
                break;
            }
        }

        /*

            Pega posicao/index do p1 e do p2 na array **Pontos, e usa a index
            pra operacoes do union find.


            Check if p1 and p2 are already connected (in the same set)

            (union find vai ter os pontos (indices???), MST vai ter Arestas (ordenadas, para qnd da a qtd pedida))
            Checar as raizes de p1 e p2.
        
    
        se nao eh do msm conjunto: 
        

    
        // se nao eh do mesmo conjunto
        
        tenta adicionar Aresta a MST se tiver espaco (se nao ja tiver o minimo de componentes). aqui vai um if pra isso. 
        if(arestas_adicionadasMST < maximo_arestas) < se ainda tiver espaco.
            union (p1,p2) < une os pontos no UF. 
            mst_arestas[arestas_adicionadas] = aresta_atual; // adiciona aresta na MST.
            tamanhoTotalMST += retornaTamanhoAresta(aresta_atual);
            arestas_adicionadas++;
        
        
        se o if falhar, pula até o final e da break no comando?
        if(arestasa_adicionadasMST >= maximo_arestas)
            ve como fazer pra obter a floresta pq ja esta pronto. aqui eh o fim do bgl e tera o break.
        //if (arestas_adicionadasMST == qtdPontos -1 (ou k) && qtdPontos >0) << isso pode ajudar ou ate ser melhor q o previo
        */

    }
    // funcao pra retornar grupo de cada uma?

    //printUnion(ufset,qtdPontos);
    *tamanho_mst_resultado = arestas_adicionadasMST;
    *custo_total_mst = tamanhoTotalMST;
    
    UF_free(ufset);
    // se for usar pra fora ver se faco isso
    free(arestasMST);

    return;
}