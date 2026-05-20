#include "colaCircular.h"
#include <string.h>

void crearCola(tCola* c)
{
    *c = NULL;
}

int encolar(tCola* c, const void* info, unsigned tamInfo)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));

    if(!nue)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);

    if(!nue->info)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;

    if(!*c)
    {
        nue->sig = nue;
        *c = nue;
        return EXITO;
    }

    nue->sig = (*c)->sig;
    (*c)->sig = nue;
    *c = nue;

    return EXITO;
}

int desencolar(tCola* c, void* info, unsigned tamBuffer)
{
    tNodo* elim;

    if(!*c)
        return COLA_VACIA;

    elim = (*c)->sig;

    memcpy(info, elim->info, MINIMO(elim->tamInfo, tamBuffer));

    if(elim == *c)
        *c = NULL;
    else
        (*c)->sig = elim->sig;

    free(elim->info);
    free(elim);

    return EXITO;
}

int colaLlena(const tCola* c, unsigned tamInfo)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tamInfo);

    free(nue);
    free(info);

    return !nue || !info;
}

int colaVacia(const tCola* c)
{
    return *c == NULL;
}

void vaciarCola(tCola* c)
{
    tNodo* elim;

    if(!*c)
        return;

    while((*c)->sig != *c)
    {
        elim = (*c)->sig;
        (*c)->sig = elim->sig;

        free(elim->info);
        free(elim);
    }

    free((*c)->info);
    free(*c);
    *c = NULL;
}

int verPrimero(const tCola* c, void* info, unsigned tamBuffer)
{
    tNodo* pri;

    if(!*c)
        return COLA_VACIA;

    pri = (*c)->sig;
    memcpy(info, pri->info, MINIMO(pri->tamInfo, tamBuffer));

    return EXITO;
}

