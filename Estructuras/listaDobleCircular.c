#include "listaDobleCircular.h"


void crearLista(tListaD* pl)
{
    *pl = NULL;
}

int insertarOrdenado(
    tListaD* pl,
    const void* info,
    unsigned tamInfo,
    int (*cmp)(const void*, const void*),
    int duplicados,
    void (*accion)(void*, const void*)
)
{
    tNodo *nue, *actual, *auxAnt, *auxSig;

    if(*pl)
    {
        actual = *pl;

        while(actual->sig && cmp(info, actual->info) > 0)
            actual = actual->sig;

        while(actual->ant && cmp(info, actual->info) < 0)
            actual = actual->ant;

        if(cmp(info, actual->info) > 0)
        {
            auxAnt = actual;
            auxSig = actual->sig;
        }
        else
        {
            auxAnt = actual->ant;
            auxSig = actual;
        }

        if(cmp(info, actual->info) == 0 && !duplicados)
        {
            accion(actual->info, info);
            return EXITO;
        }
    }
    else
    {
        auxAnt = NULL;
        auxSig = NULL;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));

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
    nue->ant = auxAnt;
    nue->sig = auxSig;

    if(auxAnt)
        auxAnt->sig = nue;

    if(auxSig)
        auxSig->ant = nue;

    *pl = nue;

    return EXITO;
}

int eliminarNodoPorClaveOrdenado(
    tListaD* pl,
    void* info,
    unsigned tamInfo,
    int (*cmp)(const void*, const void*)
)
{
    tNodo *elim, *actual, *auxSig, *auxAnt;

    if(!*pl)
        return 0;

    actual = *pl;

    while(actual->sig && cmp(info, actual->info) > 0)
        actual = actual->sig;

    while(actual->ant && cmp(info, actual->info) < 0)
        actual = actual->ant;

    if(cmp(info, actual->info) != 0)
        return 0;

    elim = actual;

    auxSig = actual->sig;
    auxAnt = actual->ant;

    if(auxAnt)
        auxAnt->sig = auxSig;

    if(auxSig)
        auxSig->ant = auxAnt;

    memcpy(info, elim->info, MINIMO(tamInfo, elim->tamInfo));

    free(elim->info);
    free(elim);

    if(auxAnt)
        *pl = auxAnt;
    else if(auxSig)
        *pl = auxSig;
    else
        *pl = NULL;

    return EXITO;
}
