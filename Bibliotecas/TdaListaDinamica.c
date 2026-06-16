#include "TdaListaDinamica.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Proyecto/Errores.h"
#define MINIMO( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )


void crearLista(tLista* pl)
{
    *pl = NULL;
}

int listaLlena(const tLista* pl, unsigned tamInfo)
{
    return 0;
}

int listaVacia(const tLista* pl)
{
    return *pl == NULL;
}

int insertarAlFinal(tLista* pl, const void* info, unsigned tamInfo)
{
    tNodoL* nue;

    nue = malloc(sizeof(tNodoL));
    if(nue == NULL)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;
    nue->sig = NULL;

    while(*pl)
        pl = &(*pl)->sig;

    *pl = nue;

    return EXITO;
}

void vaciarLista(tLista* pl)
{
    tNodoL* elim;

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }
}

int mapLista(tLista* pl,
             int (*accion)(void* dato, unsigned tamDato, void* ctx),
             void* ctx)
{
    if(!pl || !accion)
        return ERROR;

    while(*pl)
    {
        if(accion((*pl)->info, (*pl)->tamInfo, ctx) != EXITO)
            return ERROR;

        pl =&(*pl)->sig;
    }
    return EXITO;
}


int insertarOrdenado(tLista* pl, const void* info, unsigned tamInfo,
                     int (*cmp)(const void*, const void*),
                     void (*accion)(void*, const void*))
{
    tNodoL* nue;

    while(*pl && cmp(info, (*pl)->info) > 0)
        pl = &(*pl)->sig;

    if(*pl && cmp(info, (*pl)->info) == 0)
    {
        if(accion)
            accion((*pl)->info, info);

        return EXITO;
    }

    nue = malloc(sizeof(tNodoL));
    if(nue == NULL)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;

    nue->sig = *pl;
    *pl = nue;

    return EXITO;
}

int insertarOrdenadoAdelante(tLista* pl, const void* info, unsigned tamInfo,
                             int (*cmp)(const void*, const void*), int duplicados,
                             void (*accion)(void*, const void*))
{
    tNodoL* nue;

    while(*pl && cmp(info, (*pl)->info) > 0)
        pl = &(*pl)->sig;

    if(*pl && cmp(info, (*pl)->info) == 0 && !duplicados)
    {
        accion((*pl)->info, info);
        return EXITO;
    }

    nue = malloc(sizeof(tNodoL));
    if(nue == NULL)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;

    nue->sig = *pl;
    *pl = nue;

    return EXITO;
}

int insertarOrdenadoAtras(tLista* pl, const void* info, unsigned tamInfo,
                          int (*cmp)(const void*, const void*), int duplicados,
                          void (*accion)(void*, const void*))
{
    tNodoL* nue;

    while(*pl && cmp(info, (*pl)->info) > 0)
        pl = &(*pl)->sig;

    if(*pl && cmp(info, (*pl)->info) == 0 && !duplicados)
    {
        if(accion)
            accion((*pl)->info, info);

        return EXITO;
    }

     if(duplicados)
    {
        while(*pl && cmp(info, (*pl)->info) == 0)
            pl = &(*pl)->sig;
    }

    nue = malloc(sizeof(tNodoL));
    if(nue == NULL)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;

    nue->sig = *pl;
    *pl = nue;

    return EXITO;
}

int eliminarNodoPrimerApEnListaOrdenada(tLista* pl, void* info, unsigned tamBuffer,
                                        int (*cmp)(const void*, const void*))
{
    tNodoL* elim;

    while(*pl && cmp(info, (*pl)->info) > 0)
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return DATO_NO_ENCONTRADO;

    if(cmp(info, (*pl)->info) < 0)
        return DATO_NO_ENCONTRADO;

    elim = *pl;
    *pl = elim->sig;

    memcpy(info, elim->info, MINIMO(elim->tamInfo, tamBuffer));

    free(elim->info);
    free(elim);

    return EXITO;
}

int eliminarNodoTodasApEnListaOrdenada(tLista* pl, void* info,
                                       int (*cmp)(const void*, const void*))
{
    tNodoL* elim;
    int cant = 0;

    while(*pl && cmp(info, (*pl)->info) > 0)
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return cant;

    if(cmp(info, (*pl)->info) < 0)
        return cant;

    while(*pl && cmp(info, (*pl)->info) == 0)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);

        cant++;
    }

    return cant;
}

int eliminarNodoPrimerApEnListaDesordenada(tLista* pl, void* info, unsigned tamBuffer,
                                           int (*cmp)(const void*, const void*))
{
    tNodoL* elim;

    while(*pl && cmp(info, (*pl)->info) != 0)
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return DATO_NO_ENCONTRADO;

    elim = *pl;
    *pl = elim->sig;

    memcpy(info, elim->info, MINIMO(elim->tamInfo, tamBuffer));

    free(elim->info);
    free(elim);

    return EXITO;
}

int eliminarNodoTodasApEnListaDesordenada(tLista* pl, void* info,
                                          int (*cmp)(const void*, const void*))
{
    tNodoL* elim;
    int cant = 0;

    while(*pl)
    {
        if(cmp(info, (*pl)->info) == 0)
        {
            elim = *pl;
            *pl = elim->sig;

            free(elim->info);
            free(elim);

            cant++;
        }
        else
            pl = &(*pl)->sig;
    }

    return cant;
}

void seleccionSortLista(tLista* pl, int (*cmp)(const void*, const void*))
{
    tNodoL* min;
    tLista* pivote;
    tLista* pmin;
    tLista* rec;

    pivote = pl;

    while(*pivote)
    {
        pmin = pivote;
        rec = &(*pivote)->sig;

        while(*rec)
        {
            if(cmp((*rec)->info, (*pmin)->info) < 0)
                pmin = rec;

            rec = &(*rec)->sig;
        }

        if(pmin != pivote)
        {
            min = *pmin;
            *pmin = min->sig;

            min->sig = *pivote;
            *pivote = min;
        }

        pivote = &(*pivote)->sig;
    }
}

void mostrarLista (const tLista* pl, void(*mostrar)(const void*, unsigned))
{
    unsigned inc=0;
    while(*pl)
    {
        mostrar((*pl)->info, inc);
        inc++;
        pl=&(*pl)->sig;
    }
}

int buscarEnListaPorPosicion(const tLista* pl, int pos, void* res, unsigned cantBytes)
{
    int i = 0;

    if(*pl == NULL)
        return LISTA_VACIA;

    while(*pl && i < pos)
    {
        pl = &(*pl)->sig;
        i++;
    }
    if(*pl==NULL)
        return DATO_NO_ENCONTRADO;

    memcpy(res, (*pl)->info, MINIMO(cantBytes, (*pl)->tamInfo));

    return EXITO;
}

int buscarEnListaPorClave(const tLista* pl,void* datoEncontrado, unsigned tamDato,const void* clave,int (*cmp)(const void* clave, const void* dato))
{
    if(!pl || !clave || !cmp)
        return ERROR;

    while(*pl)
    {
        if(cmp(clave, (*pl)->info) == 0)
        {
            memcpy(datoEncontrado, (*pl)->info, MINIMO((*pl)->tamInfo, tamDato));
            return EXITO;
        }
        pl = &(*pl)->sig;
    }
    return DATO_NO_ENCONTRADO;
}

int modificarEnListaPorClave(tLista* pl,const void* clave,int (*cmp)(const void* clave, const void* dato),void (*accion)(void* dato, void* ctx),
                             void* ctx)
{
    if(!pl || !cmp || !accion)
        return ERROR;

    while(*pl)
    {
        if(cmp(clave, (*pl)->info) == 0)
        {
            accion((*pl)->info, ctx);
            return EXITO;
        }

        pl = &(*pl)->sig;
    }

    return DATO_NO_ENCONTRADO;
}

int sacarPrimeroLista(tLista* pl, void* info, unsigned tamBuffer)
{
    tNodoL* elim;


    if(*pl == NULL)
        return DATO_NO_ENCONTRADO;

    elim = *pl;
    *pl = elim->sig;


    if(info != NULL)
        memcpy(info, elim->info, MINIMO(elim->tamInfo, tamBuffer));


    free(elim->info);
    free(elim);

    return EXITO;
}

