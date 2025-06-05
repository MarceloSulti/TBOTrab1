#include "unionfind.h"

// precisa de uma struct so pra isso? n da pra usar o metodo normal?

typedef struct {
	UFSet *parente;
	int rank;
} UFSet;

//remover lol



//copiado do prof
void UF_init(int size) 
{
    static int N = size;
    for (int i = 0; i < N; i++) 
    {
        id[i] = i; // Cada objeto comeca na sua propria componente.
    } // N acessos ao array.
}



int UF_find(int *id,int i) 
{
    while (i != id[i]) 
    {
        id[i] = id[id[i]]; // Uma unica linha de codigo adicional.
        i = id[i]; // Cada passo agora requer 5 acessos.
    }
    return i;
}

/*int UF_find(int *id,int i) 
{
    while (i != id[i]) 
    {

        i = id[i]; // Buscar o pai ate a raiz.
    }
    return i; // Profundidade de i acessos.
}*/


void UF_union(int p, int q) 
{
    int i = UF_find(p); // Modifique raiz de p para a raiz de q.
    int j = UF_find(q); // Profundidade de p+q acessos.
    id[i] = j;
}


//weighted
void UF_union(int p, int q) 
{
    int i = UF_find(p); // Pendure a arvore menor sob a maior.
    int j = UF_find(q); // Profundidade de ? acessos.
    if (i == j) return;
    if (sz[i] < sz[j]) 
    { 
        id[i] = j; sz[j] += sz[i]; 
    }
    else 
    {
         id[j] = i; sz[i] += sz[j]; 
    }

}