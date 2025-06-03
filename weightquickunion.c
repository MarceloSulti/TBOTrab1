#include "weightquickunion.h"


struct UFSet
{
    int *id;
    int *size;
};


void UF_init(int range)
{
    UFSet *newUF = malloc(sizeof(UFSet));
    newUF->id = malloc(sizeof(int) * range);
}



void UF_libera(UFSet *uf)
{
    if(uf)
    {
        free(uf->id);
        free(uf)
        uf = NULL;
    }
}


