#include <unistd.h>
#include <time.h> // temp!
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*

- Em que arquivos vou modularizar? Separar no que as funcionalidades?
: main, leitura, TAD (ponto, um pra cada), calcular distancias, talvez matriz.

1- pegar inputs dos arquivos
2- armazenar os dados em estruturas corretas e eficientes.
3- junta-las (estruturas? union-find?) calculando distancia (talvez precise separar esse em outros.) < suporte a multidimensionalidade



*/

int main(int argc, char **argv)
{

    if(argc<4) // se nao tiver argumentos < opcional, to botando só pra ficar bonitinho
    {
        return 0;
    }

    FILE *fileProg = fopen(argv[1], "r"); // argc[1] eh o nome do arquivo de entrada.
    if(!fileProg) // se o arquivo nao for encontrado. << necessario? acho q n.
    {
        printf("arq nao encontrado\n");
        return 1;
    }

    /*
    Em loop (cada linha):
        Nome do ponto
        ,posicao (xdimensao) 
        \n

    */

    // getline e strtok recomendadas para ler linhas.

    int res = 0;
    while(!feof(fileProg) || fileProg) // << ?? faz algo?
    {


        if(feof(fileProg))
        {
            break;
        }

        char *buffer = NULL;
        size_t bufsize = 0;
        size_t characters = 0;

        characters = getline(&buffer,&bufsize,fileProg);
        //printf("You typed: '%s'\n",buffer);



        char* token = strtok(buffer, ",");
        while (token != NULL) 
        {
            printf(" %s\n", token);
            token = strtok(NULL, ",");
        }

        if(feof(fileProg))
        {
            break;
        }



        // acima eh copia pra aprender apenas como fazer.
        
        /*char * strLinhaArq = NULL; // nao alocada por enquanto
        size_t sizeAllocated = 0;
        res = getline(&strLinhaArq,&sizeAllocated,fileProg);
        if(res = -1) // possivel de remover.
        {
            break;
        }
        printf("%s.", strLinhaArq);
        */
        // ler nome do ponto.
        // ler ponto(s) com virgula na frente
        
        // bota valores nos pontos (talvez agora)

        // (talvez) checa se eh EOF

        // 2- inicializar. TAD.
    


        
        
    } 


    fclose(fileProg);

    return 0;
}