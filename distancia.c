#include "distancia.h"

// fiz com *p1 em vez de **p1, pra desalocar pode dar ruim? talvez nao pq aloquei
struct Aresta
{
    Ponto *p1;
    Ponto *p2;
    double tamanho;  
};

double distanciaEuclidiana(Ponto* pon1, Ponto* pon2)
{
    int dimensoes = retornaQtdDimensao(pon1);
    double sum=0;
    
    for(int i=0;i<dimensoes;i++)
    {
        sum+= pow(retornaValorPos(pon1, i)-retornaValorPos(pon2,i),2);
    }
    return sqrt(sum);
    // depois, faz a raiz disso. pra pegar a distancia. (result)
}


Aresta *montaArestaSVal(Ponto* pon1, Ponto* pon2)
{   
    Aresta *newAresta = malloc(sizeof(Aresta));
    newAresta->tamanho = distanciaEuclidiana(pon1,pon2);
    newAresta->p1 = pon1;
    newAresta->p2 = pon2;
    

    return newAresta;
}

Aresta *montaAresta(Ponto* pon1, Ponto* pon2, double distancia)
{   
    Aresta *newAresta = malloc(sizeof(Aresta));
    newAresta->tamanho = distancia;
    newAresta->p1 = pon1;
    newAresta->p2 = pon2;
    
    return newAresta;
}

Ponto *retornaP1(Aresta *ar)
{
    return ar->p1;
}

Ponto *retornaP2(Aresta *ar)
{
    return ar->p2;
}

double retornaTamanhoAresta(Aresta *ar)
{
    return ar->tamanho;
}

void liberaAresta(Aresta *arest)
{
    if(arest)
    {
        free(arest);
        arest = NULL;
    }
}

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


void imprimeArrayDistancia(double * pontos, int qtdPontos)
{
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
                printf("%.2f, ", pontos[indArr]);
                indArr++;
            }
            
            //printf("%.2f ,", newMatrix[i][j]);
        }
        printf("\n");
    }
}


//precisa disso? eh so uma array..
void liberaArrayDistancia(double *pontos)
{
    free(pontos);
}

//////

void imprimeAresta(Aresta *arestaA)
{
    printf("%s, %.2lf  -", retornaNome(arestaA->p1) ,arestaA->tamanho);
}

int compAresta(const void *a, const void *b)
{
    const Aresta *aresta1 = *(const Aresta**) a;
    const Aresta *aresta2 = *(const Aresta**) b;


    return (aresta1->tamanho > aresta2->tamanho) - (aresta1->tamanho < aresta2->tamanho);
}

//
//
//

void ordenaAresta(Aresta **arestas, int qtdArestas)
{
    qsort(arestas,qtdArestas,sizeof(Aresta*),compAresta);
}

int comp(const void *a, const void *b) 
{
    return (*(double*)a >= *(double*)b) ? 1 : -1;
}

// renomear pra sort matriz ou algo do tipo.
void matrizToArr(double** matriz, int qtdPontos)
{
    // tamanho de uma matriz de distancias sem valores repetidos nem distancia entre os proprios pontos.
    int tamArrAux = (((qtdPontos*qtdPontos)-qtdPontos)/2);
    double *arrAux = malloc(sizeof(double) * tamArrAux);
    //"achata" a matriz em um array.
    int indArr = 0;
    for (int i = 0; i < qtdPontos; i++) 
    {
        for (int j = 0; j < qtdPontos; j++) 
        {
            if(j>=i)
            {
                continue;
            }
            arrAux[indArr] = matriz[i][j];
            indArr++;
        }
    }
    //ordena a array que era a matriz.
    qsort(arrAux,tamArrAux,sizeof(double),comp);
    for(int i=0;i<tamArrAux;i++)
    {
        //printf("%lf, ", arrAux[i]);
    }
    //"desachata" o array de volta na matriz, dessa vez ordenado pelo qsort.
    indArr = 0;
    for (int i = 0; i < qtdPontos; i++) 
    {
        for (int j = 0; j < qtdPontos; j++) 
        {
            if(j>=i)
            {
                continue;
            }
            matriz[i][j] = arrAux[indArr];
            indArr++;
        }
    }
    free(arrAux);
}
