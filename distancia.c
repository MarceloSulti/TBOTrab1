#include "distancia.h"



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


// por enquanto aloca ela toda, ineficiente.
double **matrixDistancia(Ponto ** pontos, int qtdPontos)
{

    int tamArrAux = (((qtdPontos*qtdPontos)-qtdPontos)/2);

    double **newMatrix = malloc(sizeof(double*) * qtdPontos);
    for(int i=0;i<qtdPontos;i++)
    {
        // estou alocando "desnecessarias" porem vou ver se consigo mudar.
        newMatrix[i] = malloc(sizeof(double) * (i));
        for(int j=0;j<qtdPontos;j++)
        {
            // naoz calcula desnecessarias, ou seja, distancias repetidas ou distancia entre o proprio ponto.
            if(j>=i)
            {
                break;
            }
            else
            {
                newMatrix[i][j] = distanciaEuclidiana(pontos[j],pontos[i]);
            }
            
            //printf("%.2f ,", newMatrix[i][j]);
        }
    }
    return newMatrix;
}

void imprimeMatrixDistancia(double ** pontos, int qtdPontos)
{
    for(int i=0;i<qtdPontos;i++)
    {
        printf("\n");
        for(int j=0;j<qtdPontos;j++)
        {
            // nao imprime 0 (pq eh distancia do ponto a ele mesmo) nem -1 (que sao numeros repetidos da matriz, que eh espelhada)
            if(pontos[i][j]>0)
            {
                 printf("%.2lf, ", pontos[i][j]);
            }
            else
            {
                printf("----, ");
            }
        }
    }
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



// ineficiente, sem if j>=i. ademais, ver pq nao deu certo. (provavelmente arrAux tamanho)
void meusortmatrix(double **arr, int qtdPontos)
{
    int tamArrAux = (((qtdPontos*qtdPontos)));
    double *arrAux = malloc(sizeof(double) * tamArrAux);
    //flatten
    for (int i = 0; i < qtdPontos; i++) 
    {
        for (int j = 0; j < qtdPontos; j++) 
        {
            arrAux[(i*qtdPontos)+(j)] = arr[i][j];
        }
    }
    
    qsort(arrAux,tamArrAux,sizeof(double),comp);

    //unflatten
    for (int i = 0; i < qtdPontos; i++) 
    {
        for (int j = 0; j < qtdPontos; j++) 
        {
            arr[i][j] = arrAux[(i*qtdPontos)+(j)];             
        }
    }
}



void liberaMatriz(double ** matrix, int qtdPontos)
{
    for(int i=0;i<qtdPontos;i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}