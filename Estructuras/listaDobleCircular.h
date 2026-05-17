#ifndef LISTADOBLECIRCULAR_H_INCLUDED
#define LISTADOBLECIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Errores.h"

#define MINIMO(X, Y) ((X) <= (Y) ? (X) : (Y))

typedef struct tnodo
{
    void* info;
    unsigned tamInfo;
    struct tnodo* sig;
    struct tnodo* ant;
} tNodo;

typedef tNodo* tListaD;

void crearLista(tListaD* pl);

int insertarOrdenado(
    tListaD* pl,
    const void* info,
    unsigned tamInfo,
    int (*cmp)(const void*, const void*),
    int duplicados,
    void (*accion)(void*, const void*)
);

int eliminarNodoPorClaveOrdenado(
    tListaD* pl,
    void* info,
    unsigned tamInfo,
    int (*cmp)(const void*, const void*)
);

#endif // LISTADOBLEF_H_INCLUDED
