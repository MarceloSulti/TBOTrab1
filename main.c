
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ponto.h"
#include "distancia.h"
#include "kruskal.h"
/*

- Em que arquivos vou modularizar? Separar no que as funcionalidades?
: main, leitura, TAD (ponto, um pra cada), calcular distancias, talvez matriz.

1- pegar inputs dos arquivos
2- armazenar os dados em estruturas corretas e eficientes.
3- junta-las (estruturas? union-find?) 
4- calculando distancia (talvez precise separar esse em outros.) < suporte a multidimensionalidade, distancia euclidiana


'''''
Conceitos a ler: 

- MST (Minimum SPanning Tree)
- Distancia euclidiana
- Cluster (ambos artigos linkados)
- Ler do agrupamento de espacamento maximo
-  estrutura de dados disjoint-set, union-find vista em sala. adaptar a versao mais eficiente do algoritmo e usala no trabalho
- algoritmo de kruskal preicsa ser ordenada, usar qsort pra isso. 
- RELER ATENTAMENTE TODOS OS LABS ATE AGORA.

Problemas: 
- (2.2) Matriz Y vai ser armazenada como? oq eh? 




(Coisas a armazenar no trabalho)
- Pontos
- Distancias (Recomendado Matriz)
- Arvore
- Grupos/Componente Conexa

DECIDIR:

1- como armazenar os pontos. 
2- Como armazenar as distancias. 
3- Como armazenar a arvore. 
4- Como armazenar os grupos/componente conexa.

!!! Na main, pegar a quantia de pontos apos nome (pela string) e usar isso pra malloc a quantia exata de dimensoes pros pontos. 

!!! Prof disse que pode tanto usar uma funcao dentro do Kruskal pra imprimir as saidas quanto pegar e imprimir as saidas
    na main. 

!!! Ver se eu consigo em vez de dar realloc pra cada novo valor do ponto, eu consigo depois do Nome ler quantos
    valores um ponto tem e dar malloc nesse tamanho. (ver se eh mais eficiente)

!!! Realloc pode ser 1.2 ou 1.5 a mais ou algo do tipo, e depois dar um ultimo realloc com o tamanho.abort

!! Converter para array a matriz, extremamente mais eficiente, ja que teria que ficar transformando em array 
   de qualquer jeito.

!!! ORDENAR OS VERTICES JUNTO! Guardar a posição deles em vez de ficar iterando 3000x com ordem N

FIZ:

1- Li valores (+/- eficiente o suficiente acho)
2- Coloquei em array (acho que eficiente o suficiente)
3- Matriz de distancias (sem os ineficientes, j>= i, que sao repetidos ou distancia do ponto com ele mesmo.)
3.5- ordenei, mas nao terminei o kruskal nem to usando a ordenacao. 

FAZER: 
    4- Union Find logica completa com base no codigo (pegar o eficiente QUE TA NO SLIDE!)
    4.5? - Ordenar matriz de distancias (para pegar pesos pro kruskal) < tem q ser matriz? < nao! usar array pq eh melhor
    5- Arvore geradora minima (Kruskal?)
    6- Remover  arestas k-1 pra deixar componentes (ver como remover do union find) << nao eh so nao juntar elas? fazer em vez de n-1 n-(k-1)/n-k?

    FAZER update:
    - Converter matrizes pra arrays (conveniente), incluindo todas funcoes. (funcao Ordenar deixa de existir? ja q eh um wrapper
    pra qsort)
    --
    - Implementar um dos Union-Finds nos slides (nao precisa de struct,,,)
    - Implementar o Kruskal mesmo (MST)
    - Na hora do union find, pegar arestas levando em consideracao k (nao adiciona as k ultimas etc etc)
    - cuidar da saida
    - ver se modularizo mais?
    --
    - make
    - analise

 -1 - saida (para um arquivo que eh o 3 argumento do codigo)
    - modularizar isso mais ainda. kruskal pode ser um so?
 final - make
 final - apresentacao, analise (um dia so pra isso e talvez make)
*/

int main(int argc, char **argv)
{








    printf("\na\n\n");
    if(argc<4) // se nao tiver argumentos < opcional, to botando só pra ficar bonitinho
    {
        return 0;
    }

    FILE *fileProg = fopen(argv[1], "r"); // argc[1] eh o nome do arquivo de entrada.
    if(!fileProg) // se o arquivo nao for encontrado. << nao eh necessario pq o professor falou que sempre seguira aquele padrao estritamente, mas bom ne
    {
        printf("arq nao encontrado\n");
        return 1;
    }
    //usar size_t? < sim, getline pede.


    int kGrupos = atoi(argv[2]);
    // por enquanto aonde armazeno todos pontos.
    Ponto ** arrPonto = NULL;
    int qtdPontos = 0;
    int qtdMalloc = 0;
    //lendo os pontos do arquivo.
    while(!feof(fileProg)) // << enquanto nao acabar o arquivo
    {

        char *buffer = NULL;
        size_t bufferSize = 0;
        int resultGetline = 0;

        resultGetline = getline(&buffer,&bufferSize,fileProg);
        if(resultGetline != -1)
        {
            char* token = strtok(buffer, ",");
            qtdPontos++;
            //realloc tamanho a mais pra ser eficiente. / comparar eficiencia disso e do N
            if(qtdPontos >= qtdMalloc)
            {
                qtdMalloc = qtdPontos * 1.5;
                arrPonto = realloc(arrPonto, sizeof(Ponto*) * qtdMalloc);
            }
            
            Ponto * ponew = criaPontoNome(token);
            arrPonto[qtdPontos-1] = ponew;
            token = strtok(NULL, ",");
            while (token != NULL) 
            {
                ponew = addValor(ponew, atof(token));
                token = strtok(NULL, ",");
            }
            
        }
        free(buffer);
        
    } 
    // precisa? deve ajudar pra caso o programa esteja usando mt memoria que nao use 
    // desnecessariamente alocando pontos nao utilizados.
    arrPonto = realloc(arrPonto, sizeof(Ponto*) * qtdPontos);
    fclose(fileProg);
    double * arrDis= arrayDistancia(arrPonto,qtdPontos);
    int posId[qtdPontos];
    for(int i=0;i<qtdPontos;i++)
    {
        posId[i] = i;
    }

    

    printf("\n");
    
    //imprimeArrayDistancia(arrDis, qtdPontos);
    printf("\n\n");

    // qtd de arestas.
    int tamArrAux = (((qtdPontos*qtdPontos)-qtdPontos)/2);

    Aresta **arrAresta = malloc(sizeof(Aresta*) * tamArrAux);
    int auxArrAresta = 0;
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
                arrAresta[auxArrAresta] = montaArestaSVal(arrPonto[i],arrPonto[j]);
                auxArrAresta++;
            }
        }
    }

    qsort(arrDis,tamArrAux,sizeof(double),comp);

    printf("\n");
    //imprimeArrayDistancia(arrDis, qtdPontos);

    printf("\n");

    // ordena as arestas
    ordenaAresta(arrAresta, tamArrAux);

    int resInt = 0;
    double resDouble = 0;


    printf("\nkruskaltest\n");

    algoritmo_kruskal(arrPonto, qtdPontos,
                             arrAresta, tamArrAux,
                             &resInt, &resDouble);

    auxArrAresta = 0;
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
                liberaAresta(arrAresta[auxArrAresta]);
                auxArrAresta++;
            }
        }
    }
    free(arrAresta);

    liberaPontos(arrPonto,qtdPontos);
    
    free(arrDis);

    // deve ta errado, mas ta aqui so pra manter no lugar por enquanto.
    /*FILE *fileOutput = fopen(argv[3], "w+"); // argc[1] eh o nome do arquivo de entrada.
    if(!fileOutput) // se o arquivo nao for encontrado. << necessario? acho q n.
    {

    }
    else
    {
        // inserir aqui coisas pro output do arquivo.



        fclose(fileOutput);
    }*/

    return 0;
}