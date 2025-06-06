#include "distancia.h"

struct Aresta
{
    Ponto *p1;
    Ponto *p2;
    double tamanho;  
};

// funcao que calcula o tamanho da aresta, com base na distancia euclidiana entre dois pontos.
double distanciaEuclidiana(Ponto* pon1, Ponto* pon2)
{
    int dimensoes = retornaQtdDimensao(pon1);
    double sum=0;
    
    for(int i=0;i<dimensoes;i++)
    {
        sum+= pow(retornaValorPos(pon1, i)-retornaValorPos(pon2,i),2);
    }
    return sqrt(sum);
}

// cria uma Aresta e calcula o valor da distancia na hora de criacao.
Aresta *montaArestaSVal(Ponto* pon1, Ponto* pon2)
{   
    Aresta *newAresta = malloc(sizeof(Aresta));
    newAresta->tamanho = distanciaEuclidiana(pon1,pon2);
    newAresta->p1 = pon1;
    newAresta->p2 = pon2;
    

    return newAresta;
}

// cria uma Aresta ja com distancia calculada.
Aresta *montaAresta(Ponto* pon1, Ponto* pon2, double distancia)
{   
    Aresta *newAresta = malloc(sizeof(Aresta));
    newAresta->tamanho = distancia;
    newAresta->p1 = pon1;
    newAresta->p2 = pon2;
    
    return newAresta;
}

// getter ponto1 da aresta
Ponto *retornaP1(Aresta *ar)
{
    return ar->p1;
}
// getter ponto2 da aresta
Ponto *retornaP2(Aresta *ar)
{
    return ar->p2;
}

// getter tamanho(peso) da aresta.
double retornaTamanhoAresta(Aresta *ar)
{
    return ar->tamanho;
}
// free da aresta (como os pontos dentro sao ponteiros pra pontos ja alocados
//, nao precisa desalocar, nem foram alocados)
void liberaAresta(Aresta *arest)
{
    if(arest)
    {
        free(arest);
        arest = NULL;
    }
}

void liberaArestas(Aresta **arrArestas, int qtdArestas)
{
    if(arrArestas)
    {
        for(int i=0;i<qtdArestas;i++)
        {
            liberaAresta(arrArestas[i]);
        }
        free(arrArestas);
        arrArestas = NULL;
    }
}

// constroi uma array de doubles com a distancia de todos os pontos, usado
// para o tamanho das arestas.
double *arrayDistancia(Ponto ** pontos, int qtdPontos)
{

    int tamArrAux = (((qtdPontos*qtdPontos)-qtdPontos)/2);

    double *newArray = malloc(sizeof(double) * tamArrAux);
    int indArr = 0;
    for(int i=0;i<qtdPontos;i++)
    {
        // estou alocando "desnecessarias" porem vou ver se consigo mudar.
        // enquanto j<= i?
        for(int j=0;j<qtdPontos;j++)
        {
            // naoz calcula desnecessarias, ou seja, distancias repetidas ou distancia entre o proprio ponto.
            if(j>=i)
            {
                break;
            }
            else
            {
                newArray[indArr] = distanciaEuclidiana(pontos[j],pontos[i]);
                indArr++;
            }
            
            //printf("%.2f ,", newMatrix[i][j]);
        }
    }
    return newArray;
}

// imprime todas as distancias na saida padrao. usada principalmente para debug
void imprimeArrayDistancia(double * pontos, int qtdPontos)
{
    int indArr = 0;
    for(int i=0;i<qtdPontos;i++)
    {
        for(int j=0;j<qtdPontos;j++)
        {
            // naoz calcula desnecessarias, ou seja, distancias repetidas ou distancia entre o proprio ponto.
            if(j>=i)
            {
                break;
            }
            else
            {
                printf("%.2f, ", pontos[indArr]);
                indArr++;
            }
        }
        printf("\n");
    }
}


//precisa disso? eh so uma array..
void liberaArrayDistancia(double *pontos)
{
    free(pontos);
}

// funcao utilizada principalmente pra debug.
void imprimeAresta(Aresta *arestaA)
{
    printf("%s, %.2lf  -", retornaNome(arestaA->p1) ,arestaA->tamanho);
}

// funcao usada para ordenar Arestas no qsort.
int compAresta(const void *a, const void *b)
{
    const Aresta *aresta1 = *(const Aresta**) a;
    const Aresta *aresta2 = *(const Aresta**) b;


    return (aresta1->tamanho > aresta2->tamanho) - (aresta1->tamanho < aresta2->tamanho);
}

// funcao do qsort que ordena as Arestas.
void ordenaAresta(Aresta **arestas, int qtdArestas)
{
    qsort(arestas,qtdArestas,sizeof(Aresta*),compAresta);
}

// qsort para comparar doubles, para ordenar o array de distancias.
int comp(const void *a, const void *b) 
{
    return (*(double*)a >= *(double*)b) ? 1 : -1;
}
