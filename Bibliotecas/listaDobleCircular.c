#include "listaDobleCircular.h"
#include "../Proyecto/Errores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))


void crearListaDC(tListaDC* pl)
{
    *pl = NULL;
}

int insertarAlFinalDC(tListaDC *pl,const void *d,unsigned tamInfo)
{
    tNodoListaDC *nue;

    nue = (tNodoListaDC*)malloc(sizeof(tNodoListaDC));
    if(!nue)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(!nue->info)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, d, tamInfo);
    nue->tamInfo = tamInfo;

    if(!*pl)
    {
        nue->sig = nue;
        nue->ant = nue;
    }
    else
    {
        nue->sig = (*pl)->sig;   // apunta al primero
        nue->ant = *pl;          // apunta al ultimo

        (*pl)->sig->ant = nue;   // el primero ahora apunta atras al nuevo
        (*pl)->sig = nue;        // el ultimo ahora apunta adelante al nuevo
    }

    *pl = nue; // el nuevo pasa a ser el ultimo

    return EXITO;
}

void vaciarListaDC(tListaDC *pl)
{
    tNodoListaDC *elim;

    if(!*pl)
        return;
    while((*pl)->sig !=*pl)
    {
        //pl siempre apunta al ultimo, y siempre elimino en el segundo
        elim=(*pl)->sig;
        (*pl)->sig=elim->sig;
        elim->sig->ant=*pl;

        free(elim->info);
        free(elim);

    }
    free((*pl)->info);
    free(*pl);

    *pl=NULL;

}

int listaVaciaDC(const tListaDC* pl)
{
    return *pl == NULL;
}

tCursorDC obtenerPrimeroDC(const tListaDC* pl)
{
    if(!pl || !*pl)
        return NULL;

    return (*pl)->sig;
}
tCursorDC obtenerUltimoDC(const tListaDC* pl)
{
    if(!pl || !*pl)
        return NULL;

    return *pl;
}

tCursorDC siguienteDC(tCursorDC cursor)
{
    if(!cursor)
        return NULL;

    return cursor->sig;
}
tCursorDC anteriorDC(tCursorDC cursor)
{
    if(!cursor)
        return NULL;

    return cursor->ant;
}

int verActualDC(tCursorDC cursor, void* dato, unsigned tamDato)
{
    if(!cursor || !dato)
        return ERROR;

    memcpy(dato, cursor->info, MINIMO(tamDato, cursor->tamInfo));

    return EXITO;
}

int modificarActualDC(tCursorDC cursor, void (*accion)(void* dato, void* ctx), void* ctx)
{
    if(!cursor || !accion)
        return ERROR;

    accion(cursor->info, ctx);

    return EXITO;
}

int mismoCursorDC(tCursorDC a, tCursorDC b)
{
    return a == b;
}

tCursorDC avanzarNDC(tCursorDC cursor, unsigned n)
{
    while(cursor && n--)
        cursor = cursor->sig;

    return cursor;
}

tCursorDC retrocederNDC(tCursorDC cursor, unsigned n)
{
    while(cursor && n--)
        cursor = cursor->ant;

    return cursor;
}


