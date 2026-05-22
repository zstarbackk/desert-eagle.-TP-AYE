#ifndef LISTADOBLECIRCULAR_H_INCLUDED
#define LISTADOBLECIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Proyecto/Errores.h"

#define MINIMO(X, Y) ((X) <= (Y) ? (X) : (Y))

typedef struct tnodo
{
    void* info;
    unsigned tamInfo;
    struct tnodo* sig;
    struct tnodo* ant;
} tNodoListaDC;

typedef tNodoListaDC* tListaDC;

void crearListaDC(tListaDC* pl);

int insertarAlFinalDC(tListaDC *pl,const void *d,unsigned tamInfo);
void vaciarListaDC(tListaDC *pl);

#endif // LISTADOBLEF_H_INCLUDED
