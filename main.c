
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ponto.h"
#include "distancia.h"
#include "kruskal.h"
/*

Conceitos a ler: 

- MST (Minimum SPanning Tree)
- Distancia euclidiana
- Cluster (ambos artigos linkados)
- Ler do agrupamento de espacamento maximo
-  estrutura de dados disjoint-set, union-find vista em sala. adaptar a versao mais eficiente do algoritmo e usala no trabalho
- algoritmo de kruskal preicsa ser ordenada, usar qsort pra isso. 
- RELER ATENTAMENTE TODOS OS LABS ATE AGORA.


(Coisas a armazenar no trabalho)
- Pontos
- Distancias (Recomendado Matriz) << porra nenhuma kkkkk
- Arvore
- Grupos/Componente Conexa



!!! Prof disse que pode tanto usar uma funcao dentro do Kruskal pra imprimir as saidas quanto pegar e imprimir as saidas
    na main. 

!!! Na main, pegar a quantia de pontos apos nome (pela string) e usar isso pra malloc a quantia exata de dimensoes pros pontos. 
!!! Ver se eu consigo em vez de dar realloc pra cada novo valor do ponto, eu consigo depois do Nome ler quantos
    valores um ponto tem e dar malloc nesse tamanho. (ver se eh mais eficiente) << acho q n afetaria mt a performance

!!! ORDENAR OS VERTICES JUNTO! Guardar a posição deles em vez de ficar iterando 3000x com ordem N

FIZ:

1- Li valores (+/- eficiente o suficiente acho)
2- Coloquei em array (acho que eficiente o suficiente)
3- Matriz de distancias (sem os ineficientes, j>= i, que sao repetidos ou distancia do ponto com ele mesmo.)
3.5- ordenei, mas nao terminei o kruskal nem to usando a ordenacao. 

FAZER: 

    - cuidar da saida
    - ver se modularizo mais?
    --
    - make
    - analise

 -1 - saida (para um arquivo que eh o 3 argumento do codigo)

 final - make
 final - apresentacao, analise (um dia so pra isso e talvez make)
*/

int main(int argc, char **argv)
{

    if(argc<4) // se nao tiver argumentos < opcional, to botando só pra ficar bonitinho
    {
        printf("Muitos poucos argumentos na execucao do programa. Sao necessarios 3 argumentos.\n");
        return 1;
    }
    // "fileProg" (argv[1]) eh o arquivo do qual todos os pontos serao lidos. Nao ha checagem alguma de formatacao nem erros porque o professor disse que
    //      os arquivos de teste sempre seguirao o padrao, entao nao precisa fazer programacao defensiva.



    FILE *fileProg = fopen(argv[1], "r");

    if(!fileProg) // se o arquivo nao for encontrado. << nao eh necessario pq o professor falou que sempre seguira aquele padrao estritamente, 
    //mas vai ver o prof digita errado o nome do arquivo?
    {
        printf("Arquivo \"%s\" nao encontrado, finalizando programa.\n", argv[1]);
        return 1;
    }
    // "kGrupos" (argv[2]) eh a quantia de arvores que o Kruskal ira retornar.
    int kGrupos = atoi(argv[2]);


    // Aonde todos os pontos serao armazenados.
    Ponto ** arrPonto = NULL;
    // "qtdMalloc" eh para realloc em incrementos de 150% em 150%.
    int qtdPontos = 0;
    int qtdMalloc = 0;

    //comentario
    printf("iniciando getline\n");

    // Lendo
    while(!feof(fileProg)) // << enquanto nao acabar o arquivo
    {

        char *buffer = NULL;
        // usando size_t pq o getline pede
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

    //comentario
    printf("getline finalizado.\n");
    arrPonto = realloc(arrPonto, sizeof(Ponto*) * qtdPontos);

    // tudo do arquivo lido, nao sera mais usado.
    fclose(fileProg);

    //comentario
    printf("iniciando array de arestas.\n");

    // Quantidade de Arestas entre todos os pontos, sem incluir arestas entre o proprio ponto (j==i) e arestas repetidas (j>1).
    int qtdArestas = (((qtdPontos*qtdPontos)-qtdPontos)/2);
    

    // Array onde serao armazenadas todas as Arestas. << TODO: possivelmente mover pra uma funcao isso?
    Aresta **arrAresta = malloc(sizeof(Aresta*) * qtdArestas);

    // Usado para indexar a atual posicao no array.
    int auxArrAresta = 0;

    // Loop para montar as Arestas, novamente sem incluir arestas entre o proprio ponto (j==i) e arestas repetidas (j>1).
    for(int i=0;i<qtdPontos;i++)
    {
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


    //comentario
    printf("agora qsort na array de arestas.\n");

    // Ordena as arestas em ordem crescente de tamanho, necessario para o Kruskal.
    ordenaAresta(arrAresta, qtdArestas);

    //comentario
    printf("agora teste kruskal\n");


    UFSet *ufset = UF_init(qtdPontos);
    
    // tamanho total da MST
    double resultDouble = 0;
    // quantidade de arestas da MST, remover?
    int resultInt = 0;
    

    algoritmo_kruskal(arrPonto, qtdPontos, arrAresta, qtdArestas, &resultInt,
    &resultDouble, kGrupos);



    
    

    FILE *fileOutput = fopen(argv[3], "w+"); // argc[1] eh o nome do arquivo de entrada.
    if(!fileOutput) // se o arquivo nao for encontrado. << necessario? acho q n.
    {
        //comentario
        printf("Arquivo de saida nao encontrado.\n");
    }
    else
    {
        // inserir aqui coisas pro output do arquivo.



        fclose(fileOutput);
    }

    UF_free(ufset);

    liberaArestas(arrAresta, qtdArestas);

    liberaPontos(arrPonto,qtdPontos);
        
    return 0;
}